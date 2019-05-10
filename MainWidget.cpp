#include "MainWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
  this->createLayout();
  this->connectObjects();
}

void MainWidget::togglePlayer()
{
  this->isPlayerTwosTurn = !this->isPlayerTwosTurn;
}

bool MainWidget::getIsPlayerOnesTurn() const
{
  return isPlayerTwosTurn;
}

void MainWidget::createLayout()
{
  // Create widgets
  QLabel *title = new QLabel("<h1>The Gorilla QT Game</h1>");
  title->setFixedHeight(30);
  this->gameArea = new GameArea();
  this->angleInput = new QLineEdit("1");
  this->angleInput->setReadOnly(true);
  this->speedInput = new QLineEdit("1");
  this->speedInput->setReadOnly(true);
  this->angleSlider = new QSlider(Qt::Orientation::Horizontal);
  this->angleSlider->setMinimum(0);
  this->angleSlider->setMaximum(90);
  this->angleSlider->setEnabled(false);
  this->speedSlider = new QSlider(Qt::Orientation::Horizontal);
  this->speedSlider->setMinimum(1);
  this->speedSlider->setMaximum(100);
  this->speedSlider->setEnabled(false);
  this->actionButton = new QPushButton("Start");
  this->numberOfShotsInput = new QLineEdit();
  this->numberOfShotsInput->setReadOnly(true);


  // Create layout
  QVBoxLayout *layoutMain = new QVBoxLayout();
  QHBoxLayout *layoutControls = new QHBoxLayout();

  layoutControls->addWidget(actionButton);
  layoutControls->addWidget(new QLabel("#Shots"));
  layoutControls->addWidget(numberOfShotsInput);
  layoutControls->addWidget(new QLabel("Speed"));
  layoutControls->addWidget(speedSlider);
  layoutControls->addWidget(speedInput);
  layoutControls->addWidget(new QLabel("Angle"));
  layoutControls->addWidget(angleSlider);
  layoutControls->addWidget(angleInput);

  layoutMain->addWidget(title);
  layoutMain->addWidget(gameArea);
  layoutMain->addLayout(layoutControls);

  this->setLayout(layoutMain);
}

void MainWidget::connectObjects()
{
  connect(this->angleSlider, &QSlider::valueChanged, this, &MainWidget::angleSliderMoved);
  connect(this->speedSlider, &QSlider::valueChanged, this, &MainWidget::speedSliderMoved);
  connect(this->actionButton, &QPushButton::clicked, this, &MainWidget::actionButtonClicked);
  connect(this->gameArea, &GameArea::gameFinished, this, &MainWidget::gameFinished);
  connect(this->gameArea, &GameArea::playerToggled, this, &MainWidget::togglePlayer);
}

void MainWidget::speedSliderMoved(int value)
{
  this->speedInput->setText(QString::number(value));
  this->gameArea->getPlayers().at(this->isPlayerTwosTurn)->setSpeed(value);
}

void MainWidget::angleSliderMoved(int value)
{
  this->angleInput->setText(QString::number(value));
  this->gameArea->getPlayers().at(this->isPlayerTwosTurn)->setAngle(value);
}

void MainWidget::actionButtonClicked()
{
  if(this->actionButton->text() == "Start") {
    qDebug("Starting game");
    this->actionButton->setText("Shoot");
    this->angleSlider->setEnabled(true);
    this->speedSlider->setEnabled(true);
    this->numberOfShotsInput->setText("0");
    this->gameArea->startGame();
  } else {
    qDebug("Shooting");
    this->gameArea->getPlayers().at(this->isPlayerTwosTurn)->incrementShots();
    int shots = this->gameArea->getPlayers().at(this->isPlayerTwosTurn)->getShots();
    this->numberOfShotsInput->setText(QString::number(shots));
    this->gameArea->shoot(this->speedSlider->value(), this->angleSlider->value());
  }
}

void MainWidget::gameFinished()
{
  qDebug("Game Finished");
  this->actionButton->setText("Start");
  this->numberOfShotsInput->setText("");
  this->gameArea->reset();
}
