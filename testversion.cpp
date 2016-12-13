#include "testversion.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include "muteen.h"
#include <QUrl>
#include <QThread>
#include <definitions.h>

TestVersion::TestVersion()
{
    manager = new QNetworkAccessManager();
}

void TestVersion::doDownload()
{
    QUrl url;
    url.setUrl(tr(URL)+"version.muteen");
    QNetworkRequest request(url);
    reply = manager->get(request);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(testVersion(QNetworkReply*)));
}

void TestVersion::testVersion(QNetworkReply * reply)
{
    if(reply->error())
        qDebug() << reply->errorString();
    else
    {
            QFile file("version.muteen");
            file.open(QIODevice::ReadWrite);
            QByteArray clientVersion = file.readAll();
            QByteArray versionPatch  = reply->readAll();

            qDebug() << "Server Version :" << versionPatch << " Client Version: " << clientVersion;
            if(clientVersion != versionPatch)
            {
                isVersion = false;
            }
            else{
                isVersion = true;
            }
            emit resultReady(isVersion,versionPatch.toInt());
    }
}
