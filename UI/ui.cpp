#include "ui.h"
#include <QScreen>
#include <QGuiApplication>
#include <QRect>
#include <QDebug>
#include <QScrollBar>

MainForm::MainForm(int uiWidth,int uiHeight,QWidget *parent)
    : QWidget(parent),m_uiWidth(uiWidth),m_uiHeight(uiHeight)
{
    //重新设置界面大小;
    reWindowSize();

    //窗口主布局;
    vlayout = new QVBoxLayout;
    vlayout->addLayout(paintTopNav());

    //将播放窗口,播放列表窗口添加到主界面中;
    QHBoxLayout* ptr_formVlayout = new QHBoxLayout;
    ptr_formVlayout->addLayout(paintVideoPlayForm(),3);
    ptr_formVlayout->addWidget(paintVideoListForm(),1);
    vlayout->addLayout(ptr_formVlayout);

    vlayout->setMargin(0);
    //设置主布局;
    setLayout(vlayout);
}
MainForm::~MainForm()
{
}
void MainForm::mousePressEvent(QMouseEvent *event)
{
    /*
     * 鼠标拖动窗口实现函数;
     * */
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
       event->ignore();
#else
#endif
}
void MainForm::reWindowSize()
{

    //获取当前电脑桌面的大小;
    QRect screenRect = QGuiApplication::primaryScreen()->availableGeometry();
    //计算宽,高的伸缩系数;
    float widthScial = 1366 / screenRect.width() + 1366 % screenRect.width();
    float heightScial = 738 / screenRect.height() + 738 % screenRect.height();

    aveFlexDiget = (widthScial + heightScial)/2;

    //重设界面大小;
    setMinimumSize(int(m_uiWidth*widthScial),int(m_uiHeight*heightScial));

    //显示位于桌面居中;
    move((screenRect.width()-m_uiWidth)/2,(screenRect.height()-m_uiHeight)/2);
    //设置窗口默认背景颜色;
    setStyleSheet("QWidget{background-color:#2e2e36;}");
    //去除默认窗口导航栏按钮
    setWindowFlag(Qt::FramelessWindowHint);;
}

QLayout* MainForm::paintTopNav()
{
    QHBoxLayout *ptr_barlayout = new QHBoxLayout;
    ptr_barlayout->addStretch();

    //添加当前视频播放标题栏;
    ptr_videoTitle = new QLabel;
    ptr_videoTitle->setParent(this);
    ptr_videoTitle->setText("视频标题");
    ptr_videoTitle->setStyleSheet({"QLabel{color:#fff;font-size:18px;margin-top:5px;}"});
    ptr_barlayout->addWidget(ptr_videoTitle);

    //最小化，最大化，关闭按钮申明;
    barBtn = new QPushButton*[3];
    QString barTipName[3] =  {"最小化","最大化","关闭"};
    QString barIconNmae[3] = {"min.svg","max.svg","close.svg"};
    ptr_barlayout->addStretch();
    //重新添加最小化，最大化，关闭按钮;
    for(int i = 0;i < 3;++i){
        barBtn[i] = new QPushButton;
        barBtn[i]->setParent(this);
        barBtn[i]->setIcon(QIcon(":/Icons/"+barIconNmae[i]));
        barBtn[i]->setToolTip(QString(barTipName[i]));
        barBtn[i]->setFixedSize(QSize(int(20*aveFlexDiget),int(20*aveFlexDiget)));
        //barBtn[i]->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        connect(barBtn[i],&QPushButton::clicked,this,[=](){
            //实现最小化，最大化，关闭按钮功能;
            QPushButton *pbarBtn = qobject_cast<QPushButton *>(sender());
            QWidget *pWindow = this->window();
            if (pWindow->isTopLevel()){
                if(pbarBtn == barBtn[0]){
                    pWindow->showMinimized();
                }else if(pbarBtn == barBtn[1]){
                    pWindow->isMaximized()?pWindow->showNormal() : pWindow->showMaximized();
                    pWindow->isMaximized()?barBtn[1]->setIcon(QIcon(":/Icons/min_streth.svg"))
                        :barBtn[1]->setIcon(QIcon(":/Icons/max.svg"));
                }else if(pbarBtn == barBtn[2]){
                    pWindow->close();
                }
            }
        });
        //设置鼠标滑过样式;
        if(i == 2){
            barBtn[i]->setStyleSheet("QPushButton{border:0px}"
                                     "QPushButton:hover{background-color:red}");
        }else{
            barBtn[i]->setStyleSheet("QPushButton{border:0px}"
                                     "QPushButton:hover{background-color:#BEBEBE}");
        }
        ptr_barlayout->addWidget(barBtn[i]);
    }
    ptr_barlayout->setSpacing(int(5*aveFlexDiget));
    ptr_barlayout->setMargin(0);
    return ptr_barlayout;
}

