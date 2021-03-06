
#pragma once

#include <string>
#include <QWidget>
#include <QDateTime>
#include "Path.h"
#include "DocumentType.h"

class IDocument : public QWidget
{
    Q_OBJECT

public:
    virtual DocumentType getType() const = 0;

    void open(Path documentPath);
    virtual void save();
    virtual void reload();

    Path getPath() { return documentPath; }
    std::string getName() { return documentPath.getName(); }
    std::string getTabName();

    bool isModifiedOutside();
    void ignoreOutsideModification();

    virtual bool changed() const = 0;

protected:
    QDateTime getLastModifiedTime();
    virtual void setBinaryData(QByteArray data) = 0;
    virtual QByteArray getBinaryData() const = 0;

private slots:
    void onModified();

signals:
    void modified();

protected:
    Path documentPath;
    QDateTime modifiedTime;
};
