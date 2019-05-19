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
  return this->playerTwo ? 180 - this->angle : this->angle;
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

bool Player::isPlayerTwo() const
{
  return playerTwo;
}

Player::Player(int x, int y, bool playerTwo) : playerTwo(playerTwo), shots(0), speed(50), angle(50), score(0)
{
  QString imgPath = Constants::imgFolder;
  imgPath += this->playerTwo ? Constants::player2ImgFile : Constants::player1ImgFile;
  int imgWidth = this->playerTwo ? Constants::player2Width : Constants::player1Width;
  this->x = x;
  this->y = y;
  this->img = new QImage(imgPath);
  *this->img = this->img->scaledToWidth(imgWidth);
}

void Player::move() {}
