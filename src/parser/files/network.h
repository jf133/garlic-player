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
#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFileInfo>

#include <logging_categories.h>

/**
 * @brief The Network class capsulates network accesses
 * - handles head, get and redirect requests
 * - emit a signal with QIODevioce for download when succeeded
 * - logs success (info) and error notifications
 */
class Network : public QObject
{
    Q_OBJECT
public:

    Network(QByteArray agent);

    void       processFile(QUrl url, QFileInfo fi);

    //Getter/Setter
    QByteArray getUserAgent() const {return user_agent;}
    void       setUserAgent(const QByteArray &value) {user_agent = value;}
    QFileInfo  getLocalFileInfo() const {return local_file_info;}
    void       setLocalFileInfo(const QFileInfo &value) {local_file_info = value;}
    QUrl       getRemoteFileUrl() const {return remote_file_url;}
    void       setRemoteFileUrl(const QUrl &value){remote_file_url = value;}
public slots:

protected:
    QUrl                   remote_file_url;
    QByteArray             user_agent;
    QFileInfo              local_file_info;
    QNetworkAccessManager *manager_head, *manager_head_redirect, *manager_get;
    void                   doHttpHeadRequest();
    void                   doHttpGetRequest();
    QNetworkRequest        prepareNetworkRequest(QUrl remote_url);
    void                   checkStatusCode(QNetworkReply *reply, int status_code);
    void                   checkHttpHeaders(QNetworkReply *reply);
    bool                   validContentType(QString content_type);
    void                   handleNetworkError(QNetworkReply *reply);
protected slots:
    void                   finishedHeadRequest(QNetworkReply *reply);
    void                   finishedHeadRedirectRequest(QNetworkReply *reply);
    void                   finishedGetRequest(QNetworkReply *reply);
signals:
    void                   downloadPossible(QIODevice *data);
    void                   downloadInpossible();
};

#endif // NETWORK_H
