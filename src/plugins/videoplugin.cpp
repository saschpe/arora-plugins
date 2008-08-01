#include "videoplugin.h"

VideoPlugin::VideoPlugin(const QString &videoUrl, QWidget *parent)
    : QWidget(parent)
{
    if (!videoUrl.isEmpty()) {
        //TODO: Start streaming video provided by url and display a Phonon::VideoPlayer
    }
}
