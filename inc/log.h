#pragma once

#include <format>
#include <string>

namespace Log {
void Info(std::string &&message);
void Error(std::string &&message);
};  // namespace Log
