#include "json.h"

json readJSONFile(const std::string &filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file: " + filePath);
  }
  json j;
  try {
    file >> j;
  } catch (const json::parse_error &e) {
    throw std::runtime_error("JSON Parsing Error: " + std::string(e.what()));
  }

  return j;
}

bool validateJSON(const json &j) {
  try {
    // Check for key "rects", and validate that it is an array
    if (!j.contains("rects") || !j["rects"].is_array())
      return false;

    // Iterate through "rects", and validate that each rectangle has the
    // sufficient and correctly typed fields
    for (const auto &rect : j["rects"]) {
      if (!rect.contains("x") || !rect["x"].is_number_integer() ||
          !rect.contains("y") || !rect["y"].is_number_integer() ||
          !rect.contains("w") || !rect["w"].is_number_integer() ||
          !rect.contains("h") || !rect["h"].is_number_integer()) {
        return false;
      }
    }
  } catch (const std::exception &e) {
    // In case any step of parsing throws an exception
    return false;
  }
  // If all works, the JSON is valid
  return true;
}
