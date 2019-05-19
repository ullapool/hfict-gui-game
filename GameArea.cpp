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

GameArea::GameArea(MainWidget *parent) :
  QWidget(parent),
  parent(parent),
  activeShot(nullptr),
  balloon(nullptr),
  status(GameStatus::NotStarted)
{
  qDebug("Game Area");

  // Load background image
  this->backgroundImg = new QImage(Constants::imgFolder + Constants::sceneImgFile);
  *this->backgroundImg = this->backgroundImg->scaledToWidth(1000);

  // Load screen images
  this->startScreenImg = new QImage(Constants::imgFolder + Constants::startScreenImgFile);
  *this->startScreenImg = this->startScreenImg->scaledToWidth(1000);
  this->player1WonImg = new QImage(Constants::imgFolder + Constants::player1WonImgFile);
  *this->player1WonImg = this->player1WonImg->scaledToWidth(1000);
  this->player2WonImg = new QImage(Constants::imgFolder + Constants::player2WonImgFile);
  *this->player2WonImg = this->player2WonImg->scaledToWidth(1000);

  // Load score board image
  this->scoreBoardImg = new QImage(Constants::imgFolder + Constants::scoreBoardImgFile);
  *this->scoreBoardImg = this->scoreBoardImg->scaledToWidth(Constants::scoreBoardWidth);

  // Setup animation thread
  this->setupAnimationThread();
}

void GameArea::paintEvent(QPaintEvent *event)
{
  QPainter *p = new QPainter(this);

  // Background
  p->drawImage(0, 0, *this->backgroundImg);

  switch (this->status) {
  case GameStatus::NotStarted :
    p->drawImage(0, 0, *this->startScreenImg);
    break;
  case GameStatus::InProgress :
    // Game objects
    for (GameObject *gameObject : this->gameObjects) {
      gameObject->paint(p);
    }

    if (this->players.size() == 2) {
      // Score Board
      p->drawImage(this->width() / 2 - 50, -10, *this->scoreBoardImg);

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

    // Shot trajectory
    if (Constants::showTrajectory && this->players.size() == 2 && !this->activeShot) {
      p->setPen(QPen(Qt::red, 3));
      Player *player = this->players.at(parent->isPlayerTwosTurn());
      double t = 0;
      int x = player->center().rx();
      int y = player->center().ry();
      for (int i = 0; i < 30; i++) {
        int angle = player->getAngleConverted();
        int speed = player->getSpeed();
        const double g = 9.81;
        double rad = 3.1415926 / 180 * angle;
        int dx = speed/3 * cos(rad) * t;
        int dy = speed/3 * sin(rad) * t - (g/2) * pow(t, 2);
        t += 0.1;
        x += dx / 2;
        y -= dy / 2;
        p->drawPoint(x, y);
      };
    }
    break;
  case GameStatus::Player1Won :
    p->drawImage(0, 0, *this->player1WonImg);
    break;
  case GameStatus::Player2Won :
    p->drawImage(0, 0, *this->player2WonImg);
    break;
  }

  delete p;
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
  this->status = GameStatus::InProgress;
  srand(time(nullptr));

  // Create goal
  Goal *goal1 = new Goal(-10, 30, false);
  Goal *goal2 = new Goal(this->width() - Constants::goal2Width + 10, 30, true);
  this->gameObjects.push_back(goal1);
  this->gameObjects.push_back(goal2);
  this->goals.push_back(goal1);
  this->goals.push_back(goal2);

  // Create player
  Player *player1 = new Player(5, 340, false);
  Player *player2 = new Player(this->width() - Constants::player2Width - 5, 340, true);
  this->gameObjects.push_back(player1);
  this->gameObjects.push_back(player2);
  this->players.push_back(player1);
  this->players.push_back(player2);
  emit this->playerToggled();
  if (rand() % 2) emit this->playerToggled();

  // Create obstacle
  this->resetBalloon();
}

void GameArea::shoot(Player *player)
{
  this->activeShot = new Shot(player->center().rx(), player->center().ry() - 30, player->getSpeed(), player->getAngleConverted());
  this->gameObjects.push_back(this->activeShot);
  emit shotStatusChanged(true);
}

void GameArea::removeShot()
{
  qDebug("Remove Shot");
  auto itGameObjects = std::find(gameObjects.begin(), gameObjects.end(), this->activeShot);
  gameObjects.erase(itGameObjects);
  delete this->activeShot;
  this->activeShot = nullptr;
  emit this->playerToggled();
  emit shotStatusChanged(false);
}

void GameArea::reset()
{
  // Delete all game objects
  for (GameObject *gameObject : this->gameObjects) {
    delete gameObject;
  }

  // Remove all game objects from vectors
  this->gameObjects.clear();
  this->players.clear();
  this->goals.clear();
  this->activeShot = nullptr;
  this->balloon = nullptr;
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
}

void GameArea::balloonMissed()
{
  qDebug("Out of bounds");

  this->removeShot();
}

void GameArea::opponentHit()
{
  qDebug("Opponent Hit");
  this->removeShot();
  // play sound here
}

void GameArea::goalHit(Goal *goal)
{
  qDebug("GOOOAAAAL");
  Player *scoringPlayer = this->players.at(!goal->isGoalTwo());
  scoringPlayer->incrementScore();
  qDebug() << "Player 1: " << players.at(0)->getScore() << " | Player 2: " << players.at(1)->getScore();
  this->resetBalloon();
  for (Player *player : this->players) player->resetShots();
  if (scoringPlayer->getScore() == Constants::targetScore) {
    this->status = scoringPlayer->isPlayerTwo() ? GameStatus::Player2Won : GameStatus::Player1Won;
    emit this->gameFinished();
    this->reset();
  }
}

void GameArea::next()
{
  // Move objects
  for (GameObject *gameObject : this->gameObjects) {
    gameObject->move();
  }
  this->update();

  // Check balloon hit
  if (this->activeShot && this->balloon && CollisionDetection::checkHit(this->balloon, this->activeShot)) this->balloonHit();

  // Check goal hit
  for (Goal *goal : this->goals) {
    if (this->balloon && CollisionDetection::checkGoal(this->balloon, goal)) this->goalHit(goal);
  }

  // Check boundary hit
  if (this->balloon) this->balloon->impulse(CollisionDetection::checkBoundary(this->balloon, this));

  // Check opponent hit
  if (this->activeShot && this->players.size() == 2 && CollisionDetection::checkHit(this->players.at(!parent->isPlayerTwosTurn()), this->activeShot)) this->opponentHit();

  // Check out of bounds
  if (this->activeShot && CollisionDetection::outOfBounds(this->activeShot, this)) this->balloonMissed();
}
