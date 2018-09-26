#include "widget.h"
#include "ui_widget.h"
#include "openglui.h"
#include <QVBoxLayout>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    OpenglUI *oi = new OpenglUI(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(oi);
    this->setLayout(layout);
}

Widget::~Widget()
{
    delete ui;
}
