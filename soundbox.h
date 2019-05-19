#ifndef SOUNDBOX_H
#define SOUNDBOX_H
#include <QSound>
#include "GameObject.h"
#include <QMediaPlaylist>
#include <QtMultimedia/QMediaPlayer>

enum class Sound {
    shootingJukbox,
    ballonStriked,
    opponentHit,
    goalCheering,
    //soundtrack,
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
    QMediaPlaylist *playList;
    QVector<QString> shootingJukbox;
    QVector<QString> ballonStriked;
    QVector<QString> opponentHit;
    QString soundtrack;
    QString goalCheering;

    static Soundbox *getInstance();
    void playSoundEffect(Sound sound);


};

#endif // SOUNDBOX_H
