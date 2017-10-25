#include "world.hpp"
#include "engine.hpp"
#include "ai.hpp"

const double Battlefield::SIZE_X = 1000.0;
const double Battlefield::SIZE_Y = 1000.0;

UnitKind::UnitKind()
  {
    this->health_max = 100;
    this->attack = 1;
    this->attack_speed = 0.3;
    this->movement_speed = 5.0;
    this->rotation_speed = 1.0;
    this->radius = 1.0;
    this->height = 1.0;
  }

void UnitInstance::update(double dt)
  {
    this->current_dt = dt;

    this->attack_cooldown -= dt;

    this->position.z = this->frontend->get_terrain_height(this->position.x,this->position.y);
    
    this->action_run_performed = false;
    this->action_turn_performed = false;
    this->action_attack_performed = false;

    this->ai->update(dt);
    this->ai->act();

    if ( !this->action_run_performed && !this->action_turn_performed && !this->action_attack_performed && this->can_attack() )
      this->frontend->set_unit_node_animation(this->node_handle,ANIMATION_IDLE);
  }

void UnitInstance::action_run_forward()
  {
    if (this->action_run_performed || this->action_attack_performed)
      return;

    double distance = this->current_dt * this->kind->movement_speed;

    this->set_position(Point3D(
      this->position.x + distance * sin(deg_to_rad(this->rotation)),
      this->position.y + distance * cos(deg_to_rad(this->rotation)),
      this->position.z));

    this->frontend->set_unit_node_animation(this->node_handle,ANIMATION_RUN);

    this->action_run_performed = true;
  }

void UnitInstance::action_turn(bool right)
  {
    if (this->action_turn_performed)
      return;

    double sign = right ? 1.0 : -1.0;

    this->rotation += sign * this->current_dt * this->kind->rotation_speed * 360.0;

    this->frontend->set_unit_node_animation(this->node_handle,ANIMATION_RUN);

    this->action_turn_performed = true;
  }

void UnitInstance::action_attack(double distance)
  {
    if (this->action_attack_performed || this->action_run_performed || !this->can_attack())
      return;

    this->frontend->set_unit_node_animation(this->node_handle,ANIMATION_ATTACK);

    this->attack_cooldown = 1.0 / this->kind->attack_speed;

    this->action_attack_performed = true;
  }

bool UnitInstance::can_attack()
  {
    return this->attack_cooldown <= 0.0;
  }

UnitInstance::UnitInstance(UnitKind *kind, Battlefield *battlefield)
  {
    this->kind = kind;
    this->position = Point3D(0,0,0);
    this->grid_x = -1;                // -1 will force update
    this->grid_y = -1;
    this->rotation = 0;
    this->health_current = this->kind->health_max;
    this->team = 0;

    this->attack_cooldown = -1.0;

    this->battlefield = battlefield;
    this->engine = battlefield->get_engine();
    this->frontend = this->engine->get_frontend();

    this->node_handle = this->frontend->create_unit_node(this);

    this->action_run_performed = false;
    this->action_turn_performed = false;
    this->action_attack_performed = false;

    this->ai = new TestAI(this);
  }

UnitInstance::~UnitInstance()
  {
    delete this->ai;
  }

void UnitInstance::set_position(Point3D new_position)
  {
    int previous_grid_x = this->grid_x;
    int previous_grid_y = this->grid_y;

    this->position = new_position;

    this->grid_x = this->position.x / SUBDIVISION_CELLS_X;
    this->grid_y = this->position.y / SUBDIVISION_CELLS_Y;

    if (this->grid_x != previous_grid_x || this->grid_y != previous_grid_y)
      this->battlefield->unit_transitions_grid_cells(this,previous_grid_x,previous_grid_y,this->grid_x,this->grid_y); 

    this->position.x = saturate(this->position.x,0,Battlefield::SIZE_X);
    this->position.y = saturate(this->position.y,0,Battlefield::SIZE_Y);
  }

Point3D UnitInstance::get_position()
  {
    return this->position;
  }

double UnitInstance::get_rotation()
  {
    return this->rotation;
  }

void UnitInstance::set_rotation(double new_rotation)
  {
    this->rotation = new_rotation;
  }

Battlefield::Battlefield(Engine *engine)
  {
    this->engine = engine;
  }

Engine *Battlefield::get_engine()
  {
    return this->engine;
  }

void Battlefield::create_unit_kind()
  {
    UnitKind new_unit_kind;
    this->unit_kinds.push_back(new_unit_kind);
  }

void Battlefield::create_unit_instance(UnitKind *unit_kind, Point3D position, double rotation)
  {
    this->units.push_back(new UnitInstance(unit_kind,this));

    this->units.back()->set_position(position);  
    this->units.back()->set_rotation(rotation);  
  }

Battlefield::~Battlefield()
  {
    for (int i = 0; i < (int) this->units.size(); i++)
      delete this->units[i];
  }

UnitKind *Battlefield::get_last_unit_kind()
  {
    if (this->unit_kinds.size() == 0)
      return NULL;

    return &(this->unit_kinds.back());
  }

void Battlefield::debug_print_grid()
  {
    for (int y = 0; y < SUBDIVISION_CELLS_Y; y++)
      {
        for (int x = 0; x < SUBDIVISION_CELLS_X; x++)
          std::cout << this->grid[x][y].size() << " ";

        std::cout << "\n";
      }

    std::cout << "-----------------" << std::endl;
  }

void Battlefield::update(double dt)
  {
    for (int i = 0; i < (int) this->units.size(); i++)
      this->units[i]->update(dt);
  }

void Battlefield::unit_transitions_grid_cells(UnitInstance *unit_instance, int x_from, int y_from, int x_to, int y_to)
  {
    if (x_from >= 0 && y_from >= 0)
      {
        std::vector<UnitInstance *> *cell = &(this->grid[x_from][y_from]);

        for (int i = 0; i < cell->size(); i++)
          if ( (*cell)[i] == unit_instance )
            {
              cell->erase(cell->begin() + i);
              break;
            }
      }

    this->grid[x_to][y_to].push_back(unit_instance);
  }

