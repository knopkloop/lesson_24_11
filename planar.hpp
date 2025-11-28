#ifndef PLANAR_HPP
#define PLANAR_HPP
#include "frame_t.hpp"
struct Planar
{
  virtual int x() const = 0;
  virtual int y() const = 0;
  virtual double area() const = 0;
  virtual frame_t frame() const = 0;
  virtual int abs_sqr() const = 0;
  virtual ~Planar() = default;
};
#endif
