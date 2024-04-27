#include <gtest/gtest.h>
#include "../../src/json.h"

TEST(JSON, canReadJSONFile) {
  json j1 = readJSONFile("./hello.json");
  EXPECT_EQ(j1.dump(),"{\"Hello\":\"World\"}");
}

TEST(JSON, JSONValidation) {
  json badJSON = readJSONFile("./hello.json");
  EXPECT_EQ(validateJSON(badJSON),false);
  json goodJSON = readJSONFile("./rectangles.json");
  EXPECT_EQ(validateJSON(goodJSON), true);
}