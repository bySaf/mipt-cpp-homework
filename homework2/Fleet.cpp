#include "Fleet.h"

#include <cmath>
#include <ostream>
#include <utility>

#include "Errors.h"

std::size_t Fleet::Find(const std::string& id) const {
  for (std::size_t i = 0; i < items_.Size(); ++i) {
    if (items_[i]->InventoryId() == id) {
      return i;
    }
  }
  return items_.Size();
}

// чет странное с указателями было переписал попроще
void Fleet::Add(std::unique_ptr<InventoryItem> item) {
  if (!item) {
    throw CommandError("empty item");
  }

  for (auto current : items_) {
    if (*current == *item) {
      throw CommandError("duplicate id");
    }
  }
  service_.Inspect(*item);
  items_.Add(std::shared_ptr<InventoryItem>(std::move(item)));
}

void Fleet::Remove(const std::string& id) {
  std::size_t index = Find(id);
  if (index == items_.Size()) {
    throw CommandError("id not found");
  }
  items_.Remove(index);
}

void Fleet::Focus(const std::string& id) {
  std::size_t index = Find(id);
  if (index == items_.Size()) {
    throw CommandError("id not found");
  }
  focus_ = items_[index];
}

void Fleet::ShowFocus(std::ostream& out) const {
  if (auto item = focus_.lock()) {
    out << *item << '\n';
  } else {
    out << "expired\n";
  }
}

void Fleet::List(std::ostream& out) const {
  auto sorted = items_;
  sorted.Sort(
      [](const auto& left, const auto& right) { return *left < *right; });
  out << sorted;
}

// аналогично было
void Fleet::Novice(std::ostream& out) const {
  for (auto item : items_) {
    if (item->IsNovice(novice_score_)) {
      out << *item << '\n';
    }
  }
}

void Fleet::SetNoviceScore(int score) {
  if (score < 1 || score > 10) {
    throw CommandError("score must be in 1..10");
  }
  novice_score_ = score;
}

double Fleet::Energy() const {
  double total = 0;
  for (const auto& item : items_) {
    total += item->DailyEnergy();
    if (!std::isfinite(total)) {
      throw CommandError("total energy is too large");
    }
  }
  return total;
}

std::size_t Fleet::Size() const { return items_.Size(); }

// тут фулл вайбкод но +-понял как он это сделал
void Fleet::MaxEnergy(std::ostream& out) const {
  const InventoryItem* best = nullptr;
  for (const auto& item : items_) {
    if (best == nullptr || item->DailyEnergy() > best->DailyEnergy() ||
        (item->DailyEnergy() == best->DailyEnergy() && *item < *best)) {
      best = item.get();
    }
  }
  if (best == nullptr) {
    out << "empty\n";
  } else {
    out << *best << ' ' << best->DailyEnergy() << '\n';
  }
}
