#include "general.hpp"
#include "engine.hpp"
#include "frontend.hpp"

int main()
  {
    terminal_print("starting...");
    Frontend frontend;
    Engine engine(&frontend);
    engine.run();
    terminal_print("quitting...");
    return 0;
  }

