#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <iostream>
#include <string>
#include <vector>

#define quick_print(what) std::cout << what << std::endl

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
