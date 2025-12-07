#include <iostream>
#include "functions.hpp"
#include "point.hpp"
#include "vector.hpp"
#include "circle.hpp"

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

  else if (cmd[0] == 'C' && cmd[1] == 'T')
  {
    if (is >> data[0] >> data[1] >> data[2])
    {
      return new Circle(Point(data[0], data[1]), data[2]);
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
    case 1:
      r = new Vector(Point(0, 0), Point(1, 1));
      break;
    case 2:
      r = new Circle(Point(0, 0), 1);
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
    delete pls[i];
  }
  delete[] pls;
}

void draw(Planar *pl)
{
  std::cout << pl->x();
  std::cout << " ";
  std::cout << pl->y() << "\n";
  frame_t fr = pl->frame();
  std::cout << fr.AA.x << " " << fr.AA.y << " " << fr.BB.x << " " << fr.BB.y << "\n";
  std::cout << "\n";
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

Planar **max_area(Planar **pls, size_t k)
{
  if(!k)
  {
    return pls;
  }
  Planar **res = pls;
  while (--k)
  {
    int next_area = (*(++pls))->area();
    int cur_area = (*res)->area();
    if (next_area > cur_area)
    {
      res = pls;
    }
  }
  return res;
}

double intersection_area(const frame_t &a, const frame_t &b)
{
    int left = std::max(a.AA.x, b.AA.x);
    int right = std::min(a.BB.x, b.BB.x);
    int bottom = std::max(a.AA.y, b.AA.y);
    int top = std::min(a.BB.y, b.BB.y);

    if (left >= right || bottom >= top)
    {
        return 0.0;
    }
    return (right - left) * (top - bottom);
}

Planar **max_frame_intersects(Planar **pls, size_t k)
{
  if (!k)
  {
    return nullptr;
  }

  double maxim = -1.0;
  double inter_area = 0.0;
  Planar **res = nullptr;

  try
  {
    res = new Planar*[2];
  }
  catch(const std::bad_alloc &)
  {
    throw;
  }

  res[0] = pls[0];
  res[1] = pls[1];
  maxim = intersection_area(pls[0]->frame(), pls[1]->frame());

  for (size_t i = 0; i < k - 1; ++i)
  {
    for (size_t j = i + 1; j < k; ++j)
    {
      frame_t fr1 = pls[i]->frame();
      frame_t fr2 = pls[j]->frame();
      inter_area = intersection_area(fr1, fr2);

      if (inter_area > maxim)
      {
        maxim = inter_area;
        res[0] = pls[i];
        res[1] = pls[j];
      }
    }
  }

  if (maxim <= 0.0)
  {
    delete[] res;
    return nullptr;
  }

  return res;
}
