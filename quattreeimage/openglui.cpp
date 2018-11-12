#include "openglui.h"
#include "UnizModeldata.h"
#include <QMouseEvent>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFramebufferObjectFormat>
#include <QPainter>
#include <QtMath>
#include "effectiverect.h"
#include "quattree.h"
#include <QTimer>
#include <QTime>

OpenglUI::OpenglUI(QWidget *parent)
    :QOpenGLWidget(parent)
    ,isFacePro(false)
{
    data = QSharedPointer<UnizModelData>(new UnizModelData);
    formModelData(data);
}

void OpenglUI::initializeGL()
{
    initializeOpenGLFunctions();
    initShader();
    glClearColor(1.0f,0.0f,1.0f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    this->_view.setToIdentity();
    this->_view.lookAt(QVector3D(0,0,500),QVector3D(0,0,0),QVector3D(0,1,0));
    this->_view.rotate(15,0.0,1.0,0.0);
    this->_view.rotate(-75,1.0,0.0,0.0);
    this->_view.translate(QVector3D(0.0,0.0,-10.0));
}

void OpenglUI::mousePressEvent(QMouseEvent *event)
{
    _mousePressPosition = QVector2D(event->localPos());
}

void OpenglUI::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton)
    {
        QVector2D newPos = QVector2D(event->pos());
        QVector2D diff = newPos-_mousePressPosition;
        float angle = (diff.length())/3.6;
        QVector3D rotationAxis = QVector3D(diff.y(),diff.x(),0.0).normalized();
        _rotation = QQuaternion::fromAxisAndAngle(rotationAxis,angle) *_rotation;
        _mousePressPosition = newPos;
        this->update();
    }
    event->accept();
}

void OpenglUI::mouseReleaseEvent(QMouseEvent *event)
{

}

void OpenglUI::resizeGL(int w, int h)
{
    float aspect = float(w)/float(h?h:1);
    float zNear = 0.1;
    float zFar = 1000.0;
    float fov = 45.0;
    this->_projection.setToIdentity();
    this->_projection.perspective(fov,aspect,zNear,zFar);
}

void OpenglUI::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    _model.setToIdentity();
    _model.translate(QVector3D(0,0,-20));
    _model.rotate(_rotation);
    _model.scale(25.0);
    _model.translate(QVector3D(0,0,1.25));
    QMatrix4x4 MVP = _projection*_view*_model;
    if(!isFacePro)
    {
        program.setUniformValue("MVP", MVP);
        program.setUniformValue("FaceColor",QVector3D(0.5,0.5,0.5));
        program.bind();
        glPolygonMode(GL_FRONT, GL_FILL);
        if(data)
        {
            data->draw(program);
        }
        if(!_box.isNull())
            qDebug()<<_box->max<<"   " <<_box->min;
        _box = data->boundingBox(_model);
        qDebug()<<_box->max<<"   " <<_box->min;
        QMatrix4x4 b_mat;
        b_mat.setToIdentity();
        program.setUniformValue("FaceColor",QVector3D(1.0,0.0,0.0));
        program.setUniformValue("MVP", _projection*_view);
        glPolygonMode(GL_FRONT, GL_LINE);
        _box->draw(program);
        _box->reset();
    }
    else
    {
        faceProgram.bind();
        faceProgram.setUniformValue("modelView", _view*_model);
        faceProgram.setUniformValue("projection", _projection);
        glPolygonMode(GL_FRONT, GL_FILL);
        if(data)
        {
            data->draw(faceProgram);
        }
        _box = data->boundingBox(_model);
        program.bind();
        program.setUniformValue("FaceColor",QVector3D(1.0,0.0,0.0));
        program.setUniformValue("MVP", _projection*_view);
        glPolygonMode(GL_FRONT, GL_LINE);
        _box->draw(faceProgram);
        _box->reset();
    }
}

void OpenglUI::onImageClick()
{
    _box = data->boundingBox(_model);
    qDebug()<<_box->max<<"   " <<_box->min;
    isFacePro=!isFacePro;
    this->update();
}

