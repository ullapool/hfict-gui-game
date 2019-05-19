#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <QWidget>
#include <QImage>
#include <vector>
#include <GameObject.h>
#include "Obstacle.h"
#include "Shot.h"
#include "Player.h"
#include "Goal.h"

class MainWidget;

class GameArea : public QWidget
{
  Q_OBJECT

enum class GameStatus {
  NotStarted,
  InProgress,
  Player1Won,
  Player2Won
};

// Public Members
public:
  // Constructors
  explicit GameArea(MainWidget *parent = nullptr);

  // Properties

  // Methods
  void paintEvent(QPaintEvent *event);
  void startGame();
  void shoot(Player *player);
  void removeShot();
  void reset();
  std::vector<Player *> getPlayers() const;

private:
  // Constructors

  // Properties
  MainWidget *parent;
  QImage *backgroundImg;
  QImage *scoreBoardImg;
  std::vector<GameObject*> gameObjects;
  Shot *activeShot;
  std::vector<Player*> players;
  std::vector<Goal*> goals;
  Obstacle *balloon;
  GameStatus status;


  // Methods
  void setupAnimationThread();
  void resetBalloon();
  void balloonHit();
  void balloonMissed();
  void opponentHit();
  void goalHit(Goal *goal);
  void next();

// Event Handling
signals:
  void gameFinished();
  void playerToggled();
  void shotStatusChanged(bool active);

public slots:

private slots:
};

#endif // GAMEAREA_H
