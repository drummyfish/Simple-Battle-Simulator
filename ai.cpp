#include "ai.hpp"


AI::AI(UnitInstance *unit_instance)
  {
    this->unit_instance = unit_instance;
  }

AI::~AI()
  {
  }

void AI::update(double dt)
  {
  }

TestAI::TestAI(UnitInstance *unit_instance): AI(unit_instance)
  {
    this->timer = 1.0;
    this->r = 0;
  }

void TestAI::update(double dt)
  {
    this->timer -= dt;
  }

void TestAI::act()
  {
    if (this->timer < 0.0)
      {
        this->r = rand() % 10;
        this->timer = (rand() % 2000) / 1000.0;
      }

    if (r < 3)
      this->unit_instance->action_run_forward();
    else if (r < 6)
      this->unit_instance->action_attack();

    if (r > 7)
      this->unit_instance->action_turn(r > 8);
  }

