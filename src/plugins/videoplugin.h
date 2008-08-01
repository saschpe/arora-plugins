#ifndef VIDEOPLUGIN_H
#define VIDEOPLUGIN_H

#include <qwidget.h>

class VideoPlugin : public QWidget
{
    Q_OBJECT

public:
    VideoPlugin(const QString &videoUrl, QWidget *parent = 0);

private slots:

private:

};

#endif
