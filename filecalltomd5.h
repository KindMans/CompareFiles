#ifndef FILECALLTOMD5_H
#define FILECALLTOMD5_H
#include <QObject>
/*
    anchor:lgl
    times:2020.5.12
*/

class fileCallToMd5 : public QObject
{
    Q_OBJECT
public:
    explicit fileCallToMd5(QObject *parent = nullptr);

    QString openDirectory();
    QString getFileMd5(const QString &path);
    QStringList getFiles(const QString &path);
signals:
    void signalGetFileMd5();
};

#endif // FILECALLTOMD5_H
