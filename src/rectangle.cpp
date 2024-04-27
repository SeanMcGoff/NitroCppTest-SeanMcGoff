#include "rectangle.h"

Rectangle::Rectangle (int x, int y, int w, int h, std::string name, std::vector<Rectangle*> parentRects) {
  if(w < 0 || h < 0) throw std::out_of_range("Area cannot be less than 0");
  this->left = x;
  this->right = x+w;
  this->top = y;
  this->bottom = y+h;
  this->name = name;
  this->parentRects = parentRects;
}

int Rectangle::getLeft() const {
  return this->left;
}

int Rectangle::getRight() const {
  return this->right;
}

int Rectangle::getTop() const {
  return this->top;
}

int Rectangle::getBottom() const {
  return this->bottom;
}

int Rectangle::getWidth() const {
  return this->getRight() - this->getLeft();
}

int Rectangle::getHeight() const {
  return this->getBottom() - this->getTop();
}

std::string Rectangle::getName() const {
  return this->name;
}

bool Rectangle::isChildOf(const Rectangle& r) {
  return std::find(this->parentRects.begin(),this->parentRects.end(),&r) != this->parentRects.end();
}

bool Rectangle::operator==(const Rectangle &r) const {
  return (r.getLeft() == this->getLeft()) && (r.getRight() == this->getRight()) && (r.getTop() == this->getTop()) && (r.getBottom() == this->getBottom());
}

Rectangle::operator std::string() const {
  std::string prefix;
  if(this->parentRects.size() != 0) {
    // If the rectangle is a result of an intersection
    prefix = "Between rectangle ";
    for(int i = 0; i < this->parentRects.size(); ++i) {
      prefix += this->parentRects[i]->getName();
      // Switch Statement determines correct comma placement
      switch(this->parentRects.size() - i) {
        case 1:
          // Last parent rectangle, no need for a last comma
          break;
        case 2:
          // Second to Last parent rectangle, "and" with no oxford comma
          prefix += " and ";
          break;
        default:
          // Standard Comma
          prefix += ", ";
          break;
      }
    }
    prefix += " at ";
  } else {
    // If the rectangle has no parents
    prefix = this->getName() + ": Rectangle at ";
  }
  return prefix + "("
  +std::to_string(this->getLeft())
  +","
  +std::to_string(this->getTop())
  +"), w="
  +std::to_string(this->getWidth())
  +", h="
  +std::to_string(this->getHeight())
  +".";
}

Rectangle Rectangle::intersection(Rectangle& r) {
  // Edge Cases (using a 0W/OH rectangle as a sort of null return)
  if(this->right <= r.getLeft() || this->left >= r.getRight()) return Rectangle(0,0,0,0);
  if(this->bottom <= r.getTop() || this->top >= r.getBottom()) return Rectangle(0,0,0,0);
  int left_inter = std::max(this->getLeft(),r.getLeft());
  int right_inter = std::min(this->getRight(),r.getRight());
  int top_inter = std::max(this->getTop(),r.getTop());
  int bottom_inter = std::min(this->getBottom(),r.getBottom());
  return Rectangle(left_inter,top_inter,right_inter-left_inter,bottom_inter-top_inter,"",{this,&r});
}