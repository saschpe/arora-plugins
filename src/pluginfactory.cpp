#include "pluginfactory.h"
#include "plugins/formplugin.h"
#include <qurl.h>
#include <qstring.h>

PluginFactory::PluginFactory(QObject *parent)
    : QWebPluginFactory(parent)
{
}

QObject *PluginFactory::create(const QString &mimeType, const QUrl &url,
                               const QStringList &argumentNames,
                               const QStringList &argumentValues) const
{
    Q_UNUSED(url);

    if (mimeType == QString::fromLatin1("application/x-qt-form")) {
        QString form = argumentValues[argumentNames.indexOf(QString::fromLatin1("form"))];
        QString script = argumentValues[argumentNames.indexOf(QString::fromLatin1("script"))];
        return new FormPlugin(form, script);
    }
    return 0;
}

QList<QWebPluginFactory::Plugin> PluginFactory::plugins() const
{
    MimeType formMimeType;
    formMimeType.name = QString::fromLatin1("application/x-qt-form");
    formMimeType.description = QString::fromLatin1("application/x-qt-form");

    QList<MimeType> formPluginMimeTypes;
    formPluginMimeTypes.append(formMimeType);

    Plugin formPlugin;
    formPlugin.name = QString::fromLatin1("Qt UI form plugin");
    formPlugin.mimeTypes = formPluginMimeTypes;

    QList<Plugin> list;
    //TODO: Find out what to enter here, plugin breaks if next line is uncommented:
    //list.append(formPlugin);

    return list;
}
