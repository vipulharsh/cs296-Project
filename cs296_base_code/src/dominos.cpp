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
  
  /*!
\brief 
\b Ground \n
					
*\a b1 : An object of class b2body to hold the properties of a real life rigid body.

\a shape : An object of class b2EdgeShape to set the fixture of the Ground. Essentially a line segment from (-90,0) to (90,0) in local coordinates.

\a bd : An object of class b2BodyDef. Holds values of parameters for constructing a rigid body.

 After constructing a rigid body(b1) using a body definition(bd) , the body is given a shape(shape).\n  \n
*/
  
  
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
      
      
      
      
      
   /*!
\brief 
\b The \b revolving \b rectangular \b bar  : \b the \b clock  \n
					
*\a b1 : An object of class b2body to hold the properties of a real life rigid body.

\a shape : An object of class b2PolygonShape to set the fixture of the Ground. Essentially a rectangle  of dimensions 2.0 by 0.2.

\a bd2 : An object of class b2BodyDef. Holds values of parameters for constructing a rigid body - position (-46.0, 21.0), declared to be a dynamic body.
        
        
 After constructing a rigid body(b1) using a body definition(bd) , the body is given a shape(shape).\n  \n
*/    
      
      
      
      
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
   
   
   
   
   
    //ball on the slider
    /*!
\brief 
\b Ball \b on \b the \b slider \n
					
\a b4: An object of class b2Body, a rigid body.

\a circle :  An object of class b2CircleShape. Holds a circular shape of radius 1 unit.

\a ballfd: An object of type b2FixtureDef . Holds the fixture definitions for a body.
             Its shape is set to $circle , density  = 10.0 , friction = 0, restitution = 0.

\a bd: An object of type b2BodyDef. Holds the body definitions.
	    Position = (-44.5,33). type=  dynamic (moving) object 

*/ 
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
    







/*!
\brief 
 \b slider \n
			
\a the slider is made up of two sets of tiny line segments(one for the convex part and the other for the concave part of the slider).

\a   the centres of the first set of line segments are sort of aligned circularly in an upper arc , centered at (-23.4,34),
   seperated by 9 degrees. 
 
\a  the centres of the second set of line segments are sort of aligned cicularly in a downward arc,  centered at (-44.25,26.5),
   seperated by 7.2 degrees.	 
	 				
\a Curve: An object of class b2Body, a rigid body.


\a shapes ,shapebd , shapefd : for the first set of line segments
\a shapes2, shapebd2 , shapefd2 : for the second set of line segments


\a shapes , shapes2: Array to hold line segment shapes(of class b2EdgeShape) that constitute the slider.

\a shapebd , shapebd2: Array to hold objects  of type b2BodyDef. Holds the body definitions of each line segment. 

\a shapefd , shape fd2: Array to hold objects of type b2FixtureDef. Holds the fixture definitions of each line segment.
			 shape set to $shape[i]
			 friction of each line segment = 0
			 restitution of each line segment = 0
*/


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





