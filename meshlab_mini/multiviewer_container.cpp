#include "multiviewer_container.h"

MultiViewer_Container::MultiViewer_Container()
{

}

Splitter::Splitter(QWidget *parent)
{

}

Splitter::Splitter(Qt::Orientation orientation, QWidget *parent)
{

}

Splitter::~Splitter()
{

}

MultiViewer_Container *Splitter::getRootContainer()
{
    return NULL;
}

QSplitterHandle *Splitter::createHandle()
{
    return NULL;
}
