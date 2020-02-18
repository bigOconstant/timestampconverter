#ifndef TIMEWINDOW_H
#define TIMEWINDOW_H

#include <QMainWindow>

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

private slots:
    void CalculateTime();
};
#endif // TIMEWINDOW_H
