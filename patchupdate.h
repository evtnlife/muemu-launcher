#ifndef PATCHUPDATE_H
#define PATCHUPDATE_H
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QtZip/zipreader.h>
#include <QUrl>

class PatchUpdate : public QObject {
    Q_OBJECT
public:
    PatchUpdate();

private:

    QNetworkAccessManager * manager;
    QNetworkReply * reply;

    bool mkPATH(ZipReader::FileInfo&);
signals:
    void fileProgress(qint64,qint64);
    void zipProgress(qint64,qint64);

private slots:
    void doDownload();
    void downloadFinished(QNetworkReply*);
    void downloadProgress(qint64,qint64);
};

#endif // PATCHUPDATE_H
