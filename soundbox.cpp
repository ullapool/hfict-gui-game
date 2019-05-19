#include "soundbox.h"
#include "Constants.h"
#include "MainWidget.h"
#include "GameArea.h"
#include <QVector>
#include <QString>
#include <QtMultimedia/QMediaPlayer>
#include <QDebug>

Soundbox::Soundbox()
{
  shootingJukbox.push_back(shooting = "bam.mp3");
  shootingJukbox.push_back(shooting_2 = "boom.mp3");
  shootingJukbox.push_back(shooting_3 = "gonnagetya.mp3");

  ballonStriked.push_back(opponentStriked = "yaFucker.mp3");
  ballonStriked.push_back(opponentStriked_2 = "fanny.mp3");
  ballonStriked.push_back(opponentStriked_3 = "bastard.mp3");
  ballonStriked.push_back( strike = "juhu.mp3");
  ballonStriked.push_back(strike_2 = "wohoo.mp3");

  opponentHit.push_back(shootOpponent = "stoppit.mp3");
  opponentHit.push_back(shootOpponent_2 = "stoppityadick.mp3");
  goalCheering = "goal.mp3";

  musicPlayer = new QMediaPlayer();
}

Soundbox *Soundbox::instance = nullptr;
Soundbox *Soundbox::getInstance()
{
    if(instance) {
        return Soundbox::instance;
    }
    else {
        Soundbox::instance = new Soundbox;
        return Soundbox::instance;
    }
}

void Soundbox::playSoundEffect(Sound sound)
{
    QString s;
    switch(sound) {
    case Sound::shootingJukbox :
        s = shootingJukbox.at(rand() % shootingJukbox.size() );
        break;

    case Sound::opponentHit :
        s = opponentHit.at(rand() & opponentHit.size() );
        break;
    case Sound::ballonStriked :
         s = ballonStriked.at(rand() % ballonStriked.size() );
        break;
    case Sound::goalCheering :
        s = goalCheering;
        break;
}

    this->musicPlayer->setMedia(QUrl::fromLocalFile(Constants::soundFolder + s));
    this->musicPlayer->play();

}





