#include "soundbox.h"
#include "Constants.h"
#include "MainWidget.h"
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

   qDebug() << "playSound called" <<endl;
   QString soundPath = Constants::soundFolder;
   QMediaPlayer *mPlayer = new QMediaPlayer;
   mPlayer->setMedia(QUrl::fromLocalFile(soundPath + shots));
   qDebug() << "after setmedia" <<endl;
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
    QString soundPath = Constants::soundFolder;
    QMediaPlayer *mPlayer = new QMediaPlayer;
    mPlayer->setMedia(QUrl::fromLocalFile(soundPath + shuffled));
    qDebug() << "after setmedia" <<endl;
    mPlayer->play();
}
void Soundbox::opponentScoredSound()
{
    QString soundPath = Constants::soundFolder;
    QMediaPlayer *mPlayer = new QMediaPlayer;
    mPlayer->setMedia(QUrl::fromLocalFile(soundPath + opponentScored));
    qDebug() << "after setmedia" <<endl;
    mPlayer->play();

}
void Soundbox::strikeBallonSound()
{
    QString soundPath = Constants::soundFolder;
    QMediaPlayer *mPlayer = new QMediaPlayer;
    mPlayer->setMedia(QUrl::fromLocalFile(soundPath + strike));
    qDebug() << "after setmedia" <<endl;
    mPlayer->play();
}
void Soundbox::goalSound()
{
    QString soundPath = Constants::soundFolder;
    QMediaPlayer *mPlayer = new QMediaPlayer;
    mPlayer->setMedia(QUrl::fromLocalFile(soundPath + goal));
    qDebug() << "after setmedia" <<endl;
    mPlayer->play();
}
