#ifndef FIZKAT_TRANSPORT_H
#define FIZKAT_TRANSPORT_H

#include "EnergyConsumer.h"
#include "Inventory.h"

class Transport : public NamedItem {
 public:
  Transport(const std::string& id, const std::string& name, int score);
  double DailyEnergy() const override = 0;
  bool IsNovice(int min_score) const override;
  bool IsTransport() const override;

 private:
  int score_;
};

class ElectricScooter : public Transport, public EnergyConsumer {
 public:
  ElectricScooter(const std::string& id, const std::string& name, double energy,
                  int score);
  double DailyEnergy() const override;

 private:
  double energy_;
};

class Bike : public Transport {
 public:
  Bike(const std::string& id, const std::string& name, int score);
  double DailyEnergy() const override;
};

class ElectricBike : public Transport, public EnergyConsumer {
 public:
  ElectricBike(const std::string& id, const std::string& name, double energy,
               int score);
  double DailyEnergy() const override;

 private:
  double energy_;
};

class Skateboard : public Transport {
 public:
  Skateboard(const std::string& id, const std::string& name, int score);
  double DailyEnergy() const override;
};

#endif
