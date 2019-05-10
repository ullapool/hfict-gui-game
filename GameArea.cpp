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
#include <algorithm>
#include <vector>

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
  srand(time(nullptr));

  // Create player
  Player *player1 = new Player(20, 410, false);
  Player *player2 = new Player(this->width() - Constants::player2Width - 20, 410, true);
  this->gameObjects.push_back(player1);
  this->gameObjects.push_back(player2);
  this->players.push_back(player1);
  this->players.push_back(player2);
  if (rand() % 2) emit this->playerToggled();

  // Create obstacle
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
}

void GameArea::removeShot(Shot *shot)
{
  auto itShots = std::find(shots.begin(), shots.end(), shot);
  auto itGameObjects = std::find(gameObjects.begin(), gameObjects.end(), shot);
  shots.erase(itShots);
  gameObjects.erase(itGameObjects);
  delete shot;
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

std::vector<Player *> GameArea::getPlayers() const
{
  return players;
}

void GameArea::next()
{
  // Move objects
  for (GameObject *gameObject : this->gameObjects) {
    gameObject->move();
  }
  this->update();

  // Check balloon hit
  for (Shot *shot : this->shots) {
    if (CollisionDetection::check(this->obstacle, shot)) {
      qDebug("Balloon hit");
      // Get impact angle
      double angle = CollisionDetection::impactAngle(this->obstacle, shot);

      // Give impulse to obstacle
      this->obstacle->impulse(shot->getSpeed(), angle);

      // Remove shot
      this->removeShot(shot);

      //emit this->gameFinished();
    }

    // Check out of bounds
    if (CollisionDetection::outOfBounds(shot, this)) {
      qDebug("Out of bounds");
      this->removeShot(shot);
    }
  }
}
