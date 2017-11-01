/*************************************************************************************
    garlic-player: SMIL Player for Digital Signage
    Copyright (C) 2016 Nikolaos Saghiadinos <ns@smil-control.com>
    This file is part of the garlic-player source code

    This program is free software: you can redistribute it and/or  modify
    it under the terms of the GNU Affero General Public License, version 3,
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*************************************************************************************/
#ifndef MEDIA_MODEL_H
#define MEDIA_MODEL_H

#include <QObject>
#include <QMap>

#include "tools/configuration.h"
#include "download_queue.h"
#include "disc_space.h"
#include "files/wgt.h"

/**
 * @brief The FileModel class handles the file management and use the DiscSpace-class as helper
 *
 * - handles different media files eg extracting of wgt
 * - organize a Map of available Files with their "real" path and statuses
 */
class MediaModel : public QObject
{
    Q_OBJECT
    public:
        const     int        _no_exist   = 0;
        const     int        _exist      = 1;
        const     int        _reloadable = 2;
        const     int        _uncachable = 3;

        explicit MediaModel(QObject *parent=Q_NULLPTR);
        ~MediaModel();

        void                                          clearQueue();
        QString                                       findLocalBySrcPath(QString src_file_path);
        int                                           findStatusBySrcPath(QString src_file_path);
        void                                          insertAvaibleLink(QString src_file_path);
        void                                          insertAvaibleFile(QString src_file_path, QString local_file_path);

        //Getter/Setter
        QMap<QString, QPair<QString, int> >           getAvailableMediaList() const {return available_media_list;}
        void                                          setAvailableMediaList(const QMap<QString, QPair<QString, int> > &value) {available_media_list = value;}
        QString                                       determineHashedFilePath(QString src_file_path);

    protected:
        QMap<QString, QPair<QString, int>>            available_media_list;
        QMap<QString, QPair<QString, int>>::iterator  i_available_media_list;
        QString                                       determinePathByMedia(QString src_file_path, QString local_file_path);

};

#endif // MEDIA_MODEL_H
