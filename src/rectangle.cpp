#include "rectangle.h"

bool hasDuplicateParents(std::vector<Rectangle>& rects,std::vector<std::string>& pr) {
  std::sort(pr.begin(),pr.end());
  for(Rectangle& r_i : rects) {
    if(r_i.getParentRects() == pr) return true;
  }
  return false;
}


std::vector<Rectangle> intersectionsOf(std::vector<Rectangle>& rects) {
  // Storing our intersections in two vectors ensures we hit every combination of intersections without overlapping
  std::vector<Rectangle> checked_intersections;
  std::vector<Rectangle> unchecked_intersections;
  // Create null Rectangle to verify whether rectangles overlap or not
  Rectangle nullRect = Rectangle(0,0,0,0);
  // Loop over every combination and find intersections (as far as I know O(n^2) is the best I'm getting it)
  for(int i = 0; i < rects.size(); ++i) {
    for(int j = 0; j < rects.size(); ++j) {
      if(i>=j) continue; // We don't want to find the intersection of the same rectangle, or double-count each rectangle
      Rectangle r_inter = rects[i].intersection(rects[j]);
      if(!(r_inter == nullRect)) unchecked_intersections.push_back(r_inter);
    }
  }
  // Finds Higher-Order Intersections
  while(unchecked_intersections.size()>0) {
    for(auto itr = unchecked_intersections.begin(); itr != unchecked_intersections.end();) {
      for(Rectangle& r : rects) {
        // We don't want to find the intersection of 1, 3, and 1 again
        if(itr->isChildOf(r)) continue;
        // Similarly, if we have the intersection of 1, 2, and 3, finding the intersection of 1, 3, and 2 is redundant
        std::vector<std::string> currentParentRects = itr->getParentRects();
        currentParentRects.push_back(r.getKey());
        if(hasDuplicateParents(unchecked_intersections,currentParentRects)) continue;
        // Provided we don't hit a duplicate case, we can check the intersection
        Rectangle r_inter = itr->intersection(r);
        if(!(r_inter == nullRect)) unchecked_intersections.push_back(r_inter);
      }
      // All possible higher-order intersections of *itr have been exhausted, so we can move it to checked
      checked_intersections.push_back(*itr);
      itr = unchecked_intersections.erase(itr);
    }
  }
  return checked_intersections;
}

Rectangle::Rectangle (int x, int y, int w, int h, std::string key, std::vector<std::string> parentRects) {
  if(w < 0 || h < 0) throw std::out_of_range("Area cannot be less than 0");
  this->left = x;
  this->right = x+w;
  this->top = y;
  this->bottom = y+h;
  this->key = key;
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

std::string Rectangle::getKey() const {
  return this->key;
}

const std::vector<std::string>& Rectangle::getParentRects() const {
  return this->parentRects;
}

bool Rectangle::isChildOf(const Rectangle& r) {
  return std::find(this->parentRects.begin(),this->parentRects.end(),r.getKey()) != this->parentRects.end();
}

bool Rectangle::operator==(const Rectangle &r) const {
  return (r.getLeft() == this->getLeft())
  && (r.getRight() == this->getRight())
  && (r.getTop() == this->getTop())
  && (r.getBottom() == this->getBottom())
  && (r.getParentRects() == this->getParentRects());
}

Rectangle::operator std::string() const {
  std::string prefix;
  if(this->parentRects.size() != 0) {
    // If the rectangle is a result of an intersection
    prefix = "Between rectangle ";
    for(int i = 0; i < this->parentRects.size(); ++i) {
      prefix += this->parentRects[i];
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
    prefix = this->getKey() + ": Rectangle at ";
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
  // Find Coords of each Edge
  int left_inter = std::max(this->getLeft(),r.getLeft());
  int right_inter = std::min(this->getRight(),r.getRight());
  int top_inter = std::max(this->getTop(),r.getTop());
  int bottom_inter = std::min(this->getBottom(),r.getBottom());
  // Construct List of Parent Rectangles
  std::vector<std::string> pr;
  // Either push back key of current rectangle, or their parents (if they exist) for both rectangles in function
  if(this->getParentRects().size() == 0) pr.push_back(this->getKey());
  else {
    for(std::string r_parent : this->getParentRects()) pr.push_back(r_parent);
  }

  if(r.getParentRects().size() == 0) pr.push_back(r.getKey());
  else {
    for(std::string r_parent : r.getParentRects()) pr.push_back(r_parent);
  }
  // Makes output look nicer + reduces time complexity of duplicate removal
  std::sort(pr.begin(),pr.end());
  // Return Rectangle
  return Rectangle(left_inter,top_inter,right_inter-left_inter,bottom_inter-top_inter,"",pr);
}





