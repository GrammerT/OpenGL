#ifndef OPENGLUI_H
#define OPENGLUI_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>


class OpenglUI :public QOpenGLWidget,protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenglUI(QWidget *parent =0);
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void keyPressEvent(QKeyEvent *event)override;
public slots:
    void onChangeState1(bool);
    void onChangeState2(bool);
    void onChangeState3(bool);
private:
    GLfloat xRot;
    GLfloat yRot;

    QAction *action1;
    QAction *action2;
    QAction *action3;
};

#endif // OPENGLUI_H
