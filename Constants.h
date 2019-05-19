#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QString>

class Constants {
 public:
  static QString imgFolder;
  static int obstacleWidth;
  static QString obstacleImgFile;
  static int player1Width;
  static QString player1ImgFile;
  static int player2Width;
  static QString player2ImgFile;
  static int shotWidth;
  static QString shotImgFile;
  static QString goal1ImgFile;
  static QString goal2ImgFile;

  // Sounds
  static QString soundFolder;

  static bool showTrajectory;

};

#endif  // CONSTANTS_H
