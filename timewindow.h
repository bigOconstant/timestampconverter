#ifndef TIMEWINDOW_H
#define TIMEWINDOW_H

#include <QMainWindow>
#include "Database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TimeWindow; }
QT_END_NAMESPACE

class TimeWindow : public QMainWindow
{
    Q_OBJECT

public:
    TimeWindow(QWidget *parent = nullptr);
    ~TimeWindow();

private:
    Ui::TimeWindow *ui;
    Database* t;

private slots:
    void CalculateTime();
    void SetSecondText();
};
#endif // TIMEWINDOW_H
