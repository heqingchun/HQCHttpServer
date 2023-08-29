#ifndef CHTTPSERVER_H
#define CHTTPSERVER_H

#include <QObject>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

#include "HQCHttpServer.h"


class CHttpServer : public QObject
{
    Q_OBJECT
public:
    explicit CHttpServer(QObject *parent = nullptr);
    ~CHttpServer();
signals:
private:
    void StructFunMap();
    QByteArray AnalysisFailed(QJsonObject responseObj = QJsonObject());
    QByteArray AnalysisSuccessed(QJsonObject responseObj = QJsonObject());
private:
    QMap<QString/*url*/,QString/*function*/> m_FunctionMap;
    HQCCHttpServer *p_HttpServer = nullptr;
private:
    Q_INVOKABLE QByteArray GetTest(const QStringList& list);
    Q_INVOKABLE QByteArray PutTest(const QStringList& list);
    Q_INVOKABLE QByteArray PostTest(const QStringList& list);
    Q_INVOKABLE QByteArray DeleteTest(const QStringList& list);
    Q_INVOKABLE QByteArray HeadTest(const QStringList& list);
};

#endif // CHTTPSERVER_H
