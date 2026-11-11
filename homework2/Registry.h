#ifndef FIZKAT_REGISTRY_H
#define FIZKAT_REGISTRY_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <ostream>
#include <utility>
#include <vector>

#include "Inventory.h"

template <typename T>
void PrintRegistryValue(std::ostream& out, const T& value) {
  out << value;
}

template <>
inline void PrintRegistryValue<std::shared_ptr<InventoryItem>>(
    std::ostream& out, const std::shared_ptr<InventoryItem>& value) {
  out << *value;
}

template <typename T>
class Registry {
 public:
  void Add(T value) { items_.push_back(std::move(value)); }
  std::size_t Size() const { return items_.size(); }
  const T& operator[](std::size_t index) const { return items_.at(index); }
  void Remove(std::size_t index) {
    items_.erase(items_.begin() + static_cast<std::ptrdiff_t>(index));
  }
  auto begin() const { return items_.begin(); }
  auto end() const { return items_.end(); }
  template <typename Compare>
  void Sort(Compare compare) {
    std::sort(items_.begin(), items_.end(), compare);
  }

 private:
  std::vector<T> items_;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Registry<T>& registry) {
  for (const auto& value : registry) {
    PrintRegistryValue(out, value);
    out << '\n';
  }
  return out;
}

#endif
