#include "mainwindow.h"
#include "ui_mainwindowform.h"
#include <vector>
#include <QTimer>
#include <iostream>
#include <QGridLayout>


mainWindow::mainWindow(QWidget *parent) :QMainWindow(parent), ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    setup_layout();
    timerID = startTimer(startTimerVal);
}

mainWindow::~mainWindow()
{
    killTimer(timerID);
    delete ui;
}

void mainWindow::setup_layout()
{
    QGridLayout *gridLayout = new QGridLayout(this->ui->frame);
    gridLayout->addWidget(renderArea,0,0);

    renderArea->set_data(grid.get_data());
    renderArea->set_width(grid.get_width());
    renderArea->set_height(grid.get_height());
}

void mainWindow::timerEvent(QTimerEvent *event)
{
    worldType.update_values();
    grid.update_values(worldType);
    renderArea->set_data(grid.get_data());
    renderArea->update();

}

void mainWindow::on_clearPheromones_clicked()
{
    worldType.generate_pheromones();
}


void mainWindow::on_resetMap_clicked()
{
    worldType.reset();
}


void mainWindow::on_pause_clicked()
{
    if(killed == false)
        killTimer(timerID);
    killed = true;
}


void mainWindow::on_play_clicked()
{
    if(killed == true)
        timerID = startTimer(startTimerVal);
    killed = false;
}

