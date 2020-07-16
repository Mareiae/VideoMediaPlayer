#include "widget.h"
#include <QListWidgetItem>
#include <QFileDialog>
#include <QFileInfo>
#include <QTime>
Widget::Widget(QWidget* parent)
    :MainForm(1200,700,parent)
{
    //播放按钮信号连接函数;
    connect(getPlayBtn(),&QPushButton::clicked,this,&Widget::play);
    //暂停按钮事件;
    connect(getPauseBtn(),&QPushButton::clicked,this,[this](){
        getPauseBtn()->hide();
        getPlayBtn()->show();
        //暂停视频播放;
        getMediaPlay()->pause();
    });
    //播放上个视频;
    connect(getPreviousBtn(),&QPushButton::clicked,this,[this](){
        getMediaPlaylist()->previous();
        play();
    });
    //播放下个视频;
    connect(getNextBtn(),&QPushButton::clicked,this,[this](){
        getMediaPlaylist()->next();
        play();
    });
    //全屏播放;
    connect(getFullScreenBtn(),&QPushButton::clicked,this,[this](){
        if(!isFullStatus){
            fullScreenPlay(true);
            isFullStatus = true;
        }else{
            fullScreenPlay(false);
            isFullStatus = false;
        }
    });
    getLocalSource();
    videoSliderChange();
    addSoundSliderWidget();
    addSettingWidget();
    settingFunc();
}
Widget::~Widget(){}
void Widget::getLocalSource()
{
    //获取本地资源列表按钮信号连接函数
    connect(getLocalVideoSource(),&QPushButton::clicked,this,&Widget::on_get_loacl_source);
    //播放列表信号连接函数
    connect(getListWidget(),&QListWidget::itemSelectionChanged,this,[this](){
        getMediaPlaylist()->setCurrentIndex(getListWidget()->currentRow());
        //设置播放视频的标题;
        getTitleLabel()->setText(getListWidget()->currentItem()->text());
        //设置按钮可用;
        toolBtnIsEnabled(true);
        play();

    });
}
void Widget::videoSliderChange()
{
    //监听当前播放视频的播放位置变化;
    connect(getMediaPlay(),&QMediaPlayer::positionChanged,this,[this](qint64 postion){
        if(getMediaPlay()->duration() != getVideoProgressBar()->maximum()){
            //更新进度条最大值;
            getVideoProgressBar()->setMaximum(int(getMediaPlay()->duration()));
            //跟新总播放时间;
            getTotalPlayTimeLabel()->setText(transTime(getMediaPlay()->duration()));
        }
        //更新进度条;
        getVideoProgressBar()->setValue(int(postion));
        //更新当前播放时间;
        getNowPlayTimeLabel()->setText(transTime(postion));
    });
    //若鼠标拖动当前视频进度条
    connect(getVideoProgressBar(),&QSlider::sliderMoved,this,[this](int postion){
        getMediaPlay()->setPosition(postion);
    });

}
//获取本地资源列表;
void Widget::on_get_loacl_source()
{
    //鼠标选择的视频路径;
    QStringList fileUrlList = QFileDialog::getOpenFileNames(this,tr("此电脑"),".","*.mp4 *.avi *.mov");
    if(fileUrlList.empty()){
        return;
    }
    //隐藏获取视频资源按钮;
    getLocalVideoSource()->hide();
    //显示视频列表资源;
    getListWidget()->show();

    for(int i = 0;i < fileUrlList.size();++i){
        //获取选择的文件信息;
        QFileInfo fileInfo(fileUrlList.at(i));
        //将视频名称添加到列表中;
        getListWidget()->addItem(fileInfo.fileName());
        //将当前视频地址添加到媒体播放列表中;
        getMediaPlaylist()->addMedia(QMediaContent(QUrl(fileInfo.filePath())));
    }
}
void Widget::play()
{
    //显示暂停按钮;
    getPauseBtn()->show();
    //隐藏播放按钮;
    getPlayBtn()->hide();

    //视频播放;
    getMediaPlay()->play();
}
QString Widget::transTime(qint64 millSec)
{
    int h,m,s;
    millSec /= 1000;  //获得的时间是以毫秒为单位的
    h = int(millSec/3600);
    m = int((millSec-h*3600)/60);
    s = int(millSec-h*3600-m*60);
    return QString("%1:%2:%3").arg(h).arg(m).arg(s);  //把int型转化为string类型;
}
void Widget::toolBtnIsEnabled(bool isEnable)
{
    if(!isEnable) return;
    if(!getPlayBtn()->isEnabled())
        getPlayBtn()->setEnabled(true);
    if(!getPreviousBtn()->isEnabled())
        getPreviousBtn()->setEnabled(true);
    if(!getPauseBtn()->isEnabled())
        getPauseBtn()->setEnabled(true);
    if(!getNextBtn()->isEnabled())
        getNextBtn()->setEnabled(true);
    if(!getSettingBtn()->isEnabled())
        getSettingBtn()->setEnabled(true);
    if(!getSoundBtn()->isEnabled())
        getSoundBtn()->setEnabled(true);
    if(!getFullScreenBtn()->isEnabled())
        getFullScreenBtn()->setEnabled(true);
    if(!getSelectPerVideo()->isEnabled())
        getSelectPerVideo()->setEnabled(true);
}

