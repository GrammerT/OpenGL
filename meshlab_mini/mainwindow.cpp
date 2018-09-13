#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiArea>
#include <QIcon>
#include <QProgressBar>
#include "layerdialog.h"

QProgressBar *MainWindow::qb;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //!
    mdiarea = new QMdiArea(this);
    setCentralWidget(mdiarea);
    connect(mdiarea,SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this,SLOT(switchCurrentContainer(QMdiSubWindow*)));
    mdiarea->setAcceptDrops(true);

    //!
    layerDialog = new LayerDialog(this);
//    connect(layerDialog, SIGNAL(toBeShow()), this, SLOT(updateLayerDialog()));
    layerDialog->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    layerDialog->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    addDockWidget(Qt::RightDockWidgetArea, layerDialog);
    //!
    QIcon icon;
    icon.addPixmap(QPixmap(":/images/eye48.png"));
    setWindowIcon(icon);
    createAction();
    createMenu();
}

MainWindow::~MainWindow()
{
}

void MainWindow::switchCurrentContainer(QMdiSubWindow *subwin)
{

}

void MainWindow::importMeshWithLayerManagement()
{
    bool layervisible = false;
    if(layerDialog!=NULL)
    {

    }
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(importMeshAct);
}

void MainWindow::createAction()
{
    importMeshAct = new QAction(QIcon(":/images/import_mesh.png"), tr("&Import Mesh..."), this);
    importMeshAct->setShortcutContext(Qt::ApplicationShortcut);
    importMeshAct->setShortcut(Qt::CTRL + Qt::Key_I);
    connect(importMeshAct, SIGNAL(triggered()), this, SLOT(importMeshWithLayerManagement()));

}