void OpenglUI::onCaptureImage()
{
    float point_distance = 1.5;
    _box = data->boundingBox(_model);
    QMatrix4x4 projectMat;
    qDebug()<<_box->left()<<"\n"<<
                        _box->right()<<"\n"<<
                        _box->down()<<"\n"<<
                        _box->up();
    projectMat.ortho(_box->left(),_box->right(),_box->down(),_box->up(),-500.0,500.0);
    QMatrix4x4 viewMat;
    viewMat.lookAt(_box->center()-QVector3D(0,0,15.0),_box->center(),QVector3D(0.0,1.0,0.0));
    qDebug()<<_box->center()-QVector3D(0,0,15.0);

//    const QRect drawRect(0, 0, _box->right()-_box->left(), _box->up()-_box->down());
    float long_length = _box->right()-_box->left()>_box->up()-_box->down()?_box->right()-_box->left():_box->up()-_box->down();
    float short_length = _box->right()-_box->left()<_box->up()-_box->down()?_box->right()-_box->left():_box->up()-_box->down();

    float height = 800.0;
    float aspect = height/long_length;
    float width = short_length*aspect;
    const QRect drawRect(0, 0, height,width);

    const QSize drawRectSize = drawRect.size();

    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::Depth);
    QOpenGLFramebufferObject fbo(drawRectSize, format);
    glEnable(GL_DEPTH_TEST);

    fbo.bind();
//    glViewport(0, 0, _box->right()-_box->left(), _box->up()-_box->down());
    glViewport(0, 0, height,width);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    faceProgram.bind();
    faceProgram.setUniformValue("projection", projectMat);
    faceProgram.setUniformValue("modelView",viewMat*_model);
    glPolygonMode(GL_FRONT, GL_FILL);
    if(data)
    {
        data->draw(faceProgram);
    }
    QImage image = fbo.toImage();
    image.save("haha.png");
    fbo.release();
    glDisable(GL_DEPTH_TEST);
    QVector3D changed_point_start = _model.mapVector(QVector3D(0.0,0.0,0.0));;
    QVector3D changed_point_end = _model.mapVector(QVector3D(0.0,0.0,point_distance));
    point_distance = changed_point_start.distanceToPoint(changed_point_end);
    generatePoint(image,point_distance,aspect);
}

void OpenglUI::formTray()
{
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINE);
    for(int i=0;i<=20;++i)
    {
        glVertex2f(-10+i,5);
        glVertex2f(-10+i,-5);
    }
    glEnd();
    glBegin(GL_LINE);
    for(int i=0;i<=10;++i)
    {
        glVertex2f(10,-5+i);
        glVertex2f(-10,-5+i);
    }
    glEnd();
}

