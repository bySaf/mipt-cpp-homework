#ifndef FIZKAT_THINGS_H
#define FIZKAT_THINGS_H

#include "EnergyConsumer.h"
#include "Inventory.h"

class Helmet : public NamedItem {
 public:
  Helmet(const std::string& id, const std::string& name);
};

class Dock : public NamedItem, public EnergyConsumer {
 public:
  Dock(const std::string& id, const std::string& name, double energy);
  double DailyEnergy() const override;

 private:
  double energy_;
};

#endif
