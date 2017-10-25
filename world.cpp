#include "world.hpp"
#include "engine.hpp"

const double Battlefield::SIZE_X = 1000.0;
const double Battlefield::SIZE_Y = 1000.0;

UnitKind::UnitKind()
  {
    this->health_max = 100;
    this->attack = 1;
    this->attack_speed = 1.0;
    this->movement_speed = 1.0;
    this->radius = 1.0;
    this->height = 1.0;
  }

void UnitInstance::update(double dt)
  {
    this->position.z = this->frontend->get_terrain_height(this->position.x,this->position.y);
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
  }

void UnitInstance::set_position(Point3D new_position)
  {
    this->position = new_position;
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

