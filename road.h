#ifndef ROAD_H
#define ROAD_H

#include "share.h"

const float section_size = 0.01;
const int num_sections = 1000;
const float road_width = 1.5;
const float road_bit_length = 1.0;
const float top_of_road = 2.0;

const float screen_bound = 1.5;


class Road
{
public:
    Road();
    explicit Road(bool random);

    void init_road();
    void paint_road();
    void update_road();
private:
    bool is_random;
    enum RoadState{left = -1, forward, right};
    RoadState state;
    QVector<Point> road;
    float road_bit;
};

#endif // ROAD_H
