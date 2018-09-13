#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "multiviewer_container.h"
#include <QFileOpenEvent>
#include <QDir>

class QProgressBar;
class QMdiArea;
class QMdiSubWindow;
class QMenu;
class QAction;

class LayerDialog;
class GLArea;
class MultiViewer_Container;
//namespace Ui {
//class MainWindow;
//}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    GLArea *GLA()const{
        MultiViewer_Container *mvc =currentViewContainer() ;
        if(!mvc) return 0;
        return mvc->currentgla;
    }
    MultiViewer_Container *currentViewContainer()const
    {
        return _currviewcontainer;
    }

public slots:
    void switchCurrentContainer(QMdiSubWindow * subwin);
    bool importMeshWithLayerManagement(QString filename = QString());
private:
    void createMenu();
    void createAction();
private slots:
    void newProject(const QString& projName = QString());


private slots:
    bool importMesh(QString fileName=QString(), bool isareload = false);

private:
//    Ui::MainWindow *ui;
    static QProgressBar *qb;
    QMdiArea *mdiarea;
    LayerDialog *layerDialog;

    QMenu *fileMenu;

    QAction *importMeshAct;
    QDir lastUsedDirectory;
    MultiViewer_Container* _currviewcontainer;
};

/// Event filter that is installed to intercept the open events sent directly by the Operative System
class FileOpenEater : public QObject
{
    Q_OBJECT

public:
    FileOpenEater(MainWindow *_mainWindow)
    {
        mainWindow= _mainWindow;
        noEvent=true;
    }

    MainWindow *mainWindow;
    bool noEvent;

protected:

    bool eventFilter(QObject *obj, QEvent *event)
    {
        if (event->type() == QEvent::FileOpen) {
            noEvent=false;
            QFileOpenEvent *fileEvent = static_cast<QFileOpenEvent*>(event);
            mainWindow->importMeshWithLayerManagement(fileEvent->file());
            qDebug("event fileopen %s", qUtf8Printable(fileEvent->file()));
            return true;
        } else {
            // standard event processing
            return QObject::eventFilter(obj, event);
        }
    }
};

#endif // MAINWINDOW_H
