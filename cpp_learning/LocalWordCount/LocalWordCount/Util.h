#pragma once

#include <string>

std::string trimTail(const std::string &str, const std::string &toTrim) {
  auto last = str.find_last_not_of(toTrim);
  return str.substr(0, last + 1);
}