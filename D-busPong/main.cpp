#include "pong.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QObject obj;
    Pong pong(&obj);

    /****************************************************
     * The order here is the most important part.
     * It makes sure they don't deadlock
    ****************************************************/

    //Checks if ping is running
    if(QDBusConnection::sessionBus().interface()->isServiceRegistered("org.QtGlucobeam.Ping")){
        //If it does, just connect
        pong.CreateConnection();
    }

    //Else if it does not, connect service watcher to connect on registration
    QDBusServiceWatcher serviceWatcher("org.QtGlucobeam.Ping", QDBusConnection::sessionBus(),
                                       QDBusServiceWatcher::WatchForRegistration);
    QObject::connect(&serviceWatcher, &QDBusServiceWatcher::serviceRegistered, &pong, &Pong::CreateConnection);

    //Register own service
    QDBusConnection::sessionBus().registerObject("/", &obj);
    if(!QDBusConnection::sessionBus().registerService(SERVICE_NAME)){
        fprintf(stderr, "%s\n", qPrintable(QDBusConnection::sessionBus().lastError().message()));
        exit(1);
    }

    return a.exec();
}