/*!
\brief 
 \b Pendulums \n

\a b2: An object of class b2Body. A rigid body. Its density is set to 10. All pendulums are hinged to this body

\a shape : An object of class b2PolygonShape to hold the shape of a polygon. In this case its a box of height 0.5 and width 6 units.
           used to give shape to the rectangular block($b2) to which all pendulums are attached.

\a bd: An object of class b2BodyDef.Holds parameters for constructing a rigid body($b2).
       Its position is set to(-22.5, 28) in local coordinates.
       It is used to create the body $b2.

\a b4: An object of class b2Body. A rigid body. Its density is set to 2.used for the spheres of the pendulums.
	
\a circleC: an Array of objects of class b2CircleShape to hold the shape of the spheres of the Pendulum.
           Set to a circle of radius 0.8 units.

\a bdC: An Array of objects of class b2BodyDef.Holds parameters for constructing the spheres. 
        Its position is set to (26.5f+i*1.9f, 20.2f) in local coordinates(i varies from 1 to 5).
        All spheres are dynamic (moving) bodies.



\a ballfdC: Array to hold objects of type b2FixtureDef. Holds the fixture definitions of each sphere.
			 shape set to $circleC[i]
			 friction of each sphere = 0
			 restitution of each sphere = 0
			 density of each sphere = 5






\a jd: An object of class b2RevoluteJointDef. An anchor point(given by a vector) about which 2 bodies are attached.
       All pendulums are eventually attached to the rectangular bar (b2) via this variable.	

\a anchor : An object of class  b2Vec2. Its position is set to (-26.5f+i*1.9f, 28.0f) in successive itereations.
            The anchor(jd) connects object b2 and b4 about this point.
\n \n


			
*/



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
   
  
  
  
/*!
\brief
\b The \b bar \b containing \b the \b dominos\n

\a shape: An object of type b2PolygonShape. Holds the rectangular shape of the bar. Dimensions = (6,0.25)

\a bd: An object of type b2BodyDef. Holds the body definitions for the bar.
	  \t  Position = (-12,16.25) wrt local coordinates. \t type=  static_body 

\a bar : object of class b2Body , a rigid body, a bar in this case. $shape is used to set its fixture.

 */
	
   
		{
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, .25f);
	
      b2BodyDef bd;
      bd.position.Set(-12.0f, 16.25f);
      b2Body* bar = m_world->CreateBody(&bd);
      bar->CreateFixture(&shape, 0.0f);
  	}
  	
  	
  	
  	
  	
  	
  	

