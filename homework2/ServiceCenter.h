#ifndef FIZKAT_SERVICE_CENTER_H
#define FIZKAT_SERVICE_CENTER_H

class InventoryItem;

class ServiceCenter {
 public:
  void Inspect(const InventoryItem& item) const;
};

#endif
