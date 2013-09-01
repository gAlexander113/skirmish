#ifndef SKIRMISH_H
#define SKIRMISH_H

#include <QGLWidget>
#include <QKeyEvent>

#include "share.h"
#include "road.h"
#include "car.h"

const int swap_speed = 10; // in miliseconds

class Skirmish : public QGLWidget
{
    Q_OBJECT
public:
    explicit Skirmish(QWidget *pwgt = 0);
    ~Skirmish();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    virtual void keyPressEvent(QKeyEvent *key);
    virtual void keyReleaseEvent(QKeyEvent *key);

private:
    Road *road;
    Car *car;

private slots:
    void repaint();
};

#endif // SKIRMISH_H
