#ifndef CAR_H
#define CAR_H

#include <QObject>
#include "share.h"

const float car_width = 0.25;
const float car_length = 0.5;
const float car_turn_speed = 0.1;
const float car_forward_speed = 2;
const float car_back_speed = 1.5;

enum CarState{neutral = 1,turn_left, turn_right, forward, back};

class Car : public QObject
{
    Q_OBJECT
public:
    Car();

    void init();
    void paint_car();
    void set_state(const CarState &st);
    Point position() const;
private:
    Point pos;
    CarState state;

private slots:
    void move_car();
};

#endif // CAR_H
