#ifndef PING_H
#define PING_H

#include <memory>
#include <iostream>
#include <cstdlib>
#include <stdio.h>

#include <QCoreApplication>
#include <QString>
#include <QtCore/QObject>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusAbstractAdaptor>
#include <QDBusConnectionInterface>

#define SERVICE_NAME "org.QtGlucobeam.Ping"

class Ping : public QDBusAbstractAdaptor{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "Dbus.Ping")
public:
    Ping(QObject *obj) : QDBusAbstractAdaptor(obj){}
    void CreateConnection();
private:
    QDBusInterface *iface;
public slots:
    void pongHandler();
signals:
    void iAmPing();
};

#endif // PING_H
