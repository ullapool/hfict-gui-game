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
    static QString gotHit;
    static QString strike;
    static QString opponentScored;
    static QString gotHit_2;



    void shotSound();
    void gotHitSound();
    void opponentScoredSound();
    void strikeBallonSound();

private:
     QMediaPlayer *mPlayer;


};

#endif // SOUNDBOX_H
