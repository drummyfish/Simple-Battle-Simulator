#ifndef FRONTEND_HPP
#define FRONTEND_HPP

#include <irrlicht/irrlicht.h>

class UnitInstance;

#define PRINT_CAMERA 0

#define print_vector3d(v) std::cout << (v).X << " " << (v).Y << " " << (v).Z << std::endl
#define point3d_to_vector3d(p) vector3df(p.y,p.z,p.x)        // also transforms from game space (Z up) into irrlicht space (Y up)

class Engine;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

/// \brief Handle presentation (graphics, sound, ...) and input and provide abstract interface.

typedef enum
  {
    ANIMATION_IDLE=0,
    ANIMATION_RUN,
    ANIMATION_ATTACK,
    ANIMATION_DIE
  } UnitAnimation;

class AttackAnimationEndCallback: public IAnimationEndCallBack  ///< Helper to set the animation to idle when the attack ends.
  {
    public:
      AttackAnimationEndCallback(int start_frame, int end_frame): IAnimationEndCallBack()
        {
          this->start_frame = start_frame;
          this->end_frame = end_frame;
        }

      virtual void OnAnimationEnd(IAnimatedMeshSceneNode *node)
        {
          node->setFrameLoop(this->start_frame,this->end_frame);
          node->setLoopMode(true);
          node->setAnimationEndCallback(NULL);
        }

    protected:
      int start_frame;
      int end_frame;
  };

class Frontend
  {
    public:
      Frontend();
      virtual ~Frontend();

      void run();

      void set_engine(Engine *engine);

      void reset_scene();

      double get_terrain_height(double x, double y);

      int create_unit_node(UnitInstance *unit_instance);     ///< Create a new node for unit, return the node handle for the unit to keep.
      void set_unit_node_animation(int node_handle, UnitAnimation animation);

    protected:
      const static int UNIT_ANIMATION_FRAMES;

      typedef struct
        {
          IAnimatedMeshSceneNode *node;
          UnitInstance *unit_instance;
          UnitAnimation animation;
        } NodeUnitPair;

      IrrlichtDevice *irr_device;
      IVideoDriver *irr_driver;
      IGUIEnvironment *irr_gui;
      ISceneManager *irr_scene;

      ICameraSceneNode *camera;
      ITerrainSceneNode *terrain_node;
      ILightSceneNode *light_node;

      std::vector<NodeUnitPair> unit_nodes;

      AttackAnimationEndCallback *attack_end_callback;

      Engine *engine;
      int previous_time;
  };

#endif
