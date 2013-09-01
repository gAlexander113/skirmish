#include <QTimer>

#include "skirmish.h"

Skirmish::Skirmish(QWidget *pwgt)
    : QGLWidget(pwgt)
{   
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    timer->start(swap_speed);

    road = new Road(true);
    road->init_road();

    car = new Car();
}

Skirmish::~Skirmish()
{
    delete road;
    delete car;
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

    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);
    road->paint_road();

    glTranslatef(0.0, 0.0, 0.1);
    car->paint_car();
    glPopMatrix();
}

void Skirmish::keyPressEvent(QKeyEvent *key)
{
    switch (key->key())
    {
    case Qt::Key_Left:
        car->set_state(turn_left);
        break;
    case Qt::Key_Right:
        car->set_state(turn_right);
        break;
    default:
        QWidget::keyPressEvent(key);
    }
}

void Skirmish::keyReleaseEvent(QKeyEvent *key)
{
    Q_UNUSED(key)
    car->set_state(neutral);
}

void Skirmish::repaint()
{
    road->update_road();

    updateGL();
}
