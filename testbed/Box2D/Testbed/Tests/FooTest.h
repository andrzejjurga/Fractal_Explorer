#ifndef FOOTEST_H
#define FOOTEST_H
 
#include <vector>

#ifndef DEGTORAD
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#endif

//This is just to avoid conflicting names in other tutorial source files.
#define Ball DRAWING_OBJECTS_Ball

class Ball {
protected:
    //class member variables
    b2Body* m_body;
    float m_radius;

public:
    Ball(b2World* world, float radius) {
        m_body = NULL;
        m_radius = radius;

        //set up dynamic body, store in class variable
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_dynamicBody;
        myBodyDef.position.Set(0, 20);
        m_body = world->CreateBody(&myBodyDef);

        //add circle fixture
        b2CircleShape circleShape;
        circleShape.m_p.Set(0, 0);
        circleShape.m_radius = m_radius; //use class variable
        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &circleShape;
        myFixtureDef.density = 1;
        m_body->CreateFixture(&myFixtureDef);
    }
    ~Ball() {}

    void renderAtBodyPosition() {
        //safety check
        if (m_body == NULL) return;

        //get current position from Box2D
        b2Vec2 pos = m_body->GetPosition();
        float angle = m_body->GetAngle();

        //call normal render at different position/rotation
        glPushMatrix();
        glTranslatef(pos.x, pos.y, 0);
        glRotatef(angle * RADTODEG, 0, 0, 1);
        glScalef(m_radius, m_radius, 1);
        render();
        glPopMatrix();
    }

    void render() {
        //change the color depending on the current velocity
        b2Vec2 vel = m_body->GetLinearVelocity();
        float red = vel.Length() / 10.0;
        red = b2Min(1.0f, red);
        glColor3f(red, 0.5, 0.5);

        //nose and eyes
        glPointSize(4);
        glBegin(GL_POINTS);
        glVertex2f(0, 0);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glEnd();

        //mouth
        glBegin(GL_LINE_LOOP);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.16, -0.6);
        glVertex2f(0.16, -0.6);
        glVertex2f(0.5, -0.5);
        glEnd();

        //circle
        glBegin(GL_LINE_LOOP);
        for (float a = 0; a < 360 * DEGTORAD; a += 30 * DEGTORAD)
            glVertex2f(sinf(a), cosf(a));
        glEnd();
    }
};

class iforce2d_drawing_objects : public Test
{

    std::vector<Ball> m_balls;

public:

    iforce2d_drawing_objects() {
        //a static body
        b2BodyDef myBodyDef;
        myBodyDef.type = b2_staticBody;
        myBodyDef.position.Set(0, 0);
        b2Body* staticBody = m_world->CreateBody(&myBodyDef);

        //shape definition
        b2PolygonShape polygonShape;

        //fixture definition
        b2FixtureDef myFixtureDef;
        myFixtureDef.shape = &polygonShape;

        //add four walls to the static body
        polygonShape.SetAsBox(20, 1, b2Vec2(0, 0), 0);//ground
        staticBody->CreateFixture(&myFixtureDef);
        polygonShape.SetAsBox(20, 1, b2Vec2(0, 40), 0);//ceiling
        staticBody->CreateFixture(&myFixtureDef);
        polygonShape.SetAsBox(1, 20, b2Vec2(-20, 20), 0);//left wall
        staticBody->CreateFixture(&myFixtureDef);
        polygonShape.SetAsBox(1, 20, b2Vec2(20, 20), 0);//right wall
        staticBody->CreateFixture(&myFixtureDef);

        //add some ball entities to the scene
        for (int i = 0; i < 20; i++) {
            float radius = 1 + 2 * (rand() / (float)RAND_MAX); //random radius between 1 - 3
            Ball ball(m_world, radius);
            m_balls.push_back(ball);
        }
    }

    void Step(Settings* settings)
    {
        //run the default physics and rendering
        Test::Step(settings);

        for (int i = 0; i < m_balls.size(); i++)
            m_balls[i].renderAtBodyPosition();

    }

    static Test* Create()
    {
        return new iforce2d_drawing_objects;
    }

};

//This is just to avoid conflicting names in other tutorial source files.
#undef Ball

#endif
