#include "Things.h"

Helmet::Helmet(const std::string& id, const std::string& name)
    : NamedItem(id, name) {}

Dock::Dock(const std::string& id, const std::string& name, double energy)
    : NamedItem(id, name), energy_(energy) {
  CheckEnergy(energy);
}

double Dock::DailyEnergy() const { return energy_; }
