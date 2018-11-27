#include "pong.h"


void Pong::pingHandler()
{
    std::cout << "Recieved a ping" << std::endl;
    emit iAmPong();
}
void Pong::CreateConnection(){

    iface = new QDBusInterface("org.QtGlucobeam.Ping", "/", "Dbus.Ping",
                               QDBusConnection::sessionBus(), this);
    if(!iface->isValid()){
        fprintf(stderr, "%s\n",
                        qPrintable(QDBusConnection::sessionBus().lastError().message()));
                QCoreApplication::instance()->quit();
    }
    std::cout << "ping-iface is valid on pong" << std::endl;
    connect(iface, SIGNAL(iAmPing()), this, SLOT(pingHandler()));

    iface->asyncCall("pongHandler");
    /*QDBusConnection::sessionBus().connect("D-bus.Ping","/","org.QtGlucobeam.Ping",
                                                 SIGNAL(iAmPing()),this, SLOT(pingHandler()));
*/
}
