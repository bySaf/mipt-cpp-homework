#include "ServiceCenter.h"

#include <cctype>
#include <string>

#include "Errors.h"
#include "Inventory.h"

void ServiceCenter::Inspect(const InventoryItem& item) const {
  if (!item.IsTransport()) {
    return;
  }

  std::string name = item.Name();

  for (char& letter : name) {
    letter =
        static_cast<char>(std::tolower(static_cast<unsigned char>(letter)));
  }
  // тоже переписывал, так как он вручную сравнивал от a до z
  // ну поч тут нет tolower для строк как в питоне(
  if (name.find("broken") != std::string::npos) {
    throw InspectionError();
  }
}
