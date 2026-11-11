#ifndef FIZKAT_ENERGY_CONSUMER_H
#define FIZKAT_ENERGY_CONSUMER_H

class EnergyConsumer {
 public:
  virtual ~EnergyConsumer() = default;
  virtual double DailyEnergy() const = 0;
};

void CheckEnergy(double energy);

#endif
