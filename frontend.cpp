#include "general.hpp"
#include "frontend.hpp"
#include "engine.hpp"
#include "world.hpp"

Frontend::Frontend()
  {
    terminal_print("initializing frontend...");
    this->previous_time = 0;

    this->engine = engine;

    this->irr_device = createDevice(EDT_OPENGL,dimension2d<u32>(1024,768),16,false,false,false,0);

    if (!this->irr_device)
      {
        terminal_print("error: could not create device");
      }

    this->irr_driver = this->irr_device->getVideoDriver();
    this->irr_scene = this->irr_device->getSceneManager();
    this->irr_gui = this->irr_device->getGUIEnvironment();

    this->reset_scene();      
  }

void Frontend::reset_scene()
  {
    this->irr_scene->clear();

    SKeyMap controls[] =
      {
        SKeyMap(EKA_MOVE_FORWARD,KEY_KEY_W),
        SKeyMap(EKA_MOVE_BACKWARD,KEY_KEY_S),
        SKeyMap(EKA_STRAFE_LEFT,KEY_KEY_A),
        SKeyMap(EKA_STRAFE_RIGHT,KEY_KEY_D)
      };

    this->terrain_node = this->irr_scene->addTerrainSceneNode("heightmap.png",0,-1,vector3df(0,0,0),vector3df(0,0,0),
      vector3df(Battlefield::SIZE_X / 128.0,1,Battlefield::SIZE_Y / 128.0)); 

    this->camera = this->irr_scene->addCameraSceneNodeFPS(0,100,0.5,-1,controls,sizeof(controls) / sizeof(SKeyMap),false,0);
    this->light_node = this->irr_scene->addLightSceneNode();

    this->light_node->setPosition(vector3df(0,200,0));

    this->camera->setPosition(vector3df(-119.793,100.996,-40.3278));
    this->camera->setRotation(vector3df(27.5347,55.3319,0));
  }

int Frontend::create_unit_node(UnitInstance *unit_instance)
  {
    NodeUnitPair pair;

    pair.node = this->irr_scene->addCubeSceneNode();
    pair.unit_instance = unit_instance;

    this->unit_nodes.push_back(pair);

    return this->unit_nodes.size() - 1;
  }

void Frontend::setEngine(Engine *engine)
  {
    this->engine = engine;
  }

double Frontend::get_terrain_height(double x, double y)
  {
    return this->terrain_node->getHeight(x,y);
  }

void Frontend::run()
  {
    terminal_print("running frontend...");

    while (this->irr_device->run())  // main loop
      {
        #if PRINT_CAMERA
        std::cout << "camera:" << std::endl;
        print_vector3d(this->camera->getPosition());
        print_vector3d(this->camera->getRotation());
        #endif

        for (int i = 0; i < (int) this->unit_nodes.size(); i++)
          {
            this->unit_nodes[i].node->setPosition(point3d_to_vector3d(this->unit_nodes[i].unit_instance->get_position()));
            this->unit_nodes[i].node->setRotation(vector3df(  0.0,this->unit_nodes[i].unit_instance->get_rotation(),0.0  ));
          }

        int current_time = this->irr_device->getTimer()->getTime();
        this->engine->update_world( (current_time - previous_time) / 1000.0 );

        this->previous_time = current_time;

        this->irr_driver->beginScene(true,true,SColor(255,100,101,140));
        this->irr_scene->drawAll();
        this->irr_gui->drawAll();
        this->irr_driver->endScene();
      }
  }

Frontend::~Frontend()
  {
    this->irr_device->drop();
  }

