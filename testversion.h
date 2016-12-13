#ifndef TESTVERSION_H
#define TESTVERSION_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>
#include <QThread>

class TestVersion : public QObject {
    Q_OBJECT
public:
    TestVersion();
    bool isVersion = false;

private:
    QNetworkAccessManager * manager;
    QNetworkReply * reply;

public slots:
    void doDownload();
    void testVersion(QNetworkReply *);

signals:
    void resultReady(bool,int);
};

#endif // TESTVERSION_H
