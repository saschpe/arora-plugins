#include "pluginfactory.h"
#include "plugins/formplugin.h"
#include <qurl.h>

PluginFactory::PluginFactory(QObject *parent)
    : QWebPluginFactory(parent)
{
}

QObject *PluginFactory::create(const QString &mimeType, const QUrl &url,
                               const QStringList &argumentNames,
                               const QStringList &argumentValues) const
{
    Q_UNUSED(url);

    if (mimeType == "application/x-qt-form") {
        QString form= argumentValues[argumentNames.indexOf("form")];
        QString script= argumentValues[argumentNames.indexOf("script")];
        return new FormPlugin(form, script);
    }
    return 0;
}

QList<QWebPluginFactory::Plugin> PluginFactory::plugins() const
{
    QList<Plugin> list;

    //TODO: Generate corect plugin/mimetype list
    /*Plugin formPlugin;
    QList<MimeType> formPluginMimeTypes;
    formPluginMimeTypes.append("application/x-qt-form");
    formPlugin.description = "";
    formPlugin.mimeTypes = formPluginMimeTypes;
    formPlugin.name="Qt Ui-Form Plugin";
    list.append(formPlugin);*/

    return list;
}