void OpenglUI::formModelData(QSharedPointer<UnizModelData> data)
{
    QSharedPointer<Vec3Array> vertexArray(new Vec3Array());
     vertexArray->push_back(QVector3D(2.5,1.25,0.0));
     vertexArray->push_back(QVector3D(-2.5,-1.25,0.0));
     vertexArray->push_back(QVector3D(2.5,-1.25,0.0));

     vertexArray->push_back(QVector3D(2.5,1.25,0.0));
     vertexArray->push_back(QVector3D(-2.5,1.25,0.0));
     vertexArray->push_back(QVector3D(-2.5,-1.25,0.0));

     vertexArray->push_back(QVector3D(2.5,1.25,0.0));
     vertexArray->push_back(QVector3D(2.5,1.25,-2.5));
     vertexArray->push_back(QVector3D(-2.5,1.25,0.0));

     vertexArray->push_back(QVector3D(2.5,1.25,-2.5));
     vertexArray->push_back(QVector3D(-2.5,1.25,-2.5));
     vertexArray->push_back(QVector3D(-2.5,1.25,0.0));

     vertexArray->push_back(QVector3D(2.5,-1.25,-2.5));
     vertexArray->push_back(QVector3D(-2.5,1.25,-2.5));
     vertexArray->push_back(QVector3D(2.5,1.25,-2.5));

     vertexArray->push_back(QVector3D(2.5,-1.25,-2.5));
     vertexArray->push_back(QVector3D(-2.5,-1.25,-2.5));
     vertexArray->push_back(QVector3D(-2.5,1.25,-2.5));

     vertexArray->push_back(QVector3D(2.5,-1.25,-2.5));
     vertexArray->push_back(QVector3D(2.5,-1.25,0.0));
     vertexArray->push_back(QVector3D(-2.5,-1.25,-2.5));

     vertexArray->push_back(QVector3D(2.5,-1.25,0.0));
     vertexArray->push_back(QVector3D(-2.5,-1.25,0.0));
     vertexArray->push_back(QVector3D(-2.5,-1.25,-2.5));

     vertexArray->push_back(QVector3D(2.5,1.25,0.0));
     vertexArray->push_back(QVector3D(2.5,-1.25,0.0));
     vertexArray->push_back(QVector3D(2.5,1.25,-2.5));

     vertexArray->push_back(QVector3D(2.5,1.25,-2.5));
     vertexArray->push_back(QVector3D(2.5,-1.25,0.0));
     vertexArray->push_back(QVector3D(2.5,-1.25,-2.5));

     vertexArray->push_back(QVector3D(-2.5,1.25,0.0));
     vertexArray->push_back(QVector3D(-2.5,1.25,-2.5));
     vertexArray->push_back(QVector3D(-2.5,-1.25,-2.5));

     vertexArray->push_back(QVector3D(-2.5,-1.25,-2.5));
     vertexArray->push_back(QVector3D(-2.5,-1.25,0.0));
     vertexArray->push_back(QVector3D(-2.5,1.25,0.0));

    data->setVertexArray(vertexArray);

    QSharedPointer<Vec3Array> norArray(new Vec3Array());
     norArray->push_back(QVector3D(0.0,0.0,1.0));

    norArray->push_back(QVector3D(0.0,0.0,1.0));
    norArray->push_back(QVector3D(0.0,1.0,0.0));
    norArray->push_back(QVector3D(0.0,1.0,0.0));
    norArray->push_back(QVector3D(0.0,0.0,-1.0));
    norArray->push_back(QVector3D(0.0,0.0,-1.0));
    norArray->push_back(QVector3D(0.0,-1.0,0.0));
    norArray->push_back(QVector3D(0.0,-1.0,0.0));
    norArray->push_back(QVector3D(1.0,0.0,0.0));
    norArray->push_back(QVector3D(1.0,0.0,0.0));
     norArray->push_back(QVector3D(-1.0,0.0,0.0));
     norArray->push_back(QVector3D(-1.0,0.0,0.0));

    data->setNormalArray(norArray);

    QSharedPointer<Vec3Array> colorArray(new Vec3Array);

    QSharedPointer<IndexArray> indexArray(new IndexArray());
    indexArray->push_back(0);
    indexArray->push_back(2);
    indexArray->push_back(1);
    colorArray->push_back(QVector3D(0,0,1));

    indexArray->push_back(0);
    indexArray->push_back(3);
    indexArray->push_back(2);
    colorArray->push_back(QVector3D(0,0,2));

    indexArray->push_back(0);
    indexArray->push_back(4);
    indexArray->push_back(3);
    colorArray->push_back(QVector3D(0,0,3));


    indexArray->push_back(4);
    indexArray->push_back(7);
    indexArray->push_back(3);
    colorArray->push_back(QVector3D(0,0,4));

    indexArray->push_back(5);
    indexArray->push_back(7);
    indexArray->push_back(4);
    colorArray->push_back(QVector3D(0,0,5));

    indexArray->push_back(5);
    indexArray->push_back(6);
    indexArray->push_back(7);
    colorArray->push_back(QVector3D(0,0,6));

    indexArray->push_back(5);
    indexArray->push_back(1);
    indexArray->push_back(6);
    colorArray->push_back(QVector3D(0,0,7));

    indexArray->push_back(1);
    indexArray->push_back(2);
    indexArray->push_back(6);
    colorArray->push_back(QVector3D(0,0,8));

    indexArray->push_back(0);
    indexArray->push_back(1);
    indexArray->push_back(4);
    colorArray->push_back(QVector3D(0,0,9));

    indexArray->push_back(4);
    indexArray->push_back(1);
    indexArray->push_back(5);
    colorArray->push_back(QVector3D(0,0,10));

    indexArray->push_back(3);
    indexArray->push_back(7);
    indexArray->push_back(6);
    colorArray->push_back(QVector3D(0,0,11));

    indexArray->push_back(6);
    indexArray->push_back(2);
    indexArray->push_back(3);
    colorArray->push_back(QVector3D(0,0,12));

    data->setIndiceArray(indexArray);
    data->setPColors(colorArray);

    GLsizei count = indexArray.data()->size();
    const GLuint *indices = &(*indexArray)[0];
    const GLuint *iLast = &indices[count];
    for (const GLuint *iptr=indices; iptr<iLast; iptr+=3)
    {
        data->formHedge(*iptr,*(iptr+1), *(iptr+2));
    }

    GLsizei count1 = indexArray.data()->size();
    const GLuint *indices1 = &(*indexArray)[0];
    const GLuint *iLast1 = &indices[count1];
    for (const GLuint *iptr1=indices1; iptr1<iLast1; iptr1+=3)
    {
        data->formColors(*iptr1,*(iptr1+1), *(iptr1+2));
    }
}

