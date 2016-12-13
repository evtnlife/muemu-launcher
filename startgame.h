#ifndef STARTGAME_H
#define STARTGAME_H
#include <QObject>
#include <QProcess>
#include "windows.h"

class StartGame : public QObject
{
    Q_OBJECT
public:
    StartGame(){}

public slots:
    void startMainGame(){
        QString nameFile = "main.exe";
        QProcess * mainEXE = new QProcess();
        QStringList listArguments;
        listArguments << "SW_SHOWNORMAL";
        if(mainEXE->startDetached(nameFile,listArguments))
            emit workingFinished(true);
        else
            emit workingFinished(false);
    }

signals:
    void workingFinished(bool);
};

#endif // STARTGAME_H
