#include <iostream>
#include "json.h"

int main() {
  json j1 = readJSONFile("test.json");
  std::cout << j1.dump() << std::endl;
  return 0;
}