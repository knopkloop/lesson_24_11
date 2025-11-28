#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "planar.hpp"
#include <iostream>
Planar *make(std::istream &is);
Planar *make(size_t id);
void draw(Planar *pl);
void free_planars(Planar **pls, size_t k);
Planar **mostLeft(Planar **pls, size_t k);
Planar **max_area(Planar **pls, size_t k);
Planar **max_frame_intersects(Planar **pls, size_t k);
#endif
