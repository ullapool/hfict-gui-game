#include "soundbox.h"
#include "Constants.h"
#include "MainWidget.h"
#include <QString>
#include <QtMultimedia/QMediaPlayer>

#include <QDebug>

//Sounds

QString Soundbox::shoots("C:\\SynologyDrive\\hfict-gui-game\\sounds\\bam_shoot.m4a");

Soundbox::Soundbox()
{
 qDebug() << "Soundbox const calles" <<endl;
 this->mPlayer = new QMediaPlayer;

}

void Soundbox::playSound()
{

   qDebug() << "playSound called" <<endl;
   //file = ("C:\\SynologyDrive\\hfict-gui-game\\sounds\\"); //(Constants::soundFolder + this->shoots);
   this->mPlayer->setMedia(QUrl::fromLocalFile(this->shoots));
   qDebug() << "after setmedia" <<endl;
   this->mPlayer->play();

}

