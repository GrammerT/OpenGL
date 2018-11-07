#include "UnizWorldViewTray.h"

UnizWorldViewTray::UnizWorldViewTray()
    : mTrayInterval(-1.0f)
    , mMarginX(-1.0f)
    , mMarginY(-1.0f)
    , mBuildArea(-1.0f, -1.0f, -1.0f)
    , mVertexArray()
    , mThickLineStart(0)
    , mFaceIndexStart(0)
    , mDirty(true)
{
    resetFenceCollision();
}

UnizWorldViewTray::~UnizWorldViewTray()
{}

UnizWorldViewTray &UnizWorldViewTray::setTrayInterval(float trayInterval)
{
    mTrayInterval = trayInterval;
    return *this;
}

UnizWorldViewTray &UnizWorldViewTray::setMarginX(float marginX)
{
    mMarginX = marginX;
    return *this;
}

UnizWorldViewTray &UnizWorldViewTray::setMarginY(float marginY)
{
    mMarginY = marginY;
    return *this;
}

UnizWorldViewTray &UnizWorldViewTray::setBuildArea(const QVector3D &buildArea)
{
    mBuildArea = buildArea;
    return *this;
}

bool UnizWorldViewTray::build()
{
    if (!canBuild()) return false;

    mVertexArray.clear();

    //! vertical line
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, 0.0f));
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, mBuildArea.z()));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, mBuildArea.z()));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), mBuildArea.z()));
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), 0.0f));
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), mBuildArea.z()));

    //! top line
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, mBuildArea.z()));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, mBuildArea.z()));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, mBuildArea.z()));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), mBuildArea.z()));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), mBuildArea.z()));
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), mBuildArea.z()));
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), mBuildArea.z()));
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, mBuildArea.z()));

    //! bottom line
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), 0.0f));
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), 0.0f));
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), 0.0f));
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, 0.0f));

    //! generate grid points according to margin and interval
    float midX = mBuildArea.x() / 2;
    float maxX = mBuildArea.x() - mMarginX;
    float minX = mMarginX;
    float midY = mBuildArea.y() / 2;
    float maxY = mBuildArea.y() - mMarginY;
    float minY = mMarginY;

    for (float x = midX+mTrayInterval; x < maxX; x += mTrayInterval)
    {
        mVertexArray.push_back(QVector3D(x, minY, 0.0f));
        mVertexArray.push_back(QVector3D(x, maxY, 0.0f));
    }

    for (float x = midX-mTrayInterval; x > minX; x -= mTrayInterval)
    {
        mVertexArray.push_back(QVector3D(x, minY, 0.0f));
        mVertexArray.push_back(QVector3D(x, maxY, 0.0f));
    }

    for (float y = midY+mTrayInterval; y < maxY; y += mTrayInterval)
    {
        mVertexArray.push_back(QVector3D(minX, y, 0.0f));
        mVertexArray.push_back(QVector3D(maxX, y, 0.0f));
    }

    for (float y = midY-mTrayInterval; y > minY; y -= mTrayInterval)
    {
        mVertexArray.push_back(QVector3D(minX, y, 0.0f));
        mVertexArray.push_back(QVector3D(maxX, y, 0.0f));
    }

    mThickLineStart = mVertexArray.size();

    //! margin line points
    mVertexArray.push_back(QVector3D(minX, minY, 0.0f));
    mVertexArray.push_back(QVector3D(maxX, minY, 0.0f));
    mVertexArray.push_back(QVector3D(maxX, minY, 0.0f));
    mVertexArray.push_back(QVector3D(maxX, maxY, 0.0f));
    mVertexArray.push_back(QVector3D(maxX, maxY, 0.0f));
    mVertexArray.push_back(QVector3D(minX, maxY, 0.0f));
    mVertexArray.push_back(QVector3D(minX, maxY, 0.0f));
    mVertexArray.push_back(QVector3D(minX, minY, 0.0f));

    //! mid line points
    mVertexArray.push_back(QVector3D(midX, minY, 0.0f));
    mVertexArray.push_back(QVector3D(midX, maxY, 0.0f));
    mVertexArray.push_back(QVector3D(minX, midY, 0.0f));
    mVertexArray.push_back(QVector3D(maxX, midY, 0.0f));

    mFaceIndexStart = mVertexArray.size();

    //! bottom plane
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), 0.0f));
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), 0.0f));

    //! right plane
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), mBuildArea.z()));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, mBuildArea.z()));

    //! left plane
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, 0.0f));
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), 0.0f));
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), mBuildArea.z()));
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, mBuildArea.z()));

    //! back plane
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), mBuildArea.z()));
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), mBuildArea.z()));

    //! front plane
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, 0.0f));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, mBuildArea.z()));
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, mBuildArea.z()));

    //! top plane
    mVertexArray.push_back(QVector3D(0.0f, 0.0f, mBuildArea.z()));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), 0.0f, mBuildArea.z()));
    mVertexArray.push_back(QVector3D(mBuildArea.x(), mBuildArea.y(), mBuildArea.z()));
    mVertexArray.push_back(QVector3D(0.0f, mBuildArea.y(), mBuildArea.z()));

    //! move tray position to center
    QMatrix4x4 translation;

    translation.translate(-0.5f*mBuildArea.x(), -0.5f*mBuildArea.y(), 0.0f);

    for (QVector3D &vertex : mVertexArray)
    {
        vertex = translation * vertex;
    }

    mDirty = true;
}


