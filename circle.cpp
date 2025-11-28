#include "circle.hpp"

Circle::Circle(Point c, int r):
  Planar(),
  center(c),
  radius(r)
{
}

int Circle::x() const
{
  return center.x();
}

int Circle::y() const
{
  return center.y();
}

double Circle::area() const
{
  const double PI = 3.141592653589793;
  return PI * radius * radius;
}

frame_t Circle::frame() const
{
  frame_t f;
  f.AA.x = x() - radius;
  f.AA.y = y() - radius;
  f.BB.x = x() + radius;
  f.BB.y = y() + radius;
  return f;
}

int Circle::abs_sqr() const
{
  return x() * x() + y() * y();
}

