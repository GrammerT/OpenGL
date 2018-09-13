#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QProgressBar;
class QMdiArea;
class QMdiSubWindow;
class QMenu;
class QAction;

class LayerDialog;
//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void switchCurrentContainer(QMdiSubWindow * subwin);
    void importMeshWithLayerManagement();
private:
    void createMenu();
    void createAction();
private:
//    Ui::MainWindow *ui;
    static QProgressBar *qb;
    QMdiArea *mdiarea;
    LayerDialog *layerDialog;

    QMenu *fileMenu;

    QAction *importMeshAct;
};

#endif // MAINWINDOW_H
