#include <gtest/gtest.h>
#include "../../src/json.h"

TEST(JsonTest, canReadJSONFile) {
  json j1 = readJSONFile("./hello.json");
  EXPECT_EQ(j1.dump(),"{\"Hello\":\"World\"}");
}