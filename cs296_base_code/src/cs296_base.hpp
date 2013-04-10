/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#ifndef _CS296BASE_HPP_
#define _CS296BASE_HPP_

#include "render.hpp"
#include <Box2D/Box2D.h>
#include <cstdlib>

#define	RAND_LIMIT 32767

namespace cs296
{

  //! What is the difference between a class and a struct in C++? \n
  //! Members of a class are private by default and members of a struct are private by default
  class base_sim_t;
  struct settings_t;
  
  //! Why do we use a typedef?   \n
  //! 	In this context , its used to give a different alias for a data type . Its also used to declare a general data type ,when we intend a  	  block of code/function to be used for many data types. 
  typedef base_sim_t* sim_create_fcn(); 

  //! Simulation settings. Some can be controlled in the GUI.
/**
//center of simulation is set to (0,20) absolute position. \n
    \a  hz(60.0f),                     : frequency of stepping set to 60\n
    \a  velocity_iterations(8),        : No of velocity_iterations set to 8 \n
    \a  position_iterations(3),        : No of position-iterations set to 3 \n
    \a  draw_shapes(1),                : enable drawing of shapes \n
    \a  draw_joints(1),                : enable drawing of joints \n
    \a  draw_AABBs(0),                 : enable drawing of AABB's \n
    \a  draw_pairs(0),                 : disable drawing of pairs \n
    \a draw_contact_points(0),         : disable drawing of contact points \n
    \a  draw_contact_normals(0),       : disable drawing of contact normals \n
    \a  draw_contact_forces(0),        : disable drawing of contact forces \n
    \a draw_friction_forces(0),        : disable drawing of friction forces \n
    \a  draw_COMs(0),                  : disable drawing of \n
    \a  draw_stats(0),                 : disable drawing of stats \n
    \a draw_profile(0),                : disable drawing of profile \n
    \a  enable_warm_starting(1),       : enable \n
    \a  enable_continuous(1),          : enable \n
    \a enable_sub_stepping(0),         : enable sub_stepping \n
    \a  pause(0),                      : disable pause \n
    \a  single_step(0)                 : disable single_step \n



    \a struct sim_t                   : creates the simulation world and starts the simulation 
 

    \a struct contact_point_t         : stores the information(such as normal , position etc) relating to a contact point between two fixtures.


   \a  virtual void step(settings_t* settings) : Callback function for the step button  \n \n
   \a  virtual void keyboard(unsigned char key) : Not of much significance \n \n
   \a  virtual void keyboard_up(unsigned char key) : Not of much significance  \n \n
   \a  void shift_mouse_down(const b2Vec2& p): Not of much significance  \n \n
   \a  virtual void mouse_down(const b2Vec2& p) : Not of much significance \n \n
   \a  virtual void mouse_up(const b2Vec2& p) : Not of much significance \n \n
   \a void mouse_move(const b2Vec2& p) : Not of much significance \n \n
   \a virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold) : callback function when two bodies are about to collide.


   
*/

  struct settings_t
  {
    //! Notice the initialization of the class members in the constructor
    //! How is this happening?
    settings_t() :
      view_center(0.0f, 20.0f),      //!center of simulation is set to (0,20) absolute position.
      hz(60.0f),                     //!sets the frequency of the simulation to 60
      velocity_iterations(8),        //!No of velocity_iterations set to 8
      position_iterations(3),        //!No of position-iterations set to 3
      draw_shapes(1),                //!enable drawing of shapes 
      draw_joints(1),                //!enable drawing of joints 
      draw_AABBs(0),                 //!enable drawing of AABB's
      draw_pairs(0),                 //!disable drawing of pairs
      draw_contact_points(0),        //!disable drawing of contact points
      draw_contact_normals(0),       //!disable drawing of contact normals
      draw_contact_forces(0),        //!disable drawing of contact forces
      draw_friction_forces(0),       //!disable drawing of friction forces
      draw_COMs(0),                  //!disable drawing of 
      draw_stats(0),                 //!disable drawing of stats
      draw_profile(0),               //!disable drawing of profile
      enable_warm_starting(1),       //!enable 
      enable_continuous(1),          //!enable
      enable_sub_stepping(0),        //!enable sub_stepping
      pause(0),                      //!disable pause
      single_step(0)                 //!disable single_step
    {}
    
