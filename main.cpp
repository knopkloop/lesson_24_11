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
    if (std::cin.peek() == EOF) {
        break;
    }

    while (std::cin.peek() == '\n' || std::cin.peek() == '\r') {
        std::cin.ignore(1);
        if (std::cin.peek() == EOF)
        {
          break;
        }
    }

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
    catch (const std::logic_error &e)
    {
      std::string err = e.what();
      if (err == "bad cmd" && std::cin.eof()) {
          break;
      }
      std::cerr << "Error: " << e.what() << "\n";
      delete pl;
      free_planars(pls, s);
      return 2;
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "Memory error" << "\n";
      delete pl;
      free_planars(pls, s);
      return 2;
    }
  }

  if (s == 0) {
    std::cerr << "No shapes read" << "\n";
    delete[] pls;
    return 0;
  }
  std::cout << "\n";
  Planar **ml = mostLeft(pls, s);
  if (ml == pls + s)
  {
    std::cerr << "Not found" << "\n";
    free_planars(pls, s);
    return 0;
  }
  std::cout << "The most left figure:" << "\n";
  draw(*ml);

  Planar **max_area_pl = max_area(pls, s);
  std::cout << "Figure with max area:" << "\n";
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

    if (max_inter_pl == nullptr)
    {
      std::cerr << "No intersecting frames found" << "\n";
    }
    else
    {
      std::cout << "Two figures with the biggest intersection area:" << "\n";
      draw(max_inter_pl[0]);
      draw(max_inter_pl[1]);
      delete[] max_inter_pl;
    }
  }
  else
  {
    std::cerr << "Need at least 2 shapes for intersection check" << "\n";
  }

  free_planars(pls, s);
  return 0;
}
