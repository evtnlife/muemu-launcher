#ifndef MUTEEN_H
#define MUTEEN_H

#include <QMainWindow>
#include <QUrl>
#include <QThread>
#include "testversion.h"
#include "patchupdate.h"
#include "startgame.h"

namespace Ui {
class MuTeeN;
}

class MuTeeN : public QMainWindow
{
    Q_OBJECT
    QThread *workerThread;
    QThread *workerThread2;
    QThread *workerThread3;

public:
    explicit MuTeeN(QWidget *parent = 0);
    ~MuTeeN();
    QString typeDown;
    TestVersion * tVersion;
    PatchUpdate * pUpdate;
    StartGame * sGame;
    int serverVersion = 0;
    bool mainStarted = false;

public slots:
    void progressDownload(qint64,qint64);
    void zipProgress(qint64,qint64);
    void showConfigForm();
    void getVersion(bool isValid, int sVersion) {
        isValidVersion = isValid;
        serverVersion = sVersion;
        emit workFinished();
    }
    void getMainStarted(bool value);
    void startUpdate();
    void startGame();
    void mainIsOpen();

private:
    Ui::MuTeeN *ui;
    bool isValidVersion = false;

signals:
    void workFinished();
    void deletWhenFinished();
};

#endif // MUTEEN_H
