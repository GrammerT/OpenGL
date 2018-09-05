#include "widget.h"
#include "ui_widget.h"
#include "openglui.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    OpenglUI *widget = new OpenglUI(this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(widget);
    this->setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}
