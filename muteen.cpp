#include "muteen.h"
#include "ui_muteen.h"
#include "config.h"
#include "patchupdate.h"
#include "testversion.h"
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include <QDir>
#include "windows.h"
#include "startgame.h"
#include <QMessageBox>
#include <QTimer>
#include <QStyle>


/*
 * name = MuTeeN
 * desc = Whem construct make a thread and test it!
 */
MuTeeN::MuTeeN(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MuTeeN)
{
    ui->setupUi(this);
    ui->btnStartGame->setEnabled(false);
    if(!ui->btnStartGame->isEnabled())
        ui->btnStartGame->setStyleSheet("QPushButton{margin:0;  border :0;background: url(:/btndisable.jpg); color: white;}");
    this->setWindowFlags(Qt::FramelessWindowHint);
    connect(ui->btnConfiguracao,SIGNAL(clicked(bool)),this,SLOT(showConfigForm()));
    connect(ui->btnStartGame,SIGNAL(clicked(bool)),this,SLOT(startGame()));
    connect(ui->btnClose,SIGNAL(clicked(bool)),this,SLOT(deleteLater()));
    bool controlVersionStart = false;
    if(controlVersionStart == false){
        controlVersionStart = true;
        workerThread = new QThread();
        tVersion = new TestVersion();

        tVersion->moveToThread(workerThread);
        connect(workerThread,SIGNAL(started()),tVersion,SLOT(doDownload()));
        connect(tVersion,SIGNAL(resultReady(bool,int)),this,SLOT(getVersion(bool,int)));
        connect(this,SIGNAL(workFinished()),this,SLOT(startUpdate()));
        connect(this,SIGNAL(deletWhenFinished()),tVersion,SLOT(deleteLater()));
        workerThread->start();
    }
}

/*
 * name = desctructor
 * desc = desctruct the class
 */
MuTeeN::~MuTeeN()
{
    delete workerThread;
    delete workerThread2;
    delete workerThread3;
    delete ui;
}

/*
 * name = startUpdate
 * desc = check if the version in client is the same that server, if not same, update patch!
 */
void MuTeeN::startUpdate()
{
    emit deletWhenFinished();
    if(isValidVersion){
        qDebug() << "versão ok";
        ui->progressBar->setValue(100);
        ui->progressBar_2->setValue(100);
        ui->btnStartGame->setEnabled(true);
        if(ui->btnStartGame->isEnabled())
            ui->btnStartGame->setStyleSheet("QPushButton{margin:0;border :0;background: url(:/btn0.jpg);color: white;} QPushButton::hover{margin:0;border :0;background: url(:/btn.jpg);color: white;}");
    }
    else{
        qDebug() << "Versao fail";
        workerThread2 = new QThread();
        pUpdate = new PatchUpdate();
        pUpdate->moveToThread(workerThread2);
        connect(workerThread2,SIGNAL(started()),pUpdate,SLOT(doDownload()));
        connect(pUpdate,SIGNAL(fileProgress(qint64,qint64)),this,SLOT(progressDownload(qint64,qint64)));
        connect(pUpdate,SIGNAL(zipProgress(qint64,qint64)),this,SLOT(zipProgress(qint64,qint64)));
        connect(workerThread2,SIGNAL(finished()),pUpdate,SLOT(deleteLater()));

        workerThread2->start();
    }
}

/*
 * name = startGame
 * desc = start the game thread;
 */
void MuTeeN::startGame()
{
    workerThread3 = new QThread();
    sGame = new StartGame();
    sGame->moveToThread(workerThread3);
    connect(workerThread3,SIGNAL(started()),sGame,SLOT(startMainGame()));
    connect(sGame,SIGNAL(workingFinished(bool)),this,SLOT(getMainStarted(bool)));
    connect(workerThread3,SIGNAL(finished()),this,SLOT(deleteLater()));
    workerThread3->start();
}

/*
 * name = progressDownload
 * desc = updateProgress Bar download using values in thread update;
 */
void MuTeeN::progressDownload(qint64 bitAtual,qint64 bitTotal)
{
    ui->progressBar->setRange(0,bitTotal);
    ui->progressBar->setValue(bitAtual);
}

/*
 * name = zipProgress
 * desc = show the uncropress timer
 */
void MuTeeN::zipProgress(qint64 bitAtual, qint64 bitFinal)
{
    ui->progressBar_2->setRange(0,bitFinal);
    ui->progressBar_2->setValue(bitAtual);
    if(bitAtual == bitFinal){
        QFile file("version.muteen");
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << serverVersion;
        file.close();
        ui->btnStartGame->setEnabled(true);
        if(ui->btnStartGame->isEnabled())
            ui->btnStartGame->setStyleSheet("QPushButton{margin:0;border :0;background: url(:/btn0.jpg);color: white;} QPushButton::hover{margin:0;border :0;background: url(:/btn.jpg);color: white;}");

    }
}

/*
 * name = showConfigForm
 * desc = show the config scream, sounds, and resoluction form.
 */
void MuTeeN::showConfigForm()
{
    Config * config = new Config();
    config->exec();
}

/*
 * name = getMainStart
 * desc = its a signal and get if the main is executed using signal and slot provided by threadworker3 and start a timer for check if the main is open
 */
void MuTeeN::getMainStarted(bool value)
{
    mainStarted = value;

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(mainIsOpen()));
    timer->start(10000);
}


/*
 * name = mainIsOpen
 * desc = check if the main is open and, close the launcher!
 */
void MuTeeN::mainIsOpen()
{
    if(mainStarted == true)
    {
        this->deleteLater();
    }
}



