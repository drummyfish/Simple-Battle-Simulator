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

double Point3D::distance(Point3D point)
  {
    double dx = this->x - point.x;
    double dy = this->y - point.y;
    double dz = this->z - point.z;

    return sqrt(dx * dx + dy * dy + dz * dz);
  }

double Point3D::length()
  {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
  }

Point3D Point3D::normalized()
  {
    return (*this) / this->length();
  }

Point3D Point3D::operator+(Point3D point)
  {
    return Point3D(this->x + point.x,this->y + point.y,this->z + point.z);
  }

Point3D Point3D::operator-(Point3D point)
  {
    return Point3D(this->x - point.x,this->y - point.y,this->z - point.z);
  }

Point3D Point3D::operator*(double val)
  {
    return Point3D(this->x * val,this->y * val,this->z * val);
  }

Point3D Point3D::operator/(double val)
  {
    return Point3D(this->x / val,this->y / val,this->z / val);
  }

void terminal_print(std::string message)
  {
    std::cout << message << std::endl;
  }
