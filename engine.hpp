#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "general.hpp"
#include "frontend.hpp"
#include "world.hpp"

class Engine
  {
    public:
      Engine(Frontend *frontend);

      void run();

      void update_world(double dt);

      virtual ~Engine();

      Frontend *get_frontend();

    protected:
      Frontend *frontend;

      Battlefield *battlefield;
  };

#endif
