#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QClipboard>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// AA 01 03 61 01 94 F6 FA A5
void MainWindow::on_btn_create_clicked()
{
    QString head = getHexString(ui->le_head->text());
    QString addr = getHexString(ui->le_addr->text());
    QString tail = getHexString(ui->le_tail->text());
    QString data = getHexString(ui->le_data->text());

    if(head.size() != 2 || addr.size() != 2 || tail.size() != 2 || data.size() == 0)
    {
        QMessageBox::warning(this, "错误", "非法数据                 ", QMessageBox::Close);
        return;
    }

    int dataLen = data.size() / 2;
    int checkLen = dataLen + 2;

    QByteArray ba;
    ba[0] = head.toInt(0, 16) & 0xFF;
    ba[1] = addr.toInt(0, 16) & 0xFF;
    ba[2] = dataLen & 0xFF;
    ba.append(hexStringtoByteArray(data));
    ba[dataLen + 3] = 0;
    ba[dataLen + 4] = 0;
    ba[dataLen + 5] = 0;

    for(int i = 1; i <= checkLen; i++)
    {
        ba[dataLen + 3] = ba[i] ^ ba[dataLen + 3];
        ba[dataLen + 4] = ba[i] + ba[dataLen + 4];
    }

    ba[dataLen + 5] = tail.toInt(0, 16) & 0xFF;

    QString pkg = ba.toHex().toUpper();
    formatString(pkg, 2, ' ');
    ui->le_pkg->setText(pkg);

    qDebug()<<pkg;

}

QString MainWindow::getHexString(QString src)
{
    src = src.remove(QChar(' '), Qt::CaseInsensitive).toUpper();

    foreach(QChar ch, src)
    {
        if(!((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F')))
        {
            qDebug()<< "invalid data: not hex string";
            src = "";
            break;
        }
    }

    if(src.size() % 2)
    {
        src = "";
    }
    qDebug()<<src;
    return src;
}

void MainWindow::formatString(QString &org, int n, const QChar &ch)
{
    int size = org.size();
    int space = qRound(size * 1.0 / n + 0.5) - 1;
    if(space <= 0)
        return;
    for(int i = 0, pos =n ; i < space; ++i, pos += (n + 1))
    {
        org.insert(pos, ch);
    }
}

QByteArray MainWindow::hexStringtoByteArray(QString hex)
{
    QByteArray ba;
    hex = hex.trimmed();
    formatString(hex, 2, ' ');

    QStringList sl = hex.split(" ");

    foreach(QString s, sl)
    {
        if(!s.isEmpty())
            ba.append(s.toInt(0, 16) & 0xFF);
    }

    return ba;
}




void MainWindow::on_btn_copy_clicked()
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(ui->le_pkg->text());
}

#if 0
QString MainWindow::ByteArrayToHexString(QByteArray data)
{
    QString ret(data.toHex().toUpper());
    int len = ret.length()/2;
    qDebug()<<len;
    for(int i=1;i<len;i++)
    {
        qDebug()<<i;
        ret.insert(2*i+i-1," ");
    }

    return ret;
}
#endif
