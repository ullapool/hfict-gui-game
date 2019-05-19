#include "soundbox.h"
#include "Constants.h"
#include "MainWidget.h"
#include "GameArea.h"
#include <QVector>
#include <QString>
#include <QtMultimedia/QMediaPlayer>
#include <QDebug>
#include <QSound>

Soundbox::Soundbox()
{
  shootingJukbox.push_back("bam.mp3");
  shootingJukbox.push_back("boom.mp3");
  shootingJukbox.push_back("gonnagetya.mp3");

  ballonStriked.push_back("yaFucker.mp3");
  ballonStriked.push_back("fanny.mp3");
  ballonStriked.push_back("bastard.mp3");
  ballonStriked.push_back("juhu.mp3");
  ballonStriked.push_back("wohoo.mp3");

  opponentHit.push_back("stoppit.mp3");
  opponentHit.push_back("stoppityadick.mp3");

  soundtrack = "pirate.mp3";
  goalCheering = "goal.mp3";

  musicPlayer = new QMediaPlayer();

  soundtrackPlayer = new QSound(Constants::soundFolder + soundtrack);
  this->soundtrackPlayer->setLoops(4);
  this->soundtrackPlayer->play();
//  musicPlayer = new QMediaPlayer();
//  soundtrackPlayer = new QMediaPlayer();
//  this->soundtrackPlayer->setMedia(QUrl::fromLocalFile(Constants::soundFolder + soundtrack));
//  this->soundtrackPlayer->play();
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
    QString m;
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





