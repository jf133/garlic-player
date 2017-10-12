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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <QSettings>
#include <QStandardPaths>
#include <QDir>
#include <QUrl>
#include <QUuid>
#include <QString>
#include "logging_categories.h"

/**
 * @brief The TConfiguration class
 */
class TConfiguration  : public QObject
{
    Q_OBJECT
public:
    explicit TConfiguration(QSettings *UserConfig, QObject *parent = Q_NULLPTR);
    QString         getVersion(){return "0.1.0";}
    void            setAppName(QString value){app_name = value;}
    QString         getAppName(){return app_name;}
    QString         getDescription() {return "SMIL Media Player for Digital Signage";}

    QString         getLastPlayedIndexPath();
    void            setLastPlayedIndexPath(const QString &value);
    QSettings      *getUserConfig() const;
    void            setUserConfig(QSettings *value);
    QString         getUserConfigByKey(QString key);
    void            setUserConfigByKey(QString key, QString value);
    QString         getUuid() const;
    void            setUuid(const QString &value);
    QString         getPlayerName() const;
    void            setPlayerName(const QString &value);
    QString         getUserAgent() const;
    void            setUserAgent(const QString &value);
    QString         getOS() const;
    void            setOS(const QString &value);
    QString         getPaths(QString path_name);
    void            setIndexUri(const QString &value);
    QString         getIndexUri();
    void            setIndexPath(const QString &value);
    QString         getIndexPath();
    QString         getBasePath() const;
    void            setBasePath(const QString &value);
    void            determineBasePath(QString absolute_path_to_bin);
    void            determineIndexUri(QString path);
    void            createDirectories();
    void            determineUserAgent();
    void            checkConfigXML();



protected:
    QSettings      *UserConfig;
    QString         uuid, player_name, user_agent, os, base_path, index_uri, index_path = "";
    QString         cache_dir, log_dir = "";
    QString         app_name = "garlic-player";
    void            createDirectoryIfNotExist(QString path);
    void            determineIndexPath();
    void            determineUuid();
    void            determinePlayerName();
    void            determineOS();
};

#endif // CONFIGURATION_H
