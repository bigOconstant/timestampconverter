#include "timewindow.h"
#include "ui_timewindow.h"
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <ctime>
TimeWindow::TimeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TimeWindow)
{
    ui->setupUi(this);
    connect(ui->ConvertButton,SIGNAL(released()),this,SLOT(CalculateTime()));
  //  alignLeftAction->setIcon(QIcon(":/icons/alignLeft.png"));

}

TimeWindow::~TimeWindow()
{
    delete ui;
}

std::string timeStampToHReadble(const time_t rawtime,int timezoneEnum)
{
    struct tm * dt;
    char buffer [30];
    //dt = localtime(&rawtime);
    if(timezoneEnum == 0){
        dt = gmtime(&rawtime);
    }else{
        dt = localtime(&rawtime);
    }
    strftime(buffer, sizeof(buffer), "%m-%d-%Y %I:%M:%S", dt);
    return std::string(buffer);
}


void TimeWindow::CalculateTime(){
    QString butval = ui->TimeStampInput->toPlainText();

    QRegExp reg("[0-9.]*");
    if(reg.exactMatch(butval)){
        ui->ErrorOutput->setText("");
       if(butval.length()>13){
           butval = butval.left(13);
       }


       long timestamp = butval.toLong();
       int sec;
        if(ui->timeformat->currentText() == "Milliseconds"){
            sec = ((timestamp + 500) / 1000);
        }else{
            sec = timestamp;
        }

       std::string buffer = timeStampToHReadble((time_t)sec,0);

        ui->utcOutput->setText(QString::fromStdString(buffer));
        ui->CentralOutput->setText(QString::fromStdString(timeStampToHReadble((time_t)sec,1)));
    }else{
        ui->ErrorOutput->setText("Error, Invalid");
    }

}

