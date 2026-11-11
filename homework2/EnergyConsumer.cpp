#include "EnergyConsumer.h"

#include <cmath>

#include "Errors.h"

void CheckEnergy(double energy) {
  if (!std::isfinite(energy) || energy < 0) {
    throw CommandError("energy must be finite and non-negative");
  }
}
