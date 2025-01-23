#include "log.h"

#include <iostream>

namespace Log {
void Info(std::string &&message) { std::cout << message << std::endl; }
void Error(std::string &&message) { std::cerr << message << std::endl; }
};  // namespace Log
