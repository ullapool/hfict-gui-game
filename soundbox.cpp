#include "soundbox.h"
#include "Constants.h"
#include "MainWidget.h"
#include <QVector>
#include <QString>
#include <QtMultimedia/QMediaPlayer>

#include <QDebug>

//Sounds

QString Soundbox::shots("bam.mp3");
QString Soundbox::gotHit("yaFucker.mp3");
QString Soundbox::gotHit_2("fanny.mp3");
QString Soundbox::strike("juhu.mp3");
QString Soundbox::opponentScored("bastard.mp3");

Soundbox::Soundbox()
{
 qDebug() << "Soundbox const. called" <<endl;
 this->mPlayer = new QMediaPlayer;
}

void Soundbox::shotSound()
{
   qDebug() << "playSound called" <<endl;
   QString soundPath = Constants::soundFolder;
   this->mPlayer->setMedia(QUrl::fromLocalFile(soundPath + this->shots));
   qDebug() << "after setmedia" <<endl;
   this->mPlayer->play();
}


void Soundbox::gotHitSound()
{
    QString shuffled;
    QVector<QString>soundVec;
    soundVec.push_back(gotHit);
    soundVec.push_back(gotHit_2);

    std::random_shuffle(soundVec.begin(), soundVec.end());
    shuffled = soundVec.at(0);
    QString soundPath = Constants::soundFolder;
    this->mPlayer->setMedia(QUrl::fromLocalFile(soundPath + shuffled));
    qDebug() << "after setmedia" <<endl;
    this->mPlayer->play();
}
void Soundbox::opponentScoredSound()
{
    QString soundPath = Constants::soundFolder;
    this->mPlayer->setMedia(QUrl::fromLocalFile(soundPath + this->opponentScored));
    qDebug() << "after setmedia" <<endl;
    this->mPlayer->play();

}
void Soundbox::strikeBallonSound()
{
    QString soundPath = Constants::soundFolder;
    this->mPlayer->setMedia(QUrl::fromLocalFile(soundPath + this->strike));
    qDebug() << "after setmedia" <<endl;
    this->mPlayer->play();
}
