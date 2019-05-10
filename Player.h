#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{
private:
  bool isPlayerTwo;
  int shots;
  int speed;
  int angle;
public:
  Player(int x, int y, bool playerTwo = false);
  virtual void move();
  int getShots() const;
  void incrementShots();
  int getSpeed() const;
  void setSpeed(int value);
  int getAngle() const;
  int getAngleConverted() const;
  void setAngle(int value);
};

#endif // PLAYER_H
