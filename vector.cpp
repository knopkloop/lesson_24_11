#include "vector.hpp"

Vector::Vector(Point begin, Point end):
  Planar(),
  data {begin, end}
{
}

int Vector::x() const
{
  return data[1].x() - data[0].x();
}

int Vector::y() const
{
  return data[1].y() - data[0].y();
}

double Vector::area() const
{
  return 0.0;
}

frame_t Vector::frame() const
{
  frame_t f;
  return f;
}

int Vector::abs_sqr() const
{
  return x() * x() + y() * y();
}
