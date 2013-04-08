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
			b2FixtureDef gfd;
			//gfd.restitution=0.0f;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 10.0f);
    }
      
    //The revolving horizontal platform
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.3f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(-46.0f, 21.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 30.0f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(-46.0f, 31.0f);
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
    //ball on the above horizontal shelf
      
      {
			b2Body* b4;	  
			b2PolygonShape shape;
			//shape.SetAsBox(0.25f, 0.25f);
			b2CircleShape circle;
			b2FixtureDef ballfd;
   		ballfd.shape = &circle; 
	
		  circle.m_radius = 1.0;
		  ballfd.density = 10.0f;
		  ballfd.friction = 0.0f;
		  ballfd.restitution = 0.0f;
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-44.5f, 33.0f);
			b4 = m_world->CreateBody(&bd);
			b4->CreateFixture(&ballfd);

      }
    
    		//Curves
  b2Body * Curve;
        b2EdgeShape shapes[12];
        b2BodyDef shapebd[12];
        b2FixtureDef shapefd[12];

        float32 x_Cent = -23.5f;
        float32 y_Cent = 34.0f;
        float32 radius = 16;
        for(int i = 0 ; i < 8 ; i++){
          shapes[i].Set(b2Vec2( x_Cent+radius*sin(b2_pi+i*b2_pi/20.0) , y_Cent + radius*cos(b2_pi+i*b2_pi/20.0)) , b2Vec2( x_Cent+radius*sin(b2_pi+(i+1)*b2_pi/20.0) , y_Cent + radius*cos(b2_pi+(i+1)*b2_pi/20.0)));
          shapefd[i].friction = 0;
          shapefd[i].shape = &shapes[i];
          shapefd[i].restitution = 1;
          Curve = m_world->CreateBody(&shapebd[i]);
          Curve->CreateFixture(&shapefd[i]);
        }
        b2Body * Curve2;
        b2EdgeShape shapes2[12];
        b2BodyDef shapebd2[12];
        b2FixtureDef shapefixd2[12];

        float32 x_Cent2 = -44.25f;
        float32 y_Cent2 = 26.5f;
        float32 radius2 = 6;
        for(int i = 0 ; i < 9 ; i++){
          shapes2[i].Set(b2Vec2( x_Cent2+radius2*sin(0+i*b2_pi/25.0) , y_Cent2 + radius2*cos(0+i*b2_pi/25.0)) , b2Vec2( x_Cent2+radius2*sin(0+(i+1)*b2_pi/25.0) , y_Cent2 + radius2*cos(0+(i+1)*b2_pi/25.0)));
          shapefixd2[i].friction = 0;
          shapefixd2[i].shape = &shapes2[i];
          shapefixd2[i].restitution = 1;
          Curve2 = m_world->CreateBody(&shapebd2[i]);
          Curve2->CreateFixture(&shapefixd2[i]);
        }
  			b2Body *smallEdge;
  			b2EdgeShape shapes3;
  			b2BodyDef shapebd3;
  			b2FixtureDef shapefixd3;
  			shapes3.Set(b2Vec2( -44.25f , 32.5f) , b2Vec2( -45.25f , 32.5f));
  			shapefixd3.friction = 0;
        shapefixd3.shape = &shapes3;
        shapefixd3.restitution = 1;
       	smallEdge = m_world->CreateBody(&shapebd3);
        smallEdge->CreateFixture(&shapefixd3);
  //--------------------------------------------------------------------------//
    
    
  //---------------pendulums------------------------------------------------// 
   //  pendulum 1

    {
      b2Body* b2;

				b2PolygonShape shape;
				shape.SetAsBox(6.0f, .5f);
			
				b2BodyDef bd;

				bd.position.Set(-22.5f, 28.0f);
				b2 = m_world->CreateBody(&bd);
				b2->CreateFixture(&shape, 10.0f);
	

      b2Body* b4;
       
				//b2PolygonShape shapeC[4];
				//shape.SetAsBox(0.25f, 0.25f);
				b2CircleShape circleC[5];
				b2FixtureDef ballfdC[5];
				b2BodyDef bdC[5];
				for(int i=0; i<5;i++){
				ballfdC[i].shape = &circleC[i]; 
	
				circleC[i].m_radius = .80f;
				ballfdC[i].density = 5.0f;
				ballfdC[i].friction = 0.0f;
				ballfdC[i].restitution = 0.0f;
				
				bdC[i].type = b2_dynamicBody;
				bdC[i].position.Set(-26.5f+i*1.9f, 20.2f);
				b4 = m_world->CreateBody(&bdC[i]);
				b4->CreateFixture(&ballfdC[i]);
				b2RevoluteJointDef jd;
		   
		    b2Vec2 anchor;
		    anchor.Set(-26.5f+i*1.9f, 28.0f);

		    jd.Initialize(b2, b4, anchor);
		    m_world->CreateJoint(&jd);
		  }
    }
   
  
  
  
   //pendulum 2
   /* {
      b2Body* b2;

      {
				b2PolygonShape shape;
				shape.SetAsBox(1.0f, .5f);
			
				b2BodyDef bd;
	

				bd.position.Set(-20.5f, 28.0f);
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
			ballfd.density = 5.0f;
			ballfd.friction = 0.0f;
			ballfd.restitution = 0.0f;
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(-20.5f, 19.0f);
			b4 = m_world->CreateBody(&bd);
			b4->CreateFixture(&ballfd);
    }

			b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(-20.5f, 28.0f);

      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
		}
	*/
	
	
   
		{
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, .25f);
	
      b2BodyDef bd;
      bd.position.Set(-12.0f, 16.25f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
  	}

