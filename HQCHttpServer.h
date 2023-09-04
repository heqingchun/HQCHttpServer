#ifndef HQCCHTTPSERVER_H
#define HQCCHTTPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkRequest>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonDocument>

class HQCCHttpServer : public QObject
{
    Q_OBJECT
public:
    explicit HQCCHttpServer(QObject *parent = nullptr);
    ~HQCCHttpServer();
signals:
public:
    enum MsgType{
        Method,
        Url,
        Param,
        Body,
        Token
    };
public:
    void InitHttpServer(const QString& ip,quint16 port,const QMap<QString,QString>& functionMap);
    void FinishResponse(QTcpSocket* socket,const QByteArray& json);
private:
    QTcpServer *p_TcpServer = nullptr;
    QMap<QString/*url*/,QString/*function*/> m_FunctionMap;
    QTcpSocket *p_TcpSocket = nullptr;
private:
    Q_INVOKABLE void HandleRequest(QTcpSocket* socket,const QByteArray& request);
};

#endif // HQCCHTTPSERVER_H
