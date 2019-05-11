#include "soundbox.h"
#include "Constants.h"
//#include "GameObject.h"
//#include "MainWidget.h"
#include <QString>
#include <QtMultimedia/QMediaPlayer>

#include <QDebug>

//Sounds

QString Soundbox::shoots("bam_shoot.m4a");

Soundbox::Soundbox()
{
   this->mPlayer = new QMediaPlayer;

}

void Soundbox::playSound()
{

    qDebug() << "playSound called" <<endl;
    this->file =(Constants::soundFolder + this->shoots);
    this->mPlayer->setMedia(QUrl::fromLocalFile(this->file));
    this->mPlayer->play();

}

