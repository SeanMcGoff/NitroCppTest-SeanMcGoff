#ifndef NITROCPPTEST_RECTANGLE_H
#define NITROCPPTEST_RECTANGLE_H
#include <vector>
class Rectangle {
private:
    // Storing the edges instead of x/y/w/h makes the intersection code simpler
    int left;
    int right;
    int top;
    int bottom;

    // Informal name of the rectangle (for this code, they will be stored as "1", "2", "3", etc.)
    std::string name;

    // This is in order to stop the algorithm from computing nested intersections of the same rectangle
    std::vector<Rectangle*> parentRects;

public:
    // Constructor
    Rectangle(int x, int y, int w, int h, std::string name="", std::vector<Rectangle*> parentRects = {});
    // Getters
    int getLeft() const;
    int getRight() const;
    int getTop() const;
    int getBottom() const;
    int getWidth() const;
    int getHeight() const;

    std::string getName() const;

    // Equality Operator (for null logic and Testing)
    bool operator==(const Rectangle& r) const;
    // String Conversion (for logging and output)
    operator std::string() const;
    // Checks if this Rectangle is a child of the Rectangle "r"
    bool isChildOf(const Rectangle& r);
    // Finds the intersection between two rectangles, and returns that Rectangle
    Rectangle intersection(Rectangle& r);
    // Destructor
    ~Rectangle()=default;
};
#endif //NITROCPPTEST_RECTANGLE_H
