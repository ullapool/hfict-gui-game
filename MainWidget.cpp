#include "MainWidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
  this->createObjects();
  this->createLayout();
  this->connectObjects();
}

void MainWidget::createObjects()
{

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
  this->speedSlider = new QSlider(Qt::Orientation::Horizontal);
  this->speedSlider->setMinimum(1);
  this->speedSlider->setMaximum(100);
  this->actionButton = new QPushButton("Start");
  this->numberOfShootsInput = new QLineEdit();
  this->numberOfShootsInput->setReadOnly(true);


  // Create layout
  QVBoxLayout *layoutMain = new QVBoxLayout();
  QHBoxLayout *layoutControls = new QHBoxLayout();

  layoutControls->addWidget(actionButton);
  layoutControls->addWidget(new QLabel("#Shots"));
  layoutControls->addWidget(numberOfShootsInput);
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
  connect(this->gameArea, &GameArea::gameFinished, this, &MainWidget::onGameFinished);
}

void MainWidget::speedSliderMoved(int value)
{
  this->speedInput->setText(QString::number(value));
}

void MainWidget::angleSliderMoved(int value)
{
  this->angleInput->setText(QString::number(value));
}

void MainWidget::actionButtonClicked()
{
  if(this->actionButton->text() == "Start") {
    qDebug("Starting game");
    this->actionButton->setText("Shoot");
    this->numberOfShootsInput->setText("0");
    this->gameArea->startGame();
  } else {
    qDebug("Shooting");
    this->numberOfShootsInput->setText(
      QString::number(this->numberOfShootsInput->text().toInt() + 1)
    );
    this->gameArea->shoot(this->speedSlider->value(), this->angleSlider->value());
  }
}

void MainWidget::onGameFinished()
{
  qDebug("Game Finished");
  this->actionButton->setText("Start");
  this->numberOfShootsInput->setText("");
  this->gameArea->reset();
}
