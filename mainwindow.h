#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "world.h"
#include "renderarea.h"
#include "colorgrid.h"

namespace Ui {class mainWindow;}

class mainWindow : public QMainWindow
{
    Q_OBJECT

private:
    RenderArea* renderArea = new RenderArea(this);
    bool killed{false};
public:
    explicit mainWindow(QWidget *parent = nullptr);
    ~mainWindow();
    void setup_layout();
    void setup_paint_event();
    void setup_timer();
private:
    Ui::mainWindow *ui;
    int timerID;
    int startTimerVal{10};
protected:
    void timerEvent(QTimerEvent *event);
    world worldType;
    ColorGrid grid{static_cast<unsigned int>(worldType.get_grid_size()),static_cast<unsigned int>(worldType.get_grid_size())};
private slots:
    void on_clearPheromones_clicked();
    void on_resetMap_clicked();
    void on_pause_clicked();
    void on_play_clicked();
};

#endif // MAINWINDOW_H
