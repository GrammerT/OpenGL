#ifndef LAYERDIALOG_H
#define LAYERDIALOG_H
#include <QDockWidget>

namespace Ui {
class DockWidget;
}

class LayerDialog :public QDockWidget
{
    Q_OBJECT
public:
    LayerDialog(QWidget *parent =0);
    ~LayerDialog();

private:
    Ui::DockWidget *ui;
};

#endif // LAYERDIALOG_H
