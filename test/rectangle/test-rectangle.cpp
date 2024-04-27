#include <gtest/gtest.h>
#include "../../src/rectangle.h"

TEST(Rectangle, Constructor) {
  Rectangle r = Rectangle(0,0,300,600);
  EXPECT_EQ(r.getTop(),0);
  EXPECT_EQ(r.getBottom(),600);
  EXPECT_EQ(r.getLeft(),0);
  EXPECT_EQ(r.getRight(),300);
}

TEST(Rectangle, isChildOf) {
  Rectangle r1 = Rectangle(0,0,100,100, "1");
  Rectangle r2 = Rectangle(100,100,100,100, "2");
  Rectangle r3 = Rectangle(0,0,50,50,"",{r1.getName()});
  EXPECT_EQ(r3.isChildOf(r1), true);
  EXPECT_EQ(r3.isChildOf(r2), false);
}

TEST(Rectangle, equalityOperator) {
  Rectangle r1 = Rectangle(0,0,100,100);
  Rectangle r2 = Rectangle(0,0,100,100);
  Rectangle r3 = Rectangle(0,0,50,50);
  EXPECT_EQ(r1==r2, true);
  EXPECT_EQ(r1==r3, false);
}

TEST(Rectangle, stringConversionOperator1) {
  std::string s = "1: Rectangle at (100,100), w=250, h=80.";
  Rectangle r = Rectangle(100,100,250,80,"1");
  EXPECT_EQ(std::string(r),s);
}

TEST(Rectangle, stringConversionOperator2) {
  std::string s = "Between rectangle 1 and 3 at (140,160), w=210, h=20.";
  Rectangle r1 = Rectangle(0,0,0,0,"1");
  Rectangle r3 = Rectangle(0,0,0,0,"3");
  Rectangle r = Rectangle(140,160,210,20,"",{r1.getName(),r3.getName()});
  EXPECT_EQ(std::string(r),s);
}

TEST(Rectangle, intersection) {
  Rectangle r1 = Rectangle(0,0,100,100);
  Rectangle r2 = Rectangle(50,50,200,25);
  Rectangle rInter = Rectangle(50,50,50,25);
  EXPECT_EQ(r1.intersection(r2),rInter);
}