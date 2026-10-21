#include <iomanip>
#include <iostream>

double CalculateAverage(const int* temperatures, int size) {
  long long sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += temperatures[i];
  }
  return 1.0 * sum / size;
}

int FindMinimum(const int* temperatures, int size){
  int minimum = temperatures[0];
  for (int i = 1; i < size; ++i) {
    if (temperatures[i] < minimum) {
      minimum = temperatures[i];
    }
  }
  return minimum;
}

int FindMaximum(const int* temperatures, int size) {
  int maximum = temperatures[0];
  for (int i = 1; i < size; ++i) {
    if (temperatures[i] > maximum) {
      maximum = temperatures[i];
    }
  }
  return maximum;
}

int CountFreezingDays(const int* temperatures, int size) {
  int count = 0;
  for (int i = 0; i < size; ++i) {
    if (temperatures[i] < 0) {
      ++count;
    }
  }
  return count;
}

int main() {
  int size;
  std::cin >> size;

  if (size <= 0) {
    return 0;
  }

  int* temperatures = new int[size];
  for (int i = 0; i < size; ++i) {
    std::cin >> temperatures[i];
  }

  double average = CalculateAverage(temperatures, size);
  int minimum = FindMinimum(temperatures, size);
  int maximum = FindMaximum(temperatures, size);
  int freezing_days = CountFreezingDays(temperatures, size);

  std::cout << std::fixed << std::setprecision(1) << average << '\n';
  std::cout << minimum << ' ' << maximum << '\n';
  std::cout << freezing_days << '\n';

  delete[] temperatures;
  return 0;
}
