#include "widget.h"
#include "ui_widget.h"
#include <QVBoxLayout>
#include "openglui.h"
#include <QPushButton>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout;
    OpenglUI *xx = new OpenglUI(this);
    layout->addWidget(xx);
    QPushButton *btn = new QPushButton;
    btn->setText(tr("change program..."));
    layout->addWidget(btn);
    this->setLayout(layout);
    connect(btn,SIGNAL(clicked(bool)),xx,SLOT(onImageClick()));
    QPushButton *cap = new QPushButton;
    layout->addWidget(cap);
    cap->setText(tr("Capture"));
    connect(cap,SIGNAL(clicked(bool)),xx,SLOT(onCaptureImage()));
}

Widget::~Widget()
{
    delete ui;
}
