#include "string_utils.h"

#include <iostream>

namespace StringUtils {
void LogInfo(std::string &&message) { std::cout << message << std::endl; }
void LogError(std::string &&message) { std::cerr << message << std::endl; }
};  // namespace StringUtils
