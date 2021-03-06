#ifndef SOUNDBOX_H
#define SOUNDBOX_H
#include "GameObject.h"
#include <QMediaPlaylist>
#include <QtMultimedia/QMediaPlayer>

enum class Sound {
    shootingJukboxPlayerOne,
    shootingJukeboxPlayerTwo,
    ballonStriked,
    opponentOnetHit,
    opponentTwoHit,
    goalCheering,
};

class Soundbox
{
private:
    Soundbox();
    static Soundbox *instance;

public:
    QMediaPlayer *musicPlayer;
    QMediaPlayer *soundtrackPlayer;
    QMediaPlaylist *playList;
    QVector<QString> playerOneShootingJukbox;
    QVector<QString> playerTwoShootingJukbox;
    QVector<QString> ballonStriked;
    QVector<QString> opponentOneHit;
    QVector<QString> opponentTwoHit;
    QString soundtrack;
    QString goalCheering;

    static Soundbox *getInstance();
    void playSoundEffect(Sound sound);


};

#endif // SOUNDBOX_H
