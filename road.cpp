#include <QTime>
#include <QDebug>
#include "road.h"

Road::Road()
    : is_random(true)
{
}

Road::Road(bool random)
    : is_random(random)
{
}

void Road::init_road()
{
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

void Road::paint_road()
{
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

void Road::update_road()
{
    for (int i = road.size() - 1; i > 0; --i)
    {
        road[i].x = road[i - 1].x;
        road[i].y = road[i - 1].y - section_size;
    }

    if (is_random)
    {
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
    }
}
