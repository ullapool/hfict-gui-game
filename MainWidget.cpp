#include "MainWidget.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QVBoxLayout>
#include "soundbox.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent) {
  qDebug("Main Widget");
  this->createLayout();
  this->connectObjects();
  this->setFocusPolicy(Qt::StrongFocus);
}

void MainWidget::togglePlayer() {
  qDebug("Toggle Player");
  this->playerTwosTurn = !this->playerTwosTurn;
  Player *activePlayer = this->gameArea->getPlayers().at(this->playerTwosTurn);
  this->angleSlider->setValue(activePlayer->getAngle());
  this->speedSlider->setValue(activePlayer->getSpeed());
  this->numberOfShotsInput->setText(QString::number(activePlayer->getShots()));
  qDebug("Toggle Player finished");
}

bool MainWidget::isPlayerTwosTurn() const
{
  return playerTwosTurn;
}

void MainWidget::createLayout() {
  qDebug("Create Layout");
  // Create widgets
  QLabel *title = new QLabel("<h1>The Gorilla QT Game</h1>");
  title->setFixedHeight(30);
  this->gameArea = new GameArea(this);
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

  // Prevent controls from gaining focus
  for (int i = 0; i < layoutControls->count(); ++i) {
    QWidget *widget = layoutControls->itemAt(i)->widget();
    if (widget) {
      widget->setFocusPolicy(Qt::NoFocus);
    }
  }

  layoutMain->addWidget(title);
  layoutMain->addWidget(gameArea);
  layoutMain->addLayout(layoutControls);

  this->setLayout(layoutMain);
}

void MainWidget::connectObjects() {
  qDebug("Connect Objects");
  connect(this->angleSlider, &QSlider::valueChanged, this,
          &MainWidget::angleSliderMoved);
  connect(this->speedSlider, &QSlider::valueChanged, this,
          &MainWidget::speedSliderMoved);
  connect(this->actionButton, &QPushButton::clicked, this,
          &MainWidget::actionButtonClicked);
  connect(this->gameArea, &GameArea::gameFinished, this,
          &MainWidget::gameFinished);
  connect(this->gameArea, &GameArea::playerToggled, this,
          &MainWidget::togglePlayer);
  connect(this->gameArea, &GameArea::scored, this, &MainWidget::updateScore);

  // Controls Key Binding
  connect(this, &MainWidget::keyPressEnter, this->actionButton,
          &QPushButton::click);
  connect(this, &MainWidget::keyPressUp, [this] {
    if (this->actionButton->text() == "Shoot")
      this->angleSlider->triggerAction(QAbstractSlider::SliderSingleStepAdd);
  });
  connect(this, &MainWidget::keyPressDown, [this] {
    if (this->actionButton->text() == "Shoot")
      this->angleSlider->triggerAction(QAbstractSlider::SliderSingleStepSub);
  });
  connect(this, &MainWidget::keyPressRight, [this] {
    if (this->actionButton->text() == "Shoot")
      this->speedSlider->triggerAction(QAbstractSlider::SliderSingleStepAdd);
  });
  connect(this, &MainWidget::keyPressLeft, [this] {
    if (this->actionButton->text() == "Shoot")
      this->speedSlider->triggerAction(QAbstractSlider::SliderSingleStepSub);
  });
}

void MainWidget::updateScore() {}

void MainWidget::keyPressEvent(QKeyEvent *event) {
  qDebug() << "Key Press Event:";
  switch (event->key()) {
    case Qt::Key_Up:
      qDebug() << "  Up";
      emit this->keyPressUp();
      break;
    case Qt::Key_Down:
      qDebug() << "  Down";
      emit this->keyPressDown();
      break;
    case Qt::Key_Left:
      qDebug() << "  Left";
      emit this->keyPressLeft();
      break;
    case Qt::Key_Right:
      qDebug() << "  Right";
      emit this->keyPressRight();
      break;
    case Qt::Key_Enter:
      qDebug() << "  Enter";
      emit this->keyPressEnter();
      break;
    case Qt::Key_Return:
      qDebug() << "  Return";
      emit this->keyPressEnter();
      break;
  }
}

void MainWidget::speedSliderMoved(int value) {
  this->speedInput->setText(QString::number(value));
  this->gameArea->getPlayers().at(this->playerTwosTurn)->setSpeed(value);
}

void MainWidget::angleSliderMoved(int value) {
  this->angleInput->setText(QString::number(value));
  this->gameArea->getPlayers().at(this->playerTwosTurn)->setAngle(value);
}

void MainWidget::actionButtonClicked() {
  if (this->actionButton->text() == "Start") {
    qDebug("Starting game");
    this->actionButton->setText("Shoot");
    this->angleSlider->setEnabled(true);
    this->speedSlider->setEnabled(true);
    this->numberOfShotsInput->setText("0");
    this->gameArea->startGame();
  } else {
    qDebug("Shooting");
    Player *player = this->gameArea->getPlayers().at(this->playerTwosTurn);
    player->incrementShots();
    int shots = player->getShots();
    this->numberOfShotsInput->setText(QString::number(shots));
    this->gameArea->shoot(player);
    // sounds
    this->soundBox = new Soundbox();
    soundBox->shotSound();
  }
}

void MainWidget::gameFinished() {
  qDebug("Game Finished");
  this->actionButton->setText("Start");
  this->numberOfShotsInput->setText("");
  this->gameArea->reset();
}
