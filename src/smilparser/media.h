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

#ifndef MEDIA_H
#define MEDIA_H

#include "smilparser/container.h"
#include "files/file_manager.h"

class TMedia : public TBaseTiming
{
    Q_OBJECT
public:
    TMedia(TBaseTiming * parent = 0);
    QString           getRegion(){return region;}
    QString           getFit(){return fit;}
    QString           getSrc() {return src;}
    QString           getBaseType() {return "media";}
    bool              parse(QDomElement element);
    void              resume(){play();}
    void              registerFile(TFileManager *FileManager);
    bool              hasPlayingChilds(){return false;}
    TBaseTiming      *getChildElementFromList(){return this;}
    TContainer       *getParentContainer(){return parent_container;}
    static  QString   parseSrc(QDomElement element);
    bool              load();
public slots:
    void              emitfinished();
protected:
    TFileManager     *MyFileManager;
    TContainer       *parent_container;
    QString           region = "screen";
    QString           src, exec, fit = "";
    QString           cached_file_path;
    QString           filename, cache_control, log_content_id  = "";
    bool              loaded;
    void              setBaseMediaAttributes();
    void              setBaseParameters();
    virtual bool      loadMedia() = 0;
    virtual void      setAttributes() = 0;
private:
signals:
    void              startedMedia(TContainer *parent , TBaseTiming *element);
    void              finishedMedia(TContainer *parent , TBaseTiming *element);

};

#endif // MEDIA_H
