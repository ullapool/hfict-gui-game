#ifndef SOUNDBOX_H
#define SOUNDBOX_H

//#include "Constants.h"
#include "GameObject.h"

#include <QtMultimedia/QMediaPlayer>


class Soundbox
{
public:
    Soundbox();
    //Sounds
    static QString shooting;
    static QString shooting_2;
    static QString shooting_3;
    static QString opponentStriked;
    static QString opponentStriked_2;
    static QString opponentStriked_3;
    static QString strike;
    static QString strike_2;
    static QString shootOpponent;
    static QString shootOpponent_2;

    static QString goalCheering;



    static void playSoundEffect(QString sound);


};

#endif // SOUNDBOX_H
