#ifndef FIZKAT_COMMANDS_H
#define FIZKAT_COMMANDS_H

#include <iosfwd>
#include <string>

class Fleet;

bool ExecuteCommand(const std::string& line, Fleet& fleet, std::ostream& out);

#endif
