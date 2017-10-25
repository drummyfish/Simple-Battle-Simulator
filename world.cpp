#include "world.hpp"
#include "engine.hpp"
#include "ai.hpp"

const double Battlefield::SIZE_X = 1000.0;
const double Battlefield::SIZE_Y = 1000.0;

UnitKind::UnitKind()
  {
    this->health_max = 100;
    this->attack = 1;
    this->attack_speed = 1.0;
    this->movement_speed = 5.0;
    this->rotation_speed = 1.0;
    this->radius = 1.0;
    this->height = 1.0;
  }

void UnitInstance::update(double dt)
  {
    this->current_dt = dt;

    this->position.z = this->frontend->get_terrain_height(this->position.x,this->position.y);
    
    this->action_run_performed = false;
    this->action_turn_performed = false;
    this->action_attack_performed = false;

    this->ai->update(dt);
    this->ai->act();

    if ( !this->action_run_performed && !this->action_turn_performed && !this->action_attack_performed)
      this->frontend->set_unit_node_animation(this->node_handle,ANIMATION_IDLE);
  }

void UnitInstance::action_run_forward()
  {
    if (this->action_run_performed)
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

void UnitInstance::action_attack(UnitInstance *enemy)
  {
    if (this->action_attack_performed)
      return;

    this->action_attack_performed = true;
  }

UnitInstance::UnitInstance(UnitKind *kind, Battlefield *battlefield)
  {
    this->kind = kind;
    this->position = Point3D(0,0,0);
    this->rotation = 0;
    this->health_current = this->kind->health_max;
    this->team = 0;

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
    this->position = new_position;

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

void Battlefield::update(double dt)
  {
    for (int i = 0; i < (int) this->units.size(); i++)
      this->units[i]->update(dt);
  }

