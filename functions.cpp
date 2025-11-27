#include <iostream>
#include "functions.hpp"
#include "point.hpp"
#include "vector.hpp"

Planar *make(std::istream &is)
{
  char cmd[2] = {};
  is >> cmd[0] >> cmd[1];
  int data[4] = {};
  
  if (cmd[0] == 'P' && cmd[1] == 'T')
  {
    if (is >> data[0] >> data[1])
    {
      return new Point(data[0], data[1]);
    }
  }
  else if (cmd[0] == 'V' && cmd[1] == 'T')
  {
    if (is >> data[0] >> data[1] >> data[2] >> data[3])
    {
      return new Vector(Point(data[0], data[1]), Point(data[2], data[3]));
    }
  }
  
  throw std::logic_error("bad cmd");
}

Planar *make(size_t id)
{
  Planar *r = nullptr;
  switch (id)
  {
    case 0:
      r = new Point(0, 0);
      break;
    default:
      throw std::logic_error("bad id");
  }
  return r;
}

void free_planars(Planar **pls, size_t k)
{
  for (size_t i = 0; i < k; ++i)
  {
    delete[] pls[i];
  }
  delete[] pls;
}

void draw(Planar *pl)
{
  std::cout << pl->x();
  std::cout << " ";
  std::cout << pl->y() << "\n";
}

Planar **mostLeft(Planar **pls, size_t k)
{
  if (!k)
  {
    return pls;
  }
  
  Planar **res = pls;
  while (--k)
  {
    int next_x = (*(++pls))->x();
    int cur_x = (*res)->x();
    if (next_x < cur_x)
    {
      res = pls;
    }
  }
  return res;
}
