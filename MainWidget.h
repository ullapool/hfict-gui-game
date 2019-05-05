#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include "GameArea.h"


class MainWidget : public QWidget
{
  Q_OBJECT

// Public Members
public:
  // Constructors
  MainWidget(QWidget *parent = nullptr);

  // Properties

  // Methods

// Private Members
private:
  // Constructors
  MainWidget(const MainWidget & obj);
  MainWidget operator=(const MainWidget & obj);

  // Properties
  QSlider *angleSlider;
  QSlider *speedSlider;
  QPushButton *actionButton;
  QLineEdit *numberOfShootsInput;
  QLineEdit *speedInput;
  QLineEdit *angleInput;
  GameArea *gameArea;

  // Methods
  void createObjects();
  void createLayout();
  void connectObjects();


// Event Handling
signals:

public slots:
  void speedSliderMoved(int value);
  void angleSliderMoved(int value);
  void actionButtonClicked();
  void onGameFinished();

private slots:

};

#endif // MAINWIDGET_H
