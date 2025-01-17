#ifdef SUPPORT_LIBVLC

#include "vlc_decoder.h"

void logCallback(void *data, int level, const libvlc_log_t *ctx, const char *fmt, va_list args)
{
   Q_UNUSED(ctx);

    char *result;
    if (vasprintf(&result, fmt, args) < 0)
    {
        return;
    }

    QString message(result);
    free(result);

    switch (level)
    {
        case LIBVLC_ERROR:
            qCritical(message.toUtf8().data(), NULL);
            break;
        case LIBVLC_WARNING:
            qWarning(message.toUtf8().data(), NULL);
            break;
        case LIBVLC_NOTICE:
            qInfo(message.toUtf8().data(), NULL);
            break;
        case LIBVLC_DEBUG:
        default:
            qDebug(message.toUtf8().data(), NULL);
            break;
    }
}


VlcDecoder::VlcDecoder(QObject *parent) : QObject(parent)
{
    vlcInstance = libvlc_new(0, Q_NULLPTR);
    if (vlcInstance)
    {
#ifdef QT_DEBUG
        libvlc_log_set(vlcInstance, logCallback, NULL);
#endif
        vlcPlayer    = libvlc_media_player_new(vlcInstance);
    }
    else
        qCritical() << "VLC-Qt Error: libvlc failed to load!";
}

VlcDecoder::~VlcDecoder()
{
    libvlc_media_player_release(vlcPlayer);
    libvlc_release(vlcInstance);
}

void VlcDecoder::setVideoOutput(MediaWidgetWrapper *renderer)
{
    Renderer = renderer;
#if defined(Q_OS_MAC)
    libvlc_media_player_set_nsobject(vlcPlayer, (void *)Renderer->getVideoWidget()->winId());
#elif defined(Q_OS_UNIX)
    libvlc_media_player_set_xwindow(vlcPlayer, Renderer->getVideoRenderer()->winId());
#elif defined(Q_OS_WIN)
    libvlc_media_player_set_hwnd(vlcPlayer, Renderer->getVideoRenderer()->winId());
#endif
}

void VlcDecoder::removeVideoOutput(MediaWidgetWrapper *renderer)
{
    Q_UNUSED(renderer);
}

bool VlcDecoder::load(QString file_path)
{
    current_media_path = file_path;
    vlcMedia = libvlc_media_new_path(vlcInstance, current_media_path.toStdString().c_str());
    if (vlcMedia == NULL)
        return false;

    libvlc_media_player_set_media(vlcPlayer, vlcMedia);

    return true;
}

void VlcDecoder::setVolume(QString percent)
{
    if (vlcPlayer == NULL)
        return;

    int vol = 0;
    if (percent.endsWith('%'))
        vol = percent.mid(0, percent.length()-1).toInt();
    libvlc_audio_set_volume(vlcPlayer,vol);
}

void VlcDecoder::unload()
{
    libvlc_media_player_set_media(vlcPlayer, NULL);
    libvlc_media_release(vlcMedia);
}

void VlcDecoder::play()
{
    if (vlcPlayer == NULL)
        return;

    libvlc_media_player_play(vlcPlayer);

    /* A timer to update the sliders */
    PositionTimer.reset(new QTimer(this));
    connect(PositionTimer.data(), SIGNAL(timeout()), this, SLOT(updatePosition()));
    PositionTimer.data()->start(100);

}

void VlcDecoder::stop()
{
    if (vlcPlayer == NULL)
        return;

    libvlc_media_player_stop(vlcPlayer);
}

void VlcDecoder::updatePosition()
{
    if (vlcPlayer == NULL)
        return;

    libvlc_state_t status = libvlc_media_player_get_state(vlcPlayer);

    switch (status)
    {
        case libvlc_Opening:
            break;
        case libvlc_Buffering:
            break;
        case libvlc_Playing:
            break;
        case libvlc_Paused:
            break;
        case libvlc_Stopped:
            PositionTimer.data()->stop();
            break;
        case libvlc_Ended:
            PositionTimer.data()->stop();
            emit finished();
            break;
        case libvlc_Error:
            qWarning(Develop) << "Error" << current_media_path;
            break;

        case libvlc_NothingSpecial:
        default:
            break;

    }
}

void VlcDecoder::displayErrorMessage()
{

}
#endif
