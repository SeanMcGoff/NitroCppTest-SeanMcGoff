#ifndef NITROCPPTEST_JSON_H
#define NITROCPPTEST_JSON_H
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json readJSONFile(const std::string& filePath);
#endif NITROCPPTEST_JSON_H