    b2Vec2 view_center;              //!<center of simulation - absolute position.
    float32 hz;                      //!<frequency of stepping
    int32 velocity_iterations;       //!<No of velocity iterations 
    int32 position_iterations;       //!<No of position iterations   
    int32 draw_shapes;               //!< disable/enable drawing of shapes   
    int32 draw_joints;               //!< disable/enable drawing of joints 
    int32 draw_AABBs;	             //!< disable/enable drawing of AABB's
    int32 draw_pairs;                //!< disable/enable drawing of pairs
    int32 draw_contact_points;       //!< disable/enable drawing of contact points
    int32 draw_contact_normals;      //!< disable/enable drawing of contact normals
    int32 draw_contact_forces;       //!< disable/enable drawing of contact forces
    int32 draw_friction_forces;      //!< disable/enable drawing of  frictional forces
    int32 draw_COMs;                 //!< disable/enable drawing of Centre of Mass         
    int32 draw_stats;                //!< disable/enable drawing of stats
    int32 draw_profile;              //!< disable/enable drawing of profile 
    int32 enable_warm_starting;      //!< disable/enable drawing of warm_starting
    int32 enable_continuous;         //!< disable/enable drawing of continous
    int32 enable_sub_stepping;       //!< disable/enable drawing of sub-stepping
    int32 pause;                     //!< disable/enable drawing of pause
    int32 single_step;               //!< disable/enable drawing of single step
  };
  

//! \a struct sim_t                   : creates the simulation world and starts the simulation 

  struct sim_t
  {
    const char *name;            //!< name of the simulation world
    sim_create_fcn *create_fcn;

    sim_t(const char *_name, sim_create_fcn *_create_fcn): 
      name(_name), create_fcn(_create_fcn) {;}
  };
  
  extern sim_t *sim;
  
  
  const int32 k_max_contact_points = 2048;  
  
//!  \a struct contact_point_t         : stores the information(such as normal , position etc) relating to a contact point between two fixtures.
struct contact_point_t
  {
    b2Fixture* fixtureA;            
    b2Fixture* fixtureB;
    b2Vec2 normal;
    b2Vec2 position;
    b2PointState state;
  };
  
  class base_sim_t : public b2ContactListener
  {
  public:
    
    base_sim_t();

    //! Virtual destructors - amazing objects. Why are these necessary? \n
    //! Virtual destructors are useful when we have to delete an object of a class through a pointer. If we don't use virtual destructors , 
    //! the memory alloted for the object never gets deallocated.
    virtual ~base_sim_t();
    
    
    inline b2World* get_world(void){ return m_world;} 
    
    
    void set_text_line(int32 line) { m_text_line = line; }
    void draw_title(int x, int y, const char *string);
    //! callback function of the step button
    virtual void step(settings_t* settings);
    //! This function is not being used.
    virtual void keyboard(unsigned char key) { B2_NOT_USED(key); }
    //! This function is not being used.
    virtual void keyboard_up(unsigned char key) { B2_NOT_USED(key); }
    //! This function is not being used.
    void shift_mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    //! This function is not being used.
    virtual void mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    //! This function is not being used.  
    virtual void mouse_up(const b2Vec2& p) { B2_NOT_USED(p); }
    //! This function is not being used.
    void mouse_move(const b2Vec2& p) { B2_NOT_USED(p); }

    //! This function is not being used.
    // Let derived tests know that a joint was destroyed.
    virtual void joint_destroyed(b2Joint* joint) { B2_NOT_USED(joint); }
    
    // Callbacks for derived classes.
    //! This function is not being used.
    virtual void begin_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    //! This function is not being used.
    virtual void end_contact(b2Contact* contact) { B2_NOT_USED(contact); }
    //! This function is not being used.
    virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold);
    //! callback function when two bodies are about to collide
    virtual void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
      B2_NOT_USED(contact);
      B2_NOT_USED(impulse);
    }

  //!How are protected members different from private memebers of a class in C++ ?
  //!Private members are accessible nowhere outside the class , but a protected member is accessible from within a derieved class
  protected:

    //! What are Friend classes? \n
    //! A Friend class of a class can access the private and protected members of the class
    friend class contact_listener_t;
    
    b2Body* m_ground_body;
    b2AABB m_world_AABB;//!
    contact_point_t m_points[k_max_contact_points];
    int32 m_point_count;

    debug_draw_t m_debug_draw;
    int32 m_text_line;
    b2World* m_world;

    int32 m_step_count;
    
    b2Profile m_max_profile;
    b2Profile m_total_profile;
  };
}

#endif
