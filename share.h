#ifndef SHARE_H
#define SHARE_H

#include <GL/gl.h>
#include <GL/glu.h>



const float section_size = 0.1;
const int num_sections = 100;

const float scene_width = 10.0; // 100 meters: 0.1 - 1 metre; 1 - 10 meters
const float scene_height = 10.0;

const float screen_bound = 4.0;

struct Point
{
    float x, y;
};


#endif // SHARE_H
