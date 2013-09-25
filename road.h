#ifndef ROAD_H
#define ROAD_H

#include "share.h"
#include "textureloader.h"


const float road_width = 2.0;
const float road_bit_length = 1.0;
const float top_of_road = 5.0;

class Road
{
public:
    Road();
    Road(TextureLoader *obj, bool random);

    void init_road();
    void paint_road();
    void update_road();
    float left_bound(const float y_pos);
private:
    bool is_random;
    enum RoadState{left = -1, forward, right};
    RoadState state;
    QVector<Point> road;
    float road_bit;
    TextureLoader *loader;
};

#endif // ROAD_H
