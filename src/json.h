#ifndef NITROCPPTEST_JSON_H
#define NITROCPPTEST_JSON_H
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Reads in JSON file and returns the parsed data
json readJSONFile(const std::string& filePath);

// Makes sure JSON is of correct format given design brief
bool validateJSON(const json& j);

#endif //NITROCPPTEST_JSON_H
