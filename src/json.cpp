#include "json.h"

// Reads in JSON file and returns the parsed data
json readJSONFile(const std::string& filePath) {
  std::ifstream file(filePath);
  if(!file.is_open()) {
    throw std::runtime_error("Could not open file: " + filePath);
  }
  json j;
  try {
    file >> j;
  } catch(const json::parse_error &e) {
    throw std::runtime_error("JSON Parsing Error: " + std::string(e.what()));
  }

  return j;
}
