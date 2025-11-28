#ifndef VECTOR_HPP
#define VECTOR_HPP
#include "point.hpp"
struct Vector: Planar
{
  virtual int x() const;
  virtual int y() const;
  virtual double area() const;
  virtual frame_t frame() const;
  virtual int abs_sqr() const;
  Vector(Point begin, Point end);
  virtual ~Vector() = default;
  private:
    Point data[2];
};
#endif
