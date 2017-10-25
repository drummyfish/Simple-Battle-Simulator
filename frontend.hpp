#ifndef FRONTEND_HPP
#define FRONTEND_HPP

#include <irrlicht/irrlicht.h>

class UnitInstance;

#define PRINT_CAMERA 0

#define print_vector3d(v) std::cout << (v).X << " " << (v).Y << " " << (v).Z << std::endl

#define point3d_to_vector3d(p) vector3df(p.x,p.z,p.y)        // also transforms from game space (Z up) into irrlicht space (Y up)

class Engine;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

/// \brief Handle presentation (graphics, sound, ...) and input and provide abstract interface.

class Frontend
  {
    public:
      Frontend();
      virtual ~Frontend();

      void run();

      void setEngine(Engine *engine);

      void reset_scene();

      double get_terrain_height(double x, double y);

      int create_unit_node(UnitInstance *unit_instance);     ///< Create a new node for unit, return the node handle for the unit to keep.

    protected:
      typedef struct
        {
          IMeshSceneNode *node;
          UnitInstance *unit_instance;
        } NodeUnitPair;

      IrrlichtDevice *irr_device;
      IVideoDriver *irr_driver;
      IGUIEnvironment *irr_gui;
      ISceneManager *irr_scene;

      ICameraSceneNode *camera;
      ITerrainSceneNode *terrain_node;
      ILightSceneNode *light_node;

      std::vector<NodeUnitPair> unit_nodes;

      Engine *engine;
      int previous_time;
  };

#endif
