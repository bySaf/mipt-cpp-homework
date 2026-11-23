// operator=(const Draft&) использует copy-and-swap - копия + обмен через Swap.
// operator=(Draft&&) использует move-and-swap - перенос во временный + обмен.
// copy a a и move a a сохраняют текст (после обычного move источник пуст)

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

class Draft {
 public:
  Draft() = default;

  ~Draft() { delete[] data_; }

  Draft(const Draft& other) : size_(other.size_), capacity_(other.size_) {
    if (size_ != 0) {
      data_ = new char[capacity_ + 1];
      std::memcpy(data_, other.data_, size_ + 1);
    }
  }

  Draft& operator=(const Draft& other) {
    Draft copy(other);
    Swap(copy);
    return *this;
  }

  Draft(Draft&& other) noexcept { Swap(other); }

  Draft& operator=(Draft&& other) noexcept {
    if (this != &other) {
      Draft moved(std::move(other));
      Swap(moved);
    }
    return *this;
  }

  void Swap(Draft& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  void append(const std::string& text) {
    if (text.empty()) {
      return;
    }
    const std::size_t max_size = std::numeric_limits<std::size_t>::max() - 1;
    if (text.size() > max_size - size_) {
      throw std::length_error("draft is too large");
    }
    std::size_t new_size = size_ + text.size();
    if (new_size > capacity_) {
      std::size_t new_capacity = new_size;
      if (capacity_ <= max_size / 2) {
        new_capacity = std::max(new_size, capacity_ * 2);
      }
      char* new_data = new char[new_capacity + 1];
      if (size_ != 0) {
        std::memcpy(new_data, data_, size_);
      }
      delete[] data_;
      data_ = new_data;
      capacity_ = new_capacity;
    }
    std::memcpy(data_ + size_, text.data(), text.size());
    size_ = new_size;
    data_[size_] = '\0';
  }

  void clear() {
    size_ = 0;
    if (data_ != nullptr) {
      data_[0] = '\0';
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Draft& draft) {
    if (draft.size_ == 0) {
      return out << "(empty)";
    }
    return out.write(draft.data_, static_cast<std::streamsize>(draft.size_));
  }

 private:
  char* data_ = nullptr;
  std::size_t size_ = 0;
  std::size_t capacity_ = 0;
};

std::string ReadText(std::istringstream& input) {
  std::string value;
  if (!(input >> value)) {
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

bool ExecuteCommand(const std::string& line,
                    std::map<std::string, Draft>& drafts, std::ostream& out) {
  std::istringstream input(line);
  std::string command;
  if (!(input >> command)) {
    return true;
  }
  if (command == "quit") {
    CheckEnd(input);
    return false;
  }
  std::string name = ReadText(input);
  if (command == "new") {
    CheckEnd(input);
    drafts[name].clear();
  } else if (command == "append") {
    std::string text = ReadText(input);
    CheckEnd(input);
    drafts.at(name).append(text);
  } else if (command == "copy" || command == "move") {
    std::string source = ReadText(input);
    CheckEnd(input);
    Draft& destination = drafts.at(name);
    Draft& original = drafts.at(source);
    if (command == "copy") {
      destination = original;
    } else {
      destination = std::move(original);
    }
  } else if (command == "show") {
    CheckEnd(input);
    out << drafts.at(name) << '\n';
  } else {
    throw std::runtime_error("unknown command");
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::map<std::string, Draft> drafts;
  std::string line;
  while (std::getline(std::cin, line)) {
    try {
      if (!ExecuteCommand(line, drafts, std::cout)) {
        break;
      }
    } catch (const std::exception&) {
      std::cout << "error\n";
    }
  }
  return 0;
}
