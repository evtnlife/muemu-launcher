#include "patchupdate.h"
#include "definitions.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDir>
#include <muteen.h>
#include "QtZip/zipreader.h"
#include <QFile>
#include <QNetworkAccessManager>

PatchUpdate::PatchUpdate()
{
    manager = new QNetworkAccessManager();
}

bool PatchUpdate::mkPATH(ZipReader::FileInfo& file)
{
    QString PATH = file.filePath;
    QString PATHTOMAKE = "";
    QString PATHINVERSO = "";
    bool firstBar = false;

    if(PATH.contains("\\") or PATH.contains("/")){
    for(int i = PATH.size(); i>-1; i--)
    {
        if(PATH[i] == '/') // procura pela \ inversa usada pelo qt.
        {
            firstBar = true;
        }

        if(firstBar == true)
        {
            if(PATH[i] != '\0')
                PATHINVERSO.append(PATH[i]);
        }
    }
    for(int i = PATHINVERSO.size()-1; i != 0; --i)
    {
        PATHTOMAKE.append(PATHINVERSO[i]);
    }

    QDir dir(PATHTOMAKE);

    if(!dir.exists())
    {

        qDebug() << PATHTOMAKE << dir.exists();
        dir.mkpath(PATHTOMAKE);
        return true;
    }
    return true;
    }
    return true;
}


void PatchUpdate::downloadFinished(QNetworkReply * reply)
{
    if(reply->error())
    {
        qDebug() << reply->errorString();
    }
    else
    {
        QFile file("patch.zip");
        file.open(QIODevice::WriteOnly | QFile::Truncate);
        file.write(reply->readAll());
        file.close();

        ZipReader zipReader("patch.zip");

        int contadorProgressBar = 0;
        foreach(ZipReader::FileInfo file, zipReader.fileInfoList()){
            if(mkPATH(file)){
            QFile fWrite(file.filePath);
            fWrite.open(QIODevice::WriteOnly);
            fWrite.write(zipReader.fileData(file.filePath));
            fWrite.close();
            }
            contadorProgressBar++;
            emit zipProgress(contadorProgressBar, zipReader.count());
        }
        zipReader.close();
    }
}

void PatchUpdate::downloadProgress(qint64 aSize, qint64 fSize)
{
    emit fileProgress(aSize,fSize);
}

void PatchUpdate::doDownload()
{
    QUrl url;
    url.setUrl(tr(URL)+"patch.zip");

    QNetworkRequest request(url);
    reply = manager->get(request);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(downloadFinished(QNetworkReply*)));
    connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(downloadProgress(qint64,qint64)));
}
