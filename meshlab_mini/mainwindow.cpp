#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMdiArea>
#include <QIcon>
#include <QProgressBar>
#include <QFileDialog>
#include "layerdialog.h"
#include <QDebug>
#include "glarea.h"

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

bool MainWindow::importMeshWithLayerManagement(QString filename)
{
    importMesh(filename,false);
    return true;
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
    qDebug()<< connect(importMeshAct, SIGNAL(triggered()), this, SLOT(importMeshWithLayerManagement()));

}

void MainWindow::newProject(const QString &projName)
{
    MultiViewer_Container *mvcont = new MultiViewer_Container(mdiarea);
    connect(&mvcont->meshDoc,SIGNAL(meshAdded(int)),this,SLOT(meshAdded(int)));
    mdiarea->addSubWindow(mvcont);

    GLArea *gla = new GLArea(this,mvcont);
    mvcont->addView(gla,Qt::Horizontal);
}

bool MainWindow::importMesh(QString fileName, bool isareload)
{
    if(!GLA())
    {
        this->newProject();
        if(!GLA())
            return false;
    }
//    QStringList fileNameList;
//    if (fileName.isEmpty())
//        fileNameList = QFileDialog::getOpenFileNames(this,tr("Import Mesh"), lastUsedDirectory.path(), PM.inpFilters.join(";;"));
//    else
//        fileNameList.push_back(fileName);

//    if (fileNameList.isEmpty())	return false;
//    else
//    {
//        //save path away so we can use it again
//        QString path = fileNameList.first();
//        path.truncate(path.lastIndexOf("/"));
//        lastUsedDirectory.setPath(path);
//    }
}
