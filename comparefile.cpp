#include "comparefile.h"
#include "ui_comparefile.h"

CompareFile::CompareFile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CompareFile)
{
    ui->setupUi(this);
    ui->file_text1->setPlaceholderText("在这里输入路径");
    ui->file_text2->setPlaceholderText("在这里输入路径");
}

CompareFile::~CompareFile()
{
    delete ui;
}

void CompareFile::getFilesInfo(Model m)
{
    if(m_path.isEmpty())
        return;
    m_fileNames1.clear();
    m_fileNames2.clear();
    QStringList fileNames = m_md5.getFiles(m_path);
    for(int i=0;i<fileNames.size();i++)
    {
        QString fileNamePath = fileNames[i];
        QString md5 = m_md5.getFileMd5(fileNamePath);
        if(m == Model::FILE1)
        {
            m_map1[fileNamePath] = md5;
            m_fileNames1.append(fileNamePath);
        }else if(m == Model::FILE2)
        {
            m_map2[fileNamePath] = md5;
            m_fileNames2.append(fileNamePath);
        }
    }
}

/*
    打开文件1
*/
void CompareFile::on_btn_open_1_clicked()
{
    ui->listWidget1->clear();
    m_compareNames.clear();
    QString path = m_md5.openDirectory();
    m_path = path;
    getFilesInfo(Model::FILE1);
    //数据展示到界面
    ui->file_text1->setText(path);
    ui->listWidget1->addItems(m_fileNames1);
}

/*
    打开文件2
*/
void CompareFile::on_btn_open_2_clicked()
{
    ui->listWidget2->clear();
    m_compareNames.clear();
    QString path = m_md5.openDirectory();
    m_path = path;
    getFilesInfo(Model::FILE2);
    ui->file_text2->setText(path);
    ui->listWidget2->addItems(m_fileNames2);
}

/*
    比较文件
*/
void CompareFile::on_btn_compare_clicked()
{
    for(QMap<QString,QString>::iterator iter=m_map1.begin();iter!=m_map1.end();iter++)
    {
        for(QMap<QString,QString>::iterator iter2=m_map2.begin();iter2!=m_map2.end();iter2++)
        {
            if(iter.value() == iter2.value())
            {
                m_compareNames.append(iter2.key());
            }
        }
    }

    for(int i=0;i<ui->listWidget2->count();i++)
    {
        if(!m_compareNames.contains(ui->listWidget2->item(i)->text()))
        {
            ui->listWidget2->item(i)->setTextColor(QColor("red"));
        }
    }
}










