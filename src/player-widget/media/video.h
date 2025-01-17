#ifndef VIDEO_H
#define VIDEO_H

#include "mediaplayer_wrapper.h"
#include "mediawidget_wrapper.h"
#include "smilparser/media/video.h"
#include "player_base_media.h"

class PlayerVideo : public PlayerBaseMedia
{
        Q_OBJECT
    public:
        PlayerVideo(QObject *parent = nullptr);
        ~PlayerVideo();
        void              init(BaseMedia *media, Region *reg);
        void              deinit();
        void              changeSize(int w, int h);
        QWidget          *getView();
    protected:
        QScopedPointer<MediaWidgetWrapper>     VideoWidget;
        QScopedPointer<MediaPlayerWrapper, QScopedPointerDeleteLater>   MediaDecoder;
    protected slots:
        void                  finished();
};

#endif // VIDEO_H
