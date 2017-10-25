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
  }

void TestAI::act()
  {
    this->unit_instance->action_run_forward();

    int r = rand() % 10;

    if (r > 5)
      this->unit_instance->action_turn(r > 7);
  }

