#ifndef FIZKAT_INVENTORY_H
#define FIZKAT_INVENTORY_H

#include <iosfwd>
#include <string>

class InventoryItem {
 public:
  virtual ~InventoryItem() = default;
  virtual const std::string& InventoryId() const = 0;
  virtual const std::string& Name() const = 0;
  virtual void Describe(std::ostream& out) const = 0;
  virtual double DailyEnergy() const;
  virtual bool IsNovice(int min_score) const;
  virtual bool IsTransport() const;
};

// Общие поля, чтобы не повторять id и name в каждом виде инвентаря.
class NamedItem : public InventoryItem {
 public:
  NamedItem(const std::string& id, const std::string& name);
  const std::string& InventoryId() const override;
  const std::string& Name() const override;
  void Describe(std::ostream& out) const override;

 private:
  std::string id_;
  std::string name_;
};

std::ostream& operator<<(std::ostream& out, const InventoryItem& item);
bool operator<(const InventoryItem& left, const InventoryItem& right);
bool operator==(const InventoryItem& left, const InventoryItem& right);

#endif