//Dominos
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.2f, 2.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 30.0f;
      fd.friction = 0.3f;
		
      for (int i = 0; i < 6; ++i)
	{
	  b2BodyDef bd;
	  bd.type = b2_dynamicBody;
	  bd.position.Set(-15.5f + 1.0f * i, 18.25f);
	  b2Body* body = m_world->CreateBody(&bd);
	  body->CreateFixture(&fd);
	}
  }


//ball after dominos
  {
		b2Body* b4;	  
		b2PolygonShape shape;
		//shape.SetAsBox(0.25f, 0.25f);
		b2CircleShape circle;
		b2FixtureDef ballfd;
    ballfd.shape = &circle; 
	
    circle.m_radius = 1.0;
    ballfd.density = 20.0f;
    ballfd.friction = 0.0f;
		ballfd.restitution = 0.0f;
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.position.Set(-8.2f, 16.75f);
		b4 = m_world->CreateBody(&bd);
		b4->CreateFixture(&ballfd);

 }

		//The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(10,15);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,1, b2Vec2(2.0f,-1.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,1, b2Vec2(-2.0f,-1.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(25,15);	
      fd1->density = 20.50;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(25, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(10, 20); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(25, 20); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }


	//The see-saw system at the bottom
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,3.0);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(10.0f, 0.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(10.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(10.0f, 3.0f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
			fd2->friction=.5f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(10.0f, 3.0f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      b2PolygonShape shape2;
      shape2.SetAsBox(1.0f, 1.0f);
      b2BodyDef bd3;
      bd3.position.Set(18.0f, 3.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 5.0f;
			fd3->friction=.4f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }
		//The see-saw system at the top 
    {
      //The triangle wedge
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,3.0);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(30.0f, 17.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      //The plank on top of the wedge
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.2f);
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 20.0f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
			fd2->friction=.5f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);

      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.0f, 20.0f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);

      //The light box on the right side of the see-saw
      /*b2PolygonShape shape2;
      shape2.SetAsBox(1.0f, 1.0f);
      b2BodyDef bd3;
      bd3.position.Set(34.0f, 28.0f);
      bd3.type = b2_dynamicBody;
      b2Body* body3 = m_world->CreateBody(&bd3);
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 3.0f;
			fd3->friction=.4f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);*/
			
			
			//The light box on the left side of the see-saw
  		b2PolygonShape shape3;
      shape3.SetAsBox(1.0f, 1.0f);
      b2BodyDef bd4;
      bd4.position.Set(25.98f, 21.0f);
      bd4.type = b2_dynamicBody;
      b2Body* body4 = m_world->CreateBody(&bd4);
      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 21.0f;
			fd4->friction=.4f;
      fd4->shape = new b2PolygonShape;
      fd4->shape = &shape3;
      body4->CreateFixture(fd4);
    }
    {
      

      
      	b2Body* b2;
				b2PolygonShape shape;
				shape.SetAsBox(1.0f, .5f);
			
				b2BodyDef bd1;
	

				bd1.position.Set(45.5f, 40.0f);
				b2 = m_world->CreateBody(&bd1);
				b2->CreateFixture(&shape, 10.0f);
      
      
    	b2Body* box1;
    
    	b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(35,25.0);
      //bd->fixedRotation = true;
		 	b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 1.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.05, b2Vec2(0.f,4.0f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.05,4, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 1.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.05,4, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
      b2FixtureDef *fd4 = new b2FixtureDef;
      fd4->density = 1.0;
      fd4->friction = 0.5;
      fd4->restitution = 0.f;
      fd4->shape = new b2PolygonShape;
      b2PolygonShape bs4;
      bs4.SetAsBox(0.05,.5, b2Vec2(2.0f,-4.0f), .75f*b2_pi);
      fd4->shape = &bs4;
      b2FixtureDef *fd5 = new b2FixtureDef;
      fd5->density = 1.0;
      fd5->friction = 0.5;
      fd5->restitution = 0.f;
      fd5->shape = new b2PolygonShape;
      b2PolygonShape bs5;
      bs5.SetAsBox(0.05,.5, b2Vec2(-2.0f,-4.0f),1.25f*b2_pi);
      fd5->shape = &bs5;
      bd->angle=-0.20f*b2_pi;
      box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);
      box1->CreateFixture(fd4);
      box1->CreateFixture(fd5);
			b2Body* b3;
			b2PolygonShape shape1;
			shape1.SetAsBox(.05f, 2.0f);
			
			b2BodyDef bd3;
	
			bd3.type = b2_dynamicBody;
			bd3.position.Set(box1->GetWorldCenter().x-3.0f,box1->GetWorldCenter().y-4.0f);
			bd3.angle=0.30f*b2_pi;
			b3 = m_world->CreateBody(&bd3);
			b2FixtureDef *fd6 = new b2FixtureDef;
      fd6->density = 1.0;
      fd6->friction = 0.5;
      fd6->restitution = 0.f;
      fd6->shape=&shape1;
			b3->CreateFixture(fd6);
			
			b2RevoluteJointDef jointDef;
      jointDef.bodyA = box1;
      jointDef.bodyB = b3;
      jointDef.localAnchorA.Set(-2.0f,-4.50f);
      jointDef.localAnchorB.Set(-0.18f,2.23f);
      
			jointDef.upperAngle = 0.5f * b2_pi;
			jointDef.enableLimit = true;
      jointDef.enableMotor = true;
      jointDef.maxMotorTorque = 1000.0f;
			jointDef.motorSpeed = 4.0f;
      jointDef.collideConnected =false;
      m_world->CreateJoint(&jointDef);
      
      
      b2Body * Circle;
      b2CircleShape circle[20];
      b2BodyDef shapebd2[20];
     	b2FixtureDef shapefixd2[20];
     	for(int i=0;i<3;i++)
     	{
     		//b2CircleShape circle;
     		
	
				circle[i].m_radius = 1.20f;
				shapefixd2[i].shape = &circle[i]; 
     		shapefixd2[i].friction = 0;      
        shapefixd2[i].restitution = 0;
        shapefixd2[i].density = 4.0f;
        
        shapebd2[i].type = b2_dynamicBody;
				shapebd2[i].position.Set(box1->GetWorldCenter().x-i*0.001f,box1->GetWorldCenter().y+i*.005f);
        Circle = m_world->CreateBody(&shapebd2[i]);
        Circle->CreateFixture(&shapefixd2[i]);
     	}
		    b2RevoluteJointDef jd;
		    b2Vec2 anchor;
		    anchor.Set(45.0f, 40.0f);

		    jd.Initialize(b2, box1, anchor);
		    m_world->CreateJoint(&jd);
		    
    }
    //The pulley system
    {
    
    	b2Body * head;
    	b2BodyDef headbd;
    	headbd.type = b2_dynamicBody;
    	b2CircleShape headC;
    	headC.m_radius = 1.0f;
    	b2PolygonShape headB;
    	headB.SetAsBox(3 , 0.2f ,b2Vec2(-2 , 0) , 0);
    	b2FixtureDef headBfd;
    	b2FixtureDef headCfd;
    	headBfd.shape = &headB;
    	headCfd.shape = &headC;
    	headBfd.density = 10.0;
    	headCfd.density = 10.0f;
    	headbd.position.Set(75 , 2);
    	head = m_world->CreateBody(&headbd);
    	head->CreateFixture(&headBfd);
    	head->CreateFixture(&headCfd);
    	
    	b2Body * body2;
    	b2PolygonShape fake;
    	fake.SetAsBox(0.2,0.2);
    	b2BodyDef body2bd;
    	body2bd.position.Set(70,  2);
    	body2 = m_world->CreateBody(&body2bd);
    	body2->CreateFixture(&fake , 0);
    	
    	
    	b2Body * LowerP;
    	b2BodyDef Lowerbd;
    	headbd.type = b2_dynamicBody;
    	b2PolygonShape LegS;
    	b2PolygonShape FeetS;
    	LegS.SetAsBox(2 , 0.2f ,b2Vec2(0 , 0) , 0);
    	FeetS.SetAsBox(.2f , .5f ,b2Vec2(-2 , .5) , 0);
    	b2FixtureDef Legfd;
    	b2FixtureDef Feetfd;
    	Legfd.shape=&LegS;
    	Feetfd.shape=&FeetS;
    	Legfd.density=1.0f;
    	Feetfd.density=1.0f;
    	Lowerbd.position.Set(68.5,2);
    	LowerP=m_world->CreateBody(&Lowerbd);
    	LowerP->CreateFixture(&Legfd);
    	LowerP->CreateFixture(&Feetfd);
    	
    	
    	b2RevoluteJointDef jd;
    	b2Vec2 anchor;
    	anchor.Set(70 , 2);
    	jd.Initialize(head , body2 , anchor);
    	m_world->CreateJoint(&jd);
    	
    	
    	
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
     	bd->position.Set(50,10);
      bd->fixedRotation = true;
    /*  b2FixtureDef *fixd=new b2FixtureDef;
      b2CircleShape circle;
      fixd->shape=&circle;
      circle.m_radius=1.0f;
      b2BodyDef *bd2 = new b2BodyDef;
      bd2->type = b2_dynamicBody;
      b2PolygonShape bshape;
      bshape.SetAsBox(3.0f,.10f);
      bd2->position.Set(72.5f, 0.5f);
      b2FixtureDef *fixd1 = new b2FixtureDef;
      fixd1->shape=&bshape;
      b2Body *bod2 = m_world->CreateBody(bd2);*/

      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.1,3, b2Vec2(3.0f,-0.f),-.25*b2_pi);
      fd2->shape = &bs2;
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.1,3, b2Vec2(-3.0f,-0.f),.25*b2_pi);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

   
			
			
			
			
      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(50, 10); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(75, 2); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(50, 14); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(65, 14); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, head, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), head->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

	}
    
  

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
