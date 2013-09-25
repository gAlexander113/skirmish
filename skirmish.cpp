#include "skirmish.h"

#include <QTimer>
#include <QDebug>
#include "textureloader.h"

Skirmish::Skirmish(QWidget *pwgt)
    : QGLWidget(pwgt)
    , height(0)
    , width(0)
{   
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
    connect(this, SIGNAL(game_over()), SLOT(slot_game_over()));        
}

Skirmish::~Skirmish()
{
    delete road;
    delete car;
}

void Skirmish::init()
{
    TextureLoader *loader = new TextureLoader;
    loader->init();
    loader->load_textures();

    road = new Road(loader, true);
    car = new Car();

    timer->start(swap_speed);
    road->init_road();
    car->init();
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

    height = h;
    width = w;

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
//    gluLookAt(1.0, 0.0, 0.1, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -18.0);
    glBegin(GL_QUADS);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(scene_width / 2.0, scene_height / 2.0, 0.0);
    glVertex3f(-scene_width / 2.0, scene_height / 2.0, 0.0);
    glVertex3f(-scene_width / 2.0, -scene_height / 2.0, 0.0);
    glVertex3f(scene_width / 2.0, -scene_height / 2.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glEnd();


    road->paint_road();
    car->paint_car();
    glPopMatrix();

    Point car_position = car->position();
    float left_road_bound = road->left_bound(car_position.y);
    float right_road_bound = left_road_bound + road_width;

    if (car_position.x < left_road_bound || car_position.x > right_road_bound)
        emit game_over();
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
    case Qt::Key_Up:
        car->set_state(forward);
        break;
    case Qt::Key_Down:
        car->set_state(back);
        break;
    case Qt::Key_Space:
        this->init();
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
    for (int i = 0; i < general_speed; ++i) // TODO: make normal change of the world generation speed
        updateGL();
}

void Skirmish::slot_game_over()
{
    qDebug() << "game over: press space to play again";
    timer->stop();
}
