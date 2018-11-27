#include "ping.h"


void Ping::pongHandler()
{
    std::cout << "Recieved a pong" << std::endl;
    emit iAmPing();
}
void Ping::CreateConnection(){

    iface = new QDBusInterface("org.QtGlucobeam.Pong", "/", "Dbus.Pong",
                               QDBusConnection::sessionBus(), this);
    if(!iface->isValid()){
        fprintf(stderr, "%s\n",
                        qPrintable(QDBusConnection::sessionBus().lastError().message()));
                QCoreApplication::instance()->quit();
    }
    std::cout << "pong-iface valid on ping" << std::endl;
    connect(iface, SIGNAL(iAmPong()), this, SLOT(pongHandler()));

    iface->asyncCall("pingHandler");
    /*QDBusConnection::sessionBus().connect("D-bus.Pong","/","org.QtGlucobeam.Pong", SIGNAL(iAmPong()),
                                                 this, SLOT(pongHandler()));
*/
}
