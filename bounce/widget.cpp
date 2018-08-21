#include "widget.h"
#include "ui_widget.h"
#include "openglwidgets.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    OpenGLWidgets *widget = new OpenGLWidgets(this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(widget);
    this->setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}
