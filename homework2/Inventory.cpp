#include "Inventory.h"

#include <ostream>

#include "Errors.h"

double InventoryItem::DailyEnergy() const { return 0; }

bool InventoryItem::IsNovice(int) const { return false; }

bool InventoryItem::IsTransport() const { return false; }

NamedItem::NamedItem(const std::string& id, const std::string& name)
    : id_(id), name_(name) {
  if (id.empty() || name.empty()) {
    throw CommandError("id and name must not be empty");
  }
}

const std::string& NamedItem::InventoryId() const { return id_; }

const std::string& NamedItem::Name() const { return name_; }

void NamedItem::Describe(std::ostream& out) const {
  out << id_ << ' ' << name_;
}

std::ostream& operator<<(std::ostream& out, const InventoryItem& item) {
  item.Describe(out);
  return out;
}

bool operator<(const InventoryItem& left, const InventoryItem& right) {
  return left.InventoryId() < right.InventoryId();
}

bool operator==(const InventoryItem& left, const InventoryItem& right) {
  return left.InventoryId() == right.InventoryId();
}
