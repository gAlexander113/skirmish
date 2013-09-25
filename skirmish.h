#ifndef SKIRMISH_H
#define SKIRMISH_H

#include <QGLWidget>
#include <QKeyEvent>

#include "share.h"
#include "road.h"
#include "car.h"

const int swap_speed = 20; // in miliseconds
const int general_speed = 1; // speed of the wole world

class Skirmish : public QGLWidget
{
    Q_OBJECT
public:
    explicit Skirmish(QWidget *pwgt = 0);
    ~Skirmish();

    void init();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    virtual void keyPressEvent(QKeyEvent *key);
    virtual void keyReleaseEvent(QKeyEvent *key);

private:
    Road *road;
    Car *car;

    QTimer *timer;

    int height;
    int width;

signals:
    void game_over();

private slots:
    void repaint();
    void slot_game_over();
};

#endif // SKIRMISH_H
