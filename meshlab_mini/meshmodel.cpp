#include "meshmodel.h"
#include <QFileInfo>

MeshDocument::MeshDocument()
{

}

MeshModel *MeshDocument::getMesh(int id)
{
    foreach(MeshModel *mmp, meshList)
    {
        if(mmp->id() == id) return mmp;
    }
    return 0;
}

void MeshDocument::setCurrentMesh(int new_curr_id)
{
    currentMesh = getMesh(new_curr_id);
    emit currentMeshChanged(new_curr_id);
}

MeshModel *MeshDocument::addNewMesh(QString fullPath, QString Label, bool setAsCurrent)
{
    if(!fullPath.isEmpty())
    {
        QFileInfo fi(fullPath);
        fullPath = fi.absoluteFilePath();
    }
    MeshModel *newMesh = new MeshModel(this,fullPath,"");
    meshList.push_back(newMesh);

    if(setAsCurrent)
        this->setCurrentMesh(newMesh->id());

    emit meshSetChanged();
    emit meshAdded(newMesh->id());

    return newMesh;
}

MeshModel::MeshModel(MeshDocument *_parent, QString fullFileName, QString labelName)
{
    Clear();
    parent = _parent;
    _id = parent->newMeshId();
    if(!fullFileName.isEmpty()) this->fullPathFileName = fullFileName;
    if(!labelName.isEmpty()) this->_label = labelName;
}

MeshModel::MeshModel(MeshModel *cp)
{

}

void MeshModel::Clear()
{
    meshModified()=false;
    visible = true;
    cm.Tr.SetIdentity();
    cm.sfn = 0;
    cm.svn = 0;
}

bool &MeshModel::meshModified()
{
    return modified;
}
