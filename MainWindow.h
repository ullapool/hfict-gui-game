#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MainWidget.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

// Public Members
public:
  // Constructors
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  // Properties

  // Methods

// Private Members
private:
  // Constructors
  MainWindow operator=(const MainWindow & obj);
  MainWindow(const MainWindow & obj);

  // Properties
  MainWidget *mainWidget;

  // Methods
  void setupLayout();
  void setupEvents();


// Event Handling
signals:

public slots:

private slots:

};

#endif // MAINWINDOW_H
