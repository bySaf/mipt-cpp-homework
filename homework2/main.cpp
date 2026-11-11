#include <exception>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>

#include "Commands.h"
#include "Fleet.h"

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout << std::fixed << std::setprecision(1);
  Fleet fleet;
  std::string line;
  while (std::getline(std::cin, line)) {
    try {
      if (!ExecuteCommand(line, fleet, std::cout)) {
        break;
      }
    } catch (const std::exception& error) {
      std::cout << "error: " << error.what() << '\n';
    }
  }
  return 0;
}
