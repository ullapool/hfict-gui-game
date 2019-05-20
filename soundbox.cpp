#include "soundbox.h"
#include "Constants.h"
#include "MainWidget.h"
#include "GameArea.h"
#include <QVector>
#include <QString>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>
#include <QDebug>
#include <QSound>

Soundbox::Soundbox()
{
  //loading sounds
  shootingJukbox.push_back("bam.mp3");
  shootingJukbox.push_back("boom.mp3");
  shootingJukbox.push_back("gonnagetya.mp3");

  //ballonStriked.push_back("yaFucker.mp3");
  //ballonStriked.push_back("fanny.mp3");
  //ballonStriked.push_back("bastard.mp3");
  ballonStriked.push_back("parrot.mp3");
  ballonStriked.push_back("landHo.mp3");
  ballonStriked.push_back("juhu.mp3");
  ballonStriked.push_back("wohoo.mp3");

  opponentHit.push_back("sharks.mp3");
  opponentHit.push_back("rum.mp3");
  opponentHit.push_back("liver.mp3");
  opponentHit.push_back("aye.mp3");
  //opponentHit.push_back("stoppit.mp3");
  opponentHit.push_back("stoppityadick.mp3");

  soundtrack = "pirate.mp3";
  goalCheering = "goal.mp3";

  playList = new QMediaPlaylist;
  this->playList->addMedia(QUrl::fromLocalFile(Constants::soundFolder + soundtrack));
  this->playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

  soundtrackPlayer = new QMediaPlayer;
  this->soundtrackPlayer->setPlaylist(playList);
  this->soundtrackPlayer->play();

  musicPlayer = new QMediaPlayer;
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
        s = opponentHit.at(rand() % opponentHit.size() );
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





