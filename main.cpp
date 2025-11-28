#include <iostream>
#include "planar.hpp"
#include "frame_t.hpp"
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
      pls[s++] = pl;
    }
    catch (...)
    {
      delete[] pl;
      free_planars(pls, s);
      return 2;
    }
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
    return 0;
  }
  draw(*ml);
  std::cout << "\n";
  
  Planar **max_area_pl = max_area(pls, s);
  draw(*max_area_pl);
  
  if (s >= 2)
  {
    Planar **max_inter_pl = nullptr;
    try
    {
      max_inter_pl = max_frame_intersects(pls, s);
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "Memory allocation error" << "\n";
      free_planars(pls, s);
      return 2;
    }
    
    if (max_inter_pl == pls + s)
    {
      std::cerr << "Not found" << "\n";
      free_planars(pls, s);
      return 0;
    }
    
    draw(max_inter_pl[0]);
    draw(max_inter_pl[1]);
  }
  
  else
  {
    std::cerr << "Not enough Planars" << "\n";
    free_planars(pls, s);
    return 3;
  }
  
  free_planars(pls, s);
  return 0;
}





