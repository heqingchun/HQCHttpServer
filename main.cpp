#include <QCoreApplication>
#include "HttpServer.h"

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    CHttpServer HttpServer;
    return a.exec();
}
