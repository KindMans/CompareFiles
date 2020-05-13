#include "filecalltomd5.h"
#include <QFile>
#include <QCryptographicHash>
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QByteArray>

fileCallToMd5::fileCallToMd5(QObject *parent) : QObject(parent)
{

}

QString fileCallToMd5::openDirectory()
{
    return QFileDialog::getExistingDirectory(nullptr,"打开文件夹","*");
}

QStringList fileCallToMd5::getFiles(const QString &path)
{
    if(path.isEmpty())
        return QStringList();

    QStringList fileListRet,fileNames;
    QDir dir(path);
    QFileInfoList infoList=dir.entryInfoList(QDir::NoDotAndDotDot|QDir::Dirs|QDir::Files);
    for(int i=0;i<infoList.size();i++)
    {
        QFileInfo info = infoList[i];
        if(info.isDir()){
            QString dir = info.absoluteFilePath();
            fileNames = getFiles(dir);
            fileListRet.append(fileNames);
        }else{
            QString fileName = info.absoluteFilePath();
            fileListRet.append(fileName);
        }
    }
    return fileListRet;
}

QString fileCallToMd5::getFileMd5(const QString &path)
{
    if(path.isEmpty())
        return QString();

    QCryptographicHash md5Hash(QCryptographicHash::Md5);
    QFile file(path);
    if(file.open(QIODevice::ReadWrite))
    {
        while (!file.atEnd())
        {
            QString data = file.read(1024*1024);
            QByteArray curData=data.toLatin1();
            md5Hash.addData(curData,curData.size());
            qApp->processEvents();
            qDebug()<< md5Hash.result().toHex();
        }
    }

    file.close();

    return md5Hash.result();
}


















