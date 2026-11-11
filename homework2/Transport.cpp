#include "Transport.h"

#include "Errors.h"

Transport::Transport(const std::string& id, const std::string& name, int score)
    : NamedItem(id, name), score_(score) {
  if (score < 1 || score > 10) {
    throw CommandError("score must be in 1..10");
  }
}

bool Transport::IsNovice(int min_score) const { return score_ >= min_score; }

bool Transport::IsTransport() const { return true; }

ElectricScooter::ElectricScooter(const std::string& id, const std::string& name,
                                 double energy, int score)
    : Transport(id, name, score), energy_(energy) {
  CheckEnergy(energy);
}

double ElectricScooter::DailyEnergy() const { return energy_; }

Bike::Bike(const std::string& id, const std::string& name, int score)
    : Transport(id, name, score) {}

double Bike::DailyEnergy() const { return 0; }

ElectricBike::ElectricBike(const std::string& id, const std::string& name,
                           double energy, int score)
    : Transport(id, name, score), energy_(energy) {
  CheckEnergy(energy);
}

double ElectricBike::DailyEnergy() const { return energy_; }

Skateboard::Skateboard(const std::string& id, const std::string& name,
                       int score)
    : Transport(id, name, score) {}

double Skateboard::DailyEnergy() const { return 0; }
