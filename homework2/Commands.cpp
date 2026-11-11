#include "Commands.h"

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

#include "Errors.h"
#include "Fleet.h"
#include "Things.h"
#include "Transport.h"

namespace {

void CheckEnd(std::istringstream& input) {
  std::string extra;
  if (input >> extra) {
    throw CommandError("too many arguments");
  }
}

template <typename T>
T Read(std::istringstream& input) {
  std::string token;
  input >> token;
  std::istringstream argument(token);
  T value;
  if (!(argument >> value) || !argument.eof()) {
    throw CommandError("invalid arguments");
  }
  return value;
}

// тоже подписал, так как он использовал какие-то сложные stl проверки, не
// нужные по тз, переписал
std::string ReadText(std::istringstream& input) {
  std::string value;
  if (!(input >> value)) {
    throw CommandError("invalid arguments");
  }
  return value;
}

std::unique_ptr<InventoryItem> ReadItem(std::istringstream& input) {
  std::string type = ReadText(input);
  std::string id = ReadText(input);
  std::string name = ReadText(input);

  if (type == "scooter" || type == "ebike") {
    double energy = Read<double>(input);
    int score = Read<int>(input);
    CheckEnd(input);
    if (type == "scooter") {
      return std::make_unique<ElectricScooter>(id, name, energy, score);
    }
    return std::make_unique<ElectricBike>(id, name, energy, score);
  }
  if (type == "bike" || type == "skateboard") {
    int score = Read<int>(input);
    CheckEnd(input);
    if (type == "bike") {
      return std::make_unique<Bike>(id, name, score);
    }
    return std::make_unique<Skateboard>(id, name, score);
  }
  if (type == "helmet") {
    CheckEnd(input);
    return std::make_unique<Helmet>(id, name);
  }
  if (type == "dock") {
    double energy = Read<double>(input);
    CheckEnd(input);
    return std::make_unique<Dock>(id, name, energy);
  }
  throw CommandError("unknown item type");
}

}

bool ExecuteCommand(const std::string& line, Fleet& fleet, std::ostream& out) {
  std::istringstream input(line);
  std::string command;
  if (!(input >> command)) {
    return true;
  }

  if (command == "add") {
    fleet.Add(ReadItem(input));
  } else if (command == "remove" || command == "focus") {
    std::string id = ReadText(input);
    CheckEnd(input);
    if (command == "remove") {
      fleet.Remove(id);
    } else {
      fleet.Focus(id);
    }
  } else if (command == "novice_score") {
    int score = Read<int>(input);
    CheckEnd(input);
    fleet.SetNoviceScore(score);
  } else {
    CheckEnd(input);
    if (command == "quit") {
      return false;
    }
    if (command == "energy") {
      out << fleet.Energy() << '\n';
    } else if (command == "report") {
      double energy = fleet.Energy();
      out << "count: " << fleet.Size() << " energy: " << energy << '\n';
    } else if (command == "list") {
      fleet.List(out);
    } else if (command == "novice") {
      fleet.Novice(out);
    } else if (command == "show_focus") {
      fleet.ShowFocus(out);
    } else if (command == "max_energy") {
      fleet.MaxEnergy(out);
    } else {
      throw CommandError("unknown command");
    }
  }
  return true;
}
