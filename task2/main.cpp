#include <cstring>
#include <iostream>

using Operation = void (*)(int&);

void Deposit(int& balance) {
  int amount;
  std::cin >> amount;
  if (amount <= 0) {
    std::cout << "error" << "\n";
    return;
  }
  balance += amount;
}

void Withdraw(int& balance) {
  int amount;
  std::cin >> amount;
  if (amount <= 0 || amount > balance) {
    std::cout << "error" << "\n";
    return;
  }
  balance -= amount;
}

void PrintBalance(int& balance) {
  std::cout << balance << '\n';
}

void Reset(int& balance) {
  balance = 0;
}

void DoubleBalance(int& balance) {
  balance *= 2;
}

int main() {
  const char* command_names[] = {"deposit", "withdraw", "balance", "reset",
                                 "double"};
  Operation operations[] = {Deposit, Withdraw, PrintBalance, Reset,
                            DoubleBalance};
  const int command_count = sizeof(command_names) / sizeof(command_names[0]);

  int balance = 0;
  char command[32];

  while (std::cin >> command) {
    if (std::strcmp(command, "stop") == 0) {
      break;
    }

    int command_index = -1;
    for (int i = 0; i < command_count; ++i) {
      if (std::strcmp(command, command_names[i]) == 0) {
        command_index = i;
        break;
      }
    }

    if (command_index == -1) {
      std::cout << "error\n";
    } else {
      operations[command_index](balance);
    }
  }

  return 0;
}
