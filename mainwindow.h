#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_create_clicked();

    void on_btn_copy_clicked();

private:
    Ui::MainWindow *ui;

    QString getHexString(QString src);
    QByteArray hexStringtoByteArray(QString hex);
    void formatString(QString &org, int n=2, const QChar &ch=QChar(' '));
};

#endif // MAINWINDOW_H
