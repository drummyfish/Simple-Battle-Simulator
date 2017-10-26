#include "engine.hpp"
#include "world.hpp"

Engine::Engine(Frontend *frontend)
  {
    terminal_print("initializing engine...");
    this->frontend = frontend;
    frontend->set_engine(this);

    this->battlefield = NULL;

    

    // TMP: setup test battlefield

    this->battlefield = new Battlefield(this);

    this->battlefield->create_unit_kind();
    UnitKind *unit_kind = this->battlefield->get_unit_kind(0);
    unit_kind->filename = "testunit";

    this->battlefield->create_unit_kind();
    UnitKind *unit_kind2 = this->battlefield->get_unit_kind(1);
    unit_kind2->filename = "testunit";
    unit_kind2->model_scale = 2.0;
    unit_kind2->radius *= 2;

    bool flag = false;

    for (int y = 0; y < 30; y++)
      for (int x = 0; x < 20; x++)
        {
          this->battlefield->create_unit_instance( flag ? unit_kind : unit_kind2 ,Point3D(x * 20 + 100,y * 20.0 + 100,0.0),0.0);
          flag = !flag;
        }
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
