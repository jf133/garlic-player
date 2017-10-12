#ifndef WGT_H
#define WGT_H

#include <QObject>
#include "../ext/quazip/JlCompress.h"
#include <logging_categories.h>
#include "disc_space.h"

class Wgt : public QObject
{
    Q_OBJECT
public:
    explicit Wgt(QString file_path = "", QObject *parent=Q_NULLPTR);
    ~Wgt();
    void         setFilePath(QString file_path);
    bool         isOpen();
    QString      handleRealPath();
    bool         extract();
    qint64       calculateUncompressedSize();
protected:
    QuaZip zip;
    QString local_file_path;
signals:

public slots:
};

#endif // WGT_H 
