#ifndef GOAL_H
#define GOAL_H

#include "GameObject.h"

class Goal : public GameObject
{
private:
  bool goalTwo;
public:
  Goal(int x, int y, bool goalTwo);
  virtual ~Goal();
  virtual void move();
  bool isGoalTwo() const;
};

#endif // GOAL_H
