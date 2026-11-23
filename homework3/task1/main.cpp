// своя команда best печатает первую запись с макс баллом
// если журнал пуст PrintBest кидает StateError

#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class LabError : public std::exception {
 public:
  explicit LabError(const std::string& message) : message_(message) {}
  const char* what() const noexcept override { return message_.c_str(); }

 private:
  std::string message_;
};

class ParseError : public LabError {
 public:
  using LabError::LabError;
};

class RangeError : public LabError {
 public:
  using LabError::LabError;
};

class StateError : public LabError {
 public:
  using LabError::LabError;
};

struct Record {
  int id;
  int score;
};

int ReadInt(std::istringstream& input) {
  std::string token;
  if (!(input >> token)) {
    throw ParseError("not enough arguments");
  }
  std::istringstream argument(token);
  int value = 0;
  if (!(argument >> value) || !argument.eof()) {
    throw ParseError("invalid integer");
  }
  return value;
}

void CheckEnd(std::istringstream& input) {
  std::string extra;
  if (input >> extra) {
    throw ParseError("too many arguments");
  }
}

void Add(std::vector<Record>& records, int id, int score) {
  if (score < 0 || score > 10) {
    throw RangeError("score out of range");
  }
  records.push_back({id, score});
}

void Undo(std::vector<Record>& records) {
  if (records.empty()) {
    throw StateError("nothing to undo");
  }
  records.pop_back();
}

void Print(const std::vector<Record>& records, std::ostream& out) {
  if (records.empty()) {
    out << "(empty)\n";
    return;
  }
  for (std::size_t i = 0; i < records.size(); ++i) {
    if (i != 0) {
      out << ' ';
    }
    out << records[i].id << ':' << records[i].score;
  }
  out << '\n';
}

void PrintBest(const std::vector<Record>& records, std::ostream& out) {
  if (records.empty()) {
    throw StateError("journal is empty");
  }
  const Record* best = &records.front();
  for (const auto& record : records) {
    if (record.score > best->score) {
      best = &record;
    }
  }
  out << best->id << ':' << best->score << '\n';
}

bool ExecuteCommand(const std::string& line, std::vector<Record>& records,
                    std::ostream& out) {
  std::istringstream input(line);
  std::string command;
  if (!(input >> command)) {
    return true;
  }
  if (command == "add") {
    int id = ReadInt(input);
    int score = ReadInt(input);
    CheckEnd(input);
    Add(records, id, score);
  } else {
    CheckEnd(input);
    if (command == "stop") {
      return false;
    }
    if (command == "undo") {
      Undo(records);
    } else if (command == "list") {
      Print(records, out);
    } else if (command == "best") {
      PrintBest(records, out);
    } else {
      throw ParseError("unknown command");
    }
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::vector<Record> records;
  std::string line;
  while (std::getline(std::cin, line)) {
    try {
      if (!ExecuteCommand(line, records, std::cout)) {
        break;
      }
    } catch (const LabError& error) {
      std::cout << "error: " << error.what() << '\n';
    }
  }
  return 0;
}
