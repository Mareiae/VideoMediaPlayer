#ifndef UI_H
#define UI_H

#include <QWidget>
#include <QMediaPlayer>
#include <QScreen>
#include <QGuiApplication>
#include <QRect>
#include <QDebug>
#include <QMediaPlaylist>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QVideoWidget>
#include <QPushButton>
#include <QLabel>
#include <windows.h>
#include <QMouseEvent>
#include <QListWidget>
#include "common/soundslider.h"
class MainForm : public QWidget
{
    Q_OBJECT
public:
    explicit MainForm(int uiWidth,int uiHeight,QWidget *parent = nullptr);
    ~MainForm();
    void reWindowSize();//设置窗口大小;
    QLayout* paintTopNav();//重新绘制顶部栏按钮;
    QLayout* paintVideoPlayForm();//绘制视频播放界面;
    QWidget* paintVideoListForm();//绘制播放列表界面;
    QLayout* paintPlayToolForm();//播放工具栏按钮界面;
    void toolBtn_click_func();//实现工具栏按钮点击事件;
    void fullScreenPlay(bool isFull);//全屏播放函数;

protected:
   void mousePressEvent(QMouseEvent *event);    //实现鼠标拖动窗口;

private:
    int m_uiWidth,m_uiHeight;   //界面的长宽;
    float aveFlexDiget; //界面控件争对不同分辨率缩放系数;
    QVBoxLayout* vlayout; //主布局;
    QPushButton **barBtn;//最大化,关闭等按钮;
    QLabel* ptr_videoTitle; //当前视频播放标题;
    QLabel** ptr_timeInfolab;//设置播放时间显示标签;
    QPushButton** ptr_toolBtn; //工具栏按钮右侧部分;
    QPushButton* ptr_getPlayListBtn; //获取播放列表控件;
    MySlider* progressBar;//视频播放进度条;
    QMediaPlaylist* ptr_mediaPlaylist;//视频播放列表;
    QMediaPlayer* ptr_mediaPlay;//视频播放媒介;
    QVideoWidget* ptr_videoWidget;//播放控件;
    QVBoxLayout* ptr_listLayout;//视频列表布局;
    QListWidget* ptr_listWidget;//视频资源播放列表;
    QWidget* ptr_playLBWidget;//视频列表背景控件;
    QHBoxLayout* ptr_playToolVlay;//工具栏布局;
protected:
    //获取上一集按钮;
    QPushButton* getPreviousBtn(){
        return ptr_toolBtn[0];
    }
    //获取播放按钮;
    QPushButton* getPlayBtn(){
        return ptr_toolBtn[1];
    }
    //获取暂停按钮;
    QPushButton* getPauseBtn(){
        return ptr_toolBtn[2];
    }
    //获取下一集按钮;
    QPushButton* getNextBtn(){
        return ptr_toolBtn[3];
    }
    //获取设置按钮;
    QPushButton* getSettingBtn(){
        return ptr_toolBtn[4];
    }
    //获取声音按钮;
    QPushButton* getSoundBtn(){
        return ptr_toolBtn[5];
    }
    //获取全屏按钮;
    QPushButton* getFullScreenBtn(){
        return ptr_toolBtn[6];
    }
    //获取当前播放时间标签;
    QLabel* getNowPlayTimeLabel(){
        return ptr_timeInfolab[0];
    }
    //获取总播放时间标签;
    QLabel* getTotalPlayTimeLabel(){
        return ptr_timeInfolab[2];
    }
    //获取播放标题;
    QLabel* getTitleLabel(){
        return ptr_videoTitle;
    }
    //获取选集按钮;
    QPushButton* getSelectPerVideo(){
        return ptr_toolBtn[4];
    }
    //获取媒体控件;
    QMediaPlayer* getMediaPlay(){
        return ptr_mediaPlay;
    }
    QVideoWidget* getVideoWidget(){
        return ptr_videoWidget;
    }
    //获取视频播放列表控件;
    QMediaPlaylist* getMediaPlaylist(){
        return ptr_mediaPlaylist;
    }

    //获取本地视频资源按钮;
    QPushButton* getLocalVideoSource(){
        return ptr_getPlayListBtn;
    }
    //获取视频资源播放列表;
    QListWidget* getListWidget(){
        return ptr_listWidget;
    }
    //视频进度条;
   MySlider* getVideoProgressBar()
   {
       return progressBar;
   }

};

#endif // UI_H