QLayout* MainForm::paintVideoPlayForm()
{
    QVBoxLayout* ptr_palyLayout = new QVBoxLayout;

    //添加视频播放控件;
     ptr_mediaPlay = new QMediaPlayer;
     ptr_mediaPlay->setParent(this);
     ptr_mediaPlaylist = new QMediaPlaylist;
     ptr_mediaPlaylist->setParent(this);
     //默认开启列表循环播放;
     ptr_mediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop);
     ptr_mediaPlay->setPlaylist(ptr_mediaPlaylist);
     ptr_videoWidget = new QVideoWidget;
     ptr_videoWidget->setParent(this);
     ptr_mediaPlay->setVideoOutput(ptr_videoWidget);
     ptr_palyLayout->addWidget(ptr_videoWidget);


    //添加视频播放进度条;
    progressBar = new MySlider(OrientationType::Horizontal);
    progressBar->setParent(this);
    progressBar->setOrientation(Qt::Horizontal);
    ptr_palyLayout->addWidget(progressBar);

    ptr_palyLayout->addLayout(paintPlayToolForm());
    return ptr_palyLayout;
}
QLayout* MainForm::paintPlayToolForm()
{
    ptr_playToolVlay = new QHBoxLayout;
    //添加当前播放时间,总播放时间标签;
    QString timeText[3] = {"0:0:0","/","0:0:0"};
    ptr_timeInfolab = new QLabel*[3];

    for(int i = 0;i < 3;++i){
        ptr_timeInfolab[i] = new QLabel;
        ptr_timeInfolab[i]->setParent(this);
        ptr_timeInfolab[i]->setText(timeText[i]);
        ptr_timeInfolab[i]->setStyleSheet("QLabel{color:#CFCFCF;font-size:12px;font-weight:bold;}");
    }

    //添加播放工具栏按钮
    ptr_toolBtn = new QPushButton*[7];
    QString playIconName[7] = {"previous.svg","play.svg","pause.svg","next.svg","setting.svg","sound.svg","full_screen.svg"};

    for(int i = 0;i < 7;++i){
        ptr_toolBtn[i] = new QPushButton;
        ptr_toolBtn[i]->setParent(this);
        if(i == 4){
            for(int j = 0;j < 3;++j){
                ptr_playToolVlay->addWidget(ptr_timeInfolab[j]);
            }
            ptr_playToolVlay->addStretch();
        }
        ptr_toolBtn[i]->setIcon(QIcon(":/Icons/"+playIconName[i]));
        ptr_toolBtn[i]->setFixedSize(QSize(int(20*aveFlexDiget),int(20*aveFlexDiget)));
        ptr_toolBtn[i]->setIconSize(QSize(int(20*aveFlexDiget),int(20*aveFlexDiget)));
        ptr_toolBtn[i]->setFlat(true);
        ptr_toolBtn[i]->setEnabled(false);//设置按钮不可用;
        ptr_toolBtn[i]->setCursor(Qt::PointingHandCursor);
        ptr_playToolVlay->addWidget(ptr_toolBtn[i]);
    }
    //隐藏暂停按钮;
    ptr_toolBtn[2]->hide();
    //设置按钮间距;
    ptr_playToolVlay->setSpacing(10);
    //设置外边距;
    ptr_playToolVlay->setMargin(10);
    return ptr_playToolVlay;
}
QWidget* MainForm::paintVideoListForm()
{
    ptr_listLayout = new QVBoxLayout;
    //为播放列表添加背景部件,方便设置背景颜色;
    ptr_playLBWidget = new QWidget;
    ptr_playLBWidget->setParent(this);
    ptr_playLBWidget->setLayout(ptr_listLayout);
    //添加背景颜色;
    ptr_playLBWidget->setStyleSheet("QWidget{background-color:#1C1C1C}");

    //添加播放列表标签;
    QLabel* ptr_listTitle = new QLabel;
    ptr_listTitle->setParent(this);
    ptr_listTitle->setText("播放列表:");
    ptr_listTitle->setStyleSheet("QLabel{color:	#EE4000;font-size:14px;font-weight:bold;}");
    ptr_listLayout->addWidget(ptr_listTitle);

    //添加播放列表控件;
    ptr_getPlayListBtn = new QPushButton;
    ptr_getPlayListBtn->setParent(this);
    ptr_getPlayListBtn->setText("获取本地播放列表");
    ptr_getPlayListBtn->setStyleSheet("QPushButton{width:40px;height:30px;border-radius:4px;background-color:#363636;"
                                      "margin:50% auto;color:#EE4000;font-weight:bold;}");
    ptr_getPlayListBtn->setCursor(Qt::PointingHandCursor);
    ptr_listLayout->addWidget(ptr_getPlayListBtn);


    //播放列表控件;
    ptr_listWidget = new QListWidget;
    ptr_listWidget->setParent(this);
    ptr_listWidget->setCursor(Qt::PointingHandCursor);
    ptr_listWidget->setSpacing(5);
    //修改播放列表样式;
    ptr_listWidget->setStyleSheet("QListWidget{background:#1C1C1C;border:0px;color:	#CFCFCF;font-size:14px;font-weight:bold;}"
                            "QListWidget::item:hover{background:#696969;border:0px;}"
                            "QListWidget::item:selected{background:#696969;border:0px;}");
    ptr_listWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {border: none;"
                                                 "background: #dfdfdf;"
                                                 "width: 12px;}"
                                                 "QScrollBar::handle:vertical {border: none;"
                                                 "border-radius: 5px;"
                                                 "background: #cfcfcf;}"
                                                 "QScrollBar::add-page:vertical {border: none;"
                                                 "background-color: #dfdfdf;}"
                                                 "QScrollBar::sub-page:vertical {border: none;"
                                                 "background-color: #dfdfdf;}");
    //ptr_listWidget->hide();
    ptr_listLayout->addWidget(ptr_listWidget,5);
    ptr_listLayout->addStretch(1);
    return ptr_playLBWidget;
}
void MainForm::fullScreenPlay(bool isFull)
{
    if(isFull){
        ptr_playLBWidget->hide();
    }else{
        ptr_playLBWidget->show();
    }
}