void Widget::addSoundSliderWidget()
{
    //音量控制进度条;
    ptr_soundSlider = new SoundSlider;
    ptr_soundSlider->setParent(this);
    ptr_soundSlider->hide();
    //为音量按钮添加槽函数;
    connect(getSoundBtn(),&QPushButton::clicked,this,[this](){
        //若音量控制面板不可见
        if(ptr_soundSlider->isVisible()){
            ptr_soundSlider->hide();
        }else{
            //若音量控制面板可见;
            ptr_soundSlider->move(QCursor::pos().x() - 105,QCursor::pos().y() - 240);
            ptr_soundSlider->show();
        }
    });
    //当音量滑块的值发生变化，则更新当前媒体的音量;
    connect(ptr_soundSlider->getSlider(),&QSlider::valueChanged,this,[this](int value){
        getMediaPlay()->setVolume(value);
    });
}

void Widget::addSettingWidget()
{
    ptr_settingWidget = new MySettingWidget;
    ptr_settingWidget->setParent(this);
    ptr_settingWidget->hide();//设置界面默认隐藏;

    connect(getSettingBtn(),&QPushButton::clicked,this,[this](){
        if(ptr_settingWidget->isVisible()){
            ptr_settingWidget->hide();
        }else{
            ptr_settingWidget->move(QCursor::pos().x()-395,QCursor::pos().y() - 270);
            ptr_settingWidget->show();
        }
    });
}
void Widget::settingFunc()
{
    //设置亮度范围0-200;
    ptr_settingWidget->getLightSlider()->setRange(0,200);
    //监听亮度值是否需要发生改变;
    connect(ptr_settingWidget->getLightSlider(),&QSlider::valueChanged,this,[this](int value){
        getVideoWidget()->setBrightness(value);
    });

    //播放速度;
    connect(ptr_settingWidget,&MySettingWidget::speedValue,this,[this](double speed){
        getMediaPlay()->setPlaybackRate(speed);
    });

    //是否循环播放;
    connect(ptr_settingWidget->getCirclePlayCheck(),&QCheckBox::stateChanged,this,[this](int state){
        if(state == 2){
            //设置当前播放模式为循环播放;
            getMediaPlaylist()->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        }else if(state == 0){
            getMediaPlaylist()->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        }
    });
    //是否自动播放下一集;
    connect(ptr_settingWidget->getSkipPlayCheck(),&QCheckBox::stateChanged,this,[this](int state){
        qDebug()<<state;
        if(state == 2){
            //设置当前播放模式为循环播放;
            getMediaPlaylist()->setPlaybackMode(QMediaPlaylist::Loop);
        }else if(state == 0){
            getMediaPlaylist()->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        }
    });
}
