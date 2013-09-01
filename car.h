#ifndef CAR_H
#define CAR_H

#include <QObject>
#include "share.h"

const float car_width = 0.1;
const float car_length = 0.1;
const float car_turn_speed = 0.01;
enum CarState{neutral = 1,turn_left, turn_right};

class Car : public QObject
{
    Q_OBJECT
public:
    Car();

    void paint_car();
    void set_state(const CarState &st);
private:
    Point pos;
    CarState state;

private slots:
    void move_car();
};

#endif // CAR_H
