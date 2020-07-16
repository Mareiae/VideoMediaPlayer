#include "myqprogressbar.h"
MySlider::MySlider(OrientationType orientationType,QWidget *parent)
    :QSlider(parent),m_orientationType(orientationType)
{
    initQssFiles();
}
MySlider::~MySlider(){}
void MySlider::initQssFiles()
{
    if(m_orientationType == Horizontal){
        QFile file(":/common/qss/sliderHStyle.qss");
        file.open(QFile::ReadOnly);
        setStyleSheet(file.readAll());
        file.close();
    }else if(m_orientationType == Vertical){
        QFile file(":/common/qss/sliderVStyle.qss");
        file.open(QFile::ReadOnly);
        setStyleSheet(file.readAll());
        file.close();
    }
}
