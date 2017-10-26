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

      std::string filename;
      double model_scale;
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
      UnitKind *get_kind();

      void action_run_forward();       ///< Makes the unit move forward with collisions.
      void action_turn(bool right);
      void action_attack(double distance=0.0);  ///< Performs attack forward (distance only has effect for ranged attack type).

      bool can_attack();               ///< Check if cooldown allows attack to be performed;

      double get_radius();

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

      double attack_cooldown;

      bool action_run_performed;      ///< whether run action was performed in this cycle
      bool action_turn_performed;
      bool action_attack_performed;

      AI *ai;
      double current_dt;
      void handle_collisions();
  };

typedef std::set<UnitInstance *> SubdivisionCell;

class Battlefield
  {
    public:
      Battlefield(Engine *engine);
      ~Battlefield();
      void create_unit_kind();
      UnitKind *get_unit_kind(int index);
      void create_unit_instance(UnitKind *unit_kind, Point3D position, double rotation);
      Engine *get_engine();
      void update(double dt);

      /// Unit instances have to call this to keep the grid updated.
      void unit_transitions_grid_cells(UnitInstance *unit_instance, int x_from, int y_from, int x_to, int y_to); 
      SubdivisionCell *get_cell(int x, int y);

      static const double SIZE_X;
      static const double SIZE_Y;
      static const double CELL_SIZE_X;
      static const double CELL_SIZE_Y;
    protected:
      std::vector<UnitKind *> unit_kinds;
      std::vector<UnitInstance *> units;
      Engine *engine;

      SubdivisionCell grid[SUBDIVISION_CELLS_X][SUBDIVISION_CELLS_Y];     ///< Battlefield subdivision to accelerate collisions etc.

      void remove_unit_from_cell(UnitInstance *unit_instance, int x, int y);       ///< Removes unit pointer from given single grid cell.
      void update_grid_cell_neighbourhood(bool add, UnitInstance *unit_instance, int x, int y, int neighbour_size);
      void debug_print_grid();
  };

#endif
