#ifndef FILES_H
#define FILES_H

#include <QTemporaryFile>
#include <QDateTime>
#include "base_controller.h"
#include "db/inventory_table.h"
#include "files/free_disc_space.h"

namespace RestApi
{
    namespace V2
    {
        class Files : public BaseController
        {
                Q_OBJECT
            public:
                explicit Files(QObject *parent = nullptr);
                void     setInventoryTable(DB::InventoryTable *it);
                void     setFreeDiscSpace(FreeDiscSpace *fds);
                QString  findInfoByID(QString id);
                QString  modifyByID(QString id,  qint64 seek, QTemporaryFile *tfile, qint64 file_size, QString download_path, QString etag, QString mime_type, QString modified_date);
                QString  createNew(QTemporaryFile *tfile, qint64 file_size, QString download_path, QString etag, QString mime_type, QString modified_date);
                QString  findPaginated(int max_results, int begin);
                QString  remove(QString body);
            private:
                DB::InventoryTable *MyInventoryTable;
                FreeDiscSpace      *MyFreeDiscSpace;
                bool        canCreateNewProceed(QTemporaryFile *tfile, quint64 file_size, QString download_path);
                void        createJsonFromList(QList<DB::InventoryDataset> results);
                QJsonObject createObject(DB::InventoryDataset dataset);
                QString     getState(int state);
                QString     determineIDFromJson(QString json_string);
        };
    }
}
#endif // FILES_H
