#ifndef COMPAREFILE_H
#define COMPAREFILE_H

#include <QWidget>
#include "filecalltomd5.h"
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class CompareFile; }
QT_END_NAMESPACE

enum Model{
    FILE1 = 0,
    FILE2,
};

class CompareFile : public QWidget
{
    Q_OBJECT

public:
    CompareFile(QWidget *parent = nullptr);
    ~CompareFile();

    void getFilesInfo(Model);

private slots:
    void on_btn_open_1_clicked();

    void on_btn_open_2_clicked();

    void on_btn_compare_clicked();

private:
    Ui::CompareFile *ui;

    fileCallToMd5 m_md5;

    QString m_path;
    QStringList m_fileNames1;
    QStringList m_fileNames2;
    QStringList m_compareNames;
    QMap<QString,QString> m_map1;
    QMap<QString,QString> m_map2;
};
#endif // COMPAREFILE_H
