// PrinterGuard занимает общий принтер, а busy хранит состояние ресурса
// свой метод Rename меняет имя принтера, не освобождая его.
// при исключении released печатается до error, а IsFree затем даёт true

#include <iostream>
#include <stdexcept>
#include <string>

class PrinterGuard {
 public:
  explicit PrinterGuard(const std::string& name) : name_(name) {
    if (name.empty()) {
      throw std::invalid_argument("empty printer name");
    }
    if (busy) {
      throw std::runtime_error("printer is busy");
    }
    busy = true;
    std::cout << "acquired " << name_ << '\n';
  }

  ~PrinterGuard() {
    busy = false;
    std::cout << "released " << name_ << '\n';
  }

  PrinterGuard(const PrinterGuard&) = delete;
  PrinterGuard& operator=(const PrinterGuard&) = delete;
  PrinterGuard(PrinterGuard&&) = delete;
  PrinterGuard& operator=(PrinterGuard&&) = delete;

  void Use() const {
    if (!busy) {
      throw std::runtime_error("printer is not acquired");
    }
    std::cout << "using " << name_ << '\n';
  }

  void Rename(const std::string& name) {
    if (name.empty()) {
      throw std::invalid_argument("empty printer name");
    }
    name_ = name;
  }

  static bool IsFree() { return !busy; }

 private:
  std::string name_;
  inline static bool busy = false;
};

void PrintState() {
  std::cout << (PrinterGuard::IsFree() ? "free" : "busy") << '\n';
}

int main() {
  {
    PrinterGuard printer("lab-printer");
    printer.Use();
  }
  PrintState();

  try {
    {
      PrinterGuard printer("lab-printer");
      throw std::runtime_error("simulated failure");
    }
  } catch (const std::exception& error) {
    std::cout << "error: " << error.what() << '\n';
  }
  PrintState();

  {
    PrinterGuard printer("lab-printer");
    printer.Rename("course-printer");
    printer.Use();
  }
  PrintState();
  return 0;
}
