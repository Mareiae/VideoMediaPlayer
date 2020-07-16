#ifndef MYQPROGRESSBAR_H
#define MYQPROGRESSBAR_H
#include <QSlider>
#include <QPaintEvent>

enum OrientationType{
    Vertical,
    Horizontal
};

class MySlider:public QSlider
{
    Q_OBJECT
public:
    explicit MySlider(OrientationType orientationType,QWidget *parent = nullptr);
    ~MySlider();
private:
    OrientationType m_orientationType;
    void initQssFiles();
};

#endif // MYQPROGRESSBAR_H
