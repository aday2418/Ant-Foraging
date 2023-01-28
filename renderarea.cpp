#include "renderarea.h"
#include <qpainter.h>
#include <QDebug>
#include <QImage>
#include <iostream>

RenderArea::RenderArea(QWidget *parent) : QWidget{parent}
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void RenderArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    int intSize = sizeof(int);
    int numberOfBytesPerWidth{widthVal*intSize};
    QImage gridImage{dataVal,widthVal,heightVal,numberOfBytesPerWidth,QImage::Format_ARGB32};
    painter.drawImage(QRect{0,0,this->width(),this->height()},gridImage);
}

void RenderArea::set_data(const uchar* data)
{
    dataVal = data;
}

void RenderArea::set_width(int width)
{
    widthVal = width;
}

void RenderArea::set_height(int height)
{
    heightVal = height;
}
