#include "HttpServer.h"

CHttpServer::CHttpServer(QObject *parent) : QObject(parent){
    p_HttpServer = new HQCCHttpServer(this);
    StructFunMap();
    p_HttpServer->InitHttpServer("127.0.0.1",60000,m_FunctionMap);
}
CHttpServer::~CHttpServer(){
    if(p_HttpServer) p_HttpServer->deleteLater();
}
void CHttpServer::StructFunMap(){
    m_FunctionMap.insert("GET/test","GetTest");
    m_FunctionMap.insert("PUT/test","PutTest");
    m_FunctionMap.insert("POST/test","PostTest");
    m_FunctionMap.insert("DELETE/test","DeleteTest");
    m_FunctionMap.insert("HEAD/test","HeadTest");
}
QByteArray CHttpServer::AnalysisFailed(QJsonObject responseObj){
    responseObj.insert("code",400);
    responseObj.insert("ret","failed");
    responseObj.insert("msg","失败");
    QJsonDocument tempFailedDoc(responseObj);
    return tempFailedDoc.toJson();
}
QByteArray CHttpServer::AnalysisSuccessed(QJsonObject responseObj){
    responseObj.insert("code",200);
    responseObj.insert("ret","successed");
    responseObj.insert("msg","成功");
    QJsonDocument tempSuccessedDoc(responseObj);
    return tempSuccessedDoc.toJson();
}
QByteArray CHttpServer:: GetTest(const QStringList& list){
    QString tmpMethod = list.at(HQCCHttpServer::MsgType::Method);
    QString tmpUrl = list.at(HQCCHttpServer::MsgType::Url);
    QString tmpParam = list.at(HQCCHttpServer::MsgType::Param);
    QString tmpBody = list.at(HQCCHttpServer::MsgType::Body);
    QString tmpToken = list.at(HQCCHttpServer::MsgType::Token);
    qDebug()<<"tmpMethod:"<<tmpMethod<<"tmpUrl:"<<tmpUrl<<"tmpParam:"<<tmpParam<<"tmpBody:"<<tmpBody<<"tmpToken:"<<tmpToken;
    QJsonObject tempResponseObj;
    tempResponseObj.insert("otherMsg","...");
    return AnalysisSuccessed(/*tempResponseObj*/);
}
QByteArray CHttpServer:: PutTest(const QStringList& list){
    QString tmpMethod = list.at(HQCCHttpServer::MsgType::Method);
    QString tmpUrl = list.at(HQCCHttpServer::MsgType::Url);
    QString tmpParam = list.at(HQCCHttpServer::MsgType::Param);
    QString tmpBody = list.at(HQCCHttpServer::MsgType::Body);
    QString tmpToken = list.at(HQCCHttpServer::MsgType::Token);
    qDebug()<<"tmpMethod:"<<tmpMethod<<"tmpUrl:"<<tmpUrl<<"tmpParam:"<<tmpParam<<"tmpBody:"<<tmpBody<<"tmpToken:"<<tmpToken;
    QJsonObject tempResponseObj;
    tempResponseObj.insert("otherMsg","...");
    return AnalysisSuccessed(/*tempResponseObj*/);
}
QByteArray CHttpServer:: PostTest(const QStringList& list){
    QString tmpMethod = list.at(HQCCHttpServer::MsgType::Method);
    QString tmpUrl = list.at(HQCCHttpServer::MsgType::Url);
    QString tmpParam = list.at(HQCCHttpServer::MsgType::Param);
    QString tmpBody = list.at(HQCCHttpServer::MsgType::Body);
    QString tmpToken = list.at(HQCCHttpServer::MsgType::Token);
    qDebug()<<"tmpMethod:"<<tmpMethod<<"tmpUrl:"<<tmpUrl<<"tmpParam:"<<tmpParam<<"tmpBody:"<<tmpBody<<"tmpToken:"<<tmpToken;
    QJsonObject tempResponseObj;
    tempResponseObj.insert("otherMsg","...");
    return AnalysisSuccessed(/*tempResponseObj*/);
}
QByteArray CHttpServer:: DeleteTest(const QStringList& list){
    QString tmpMethod = list.at(HQCCHttpServer::MsgType::Method);
    QString tmpUrl = list.at(HQCCHttpServer::MsgType::Url);
    QString tmpParam = list.at(HQCCHttpServer::MsgType::Param);
    QString tmpBody = list.at(HQCCHttpServer::MsgType::Body);
    QString tmpToken = list.at(HQCCHttpServer::MsgType::Token);
    qDebug()<<"tmpMethod:"<<tmpMethod<<"tmpUrl:"<<tmpUrl<<"tmpParam:"<<tmpParam<<"tmpBody:"<<tmpBody<<"tmpToken:"<<tmpToken;
    QJsonObject tempResponseObj;
    tempResponseObj.insert("otherMsg","...");
    return AnalysisSuccessed(/*tempResponseObj*/);
}
QByteArray CHttpServer:: HeadTest(const QStringList& list){
    QString tmpMethod = list.at(HQCCHttpServer::MsgType::Method);
    QString tmpUrl = list.at(HQCCHttpServer::MsgType::Url);
    QString tmpParam = list.at(HQCCHttpServer::MsgType::Param);
    QString tmpBody = list.at(HQCCHttpServer::MsgType::Body);
    QString tmpToken = list.at(HQCCHttpServer::MsgType::Token);
    qDebug()<<"tmpMethod:"<<tmpMethod<<"tmpUrl:"<<tmpUrl<<"tmpParam:"<<tmpParam<<"tmpBody:"<<tmpBody<<"tmpToken:"<<tmpToken;
    QJsonObject tempResponseObj;
    tempResponseObj.insert("otherMsg","...");
    return AnalysisSuccessed(/*tempResponseObj*/);
}
