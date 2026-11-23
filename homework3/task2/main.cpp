// Concept PairValue требует вывода в ostream + сравнение на равенство
// Pair<std::vector<int>, int> не компилится т.к у vector нет operator<<
// добавил свой метод Reversed
// команда reverse room/course i печатает такую пару, не меняя журнал.

#include <concepts>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
concept PairValue =
    std::equality_comparable<T> && requires(std::ostream& out, const T& value) {
      { out << value } -> std::same_as<std::ostream&>;
    };

template <PairValue First, PairValue Second>
class Pair {
 public:
  First first;
  Second second;

  Pair(const First& first_value, const Second& second_value)
      : first(first_value), second(second_value) {}

  bool operator==(const Pair& other) const {
    return first == other.first && second == other.second;
  }

  Pair<Second, First> Reversed() const { return {second, first}; }

  friend std::ostream& operator<<(std::ostream& out, const Pair& pair) {
    return out << '(' << pair.first << ", " << pair.second << ')';
  }
};

template <typename T>
T Read(std::istringstream& input) {
  std::string token;
  input >> token;
  std::istringstream argument(token);
  T value{};
  if (!(argument >> value) || !argument.eof()) {
    throw std::runtime_error("invalid arguments");
  }
  return value;
}

void CheckEnd(std::istringstream& input) {
  std::string extra;
  if (input >> extra) {
    throw std::runtime_error("too many arguments");
  }
}

template <typename T>
const T& Get(const std::vector<T>& journal, int index) {
  if (index < 0 || static_cast<std::size_t>(index) >= journal.size()) {
    throw std::runtime_error("invalid index");
  }
  return journal[static_cast<std::size_t>(index)];
}

template <typename T>
void Print(const std::vector<T>& journal, std::ostream& out) {
  for (std::size_t i = 0; i < journal.size(); ++i) {
    if (i != 0) {
      out << ' ';
    }
    out << journal[i];
  }
  out << '\n';
}

template <PairValue First, PairValue Second>
void ExecuteJournalCommand(const std::string& command,
                           std::istringstream& input,
                           std::vector<Pair<First, Second>>& journal,
                           std::ostream& out) {
  if (command == "put") {
    auto first = Read<First>(input);
    auto second = Read<Second>(input);
    CheckEnd(input);
    journal.emplace_back(first, second);
  } else if (command == "print") {
    CheckEnd(input);
    Print(journal, out);
  } else if (command == "eq") {
    int left = Read<int>(input);
    int right = Read<int>(input);
    CheckEnd(input);
    bool equal = Get(journal, left) == Get(journal, right);
    out << (equal ? "equal" : "not equal") << '\n';
  } else if (command == "find") {
    auto first = Read<First>(input);
    CheckEnd(input);
    for (const auto& pair : journal) {
      if (pair.first == first) {
        out << pair << '\n';
        return;
      }
    }
    throw std::runtime_error("not found");
  } else if (command == "reverse") {
    int index = Read<int>(input);
    CheckEnd(input);
    out << Get(journal, index).Reversed() << '\n';
  } else {
    throw std::runtime_error("unknown command");
  }
}

bool ExecuteCommand(const std::string& line,
                    std::vector<Pair<std::string, int>>& rooms,
                    std::vector<Pair<int, std::string>>& courses,
                    std::ostream& out) {
  std::istringstream input(line);
  std::string command;
  if (!(input >> command)) {
    return true;
  }
  if (command == "quit") {
    CheckEnd(input);
    return false;
  }
  auto journal = Read<std::string>(input);
  if (journal == "room") {
    ExecuteJournalCommand(command, input, rooms, out);
  } else if (journal == "course") {
    ExecuteJournalCommand(command, input, courses, out);
  } else {
    throw std::runtime_error("unknown journal");
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::vector<Pair<std::string, int>> rooms;
  std::vector<Pair<int, std::string>> courses;
  std::string line;
  while (std::getline(std::cin, line)) {
    try {
      if (!ExecuteCommand(line, rooms, courses, std::cout)) {
        break;
      }
    } catch (const std::exception&) {
      std::cout << "error\n";
    }
  }
  return 0;
}
