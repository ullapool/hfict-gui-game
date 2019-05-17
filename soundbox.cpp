#include "soundbox.h"
#include "Constants.h"
#include "MainWidget.h"
#include "GameArea.h"
#include <QVector>
#include <QString>
#include <QtMultimedia/QMediaPlayer>

#include <QDebug>

//Sounds

QString Soundbox::shooting("bam.mp3");
QString Soundbox::shooting_2("boom.mp3");
QString Soundbox::shooting_3("gonnagetya.mp3");
QString Soundbox::opponentStriked("yaFucker.mp3");
QString Soundbox::opponentStriked_2("fanny.mp3");
QString Soundbox::opponentStriked_3("bastard.mp3");
QString Soundbox::strike("juhu.mp3");
QString Soundbox::strike_2("wohoo.mp3");
QString Soundbox::shootOpponent("stoppit.mp3");
QString Soundbox::shootOpponent_2("stoppityadick.mp3");

QString Soundbox::goalCheering("goal.mp3");

Soundbox::Soundbox()
{
 qDebug() << "Soundbox const. called" <<endl;
}

void Soundbox::playSoundEffect(QString sound)
{
     qDebug() <<sound<<endl;


    if (sound == shooting) {
        QVector<QString>soundVec;
        soundVec.push_back(shooting);
        soundVec.push_back(shooting_2);
        soundVec.push_back(shooting_3);
        std::random_shuffle(soundVec.begin(), soundVec.end());
        sound = soundVec.at(0);
    }

    if(sound == strike) {
       QVector<QString>soundVec;
       soundVec.push_back(strike);
       soundVec.push_back(opponentStriked_3);
       soundVec.push_back(opponentStriked_2);
       soundVec.push_back(strike_2);
       soundVec.push_back(opponentStriked);
       std::random_shuffle(soundVec.begin(), soundVec.end());
       sound = soundVec.at(0);
    }




    QMediaPlayer *mPlayer = new QMediaPlayer;
    mPlayer->setMedia(QUrl::fromLocalFile(Constants::soundFolder + sound));
    mPlayer->play();
}


