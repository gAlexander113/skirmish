#include <QTime>
#include <QDebug>
#include "road.h"

Road::Road()
    : is_random(true)
{
}

Road::Road(TextureLoader *obj, bool random)
    : is_random(random)
{
    loader = obj;
}

void Road::init_road()
{
    road.clear();
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
    GLuint texture = loader->texture(QString("road.jpg"));

    if (texture < 0)
    {
        qDebug() << "failed";
        exit(-1);
    }

    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUAD_STRIP);
    for (int i = 0, t = 0; i < road.size(); i += 1, t = i % 2)
    {
        if (!t)
            glTexCoord2f(0.0, 1.0);
        else
            glTexCoord2f(0.0, 0.0);
        glVertex3f(road[i].x, road[i].y, 0.0);

        if (!t)
            glTexCoord2f(1.0, 1.0);
        else
            glTexCoord2f(1.0, 0.0);
        glVertex3f(road[i].x + road_width, road[i].y, 0.0);
    }
    glEnd();

    this->update_road();
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

float Road::left_bound(const float y_pos)
{
    float x = 0;
    for (int i = 0; i < road.size(); ++i)
        if (road[i].y - y_pos < 1e-3)
        {
            x = road[i].x;
            break;
        }
    return x;
}
