#ifndef SOUNDBOX_H
#define SOUNDBOX_H

//#include "Constants.h"
#include "GameObject.h"

#include <QtMultimedia/QMediaPlayer>


class Soundbox : public GameObject
{
    //Q_OBJECT
public:
    Soundbox();

    QString file;

    //Sounds
    static QString shoots;


    void playSound();
private:
     QMediaPlayer *mPlayer;

};

#endif // SOUNDBOX_H
