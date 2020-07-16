#include "soundslider.h"
#include <QVBoxLayout>
SoundSlider::SoundSlider(QWidget *parent) : QWidget(parent)
{
    initWindow();

    ptr_soundSlider = new MySlider(OrientationType::Vertical);
    ptr_soundSlider->setParent(this);
    ptr_soundSlider->setOrientation(Qt::Vertical);
    ptr_soundSlider->setRange(0,100);

    ptr_minSliderVal = new QLabel;
    ptr_minSliderVal->setParent(this);
    ptr_minSliderVal->setText(" 0 ");
    ptr_minSliderVal->setStyleSheet("QLabel{font-size:14px;font-weight:bold;color:#fff}");

    ptr_maxSliderVal = new QLabel;
    ptr_maxSliderVal->setParent(this);
    ptr_maxSliderVal->setText("100");
    ptr_maxSliderVal->setStyleSheet("QLabel{font-size:14px;font-weight:bold;color:#fff}");

    QVBoxLayout* ptr_mlay = new QVBoxLayout;
    ptr_mlay->addWidget(ptr_maxSliderVal);
    ptr_mlay->addWidget(ptr_soundSlider);
    ptr_mlay->addWidget(ptr_minSliderVal);

    setLayout(ptr_mlay);
}
SoundSlider::~SoundSlider()
{
}
void SoundSlider::initWindow()
{
    setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(QSize(50,190));
    setStyleSheet("QWidget{background-color:#2e2e36;}");
}
void SoundSlider::leaveEvent(QEvent *)
{
    //当鼠标离开界面则隐藏界面;
    hide();
}
