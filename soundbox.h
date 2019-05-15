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
    static QString shots;
    static QString opponentStriked;
    static QString strike;
    static QString opponentScored;
    static QString opponentStriked_2;
    static QString goal;



    static void shotSound();
    static void gotHitSound();
    static void opponentScoredSound();
    static void goalSound();
    static void strikeBallonSound();

private:
     //QMediaPlayer *mPlayer;


};

#endif // SOUNDBOX_H
