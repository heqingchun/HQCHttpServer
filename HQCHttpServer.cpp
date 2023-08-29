#include "HQCHttpServer.h"

HQCCHttpServer::HQCCHttpServer(QObject *parent) : QObject(parent){
    p_TcpServer = new QTcpServer();
    connect(p_TcpServer,&QTcpServer::newConnection,[&](){
        QTcpSocket *p_TcpSocket = p_TcpServer->nextPendingConnection();
        connect(p_TcpSocket,&QTcpSocket::readyRead,[&](){
            QMetaObject::invokeMethod(this,
                                      "HandleRequest",
                                      Qt::QueuedConnection,
                                      Q_ARG(QTcpSocket*,p_TcpSocket),
                                      Q_ARG(const QByteArray&,p_TcpSocket->readAll()));
        });
        connect(p_TcpSocket,&QTcpSocket::disconnected,p_TcpSocket,&QTcpSocket::deleteLater);
    });
}
HQCCHttpServer::~HQCCHttpServer(){
    if(p_TcpServer) p_TcpServer->deleteLater();
}
void HQCCHttpServer::InitHttpServer(const QString& ip,quint16 port,const QMap<QString,QString>& functionMap){
    m_FunctionMap = functionMap;
    QHostAddress tmpHostAddress(ip);
    qDebug()<<"HQCHttpServer开始监听"<<ip<<port;
    p_TcpServer->listen(tmpHostAddress,port);
}
void HQCCHttpServer::FinishResponse(QTcpSocket* socket,const QByteArray& json){
    if(!socket) return;
    QString tmpResponseStr("HTTP/1.1 200 OK"); // 接收到请求的响应-状态行:协议版本 状态码 状态码的原因短语
    tmpResponseStr += "\r\n"; // 状态行结束需要回车换行
    QHostAddress tmpRecHost(socket->peerAddress());
    quint16 tmpRecPort(socket->peerPort());
    QUrl tmpUrl(QString("http://%1:%2").arg(tmpRecHost.toString()).arg(tmpRecPort));
    //qDebug()<<"ip:"<<tmpRecHost<<"port:"<<tmpRecPort<<"url:"<<tmpUrl;
    QNetworkRequest tmpRequest;
    tmpRequest.setUrl(tmpUrl);
    QString Date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    tmpRequest.setRawHeader("Date",Date.toUtf8()); // 接收到请求的响应-响应头部
    tmpRequest.setRawHeader("Content-Type","application/json"); // 接收到请求的响应-响应头部
    QList<QByteArray> tmpRawHeaderList = tmpRequest.rawHeaderList(); // 响应头部所有的Key
    //qDebug()<<"tmpRawHeaderList:"<<tmpRawHeaderList;
    for(int i = 0;i < tmpRawHeaderList.size();++i){
        tmpResponseStr += tmpRawHeaderList.at(i) + ":" + tmpRequest.rawHeader(tmpRawHeaderList.at(i)) + "\r\n";
    }
    tmpResponseStr += "\r\n"; // 响应头部结束需要回车换行
    tmpResponseStr += json; // 接收到请求的响应-响应正文
    socket->write(tmpResponseStr.toUtf8());
    socket->close();
    return;
}
void HQCCHttpServer::HandleRequest(QTcpSocket* socket,const QByteArray& request){
    QByteArray tmpReturnByte;
    //qDebug()<<"request:"<<request;
    QStringList tmpRequestStrList = QString(request).split("\r\n");
    //qDebug()<<"tmpRequestStrList:"<<tmpRequestStrList;
//    for(int i = 0;i < tmpRequestStrList.size();++i){
//        qDebug()<<i<<":"<<tmpRequestStrList.at(i);
//    }
    QString tmpBody = tmpRequestStrList.last(); // body
    //qDebug()<<"tmpRequestStrList:"<<tmpRequestStrList;
    QString tmpMethod = tmpRequestStrList.first().split(' ').first(); // method
    QString tmpTotalUrl = tmpRequestStrList.first().split(' ').at(1);
    QString tmpUrl; // url
    QString tmpParam; // param
    if(tmpTotalUrl.contains('?')){
        tmpUrl = tmpTotalUrl.split('?').first();
        tmpParam = tmpTotalUrl.mid(tmpTotalUrl.indexOf('?') + 1,tmpTotalUrl.length());
    }else{
        tmpUrl = tmpTotalUrl;
        tmpParam = QString();
    }
    // Token
    QMap<QString,QString> tmpMap;
    for(int i = 1;i < tmpRequestStrList.size() - 1;++i){
        tmpMap.insert(tmpRequestStrList.at(i).split(':').first().simplified(),tmpRequestStrList.at(i).split(':').last().simplified());
    }
    QString tmpToken;
    if(tmpMap.contains("Authorization")){
        tmpToken = tmpMap.value("Authorization").split(' ').last();
    }
    QStringList strList;
    strList<<tmpMethod<<tmpUrl<<tmpParam<<tmpBody<<tmpToken;
    QString tempFuncUrl = strList.at(MsgType::Method) + strList.at(MsgType::Url);
    if(!m_FunctionMap.contains(tempFuncUrl)){
        QJsonObject tmpResponseObj;
        tmpResponseObj.insert("code",400);
        tmpResponseObj.insert("ret","fail");
        tmpResponseObj.insert("msg","url错误!");
        QJsonDocument tmpTesponseDoc(tmpResponseObj);
        return FinishResponse(socket,tmpTesponseDoc.toJson());
    }
    QMetaObject::invokeMethod(this->parent(),
                              m_FunctionMap.value(tempFuncUrl).toStdString().data(),
                              Qt::AutoConnection,
                              Q_RETURN_ARG(QByteArray,tmpReturnByte),
                              Q_ARG(const QStringList&,strList));
    return FinishResponse(socket,tmpReturnByte);
}
