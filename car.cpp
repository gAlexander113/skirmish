#include <QDebug>
#include "car.h"

Car::Car()
{
    pos.x = 0.0;
    pos.y = 0.0;
    state = neutral;

}

void Car::paint_car()
{
    move_car();
    glTranslatef(pos.x, pos.y, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(car_width / 2.0, car_length / 2.0, 0.0);
    glVertex3f(-car_width / 2.0, car_length / 2.0, 0.0);
    glVertex3f(-car_width / 2.0, -car_length / 2.0, 0.0);
    glVertex3f(car_width / 2.0, -car_length / 2.0, 0.0);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
}



void Car::set_state(const CarState &st)
{
    state = st;
}

void Car::move_car()
{
    switch (state)
    {
    case turn_left:
        pos.x -= car_turn_speed;
        break;
    case turn_right:
        pos.x += car_turn_speed;
        break;
    case neutral:
        break;
    default:
        qDebug() << "unknown state in car state";
        break;
    }
}
