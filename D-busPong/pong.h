#ifndef PONG_H
#define PONG_H

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

#define SERVICE_NAME "org.QtGlucobeam.Pong"

class Pong : public QDBusAbstractAdaptor{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "Dbus.Pong")
public:
    Pong(QObject *obj) : QDBusAbstractAdaptor(obj){
    }
    void CreateConnection();
private:
    QDBusInterface *iface;
public slots:
    void pingHandler();
signals:
    void iAmPong();
};

#endif // PONG_H
