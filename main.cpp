#include <iostream>
#include "planar.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "functions.hpp"

int main()
{
  size_t s = 0;
  size_t c = 20;
  Planar **pls = new Planar*[c];
  
  while (std::cin)
  {
    Planar *pl = nullptr;
    try
    {
      pl = make(std::cin);
      if (s == c)
      {
        Planar **epls = new Planar *[c * 2];
        for (size_t i = 0; i < s; ++i)
        {
          epls[i] = pls[i];
        }
        delete[] pls;
        pls = epls;
        c *= 2;
      }
      pls[s] = pl;
    }
    catch (...)
    {
      delete[] pl;
      free_planars(pls, s);
      return 2;
    }
    ++s;
  }
  
  if (!std::cin.eof())
  {
    free_planars(pls, s);
    return 3;
  }
  
  Planar **ml = mostLeft(pls, s);
  if (ml == pls + s)
  {
    std::cerr << "Not found" << "\n";
    free_planars(pls, s);
  }
  draw(*ml);
  std::cout << "\n";
  free_planars(pls, s);
  return 0;
}





