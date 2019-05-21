#include "MainWindow.h"
#include <QCoreApplication>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  this->setupLayout();
  this->setupEvents();
}

void MainWindow::setupLayout()
{
  // Setup window properties
  this->setWindowTitle("The Pirate Game");
  this->setFixedSize(1000, 630);

  // Setup main widget
  this->mainWidget = new MainWidget();
  this->setCentralWidget(mainWidget);
}

void MainWindow::setupEvents()
{
}

MainWindow::~MainWindow() {}
