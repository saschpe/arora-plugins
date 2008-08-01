#ifndef FORMPLUGIN_H
#define FORMPLUGIN_H

#include <qnetworkreply.h>
#include <qscriptengine.h>
#include <qwidget.h>

class FormPlugin : public QWidget
{
    Q_OBJECT

public:
    FormPlugin(const QString &formUrl, const QString &scriptUrl = "",
               QWidget *parent = 0);

private slots:
    void downloadFormFinished();
    void downloadScriptFinished();
    void errorOccured(QNetworkReply::NetworkError);

private:
    void finalize();

    QScriptEngine m_scriptEngine;
    QNetworkReply *m_formReply;
    QNetworkReply *m_scriptReply;
    QWidget *m_form;
    QString m_script;
    bool finalized;
};

#endif // FORMPLUGIN_H
