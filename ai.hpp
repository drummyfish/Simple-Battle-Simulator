#ifndef AI_HPP
#define AI_HPP

#include "world.hpp"

class AI
  {
    public:
      AI(UnitInstance *unit_instance);
      virtual ~AI();

      virtual void act()=0;               ///< Make the assigned unit make actions.
      virtual void update(double dt);     ///< Update AI goals etc.

    protected:
      UnitInstance *unit_instance;
  };

class TestAI : public AI
  {
    public:
      TestAI(UnitInstance *unit_instance);

      virtual void act() override;  
      virtual void update(double dt);

    protected:
      double timer;
      int r;
  };

#endif
