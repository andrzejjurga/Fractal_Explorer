#ifndef FOOTEST_H
#define FOOTEST_H
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#include <iostream>
#include <math.h>


class FooTest : public Test
{
public:

    FooTest() {
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
        myBodyDef.position.Set(0, 20); //set the starting position
        myBodyDef.angle = 0; //set the starting angle

        b2Body* dynamicBody = m_world->CreateBody(&myBodyDef);

        b2PolygonShape boxShape;
        boxShape.SetAsBox(2, 2);

        b2FixtureDef boxFixtureDef;
        boxFixtureDef.shape = &boxShape;
        boxFixtureDef.density = 1;
        dynamicBody->CreateFixture(&boxFixtureDef);

        myBodyDef.type = b2_staticBody; //this will be a static body
        myBodyDef.position.Set(0, 10); //slightly lower position
        b2Body* staticBody = m_world->CreateBody(&myBodyDef); //add body to world
        staticBody->CreateFixture(&boxFixtureDef); //add fixture to body

        myBodyDef.type = b2_kinematicBody; //this will be a kinematic body
        myBodyDef.position.Set(-18, 11); // start from left side, slightly above the static body
        b2Body* kinematicBody = m_world->CreateBody(&myBodyDef); //add body to world
        kinematicBody->CreateFixture(&boxFixtureDef); //add fixture to body

        kinematicBody->SetLinearVelocity(b2Vec2(1, 0)); //move right 1 unit per second
        kinematicBody->SetAngularVelocity(360 * DEGTORAD); //1 turn per second counter-clockwise
    }



    void Step(Settings* settings)
    {


        //run the default physics and rendering
        Test::Step(settings);


    }

    static Test* Create()
    {
       
        return new FooTest;
    }
};

#endif