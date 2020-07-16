#include "mysettingwidget.h"

MySettingWidget::MySettingWidget(QWidget *parent) : QWidget(parent)
{
    //设置界面;
    initWindow();

    ptr_mainlayout = new QVBoxLayout;
    ptr_mainlayout->addLayout(addPlaySpeedItems());
    ptr_mainlayout->addLayout(addBrightItems());
    addPlayItems();
    ptr_mainlayout->setSpacing(20);
    ptr_mainlayout->setMargin(20);
    setLayout(ptr_mainlayout);
}
MySettingWidget::~MySettingWidget(){}
void MySettingWidget::initWindow()
{
    setWindowFlag(Qt::FramelessWindowHint);
    setFixedSize(400,200);
    setStyleSheet("QWidget{background-color:#2e2e36;opacity:0.5}");
}
QLabel* MySettingWidget::getTitle(const QString &title)
{
    QLabel* ptr_title = new QLabel;
    ptr_title->setParent(this);
    ptr_title->setText(title);
    ptr_title->setStyleSheet("QLabel{font-size:12px;font-weight:bold;color:#CDC5BF;}");
    return ptr_title;
}
QLayout* MySettingWidget::addPlaySpeedItems()
{
    QHBoxLayout* ptr_speedlay = new QHBoxLayout;

    ptr_speedlay->addWidget(getTitle("播放速度"));
    ptr_speedlay->addStretch();

    //添加速度控制按钮;
    QString speedContent[5] = {"0.5x","1.0x","1.25x","1.5x","2.0x"};
    ptr_playSpeedBtn = new QPushButton*[5];
    for(unsigned i = 0;i < 5;++i){
        ptr_playSpeedBtn[i] = new QPushButton;
        ptr_playSpeedBtn[i]->setParent(this);
        ptr_playSpeedBtn[i]->setText(speedContent[i]);
        ptr_playSpeedBtn[i]->setStyleSheet("QPushButton{border:1px solid #BEBEBE;font-weight:bold;color:	#8B8989;height:20px;width:40px;border-radius:3px;background-color:#2e2e36}"
                                           "QPushButton:hover{border:1px solid #FF0000;color:#FF0000;}");
        ptr_playSpeedBtn[i]->setCursor(Qt::PointingHandCursor);
        ptr_speedlay->addWidget(ptr_playSpeedBtn[i]);
    }
    getCurrentSpeedValue();
    ptr_speedlay->setSpacing(10);
    return ptr_speedlay;
}


QLayout* MySettingWidget::addBrightItems()
{
    QHBoxLayout* ptr_brightlayout = new QHBoxLayout;

    ptr_brightlayout->addWidget(getTitle("播放亮度"),1);
    ptr_brightlayout->addStretch(1);

    ptr_lightSlider = new MySlider(OrientationType::Horizontal);
    ptr_lightSlider->setParent(this);
    ptr_lightSlider->setOrientation(Qt::Horizontal);
    ptr_brightlayout->addWidget(ptr_lightSlider,4);

    return ptr_brightlayout;
}
void MySettingWidget::addPlayItems()
{
    //添加是否单片循环,是否自动跳过片头;
    QString name[2] = {"单片循环","自动播放下一集"};
    ptr_checkBox = new QCheckBox*[2];

    for(unsigned i = 0;i < 2;++i){
        QHBoxLayout* ptr_hlay = new QHBoxLayout;
        ptr_hlay->addWidget(getTitle(name[i]));
        ptr_hlay->addStretch();

        ptr_checkBox[i] = new QCheckBox;
        ptr_checkBox[i]->setParent(this);
        ptr_checkBox[i]->setStyleSheet("QCheckBox::indicator{height:26px;width:50px;}"
                                       "QCheckBox::indicator::unchecked {image: url(:/Icons/checkBox.png);}"
                                       "QCheckBox::indicator::checked {image: url(:/Icons/checkBox_focus.png);}");
        ptr_hlay->addWidget(ptr_checkBox[i]);
        ptr_mainlayout->addLayout(ptr_hlay);
    }
    //自动跳过片头默认开启;
    ptr_checkBox[1]->setCheckState(Qt::Checked);
}

void MySettingWidget::leaveEvent(QEvent *)
{
    //当鼠标离开界面则隐藏界面;
    hide();
}

void MySettingWidget::getCurrentSpeedValue()
{
    for(int i = 0;i < 5;++i){
        connect(ptr_playSpeedBtn[i],&QPushButton::clicked,this,[=](){
            QString speedStr = ptr_playSpeedBtn[i]->text();
            emit speedValue(speedStr.mid(0,speedStr.length()-1).toDouble());
        });
    }
}




















