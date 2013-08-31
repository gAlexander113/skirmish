#include "GL/gl.h"
#include "GL/glu.h"
#include <QTimer>

#include "skirmish.h"

Skirmish::Skirmish(QWidget *pwgt)
    : QGLWidget(pwgt)
{   

    QTimer *timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(slotChange()));

    timer->start(10);

    for (int i = 0; i < 100; ++i)
    {
        Point point;
        point.x = -1;
        point.y = -1 * i * section_size + 1.0;
        road.push_back(point);
    }
    state = right;
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
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < road.size(); ++i)
        glVertex3f(road[i].x, road[i].y, 0.0);
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < road.size(); ++i)
        glVertex3f(road[i].x + road_width, road[i].y, 0.0);
    glEnd();

}

void Skirmish::slotChange()
{
    Point first = road[0];
    for (int i = road.size() - 1; i > 0; --i)
    {
        road[i] = road[i - 1];
        road[i].y -= section_size;
    }



    if (first.x < -1.5)
        state = right;
    else
        if (first.x + road_width > 1.5)
            state = left;

    Point new_point;
    switch(state)
    {
    case left:
        new_point.x = first.x - section_size;
        new_point.y = first.y;
        break;
    case right:
        new_point.x = first.x + section_size;
        new_point.y = first.y;
    }

    road[0] = new_point;

    updateGL();
}