//Dominos
 
 
 
  
/*!
\brief
\b The \b dominos

\a shape: An object of type b2PolygonShape. Holds the rectangular shape of the bar. Dimensions = (0.2,2)

\a bd: An object of type b2BodyDef. Holds the body definitions for the dominos over successive iterations.
	  \t  Position = (-15.5 + 1*i,16.25) wrt local coordinates(i goes from 0 to 5). \t type=  dynamic_body 

\a fd: An object of type b2FixtureDef . Holds the fixture definitions for the dominos.
             Its shape is set to $shape , density  = 30.0 , friction = 0.3.


\a body : object of class b2Body , a rigid body, a domino in this case. $fd is used to set its fixture.

 */
 
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


    /*!
\brief 
\b Ball \b after \b dominos \n
					
\a b4: An object of class b2Body, a rigid body.

\a circle :  An object of class b2CircleShape. Holds a circular shape of radius 1 unit.

\a ballfd: An object of type b2FixtureDef . Holds the fixture definitions for a body.
             Its shape is set to $circle , density  = 20.0 , friction = 0, restitution = 0.

\a bd: An object of type b2BodyDef. Holds the body definitions of the ball.
	    Position = (-8.52,16.75). type=  dynamic (moving) object \t ballfd is used to set its fixture.  

*/ 




  {
		b2Body* b4;	  
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
 
 
 
 
 
 
 
 
 
 
 
 
 
 
/*! 
 
\b The \b pulley \b system \n
	 
\n
\a bd : An object of class b2BodyDef. Holds values of parameters for constructing a rigid body. 
        The body's position is set to (10, 15) in local coordinates.
        \t type : moving body \t fixed rotation : enabled. 

 
\b The \b open \b box \n

\a fd1 ,\a fd2 ,\a fd3 : Objects of class b2FixtureDef. Holds fixture definitions for the three rectangular parts of the box. \n
                      For each of them , density = 10, friction= 0.5, restitution= 0. \t
                      Each of their shape is set to be a Polygon shape object(of class b2PolygonShape). \t 
                      fd1 : shape set to a box of width 2 , height 0.2, centre (0,-1.9) in local coordinates and inclination 0 degrees.\t 
		      fd2 : shape set to a box of width 0.2 , height 1, centre (2,-1) in local coordinates and inclination 0 degrees. \t
		      fd3 : shape set to a box of width 0.2 , height 1, centre (-2,-1) in local coordinates and inclination 0 degrees. \t
\n \n
\a bs1,\a bs2,\a bs3 : Objects of class b2PolygonShape. Temporary Objects used to set the shape of fd1,fd2 and fd3 respectively.		

\a box1 : object of class b2Body , a rigid body. Fixture definitions from fd1, fd2 and fd3 are added to this object.



\b The \b bar \n
	This section refers to the documentation of the bar.\n \n
\a bd : position reset to (10,15)

\a fd1 : density reset to 34 . Reuse of fixture definition! 

\a box2 : object of class b2Body , a rigid body. Fixture definitions from fd1 are added to this object.



\b The \b pulley \b joint \n

\a myjoint : Object of class b2PulleyJointDef. Attaches the various components of the pulley system.
              box1 and box2 are the end objects of this pulley and are added to myjoint.
              The two dynamic body anchor points are set to (-10,15) and (10,15) in local coordinates.
              The two Ground anchor points are set to (10, 20) and (10,20).
              The ratio of the length of two sides of the pulley is set to 1 initially.


\a worldAnchorOnBody1 ,\a worldAnchorOnBody2 : Objects of class b2Vec . Temporary objects to store values for the ground anchor points.

\a worldAnchorGround1 ,\a worldAnchorGround2 :  Objects of class b2Vec . Temporary objects to store values for the dynamic body anchor points.

\a ratio : float type variable . Temporary variable to store the value for the initial ration of the length of the two sides of the pendulum.

\n\n\n\n
 
*/
 
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







/*!
 \b The \b see \b saw \b system \b at \b the \b bottom \n \n \n
 
 \b 1> The \b triangle \b wedge:\n

\a sbody: An object of class b2Body, a rigid body. wedgefd is used to give fixtures of the body. Holds the wedge body.

\a poly: An object of class b2PolygonShape. To hold shape of a convex polygon(with 3 vertices , specified later).

\a vertices[3] : An array of objects of class b2Vec2 to store positions of the endpoints of the wedge. The values are (-1,0), (1,0) and (0,3).

\a wedgefd: An object of type b2FixtureDef . Holds the fixture definitions for a body.
             Its shape is set to 'poly' , density  = 10.0 , friction = 0, restitution = 0.

\a wedgebd: An object of type b2BodyDef. Holds the body definitions of the wed.
	    Position = (10,10). 


\b 2> \b The \b plank \b on \b top \b of \b the \b wedge:\n
	
\a shape: an object of class b2PolygonShape to hold the shape of a polygon. Set to a box of width 10 and height 0.2 units.

\a bd2 : An object of class b2BodyDef. Holds values of parameters for constructing a rigid body .\t Holds the shape of a box(of shape $shape).  
         position = (10, 3) in local coordinates. type = dynamic (moving) object, used to create body.

\a fd2: An object of type b2FixtureDef . Holds the fixture definitions for a body.
             Its shape is set to 'shape'(an object of class b2PolygonShape) , density = 1 ,friction = 0.5.

\a body: An object of class b2Body, a rigid body. Its fixture definitions are taken from fd2.

\a jd: An object of class b2RevoluteJointDef. An anchor point(given by a vector) about which 2 bodies are attached.	

\a anchor : An object of class  b2Vec2. Its position is set to (10 , 3). The anchor(jd) connects objects sbody and body about this point.


\b 3> \b The \b light \b box \b on \b the \b right \b side \b of \b the \b see-saw:\n
	

\a shape2: an object of class b2PolygonShape to hold the shape of a polygon. Set to a box of width 4 and height 4 units.

\a bd3 : An object of class b2BodyDef. Holds values of parameters for constructing a rigid body. 
         position = (40, 2) in local coordinates. type = dynamic (moving) object

\a fd3: An object of type b2FixtureDef . Holds the fixture definitions for a body.
             Its shape is set to 'shape2'(an object of class b2PolygonShape) , density = 5.

\a body3: An object of class b2Body, a rigid body. Its fixture definitions are taken from fd3.

*/
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
















/*!
 \n
 \b The \b see \b saw \b system \b at \b the \b top \n
 
 \b 1> The \b triangle \b wedge:\n

\a sbody: An object of class b2Body, a rigid body. wedgefd is used to give fixtures of the body. Holds the wedge body.

\a poly: An object of class b2PolygonShape. To hold shape of a convex polygon(with 3 vertices , specified later).

\a vertices[3] : An array of objects of class b2Vec2 to store positions of the endpoints of the wedge. The values are (-1,0), (1,0) and (0,3).

\a wedgefd: An object of type b2FixtureDef . Holds the fixture definitions for a body.
             Its shape is set to 'poly' , density  = 10.0 , friction = 0, restitution = 0.

\a wedgebd: An object of type b2BodyDef. Holds the body definitions of the wed.
	    Position = (30,17). 


\b 2> \b The \b plank \b on \b top \b of \b the \b wedge:\n
	
\a shape: an object of class b2PolygonShape to hold the shape of a polygon. Set to a box of width 6 and height 0.2 units.

\a bd2 : An object of class b2BodyDef. Holds values of parameters for constructing a rigid body .\t Holds the shape of a box(of shape $shape).  
         position = (30, 20) in local coordinates. type = dynamic (moving) object, used to create body.

\a fd2: An object of type b2FixtureDef . Holds the fixture definitions for a body.
             Its shape is set to 'shape'(an object of class b2PolygonShape) , density = 1 ,friction = 0.5.

\a body: An object of class b2Body, a rigid body. Its fixture definitions are taken from fd2.

\a jd: An object of class b2RevoluteJointDef. An anchor point(given by a vector) about which 2 bodies are attached.	

\a anchor : An object of class  b2Vec2. Its position is set to (30 , 20). The anchor(jd) connects objects sbody and body about this point.


\b 3> \b The \b light \b box \b on \b the \b left \b side \b of \b the \b see-saw:\n
	This section refers to the documentation of light box on the top of see-saw.\n

\a shape3: an object of class b2PolygonShape to hold the shape of a polygon. Set to a box of width 1 and height 1 units.

\a bd4 : An object of class b2BodyDef. Holds values of parameters for constructing a rigid body. 
         position = (25.98, 21) in local coordinates. type = dynamic (moving) object

\a fd4: An object of type b2FixtureDef . Holds the fixture definitions for a body.
             Its shape is set to 'shape2'(an object of class b2PolygonShape) , density = 5.

\a body4: An object of class b2Body, a rigid body. Its fixture definitions are taken from fd4.

*/

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
    
    
    
    
    
    
    
    
    
    
 /*!   
    
 \b The \b Box \b and \b the \b balls   
    
    
 \b  <1 \b rectangular \b body \b to \b which \b the \b box \b pendulum \b is \b attached
    
    
\a b2 : An object of class b2Body, holds the rectangular bar. $bd1 is used to give it body definitions. 
		\t density of the body is set to 10.0
   
    
 \a bd1 : An object of class b2BodyDef. Holds values of parameters for constructing a rigid body .\t Holds the shape of a box(of shape $shape).  
         position = (45.5, 40) in local coordinates. type = dynamic (moving) object, used to create body.
 

\a shape: an object of class b2PolygonShape to hold the shape of a polygon, here a rectangle. Set to a box of width 1 and height 0.5 units.



\b <2 The \b Box

\a The box is made up of different rectangular parts.

 \a box1 : An object of class b2Body, holds the rectangular container. $bd is used to give it body definitions. 
		\t density of the body is set to 10.0 , 6 fixture definitions fd1,fd2 ... fd5 for each body part 

 \a bd1 : An object of class b2BodyDef. Holds values of parameters for constructing a rigid body .\t Holds the shape of a box(of shape $shape).  
         position = (35, 40) in local coordinates. type = dynamic (moving) object, used to create box.
         \t angle=-36 deg(i.e. inclined towards the left)
  
\a fd1 , fd2 ,fd3 ,fd5 ,fd6 : objects of type b2FixtureDef . Holds the fixture definitions for various parts of the box.
             restitution  =1 , density = 1 ,friction = 0.5 (for all of them).
             Their shapes are set to bs1, bs2,bs3, bs4, bs5 and shape1 respectively


\a bs1 , bs2 , bs3 , bs4, bs4, bs5, shape1 : objects of type b2PolygonShape . Holds the shape of various rectangular parts of the box.
           
          \n  bs2 ,bs3 : the vertical portions of the box
          \n bs4,bs5 : outer small attached lids of the box 
            \n |||||| Dimension | Centre (wrt the centre of the box) | Inclination (wrt the box) 
            \n bs1 :  2,0.05 | 0 , 4 | 0 degrees
            \n bs2:   0.05,4 | 2 , 0 | 0 degrees
            \n bs3:   0.05,4 | -2 , 0 | 0 degrees
            \n bs4:   0.05,0.5| 2 , -4| 135 degrees
            \n bs5:   0.05,0.5| -2,-4 | 225 degrees
            \n shape1 : 0.05,2|

\a bd1 : An object of class b2BodyDef. Holds values of parameters for constructing a rigid body .\t Holds the shape of a box(of shape $shape).  
         position = (35, 25.0) in local coordinates. type = dynamic (moving) object, used to create the container.
         angle=-36 deg(i.e. inclined towards the left)
      
\a b3 : An object of class b2Body, holds the lid of the rectangular container. $bd3 is used to give it body definitions. 
	       
 
\a bd3:An object of class b2BodyDef. Holds values of parameters for constructing a rigid body .\t Holds the shape of a box(of shape $shape).  
         position = -3,-4 in local coordinates of the box. type = dynamic (moving) object, used to create box.
         \t angle=-54 deg(i.e. inclined towards the left)
    		
 
\a <3 The joint b\w the box and the lid:

\a jointDef : Object of class b2RevoluteJointDef. Attaches the box($box1) and the rectangular lid( $b3).
              Local Anchors are set to (-2,-4.5) and (-0.18,2.23). 
              The property "collideConnected" is disabled meaning the two attached bodies 
               can't collide with each other.
               A motor is assocsiated with the joint.
               \n Max Torque on the motor =1000 , initial motorspeed =4
               The upper angle is limited to 90 degrees.

 
 
 
 
 \b <4 \b The \b balls \b in \b the \b container
 
 \a circle: an Array of objects of class b2CircleShape to hold the shape of the spheres inside the container.
           Set to a circle of radius 1.2 units.

\a shapebd2: An Array of objects of class b2BodyDef.Holds parameters for constructing the spheres. 
        Its position is set to (-i*0.005f, +i*0.005f) in local coordinates of the box(i varies from 1 to 3).
        All spheres are dynamic (moving) bodies.



\a shapefix2: Array to hold objects of type b2FixtureDef. Holds the fixture definitions of each sphere.
			 shape set to $circleC[i]
			 friction of each sphere = 0
			 restitution of each sphere = 0
			 density of each sphere = 4


\b <5 \b The anchor which attaches the bar and the box



\a jd : Object of class b2RevoluteJointDef. Attaches the box($box1) and the rectangular bar( $b2).
           Anchors is set to (45,40) 
             
 }
 
 
 
 
 
 
 
 */   
    
    
    {
      

      //body to which the box pendulum is attached
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
      
      //jointDef.maxMotorTorque = 100.0f;
      //jointDef.lowerAngle = 2.5f * b2_pi; // -90 degrees
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
 
 
 
 
 
 
 
 
 
/*! 
 
\b The \b pulley \b system \b for \b the \b person \n
	 
\n
\b <1 The person , consisting of head ,feet legs. 
           The head is essentially a circular head attached to a small horizontal bar.
           The legs are rectangular horizontal bars.
           The feet is a small rectangular inclined bar attached to the left end point of legs.


\a head : An object of class b2Body, holds the circular part of the head of the person. $headbd is used to give it body definitions. 
		\t Fixture definitions are taken from $headBfd , $headCfd


\a headbd : An object of class b2BodyDef. Holds values of parameters for constructing a rigid body,in this case the  circular part of head of the person. 
        \t, type : moving body ,\t fixed rotation : enabled, |t position = 75,2. 


\a headB :object of class b2PolygonShape. Stores a polygon shape for the head, in this case a rectangle of dimensions 3,0 and center -2,0 wrt local coordinates of the body. The shape is aligned with the horizontal axis.


\a headC: object of class b2CircleShape. Stores a circular shape for the head , of radius 1.
    	
\a headBfd: object of class b2FixtureDef. Stores the fixture definitions for the rectangular part of the head. Shape is set $headB   

\a headCfd : object of class b2FixtureDef. Stores the fixture definitions for the rectangular part of the head. Shape is set $headC 	
    
\a body2: object of class b2Body, to hold the feet of the person. Fixture definitions are taken from $fake.	

\a fake: object of class PolygonShape to hold the shape of the feet of the person. Set as a rectangular bar of dimensions , 0.2 ,0.2

\a body2bd: object of class b2BodyDef. Holds the body definitions for the feet of the person. position = 70,2

\a LowerP : object of class b2Body, to hold the lower portion of the Body. Body definitions are taken from $Lowerbd.    	
 
 
\a Lowerbd : object of class b2BodyDef, to hold the body definitions for the lower portion of the body of the person. 
             Position = (68.5,2)   	
    	
\a Legs ,Feets : object of class b2PolygonShape, to hold the shape of a rectangle of (dimension ,centre) = (2,0.2 ,(0,0)) and (0.2 ,0.5,-2,0.5) for legS and FeetS respectively.
    	
    	
 \a Legfd , Feetfd :object of class b2FixtureDef to hold the fixture definitions for legs and feet of the person.
                     Density  = 1
                        	
    	    	
 \a jd :object of class b2RevoluteJointDef to hinge head and body2 of the person about the anchor (70,2). This ensure the person can "be lifted".
    	
    	
\b <2 \b The \b open \b box \n

\a fd1 ,\a fd2 ,\a fd3 : Objects of class b2FixtureDef. Holds fixture definitions for the three rectangular parts of the box. \n
                      For each of them , density = 10, friction= 0.5, restitution= 0. \t
                      Each of their shape is set to be a Polygon shape object(of class b2PolygonShape). \t 
        \n      fd1 : shape set to a box of width 2 , height 0.2, centre (0,-1.9) in local coordinates and inclination 0 degrees.\t 
		 \n     fd2 : shape set to a box of width 0.1 , height 3, centre (3,0) in local coordinates and inclination 45 degrees left. \t
		  \n    fd3 : shape set to a box of width 0.1 , height 3, centre (-3,0) in local coordinates and inclination 45 degrees right. \t
\n \n
\a bs1,\a bs2,\a bs3 : Objects of class b2PolygonShape. Temporary Objects used to set the shape of fd1,fd2 and fd3 respectively.		

\a box1 : object of class b2Body , a rigid body. Fixture definitions from fd1, fd2 and fd3 are added to this object.





\b <3 \b The \b pulley \b joint \n

\a myjoint : Object of class b2PulleyJointDef. Attaches the various components of the pulley system.
              box1 and box2 are the end objects of this pulley and are added to myjoint.
              The two dynamic body anchor points are set to (50,10) and (75,2) in local coordinates.
              The two Ground anchor points are set to (50, 14) and (65,14).
              The ratio of the length of two sides of the pulley is set to 1 initially.

\a worldAnchorOnBody1 ,\a worldAnchorOnBody2 : Objects of class b2Vec . Temporary objects to store values for the ground anchor points.

\a worldAnchorGround1 ,\a worldAnchorGround2 :  Objects of class b2Vec . Temporary objects to store values for the dynamic body anchor points.

\a ratio : float type variable . Temporary variable to store the value for the initial ration of the length of the two sides of the pendulum.

\n\n\n\n
 
*/
 
 
 
 
 
 
 
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
    	fake.SetAsBox(0.5,0.5);
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
