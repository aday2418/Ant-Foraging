#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QObject>
#include <QWidget>

class RenderArea : public QWidget
{
  Q_OBJECT
public:
  explicit RenderArea(QWidget *parent = nullptr);

    void set_data(const uchar *data);
    void set_width(int width);
    void set_height(int height);
signals:

protected:
    const uchar* dataVal;
    int widthVal{1};
    int heightVal{1};
    void paintEvent(QPaintEvent* event) override;
};

#endif // RENDERAREA_H
