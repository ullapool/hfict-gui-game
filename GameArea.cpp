#include "GameArea.h"
#include "Constants.h"
#include <QImage>
#include <QPainter>
#include <Obstacle.h>
#include <Player.h>
#include <Shot.h>
#include "Thread.h"
#include "CollisionDetection.h"
#include <QDebug>
#include <cmath>

GameArea::GameArea(QWidget *parent) : QWidget(parent)
{
  // Load background image
  this->backgroundImg = new QImage(Constants::imgFolder + "background.jpg");
  *this->backgroundImg = this->backgroundImg->scaledToWidth(1000);


  // Setup animation thread
  this->setupAnimationThread();
}

void GameArea::paintEvent(QPaintEvent *event)
{
  QPainter *p = new QPainter(this);

  // Background
  p->drawImage(0, 0, *this->backgroundImg);

  // Game objects
  for (GameObject *gameObject : this->gameObjects) {
    gameObject->paint(p);
  }

  // Release painting ressources
  p->end();
}

void GameArea::setupAnimationThread()
{
  Thread *animationThread = new Thread();
  connect(animationThread, &Thread::refresh, this, &GameArea::next);
  animationThread->start();
}

void GameArea::startGame()
{
  // Create player
  this->gameObjects.push_back(new Player(20, 410));

  // Create obstacle
  srand(time(nullptr));
  int x = this->width() / 2 - Constants::obstacleWidth / 2;
  int y = rand() % static_cast<int>(this->height() * 0.75);
  this->obstacle = new Obstacle(x, y);
  this->gameObjects.push_back(this->obstacle);
}

void GameArea::shoot(int speed, int angle)
{
  Shot *shot = new Shot(50, 410, speed, angle);
  this->gameObjects.push_back(shot);
  this->shots.push_back(shot);
  qDebug() << std::atan2(0, 10);
  qDebug() << std::atan2(10, 0);
  qDebug() << std::atan2(0, -10);
  qDebug() << std::atan2(-10, 0);
}

void GameArea::reset()
{
  std::vector<GameObject*> tempObjects = this->gameObjects;

  // Remove all game objects from vectors
  this->shots.clear();
  this->gameObjects.clear();

  // Delete all game objects
  for (GameObject *gameObject : tempObjects) {
    delete gameObject;
  }
}

void GameArea::next()
{
  // Move objects
  for (GameObject *gameObject : this->gameObjects) {
    gameObject->move();
  }
  this->update();

  // Collision detection
  for (Shot *shot : this->shots) {
    if (CollisionDetection::check(this->obstacle, shot)) {
      qDebug("Collision");
      double angle = CollisionDetection::impactAngle(this->obstacle, shot);
      this->obstacle->impulse(shot->getSpeed(), angle);
      //emit this->gameFinished();
    }
  }
}
