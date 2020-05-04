#ifndef FOOTEST_H
#define FOOTEST_H
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#include <iostream>
#include <math.h>

    enum _moveState {
        MS_STOP,
        MS_LEFT,
        MS_RIGHT,
    };
class FooTest : public Test
{
public:
    b2Body* body;
    _moveState moveState;
     int remainingJumpSteps;

    FooTest() {
        //body definition
          //class member variable
        remainingJumpSteps = 0;
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody;

        //shape definition
        b2PolygonShape polygonShape;
        polygonShape.SetAsBox(1, 1); //a 2x2 rectangle

        //fixture definition
        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &polygonShape;
        myFixtureDef.density = 1;

        //create dynamic body
        myBodyDef.position.Set(0, 10);
        body = m_world->CreateBody(&myBodyDef);
        body->CreateFixture(&myFixtureDef);

        //a static body
        myBodyDef.type = b2_staticBody;
        myBodyDef.position.Set(0, 0);
        b2Body* staticBody = m_world->CreateBody(&myBodyDef);

        //add four walls to the static body
        polygonShape.SetAsBox(20, 1, b2Vec2(0, 0), 0);//ground
        staticBody->CreateFixture(&myFixtureDef);
        polygonShape.SetAsBox(20, 1, b2Vec2(0, 40), 0);//ceiling
        staticBody->CreateFixture(&myFixtureDef);
        polygonShape.SetAsBox(1, 20, b2Vec2(-20, 20), 0);//left wall
        staticBody->CreateFixture(&myFixtureDef);
        polygonShape.SetAsBox(1, 20, b2Vec2(20, 20), 0);//right wall
        staticBody->CreateFixture(&myFixtureDef);

        moveState = MS_STOP;
    }

    void Keyboard(unsigned char key)
    {
        switch (key)
        {
        case 'q': //move left
            moveState = MS_LEFT;
            break;
        case 'w': //stop
            moveState = MS_STOP;
            break;
        case 'e': //move right
            moveState = MS_RIGHT;
            break;
        case 'j': //jump
        {
            b2Vec2 vel = body->GetLinearVelocity();
            vel.y = 10;//upwards - don't change x velocity
            body->SetLinearVelocity(vel);
        }
        break;
        case 'k': //jump
            remainingJumpSteps = 6;// 1/10th of a second at 60Hz
            break;
        case 'l':
        {
            //to change velocity by 10
            float impulse = body->GetMass() * 10;
            body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter(), true);
        }
        break;
        default:
            //run default behaviour
            Test::Keyboard(key);
        }
    }

    void Step(Settings* settings)
    {


        //run the default physics and rendering
        Test::Step(settings);

        b2Vec2 vel = body->GetLinearVelocity();
        switch (moveState)
        {
        case MS_LEFT:  vel.x = -5; break;
        case MS_STOP:  vel.x = 0; break;
        case MS_RIGHT: vel.x = 5; break;
        }
        body->SetLinearVelocity(vel);

        if (remainingJumpSteps > 0) {
            body->ApplyForce(b2Vec2(0, 500), body->GetWorldCenter(), true);
            remainingJumpSteps--;
        }

    }

    static Test* Create()
    {
       
        return new FooTest;
    }
};

#endif