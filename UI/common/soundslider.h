#ifndef SOUNDSLIDER_H
#define SOUNDSLIDER_H

#include <QWidget>
#include "myqprogressbar.h"
#include <QLabel>
#include <QEvent>
class SoundSlider : public QWidget
{
    Q_OBJECT
public:
    explicit SoundSlider(QWidget *parent = nullptr);
    ~SoundSlider();
    void initWindow();
    //返回滑快;
    MySlider* getSlider()
    {
        return ptr_soundSlider;
    }

private:
    MySlider* ptr_soundSlider;//声音控制进度条;
    QLabel* ptr_minSliderVal;//声音最小值;
    QLabel* ptr_maxSliderVal;//声音最大值;

signals:

public slots:

protected:
    void leaveEvent(QEvent *); //重写鼠标离开事件;

};

#endif // SOUNDSLIDER_H
