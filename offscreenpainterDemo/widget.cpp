#include "widget.h"
#include "ui_widget.h"
#include "examplepaintsurface.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
//QLabel *label =  NULL;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    label = new QLabel;
//    QVBoxLayout *layout = new QVBoxLayout(this);
//    layout->addWidget(label);
//    this->setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    ExamplePaintSurface paintersurface;
    paintersurface.resize(300,200);
    paintersurface.render();
    QImage image = paintersurface.grabFramebuffer();

    QPainter cp;
    cp.begin(this);
    cp.drawImage(rect(),image,image.rect());
    cp.end();
}
