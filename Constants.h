#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

class Constants
{
 public:
  static QString imgFolder;
  static QString soundFolder;
  static QString sceneImgFile;
  static QString startScreenImgFile;
  static QString player1WonImgFile;
  static QString player2WonImgFile;
  static int obstacleWidth;
  static QString obstacleImgFile;
  static int player1Width;
  static QString player1ImgFile;
  static int player2Width;
  static QString player2ImgFile;
  static int shotWidth;
  static QString shotImgFile;
  static int goal1Width;
  static QString goal1ImgFile;
  static int goal2Width;
  static QString goal2ImgFile;
  static int scoreBoardWidth;
  static QString scoreBoardImgFile;
  static bool showTrajectory;
  static int targetScore;
};

#endif  // CONSTANTS_H
