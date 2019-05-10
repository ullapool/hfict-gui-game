#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <QWidget>
#include <QImage>
#include <vector>
#include <GameObject.h>
#include "Obstacle.h"
#include "Shot.h"
#include "Player.h"

class GameArea : public QWidget
{
  Q_OBJECT

// Public Members
public:
  // Constructors
  explicit GameArea(QWidget *parent = nullptr);

  // Properties

  // Methods
  void paintEvent(QPaintEvent *event);
  void startGame();
  void shoot(int speed, int angle);
  void removeShot(Shot *shot);
  void reset();
  std::vector<Player *> getPlayers() const;

private:
  // Constructors

  // Properties
  QImage *backgroundImg;
  std::vector<GameObject*> gameObjects;
  std::vector<Shot*> shots;
  std::vector<Player*> players;
  Obstacle *obstacle;


  // Methods
  void setupAnimationThread();
  void next();

// Event Handling
signals:
  void gameFinished();
  void playerToggled();

public slots:

private slots:
};

#endif // GAMEAREA_H
