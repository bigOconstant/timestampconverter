#ifndef TIMEWINDOW_H
#define TIMEWINDOW_H

#include <QMainWindow>
#include "Database.h"
#include "about.h"
QT_BEGIN_NAMESPACE
namespace Ui { class TimeWindow; }
QT_END_NAMESPACE

class TimeWindow : public QMainWindow
{
    Q_OBJECT

public:
    TimeWindow(QWidget *parent = nullptr);
    ~TimeWindow();
    bool eventFilter(QObject *object, QEvent *event);
protected:
    void timerEvent(QTimerEvent *event);


private:
    Ui::TimeWindow *ui;
    Database* t;
    About *wdg;

private slots:
    void CalculateTime(bool inside = 0);
    void SetSecondText();
    void RetrieveHistoryItem(QListWidgetItem*);
    void OpenAbout();
    void setCurrentTime();
};
#endif // TIMEWINDOW_H
