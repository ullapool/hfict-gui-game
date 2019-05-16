#include "soundbox.h"
#include "Constants.h"
#include "MainWidget.h"
#include "GameArea.h"
#include <QVector>
#include <QString>
#include <QtMultimedia/QMediaPlayer>

#include <QDebug>

//Sounds

QString Soundbox::shots("bam.mp3");
QString Soundbox::opponentStriked("yaFucker.mp3");
QString Soundbox::opponentStriked_2("fanny.mp3");
QString Soundbox::strike("juhu.mp3");
QString Soundbox::opponentScored("bastard.mp3");
QString Soundbox::goal("goal.mp3");

Soundbox::Soundbox()
{
 qDebug() << "Soundbox const. called" <<endl;
}

void Soundbox::shotSound()
{
   QMediaPlayer *mPlayer = new QMediaPlayer;
   mPlayer->setMedia(QUrl::fromLocalFile(Constants::soundFolder + shots));
   mPlayer->play();
}

void Soundbox::gotHitSound()
{
    QString shuffled;
    QVector<QString>soundVec;
    soundVec.push_back(opponentStriked);
    soundVec.push_back(opponentStriked_2);
    soundVec.push_back(strike);

    std::random_shuffle(soundVec.begin(), soundVec.end());
    shuffled = soundVec.at(0);
    
    QMediaPlayer *mPlayer = new QMediaPlayer;
    mPlayer->setMedia(QUrl::fromLocalFile(Constants::soundFolder + shuffled));
    mPlayer->play();
}

void Soundbox::opponentScoredSound()
{
    QMediaPlayer *mPlayer = new QMediaPlayer;
    mPlayer->setMedia(QUrl::fromLocalFile(Constants::soundFolder + opponentScored));
    qDebug() << "after setmedia" <<endl;
    mPlayer->play();

}

void Soundbox::strikeBallonSound()
{
    QMediaPlayer *mPlayer = new QMediaPlayer;
    mPlayer->setMedia(QUrl::fromLocalFile(Constants::soundFolder + strike));
    qDebug() << "after setmedia" <<endl;
    mPlayer->play();
}

void Soundbox::goalSound()
{
    
    QMediaPlayer *mPlayer = new QMediaPlayer;
    mPlayer->setMedia(QUrl::fromLocalFile(Constants::soundFolder + goal));
    mPlayer->play();
}
