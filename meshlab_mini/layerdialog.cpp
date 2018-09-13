#include "layerdialog.h"
#include "ui_layerdialog.h"

LayerDialog::LayerDialog(QWidget *parent)
    :QDockWidget(parent)
{
    ui = new Ui::DockWidget;
    this->setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint | Qt::SubWindow);
    this->QWidget::setAttribute(Qt::WA_MacAlwaysShowToolWindow);
    this->setVisible(false);
    ui->setupUi(this);
}

LayerDialog::~LayerDialog()
{

}
