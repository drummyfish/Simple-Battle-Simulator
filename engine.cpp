#include "engine.hpp"
#include "world.hpp"

Engine::Engine(Frontend *frontend)
  {
    terminal_print("initializing engine...");
    this->frontend = frontend;
    frontend->setEngine(this);

    this->battlefield = NULL;

    

    // TMP: setup test battlefield

    this->battlefield = new Battlefield(this);

    this->battlefield->create_unit_kind();
    UnitKind *unit_kind = this->battlefield->get_last_unit_kind();

    for (int y = 0; y < 10; y++)
      for (int x = 0; x < 5; x++)
        this->battlefield->create_unit_instance(unit_kind,Point3D(x * 20.0,y * 20.0,0.0),0.0);
  }

void Engine::update_world(double dt)
  {
    if (!this->battlefield)
      return;

    this->battlefield->update(dt);
  }

Frontend *Engine::get_frontend()
  {
    return this->frontend;
  }

void Engine::run()
  {
    terminal_print("running engine...");
    this->frontend->run();
  }

Engine::~Engine()
  {
    if (this->battlefield)
      delete this->battlefield;
  }
