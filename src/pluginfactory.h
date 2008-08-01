#ifndef PLUGINFACTORY_H
#define PLUGINFACTORY_H

#include <qwebpluginfactory.h>

class PluginFactory : public QWebPluginFactory
{
    Q_OBJECT

public:
    PluginFactory(QObject *parent = 0);

    QObject *create(const QString &mimeType, const QUrl &url,
                    const QStringList &argumentNames,
                    const QStringList &argumentValues) const;
    QList<Plugin> plugins() const;
};

#endif // PLUGINFACTORY_H
