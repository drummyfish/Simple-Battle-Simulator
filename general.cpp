#include "general.hpp"

Point3D::Point3D()
  {
    this->x = 0;
    this->y = 0;
    this->z = 0;
  }

Point3D::Point3D(double x, double y, double z)
  {
    this->x = x;
    this->y = y;
    this->z = z;
  }

void Point3D::print()
  {
    std::cout << "point 3D: " << this->x << " " << this->y << " " << this->z << std::endl;
  }

void terminal_print(std::string message)
  {
    std::cout << message << std::endl;
  }
