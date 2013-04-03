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


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  dominos_t::dominos_t()
  {
    //Ground
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
	
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }
      
    
    /*
    //bottom horizontal shelf
    {
      b2PolygonShape shape;
      shape.SetAsBox(8.0f, 1.0f);
	
      b2BodyDef bd;
      bd.position.Set(-32.0f, 10.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
     */
    
	//horizontal shelf which would contain a ball
    {
      b2PolygonShape shape;
      shape.SetAsBox(3.0f, .25f);
	
      b2BodyDef bd;
      bd.position.Set(-32.0f, 20.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    
    //ball on the above horizontal shelf
      
      {
	b2Body* b4;	  
	b2PolygonShape shape;
	//shape.SetAsBox(0.25f, 0.25f);
	b2CircleShape circle;
	b2FixtureDef ballfd;
    ballfd.shape = &circle; 
	
    circle.m_radius = 1.0;
    ballfd.density = 1.0f;
    ballfd.friction = 0.0f;
    ballfd.restitution = 0.0f;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-35.0f, 21.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&ballfd);

      }
    
    
    
    
     
     
	 {
      b2PolygonShape shape;
      shape.SetAsBox(3.0f, .25f);
	
      b2BodyDef bd;
      bd.position.Set(-23.5f, 16.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
    //pendulum 1
    {
      b2Body* b2;

      {
	b2PolygonShape shape;
	shape.SetAsBox(2.0f, .5f);
	  
	b2BodyDef bd;

	bd.position.Set(-23.5f, 28.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
	

      b2Body* b4;
      {
	b2PolygonShape shape;
	//shape.SetAsBox(0.25f, 0.25f);
	b2CircleShape circle;
	b2FixtureDef ballfd;
    ballfd.shape = &circle; 
	
    circle.m_radius = 1.0;
    ballfd.density = 0.7f;
    ballfd.friction = 0.0f;
    ballfd.restitution = 0.0f;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(-23.5f, 18.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&ballfd);

      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-23.5f, 28.0f);

      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }
   
  
  
  
   //pendulum 2
    {
      b2Body* b2;

      {
	b2PolygonShape shape;
	shape.SetAsBox(2.0f, .5f);
	  
	b2BodyDef bd;
	

	bd.position.Set(-19.5f, 40.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
  
	b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.1f, 4.0f);
	  
	b2BodyDef bd;
	b2FixtureDef *fd = new b2FixtureDef;
    fd->density = 2.0f;
    fd->shape = new b2PolygonShape;
    fd->shape = &shape;
	bd.type = b2_dynamicBody;
	bd.position.Set(-19.5f, 22.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(fd);
      }

	b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-19.5f, 38.0f);

      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
	}
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
    //The revolving horizontal platform
   
   
   
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(-37.0f, 18.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 20.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(-37.0f, 20.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.maxMotorTorque = 100.0f;
      jointDef.motorSpeed = 40.0f;
      jointDef.enableMotor = true;
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

   


    //The heavy sphere on the platform
   /* {
      b2Body* sbody;
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(15.0f, 18.0f);
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }*/


    /*//The see-saw system at the bottom
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }*/
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
