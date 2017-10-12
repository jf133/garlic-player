#ifndef MPIMAGE_H
#define MPIMAGE_H

#include <QObject>
#include <QLabel>
#include <QPixmap>
#include "base_media.h"
#include "smilparser/image.h"

    class Image : public BaseMedia
    {
            Q_OBJECT
        public:
            explicit      Image(TMedia *media, QObject *parent = nullptr);
            ~Image();
            void          init();
            void          changeSize(int w, int h);
            QWidget      *getView();
        protected:
            TImage        *ParserImage;
            QPixmap        loaded_image;
            QLabel        *ImageWidget;
    };


#endif // MPIMAGE_H
