#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPainter>
#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    QPushButton *gen;
    QTextEdit *line;
    QComboBox *fgColor;
    QComboBox *bgColor;
    QColor* fg;
    QColor* bg;


protected:

    virtual void paintEvent(QPaintEvent *);

private slots:

};



#endif // MAINWINDOW_H
