#include "formplugin.h"
#include <qnetworkrequest.h>
#include <qnetworkaccessmanager.h>
#include <quiloader.h>
#include <QVBoxLayout>
#include <qurl.h>
#include <qdebug.h>

FormPlugin::FormPlugin(const QString &formUrl, const QString &scriptUrl, QWidget *parent)
    : QWidget(parent)
    , m_formReply(0), m_scriptReply(0), m_form(0), finalized(false)
{
    QNetworkAccessManager *netAccessManager = new QNetworkAccessManager(this);

    m_formReply = netAccessManager->get(QNetworkRequest(QUrl(formUrl)));
    m_scriptReply = netAccessManager->get(QNetworkRequest(QUrl(scriptUrl)));

    connect(m_formReply, SIGNAL(finished()), this, SLOT(downloadFormFinished()));
    connect(m_formReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorOccured(QNetworkReply::NetworkError)));
    connect(m_scriptReply, SIGNAL(finished()), this, SLOT(downloadScriptFinished()));
    connect(m_scriptReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorOccured(QNetworkReply::NetworkError)));
}

void FormPlugin::downloadFormFinished()
{
    QUiLoader loader;
    m_form = loader.load(m_formReply);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_form, 0, Qt::AlignCenter);
    finalize();
}

void FormPlugin::downloadScriptFinished()
{
    QTextStream stream(m_scriptReply);
    m_script = stream.readAll();
    finalize();
}

void FormPlugin::errorOccured(QNetworkReply::NetworkError error)
{
    qWarning() << "FormPlugin::errorOccured() Network error:" << error;
}

void FormPlugin::finalize()
{
    if (finalized || !m_form)
        return;

    QScriptValue ctor = m_scriptEngine.evaluate(m_script);
    QScriptValue ui = m_scriptEngine.newQObject(m_form, QScriptEngine::ScriptOwnership);
    QScriptValue calc = ctor.construct(QScriptValueList() << ui);

    finalized = true;
}
