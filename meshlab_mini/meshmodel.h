#ifndef MESHMODEL_H
#define MESHMODEL_H
#include "ml_mesh_type.h"

class MeshDocument;

class MeshModel
{
public:

    MeshModel(MeshDocument *_parent, QString fullFileName, QString labelName);
    MeshModel(MeshModel* cp);

    MeshDocument *parent;
    CMeshO cm;

    bool visible;
    bool isVisible(){return visible;}
    inline int id(){return _id;}
public :
    void Clear();

    bool &meshModified();
private:
    int currentDataMask;
    QString fullPathFileName;
    QString _label;
    int _id;
    bool modified;
};


class MeshDocument :public QObject
{
    Q_OBJECT
public:
    MeshDocument();

    MeshModel *getMesh(int id);
    QList<MeshModel*> meshList;

public:
    void setCurrentMesh(int new_curr_id);
    MeshModel *addNewMesh(QString fullPath, QString Label, bool setAsCurrent=true);

    int newMeshId(){return meshIdCounter++;}


private:
    MeshModel  *currentMesh;

private:
    int meshIdCounter;

signals:
    void documentUpdated();
    void meshAdded(int index);
    void currentMeshChanged(int index);
    void meshSetChanged();
};

#endif // MESHMODEL_H
