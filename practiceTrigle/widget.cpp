#include "widget.h"
#include "ui_widget.h"
#include "openglui.h"
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    OpenglUI *ui = new OpenglUI(this);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(ui);
    this->setLayout(layout);

}

Widget::~Widget()
{
    delete ui;
}
