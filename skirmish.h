#ifndef SKIRMISH_H
#define SKIRMISH_H

#include <QGLWidget>

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
    static const float section_size = 0.01;
    static const float road_width = 1.5;
    enum RoadState{forward, left, right};
    RoadState state;
    QVector<Point> road;

private slots:
    void slotChange();
};

#endif // SKIRMISH_H
