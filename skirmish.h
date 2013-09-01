#ifndef SKIRMISH_H
#define SKIRMISH_H

#include <QGLWidget>

const int swap_speed = 10; // in miliseconds

const float section_size = 0.01;
const int num_sections = 1000;
const float road_width = 1.5;
const float road_bit_length = 1.0;
const float top_of_road = 2.0;

const float screen_bound = 1.5;

struct Point
{
    float x, y;
};

class Skirmish : public QGLWidget
{
    Q_OBJECT
public:
    explicit Skirmish(QWidget *pwgt = 0);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
private:
    enum RoadState{left = -1, forward, right};
    RoadState state;
    QVector<Point> road;
    float road_bit;


private slots:
    void repaint();
};

#endif // SKIRMISH_H
