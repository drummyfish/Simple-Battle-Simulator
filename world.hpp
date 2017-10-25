#ifndef WORLD_HPP
#define WORLD_HPP

#include "general.hpp"
#include "frontend.hpp"

#define SUBDIVISION_CELLS_X 32
#define SUBDIVISION_CELLS_Y 32

class Battlefield;
class AI;

class UnitKind
  {
    public:
      UnitKind();

      std::string name;
      int health_max;
      int attack;
      double attack_speed;    ///< in hits per second
      double movement_speed;
      double rotation_speed;
      double radius;
      double height;
  };

class UnitInstance
  {
    public:
      UnitInstance(UnitKind *kind, Battlefield *battlefield);
      ~UnitInstance();

      void set_position(Point3D new_position);
      void set_rotation(double new_rotation);

      void update(double dt);

      Point3D get_position();
      double get_rotation();

      void action_run_forward();       ///< makes the unit move forward with collisions
      void action_turn(bool right);
      void action_attack(UnitInstance *enemy);

    protected:
      Point3D position;
      int grid_x;
      int grid_y;

      double rotation;       ///< in degrees
      UnitKind *kind;
      int health_current;
      int team;
      int node_handle;

      Battlefield *battlefield;
      Engine *engine;
      Frontend *frontend;

      bool action_run_performed;      ///< whether run action was performed in this cycle
      bool action_turn_performed;
      bool action_attack_performed;

      AI *ai;
      double current_dt;
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

      /// Unit instances have to call this to keep the grid updated.
      void unit_transitions_grid_cells(UnitInstance *unit_instance, int x_from, int y_from, int x_to, int y_to); 

      static const double SIZE_X;
      static const double SIZE_Y;
    protected:
      std::vector<UnitKind> unit_kinds;
      std::vector<UnitInstance *> units;
      Engine *engine;

      std::vector<UnitInstance *> grid[SUBDIVISION_CELLS_X][SUBDIVISION_CELLS_Y];    ///< Battlefield subdivision to accelerate collisions etc.

      void debug_print_grid();
  };

#endif
