#ifndef FIZKAT_ERRORS_H
#define FIZKAT_ERRORS_H

#include <exception>
#include <string>


class FleetError : public std::exception {
 public:
  explicit FleetError(const std::string& message) : message_(message) {}
  const char* what() const noexcept override { return message_.c_str(); }

 private:
  std::string message_;
};

class InspectionError : public FleetError {
 public:
  InspectionError() : FleetError("inspection rejected") {}
};

class CommandError : public FleetError {
 public:
  explicit CommandError(const std::string& message) : FleetError(message) {}
};

#endif