void OpenglUI::initShader()
{
    // Compile vertex shader
    if (!faceProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshaderPickFace.glsl"))
        close();
    // Compile fragment shader
    if (!faceProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshaderPickFace.glsl"))
        close();
    // Link shader pipeline
    if (!faceProgram.link())
        close();
    // Bind shader pipeline for use
    if (!faceProgram.bind())
        close();
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/function.vert"))
        close();
    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/function.frag"))
        close();
    // Link shader pipeline
    if (!program.link())
        close();
    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! distance : mm
void OpenglUI::generatePoint(QImage &img, float distance,float aspect)
{
    QSize img_size = img.size();
    int longSide = img_size.width()>img_size.height()?img_size.width():img_size.height();
    int distance_to_pixel = distance * aspect;

    int ln = ceil(qLn(longSide/distance_to_pixel)/qLn(2));
    int uppow = qPow(2,ln);
    longSide = distance_to_pixel * uppow;
    QImage img1(longSide ,longSide,QImage::Format_ARGB32);
    img1.fill(QColor(0,0,0,255));
    QImage overImg =  mergeTwoImage(img1,img);

    qDebug()<<overImg.size();
    overImg.save("haha_changed.png");
    capturePoint(overImg,distance_to_pixel,qLn(uppow)/qLn(2));


}

QImage OpenglUI::mergeTwoImage(QImage baseImage, QImage upImage)
{
    QImage imgOver = QImage(baseImage.size(),baseImage.format());
    QPainter painter(&imgOver);

    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(imgOver.rect(), Qt::transparent);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, baseImage);

    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, upImage);

    painter.end();

    return imgOver;
}

void OpenglUI::capturePoint(QImage image, int distance_pixel,int tree_deep)
{
    qDebug()<<image.width()/distance_pixel;
    qDebug()<<tree_deep;
    QTime time;
    time.start();
    QSharedPointer<QuatTree<EffectiveRect>> quatTree(new QuatTree<EffectiveRect>(image.rect(),tree_deep));
    QVector<QRect> v = quatTree->leafs();
    qDebug()<<v.size();
    for(auto rect:v)
    {
        qDebug()<<rect;
     }
    QImage img = painterRectToImage(image,v);
    qDebug()<<img.size();
    img.save("haha_changed_have_rect.png");
    qDebug()<<time.elapsed()/1000.0<<"s";
}

QImage OpenglUI::painterRectToImage(QImage image, QVector<QRect> &rects)
{
    QPainter painter(&image);
    painter.setPen(Qt::green);//设置画笔形式
    for(auto rect: rects)
    {
        painter.drawRect(rect);
    }

    painter.end();

    return image;
}


