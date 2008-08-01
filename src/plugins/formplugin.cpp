#include "formplugin.h"
#include <qnetworkrequest.h>
#include <qnetworkaccessmanager.h>
#include <quiloader.h>
#include <QVBoxLayout>
#include <qurl.h>
#include <qdebug.h>

FormPlugin::FormPlugin(const QString &formUrl, const QString &scriptUrl, QWidget *parent)
    : QWidget(parent)
    , m_formReply(0), m_scriptReply(0), m_form(0), m_script(0), m_finalized(false)
{
    QNetworkAccessManager *netAccessManager = new QNetworkAccessManager(this);
    qDebug() << "FormPlugin::FormPlugin() Form:" << formUrl << "script:" << scriptUrl;

    if (!formUrl.isEmpty()) {
        m_formReply = netAccessManager->get(QNetworkRequest(QUrl(formUrl)));
        connect(m_formReply, SIGNAL(finished()), this, SLOT(downloadFormFinished()));
        connect(m_formReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorOccured(QNetworkReply::NetworkError)));
    }
    if (!scriptUrl.isEmpty()) {
        m_scriptReply = netAccessManager->get(QNetworkRequest(QUrl(scriptUrl)));
        connect(m_scriptReply, SIGNAL(finished()), this, SLOT(downloadScriptFinished()));
        connect(m_scriptReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorOccured(QNetworkReply::NetworkError)));
    } else {
        m_script = new QString();
    }
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
    m_script = new QString(stream.readAll());
    finalize();
}

void FormPlugin::errorOccured(QNetworkReply::NetworkError error)
{
    qWarning() << "FormPlugin::errorOccured() Network error:" << error;
}

void FormPlugin::finalize()
{
    if (m_finalized || !m_form || !m_script)
        return;

    QScriptValue ctor = m_scriptEngine.evaluate(*m_script);
    QScriptValue ui = m_scriptEngine.newQObject(m_form, QScriptEngine::ScriptOwnership);
    QScriptValue calc = ctor.construct(QScriptValueList() << ui);

    m_finalized = true;
    delete m_script;
}
