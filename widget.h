#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "UI/ui.h"
#include "UI/common/mysettingwidget.h"
class Widget : public MainForm
{

public:
    explicit Widget(QWidget* parent = nullptr);
    ~Widget();
    void play();//视频播放;
    QString transTime(qint64 millSec);//将以毫秒为单位的时间转化为时分秒格式;
    void toolBtnIsEnabled(bool isEnable); //工具栏是否可用;
    void addSoundSliderWidget();//添加声音控制面板;
    void videoSliderChange();//播放进度条设置;
    void getLocalSource();//打开本地媒体资源;
    void addSettingWidget();//添加设置界面;
    void settingFunc();//亮度调节;

private:
    bool isFullStatus = false;//判断是否处于全屏状态;
    SoundSlider* ptr_soundSlider;//声音控制界面;
    MySettingWidget* ptr_settingWidget;//设置界面;
public slots:
    void on_get_loacl_source();//获取本地视频资源;
};

#endif // WIDGET_H
