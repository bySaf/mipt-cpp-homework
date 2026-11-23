// свой команда filter_priority k оставляет заявки с priority >= k.
// IsCourse — именованный функтор, Filter принимает std::function.
// лямбду задают удаление, сортировку и фильтр с захватом min_priority.

#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct Request {
  int id;
  int course;
  int priority;
};

class IsCourse {
 public:
  explicit IsCourse(int course) : course_(course) {}
  bool operator()(const Request& request) const {
    return request.course == course_;
  }

 private:
  int course_;
};

void Filter(std::vector<Request>& requests,
            const std::function<bool(const Request&)>& predicate) {
  auto should_remove = [&predicate](const Request& request) {
    return !predicate(request);
  };
  std::erase_if(requests, should_remove);
}

void SortPriority(std::vector<Request>& requests) {
  auto higher_priority = [](const Request& left, const Request& right) {
    return left.priority > right.priority;
  };
  std::stable_sort(requests.begin(), requests.end(), higher_priority);
}

void Print(const std::vector<Request>& requests, std::ostream& out) {
  if (requests.empty()) {
    out << "(empty)\n";
    return;
  }
  for (std::size_t i = 0; i < requests.size(); ++i) {
    if (i != 0) {
      out << ' ';
    }
    out << requests[i].id << ':' << requests[i].course << ':'
        << requests[i].priority;
  }
  out << '\n';
}

int ReadInt(std::istringstream& input) {
  std::string token;
  input >> token;
  std::istringstream argument(token);
  int value = 0;
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

bool ExecuteCommand(const std::string& line, std::vector<Request>& requests,
                    std::ostream& out) {
  std::istringstream input(line);
  std::string command;
  if (!(input >> command)) {
    return true;
  }
  if (command == "add") {
    int id = ReadInt(input);
    int course = ReadInt(input);
    int priority = ReadInt(input);
    CheckEnd(input);
    requests.push_back({id, course, priority});
  } else if (command == "filter_course") {
    int course = ReadInt(input);
    CheckEnd(input);
    Filter(requests, IsCourse(course));
  } else if (command == "filter_priority") {
    int min_priority = ReadInt(input);
    CheckEnd(input);
    Filter(requests, [min_priority](const Request& request) {
      return request.priority >= min_priority;
    });
  } else {
    CheckEnd(input);
    if (command == "quit") {
      return false;
    }
    if (command == "print") {
      Print(requests, out);
    } else if (command == "sort_priority") {
      SortPriority(requests);
    } else {
      throw std::runtime_error("unknown command");
    }
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::vector<Request> requests;
  std::string line;
  while (std::getline(std::cin, line)) {
    try {
      if (!ExecuteCommand(line, requests, std::cout)) {
        break;
      }
    } catch (const std::exception&) {
      std::cout << "error\n";
    }
  }
  return 0;
}
