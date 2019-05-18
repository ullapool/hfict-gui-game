#include "Player.h"
#include "Constants.h"

int Player::getShots() const
{
  return shots;
}

void Player::incrementShots()
{
  this->shots++;
}

void Player::resetShots()
{
  this->shots = 0;
}

int Player::getSpeed() const
{
  return speed;
}

void Player::setSpeed(int value)
{
  speed = value;
}

int Player::getAngle() const
{
  return this->angle;
}

int Player::getAngleConverted() const
{
  return this->isPlayerTwo ? 180 - this->angle : this->angle;
}

void Player::setAngle(int value)
{
  angle = value;
}

int Player::getScore() const
{
  return score;
}

void Player::incrementScore()
{
  this->score++;
}

void Player::resetScore()
{
  this->score = 0;
}

Player::Player(int x, int y, bool playerTwo) : isPlayerTwo(playerTwo), shots(0), speed(0), angle(0), score(0)
{
  QString imgPath = Constants::imgFolder;
  imgPath += this->isPlayerTwo ? Constants::player2ImgFile : Constants::player1ImgFile;
  int imgWidth = this->isPlayerTwo ? Constants::player2Width : Constants::player1Width;
  this->x = x;
  this->y = y;
  this->img = new QImage(imgPath);
  *this->img = this->img->scaledToWidth(imgWidth);
}

Player::~Player() {
  delete this->img;
}

void Player::move() {}
