#include "widget.h"
#include "ui_widget.h"
#include "opengglwidget.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    OpengGLWidget *widget = new OpengGLWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(widget);
    this->setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}
