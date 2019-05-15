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
#include "Goal.h"
#include <QFont>
#include <MainWidget.h>

GameArea::GameArea(MainWidget *parent) : QWidget(parent), parent(parent), activeShot(nullptr), balloon(nullptr)
{
  qDebug("Game Area");

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


  if (this->players.size() == 2) {
    // Score Board
    p->setBrush(QBrush(Qt::gray));
    p->setPen(Qt::gray);
    p->drawRect(this->width() / 2 - 50, 0, 110, 50);

    QFont font;
    font.setPixelSize(40);
    p->setFont(font);
    p->setPen(Qt::white);

    p->drawText(this->width() / 2 - 35, 40, QString::number(this->players.at(0)->getScore()));
    p->drawText(this->width() / 2, 40, ":");
    p->drawText(this->width() / 2 + 25, 40, QString::number(this->players.at(1)->getScore()));

    // Player Indicator
    p->setPen(QPen(Qt::yellow, 5));
    int indicatorX = players.at(parent->isPlayerTwosTurn())->getX();
    int indicatorY = players.at(parent->isPlayerTwosTurn())->getY() + players.at(parent->isPlayerTwosTurn())->height() + 10;
    int indicatorWidth = players.at(parent->isPlayerTwosTurn())->width();
    p->drawLine(indicatorX, indicatorY, indicatorX + indicatorWidth, indicatorY);
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

void GameArea::resetBalloon()
{
  qDebug("Reset Balloon");
  if (this->balloon) {
    auto itGameObjects = std::find(gameObjects.begin(), gameObjects.end(), this->balloon);
    gameObjects.erase(itGameObjects);
    delete this->balloon;
    this->balloon = nullptr;
  }

  int x = this->width() / 2 - Constants::obstacleWidth / 2;
  int y = rand() % static_cast<int>(this->height() * 0.75);
  this->balloon = new Obstacle(x, y);
  this->gameObjects.push_back(this->balloon);
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

  // Create goal
  Goal *goal1 = new Goal(20, 30, false);
  Goal *goal2 = new Goal(this->width() - 80, 30, true);
  this->gameObjects.push_back(goal1);
  this->gameObjects.push_back(goal2);
  this->goals.push_back(goal1);
  this->goals.push_back(goal2);

  // Create obstacle
  this->resetBalloon();
}

void GameArea::shoot(Player *player)
{
  this->activeShot = new Shot(player->center().rx(), player->center().ry(), player->getSpeed(), player->getAngleConverted());
  this->gameObjects.push_back(this->activeShot);
}

void GameArea::removeShot()
{
  qDebug("Remove Shot");
  auto itGameObjects = std::find(gameObjects.begin(), gameObjects.end(), this->activeShot);
  gameObjects.erase(itGameObjects);
  delete this->activeShot;
  this->activeShot = nullptr;
}

void GameArea::reset()
{
  std::vector<GameObject*> tempObjects = this->gameObjects;

  // Remove all game objects from vectors
  this->activeShot = nullptr;
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

void GameArea::balloonHit()
{
  qDebug("Balloon hit");

  // Get impact angle
  double angle = CollisionDetection::impactAngle(this->balloon, this->activeShot);

  // Give impulse to obstacle
  this->balloon->impulse(this->activeShot->getSpeed(), angle);

  // Remove shot
  this->removeShot();
  emit this->playerToggled();
}

void GameArea::balloonMissed()
{
  qDebug("Out of bounds");

  this->removeShot();
  emit this->playerToggled();
}

void GameArea::goalHit(Goal *goal)
{
  qDebug("GOOOAAAAL");

  unsigned int scoringPlayer = !goal->isGoalTwo();
  this->players.at(scoringPlayer)->incrementScore();
  qDebug() << "Player 1: " << players.at(0)->getScore() << " | Player 2: " << players.at(1)->getScore();
  emit this->scored(static_cast<int>(scoringPlayer));
  this->resetBalloon();

  for (Player *player : this->players) player->resetShots();
}

void GameArea::next()
{
  // Move objects
  for (GameObject *gameObject : this->gameObjects) {
    gameObject->move();
  }
  this->update();

  // Check balloon hit
  if (this->activeShot && CollisionDetection::checkBalloon(this->balloon, this->activeShot)) this->balloonHit();

  // Check goal hit
  for (Goal *goal : this->goals) {
    if (this->balloon && CollisionDetection::checkGoal(this->balloon, goal)) this->goalHit(goal);
  }

  // Check boundary hit
  int boundaryCollision = this->balloon ? CollisionDetection::checkBoundary(this->balloon, this) : 0;
  if (boundaryCollision) this->balloon->impulse(boundaryCollision);

  // Check out of bounds
  if (this->activeShot && CollisionDetection::outOfBounds(this->activeShot, this)) this->balloonMissed();
}
