#ifndef SOUNDBOX_H
#define SOUNDBOX_H

//#include "Constants.h"
#include "GameObject.h"

#include <QtMultimedia/QMediaPlayer>

enum class Sound {
    shootingJukbox,
    ballonStriked,
    opponentHit,
    goalCheering,
    soundtrack,
};

class Soundbox
{
private:
    Soundbox();
    static Soundbox *instance;
public:
    //Sounds
    QMediaPlayer *musicPlayer;
    QMediaPlayer *soundtrackPlayer;
    QVector<QString> shootingJukbox;
    QVector<QString> ballonStriked;
    QVector<QString> opponentHit;
    QString soundtrack;
//    QString shooting;
//    QString shooting_2;
//    QString shooting_3;
//    QString opponentStriked;
//    QString opponentStriked_2;
//    QString opponentStriked_3;
//    QString strike;
//    QString strike_2;
//    QString shootOpponent;
//    QString shootOpponent_2;
      QString goalCheering;

    static Soundbox *getInstance();
    void playSoundEffect(Sound sound);


};

#endif // SOUNDBOX_H
