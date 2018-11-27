#include "ping.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject obj;
    Ping ping(&obj);

    /****************************************************
     * The order here is the most important part.
     * It makes sure they don't deadlock
    ****************************************************/

    //Checks if pong is running
    if(QDBusConnection::sessionBus().interface()->isServiceRegistered(QString("org.QtGlucobeam.Pong"))){
        //If it does, just connect
        ping.CreateConnection();
    }

    //Else if it does not, connect service watcher to connect on registration
    QDBusServiceWatcher serviceWatcher("org.QtGlucobeam.Pong", QDBusConnection::sessionBus(),
                                       QDBusServiceWatcher::WatchForRegistration);
    QObject::connect(&serviceWatcher, &QDBusServiceWatcher::serviceRegistered, &ping, &Ping::CreateConnection);

    //Register own service
    QDBusConnection::sessionBus().registerObject("/", &obj);
    if(!QDBusConnection::sessionBus().registerService(SERVICE_NAME)){
        fprintf(stderr, "%s\n", qPrintable(QDBusConnection::sessionBus().lastError().message()));
        exit(1);
    }

    return a.exec();
}
