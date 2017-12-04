#include "networkmanager.h"
#include <QNetworkReply>
#include <QNetworkRequest>

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{

    manager= new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}


 //(function to load the webpage and receive timeseries data)
void NetworkManager::loadWebPage(){
    QNetworkRequest request;

    QString apikey = "2HJ6DUVQ3B4I2OQS";

    QString urlString = QString("https://www.alphavantage.co/query?function=DIGITAL_CURRENCY_DAILY&symbol=BTC&market=HUF&apikey=%0").arg(apikey);

    QUrl url(urlString);
    request.setUrl(url);

    QNetworkReply *reply = manager->get(request);
}

//Function to deserialize JSON and obtain the key value pairs of the data of interest
//need to understand it better
void NetworkManager::replyFinished(QNetworkReply *reply)
{
    QByteArray webData = reply->readAll();

    // Store requested data in a file
    QFile *file = new QFile(QDir::currentPath() + "\\BITCOINDATA.txt");
    if(file->open(QFile::Append))
    {
      file->write(webData);
      file->flush();
      file->close();
    }
    delete file;

    QList<QPair<QString,QString>> graphValuesHUF;
    QList<QPair<QString,QString>> graphValuesVolume;
    QList<QPair<QString,QString>> graphValuesUSD;

    //QString webDataString = QString(webData);

    QJsonDocument doc = QJsonDocument::fromJson(webData);

    if(doc.isArray()==true){
        QJsonArray rootArray = doc.array();
        //retrieve array
    }

    else if (doc.isObject() == true){

        QJsonObject rootObject = doc.object();

        QJsonObject timeSeries = rootObject["Time Series (Digital Currency Daily)"].toObject();
        QStringList keys = timeSeries.keys();

        for (QString k :keys){
            QJsonObject dayValues = timeSeries[k].toObject();
            QString hufValue = dayValues["1a. open (HUF)"].toString();
            QString volume = dayValues["5. volume"].toString();
            QString usdValue = dayValues["1b. open (USD)"].toString();

            QPair<QString,QString> dataItem;
            dataItem.first = k;
            dataItem.second = hufValue;

            QPair<QString,QString> dataItem2;
            dataItem2.first = k;
            dataItem2.second = volume;

            QPair<QString,QString> dataItem3;
            dataItem3.first = k;
            dataItem3.second = usdValue;



            graphValuesHUF.append(dataItem);
            graphValuesVolume.append(dataItem2);
            graphValuesUSD.append(dataItem3);

            }

    }
    for (int i=0; i<graphValuesHUF.size(); i++){
        QPair<QString,QString> data = graphValuesHUF[i];
       // qDebug()<<data.first <<" - "<<data.second;
        float list=data.second.toFloat();
        QDateTime xAxisValue; xAxisValue.setDate(QDate::fromString(data.first,"yyyy-MM-dd"));
        xAxisValue.toMSecsSinceEpoch();
        emit valueUpdated(QVariant(xAxisValue),QVariant(list));
    }

    for (int i=0; i<graphValuesVolume.size(); i++){
        QPair<QString,QString> data = graphValuesVolume[i];
        float list = data.second.toFloat();
        QDateTime xAxisValue; xAxisValue.setDate(QDate::fromString(data.first,"yyyy-MM-dd"));
        xAxisValue.toMSecsSinceEpoch();
        emit valueUpdated2(QVariant(xAxisValue),QVariant(list));
    }

    for (int i=0; i<graphValuesUSD.size(); i++){
        QPair<QString,QString> data = graphValuesUSD[i];
        float list=data.second.toFloat();
        QDateTime xAxisValue; xAxisValue.setDate(QDate::fromString(data.first,"yyyy-MM-dd"));
        xAxisValue.toMSecsSinceEpoch();
        emit valueUpdated3(QVariant(xAxisValue),QVariant(list));
    }

}

