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
  playerOneShootingJukbox.push_back("bam.mp3");
  playerOneShootingJukbox.push_back("boom.mp3");
  playerOneShootingJukbox.push_back("gonnagetya.mp3");

  playerTwoShootingJukbox.push_back("pirateShoots.mp3");
  playerTwoShootingJukbox.push_back("pirateShoots2.mp3");
  playerTwoShootingJukbox.push_back("pirateShoots3.mp3");
  //ballonStriked.push_back("yaFucker.mp3");
  //ballonStriked.push_back("fanny.mp3");
  //ballonStriked.push_back("bastard.mp3");
  ballonStriked.push_back("parrot.mp3");
  ballonStriked.push_back("landHo.mp3");
  ballonStriked.push_back("juhu.mp3");
  ballonStriked.push_back("wohoo.mp3");

  opponentTwoHit.push_back("sharks.mp3");
  opponentTwoHit.push_back("rum.mp3");
  opponentTwoHit.push_back("liver.mp3");
  opponentTwoHit.push_back("aye.mp3");

  opponentOneHit.push_back("bastard.mp3");
  opponentOneHit.push_back("yaFucker.mp3");
  opponentOneHit.push_back("stoppityadick.mp3");
  //opponentHit.push_back("stoppit.mp3");

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
    case Sound::shootingJukboxPlayerOne :
        s = playerOneShootingJukbox.at(rand() % playerOneShootingJukbox.size() );
        break;
    case Sound::shootingJukeboxPlayerTwo :
        s = playerTwoShootingJukbox.at(rand() % playerTwoShootingJukbox.size() );
        break;
    case Sound::opponentOnetHit :
        s = opponentOneHit.at(rand() % opponentOneHit.size() );
        break;
    case Sound::opponentTwoHit :
        s = opponentTwoHit.at(rand() % opponentTwoHit.size() );
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





