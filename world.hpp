#ifndef WORLD_HPP
#define WORLD_HPP

#include "general.hpp"
#include "frontend.hpp"

class Battlefield;

class UnitKind
  {
    public:
      UnitKind();

      std::string name;
      int health_max;
      int attack;
      double attack_speed;    ///< in hits per second
      double movement_speed;
      double radius;
      double height;
  };

class UnitInstance
  {
    public:
      UnitInstance(UnitKind *kind, Battlefield *battlefield);

      void set_position(Point3D new_position);
      void set_rotation(double new_rotation);

      void update(double dt);

      Point3D get_position();
      double get_rotation();

    protected:
      Point3D position;
      double rotation;
      UnitKind *kind;
      int health_current;
      int team;
      int node_handle;

      Battlefield *battlefield;
      Engine *engine;
      Frontend *frontend;
  };

class Battlefield
  {
    public:
      Battlefield(Engine *engine);
      ~Battlefield();
      void create_unit_kind();
      UnitKind *get_last_unit_kind();
      void create_unit_instance(UnitKind *unit_kind, Point3D position, double rotation);
      Engine *get_engine();
      void update(double dt);

      static const double SIZE_X;
      static const double SIZE_Y;
    protected:
      std::vector<UnitKind> unit_kinds;
      std::vector<UnitInstance *> units;
      Engine *engine;
  };

#endif
