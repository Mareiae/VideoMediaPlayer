#ifndef MYSETTINGWIDGET_H
#define MYSETTINGWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include "myqprogressbar.h"
#include <QCheckBox>
#include <QEvent>
class MySettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MySettingWidget(QWidget *parent = nullptr);
    ~MySettingWidget();
    void initWindow();//初始化窗口设置;
    QLayout* addPlaySpeedItems();//添加播放速度元素;
    QLayout* addBrightItems();//添加画面亮度元素;
    void addPlayItems();//循环播放,是否跳过片头;
    QLabel* getTitle(const QString& title);//设置标签;
    void getCurrentSpeedValue();//获取用户点击的速度值;

public:
    MySlider* getLightSlider(){
        return ptr_lightSlider;
    }
    QCheckBox* getCirclePlayCheck(){
        return ptr_checkBox[0];
    }
    QCheckBox* getSkipPlayCheck(){
        return ptr_checkBox[1];
    }

private:
    QPushButton** ptr_playSpeedBtn;//播放速度;
    QVBoxLayout* ptr_mainlayout;//主布局;
    MySlider* ptr_lightSlider;//亮度控制;
    QCheckBox** ptr_checkBox;//单选按钮组;

signals:
    void speedValue(double speed);

public slots:
protected:
    void leaveEvent(QEvent *); //重写鼠标离开事件;
};

#endif // MYSETTINGWIDGET_H
