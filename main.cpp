#include <iostream>
#include "planar.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "functions.hpp"

int main()
{
  Planar *pls[10] = {};
  size_t k = 0;
  for (size_t i = 0; i < 10; ++i)
  {
    try
    {
      pls[k] = make(i % 2);
    }
    catch (...)
    {
      free_planars(pls, k);
      return 2;
    }
    ++k;
  }
  draw(mostLeft(pls, k));
  free_planars(pls, k);
  return 0;
}





