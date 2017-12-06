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

    QString apikey = "ZLOKSV60340343I8";

    QString urlString = QString("https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=FB&apikey=0%").arg(apikey);

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
 //   QFile *file = new QFile("E:\QT\QtApp_Net\appdev_project\STOCK_FB.txt");
    QFile *file = new QFile();
    file->setFileName("E:\\QT\\QtApp_Net\\appdev_project\\STOCK_FB.txt");

    if(file->open(QFile::Append | QFile::ReadWrite))
    {
      file->write(webData);
      file->flush();
      file->close();
    }
 //   delete file;

    QList<QPair<QString,QString>> graphValuesOpen;
    QList<QPair<QString,QString>> graphValuesHigh;
    QList<QPair<QString,QString>> graphValuesClose;

    //QString webDataString = QString(webData);

    QJsonDocument doc = QJsonDocument::fromJson(webData);

    if(doc.isArray()==true){
        QJsonArray rootArray = doc.array();
        //retrieve array
    }

    else if (doc.isObject() == true){

        QJsonObject rootObject = doc.object();

        QJsonObject timeSeries = rootObject["Time Series (Daily)"].toObject();
        QStringList keys = timeSeries.keys();

        for (QString k :keys){
            QJsonObject dayValues = timeSeries[k].toObject();
            QString openvalue = dayValues["1. open"].toString();
            QString highvalue = dayValues["2. high"].toString();
            QString closevalue = dayValues["4. close"].toString();

            QPair<QString,QString> dataItem;
            dataItem.first = k;
            dataItem.second = openvalue;

            QPair<QString,QString> dataItem2;
            dataItem2.first = k;
            dataItem2.second = highvalue;

            QPair<QString,QString> dataItem3;
            dataItem3.first = k;
            dataItem3.second = closevalue;



            graphValuesOpen.append(dataItem);
            graphValuesHigh.append(dataItem2);
            graphValuesClose.append(dataItem3);

            }

    }

    for (int i=0; i<graphValuesOpen.size(); i++){
        QPair<QString,QString> data = graphValuesOpen[i];
        float list=data.second.toFloat();
        QDateTime xAxisValue; xAxisValue.setDate(QDate::fromString(data.first,"yyyy-MM-dd"));
        xAxisValue.toMSecsSinceEpoch();
        emit valueUpdated(QVariant(xAxisValue),QVariant(list));
    }

    for (int i=0; i<graphValuesHigh.size(); i++){
        QPair<QString,QString> data = graphValuesHigh[i];
        float list = data.second.toFloat();
        QDateTime xAxisValue; xAxisValue.setDate(QDate::fromString(data.first,"yyyy-MM-dd"));
        xAxisValue.toMSecsSinceEpoch();
        emit valueUpdated2(QVariant(xAxisValue),QVariant(list));
    }


    for (int i=0; i<graphValuesClose.size(); i++){
        QPair<QString,QString> data = graphValuesClose[i];
        float list=data.second.toFloat();
        QDateTime xAxisValue; xAxisValue.setDate(QDate::fromString(data.first,"yyyy-MM-dd"));
        xAxisValue.toMSecsSinceEpoch();
        emit valueUpdated3(QVariant(xAxisValue),QVariant(list));
    }

}

