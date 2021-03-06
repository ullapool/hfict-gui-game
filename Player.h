#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
private:
  bool playerTwo;
  int shots;
  int speed;
  int angle;
  int score;
public:
  Player(int x, int y, bool playerTwo = false);
  virtual void move();
  int getShots() const;
  void incrementShots();
  void resetShots();
  int getSpeed() const;
  void setSpeed(int value);
  int getAngle() const;
  int getAngleConverted() const;
  void setAngle(int value);
  int getScore() const;
  void incrementScore();
  void resetScore();
  bool isPlayerTwo() const;
};

#endif // PLAYER_H
