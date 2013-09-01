#include <GL/gl.h>
#include <GL/glu.h>
#include <QTime>
#include <QTimer>
#include <QDebug>

#include "skirmish.h"

Skirmish::Skirmish(QWidget *pwgt)
    : QGLWidget(pwgt)
{   
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(swap_speed);

    for (int i = 0; i < num_sections; ++i)
    {
        Point point;
        point.x = -1 * road_width / 2.0;
        point.y = -1 * i * section_size + top_of_road;
        road.push_back(point);
    }
    state = right;
    road_bit = 0.0;
}

void Skirmish::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void Skirmish::resizeGL(int w, int h)
{
    if (h == 0)
        h = 1; // =)

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Skirmish::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < road.size(); i += 1)
    {
        glVertex3f(road[i].x, road[i].y, 0.0);
//        glVertex3f(road[i+1].x, road[i+1].y, 0.0);
//        glVertex3f(road[i+1].x + road_width, road[i+1].y, 0.0);
        glVertex3f(road[i].x + road_width, road[i].y, 0.0);
    }
    glEnd();
}

void Skirmish::repaint()
{
    for (int i = road.size() - 1; i > 0; --i)
    {
        road[i].x = road[i - 1].x;
        road[i].y = road[i - 1].y - section_size;
    }

    road_bit += section_size;

    if (road[0].x < -1 * screen_bound ||(road[0].x + road_width) > screen_bound) // =)
        road_bit += road_bit_length + 1;

    if (road_bit > road_bit_length)
    {
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        int random = (qrand() % 3) - 1;
        if (road[0].x < -1 * screen_bound)
            random += 1;
        else
            if (road[0].x + road_width > screen_bound)
                random -= 1;

        switch (random)
        {
        case -1: state = left; break;
        case 0: state = forward; break;
        case 1: state = right; break;
        }
        road_bit = 0.0;
    }


    switch(state)
    {
    case left:
        road[0].x = road[0].x - section_size;
        break;
    case right:
        road[0].x = road[0].x + section_size;
        break;
    case forward:

        break;
    default:
        qDebug() << "my state is " << state;
        break;
    }


    updateGL();
}
