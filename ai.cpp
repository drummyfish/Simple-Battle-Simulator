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
    this->unit_instance->action_turn(true);
  }

