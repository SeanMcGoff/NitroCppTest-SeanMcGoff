#include "json.h"
#include "rectangle.h"
#include <iostream>

// As explained in the brief: "You may discard the remaining rectangles after
// the first 10."
const int MAX_RECT_INPUT = 10;

int main(int argc, char *argv[]) {
  // Argument errors
  if (argc < 2)
    throw std::runtime_error("Must supply JSON file of rectangles");
  if (argc > 2)
    throw std::runtime_error("This program does not support multiple files");
  // Attempt reading JSON from supplied file path
  std::string filePath = argv[1];
  json j = readJSONFile(filePath);
  // Validate JSON from file
  if (!validateJSON(j))
    throw std::runtime_error("JSON File is not valid");
  // Parse out JSON and store in vector of rectangles
  std::vector<Rectangle> rects;
  for (int i = 0; i < j["rects"].size() && i < MAX_RECT_INPUT; ++i) {
    const auto &rect = j["rects"][i];
    rects.push_back(Rectangle(rect["x"], rect["y"], rect["w"], rect["h"],
                              std::to_string(i + 1)));
  }
  // Print out Input
  std::cout << "Input:" << std::endl;
  for (const Rectangle &r : rects) {
    std::cout << "\t" << std::string(r) << std::endl;
  }
  // Create Vector of Intersections
  std::vector<Rectangle> intersections = intersectionsOf(rects);
  // Print out Intersections
  std::cout << "Intersections" << std::endl;
  for (const Rectangle &r : intersections) {
    std::cout << "\t" << std::string(r) << std::endl;
  }
  return 0;
}