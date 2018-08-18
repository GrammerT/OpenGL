#include "widget.h"
#include "ui_widget.h"
#include "openglwidget.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    OpenglWidget *widget = new OpenglWidget(this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(widget);
    this->setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}
