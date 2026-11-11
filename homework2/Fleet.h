#ifndef FIZKAT_FLEET_H
#define FIZKAT_FLEET_H

#include <iosfwd>
#include <memory>
#include <string>

#include "Inventory.h"
#include "Registry.h"
#include "ServiceCenter.h"

class Fleet {
 public:
  void Add(std::unique_ptr<InventoryItem> item);
  void Remove(const std::string& id);
  void Focus(const std::string& id);
  void ShowFocus(std::ostream& out) const;
  void List(std::ostream& out) const;
  void Novice(std::ostream& out) const;
  void SetNoviceScore(int score);
  double Energy() const;
  std::size_t Size() const;
  void MaxEnergy(std::ostream& out) const;

 private:
  std::size_t Find(const std::string& id) const;

  Registry<std::shared_ptr<InventoryItem>> items_;
  std::weak_ptr<InventoryItem> focus_;
  ServiceCenter service_;
  int novice_score_ = 6;
};

#endif
