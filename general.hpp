#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <stdlib.h>

#define quick_print(what) std::cout << what << std::endl
#define min(x,y) ( (x) < (y) ? (x) : (y) )
#define max(x,y) ( (x) > (y) ? (x) : (y) )
#define saturate(value,min_value,max_value) (value) > (max_value) ? (max_value) : ( (value) < (min_value) ? (min_value) : (value) )
#define deg_to_rad(d) (d / 360.0 * 2 * 3.1415926535)

// \brief Custom 3D vector to keep independency of frontend engine.

class Point3D
  {
    public:
      Point3D();
      Point3D(double x, double y, double z);

      double x;
      double y;
      double z;

    void print();
  };

void terminal_print(std::string message);

#endif