void UnizWorldViewTray::reset()
{
    mTrayInterval = -1.0f;
    mMarginX = -1.0f;
    mMarginY = -1.0f;
    mBuildArea = QVector3D(-1.0f, -1.0f, -1.0f);
    mVertexArray.clear();
}

QMatrix4x4 UnizWorldViewTray::getTrayMatrix() const
{
    return QMatrix4x4();
}

void UnizWorldViewTray::draw(QOpenGLShaderProgram *program)
{
    if (mDirty)
    {
        initializeOpenGLFunctions();

        if(mArrayBuffer.isCreated())
        {
            mArrayBuffer.destroy();
        }
        mArrayBuffer.create();
        mArrayBuffer.bind();
        mArrayBuffer.allocate(&mVertexArray[0], sizeof(QVector3D)*mVertexArray.size());
        mDirty = false;
    }

    mArrayBuffer.bind();

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));

    glDrawArrays(GL_LINES, 0, mThickLineStart);
    glDrawArrays(GL_LINES, mThickLineStart, mFaceIndexStart-mThickLineStart);
    glDrawArrays(GL_LINES, mFaceIndexStart, mVertexArray.size()-mFaceIndexStart);
}

void UnizWorldViewTray::render(QOpenGLShaderProgram &program)
{
    if (mDirty)
    {
        initializeOpenGLFunctions();

        if (mArrayBuffer.isCreated())
        {
            mArrayBuffer.destroy();
        }
        mArrayBuffer.create();
        mArrayBuffer.bind();
        mArrayBuffer.allocate(&mVertexArray[0], sizeof(QVector3D)*mVertexArray.size());
        mDirty = false;
    }

    mArrayBuffer.bind();

    int vertexLocation = program.attributeLocation("a_position");
    program.enableAttributeArray(vertexLocation);
    program.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(QVector3D));

    glDisable(GL_MULTISAMPLE);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

    glDrawArrays(GL_LINES, 0, mThickLineStart);
    glDrawArrays(GL_LINES, mThickLineStart, mFaceIndexStart-mThickLineStart);
    glDrawArrays(GL_LINES, mFaceIndexStart, mVertexArray.size()-mFaceIndexStart);

    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);

}

bool UnizWorldViewTray::canBuild()
{
    return (mTrayInterval>0.0f) && (mMarginX>0.0f) && (mMarginY>0.0f) &&
            (mBuildArea.x()>0.0f) && (mBuildArea.y()>0.0f) && (mBuildArea.z()>0.0f);
}

void UnizWorldViewTray::resetFenceCollision()
{
    mFenceCollision[0] = false;
    mFenceCollision[1] = false;
    mFenceCollision[2] = false;
    mFenceCollision[3] = false;
    mFenceCollision[4] = false;
    mFenceCollision[5] = false;
}
