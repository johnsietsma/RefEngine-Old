#include "RefEngWindowQt.h"

#include <QMouseEvent>

RefEngWindowQT::RefEngWindowQT(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

RefEngWindowQT::~RefEngWindowQT()
{
    
}

QSize RefEngWindowQT::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize RefEngWindowQT::sizeHint() const
{
    return QSize(200, 200);
}

void RefEngWindowQT::rotateBy(int xAngle, int yAngle, int zAngle)
{
}

void RefEngWindowQT::setClearColor(const QColor &color)
{
}

void RefEngWindowQT::initializeGL()
{
}

void RefEngWindowQT::paintGL()
{
}

void RefEngWindowQT::resizeGL(int width, int height)
{
}

void RefEngWindowQT::mousePressEvent(QMouseEvent *event)
{
}

void RefEngWindowQT::mouseMoveEvent(QMouseEvent *event)
{
}

void RefEngWindowQT::mouseReleaseEvent(QMouseEvent * /* event */)
{
}
