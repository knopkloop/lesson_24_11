#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "point.hpp"

struct Circle: Planar
{
  virtual int x() const;
  virtual int y() const;
  virtual double area() const;
  virtual frame_t frame() const;
  virtual int abs_sqr() const;
  Circle(Point c, int r);
  virtual ~Circle() = default;
  private:
    Point center;
    int radius;
};
#endif
