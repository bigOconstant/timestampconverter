#include "timewindow.h"
#include "ui_timewindow.h"
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <ctime>
 #include <QDateTime>

TimeWindow::TimeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TimeWindow)
{
    ui->setupUi(this);
    connect(ui->ConvertButton,SIGNAL(released()),this,SLOT(CalculateTime()));
     t = new Database();
     auto historyvalues = t->getHistory();
     for(auto it = historyvalues.begin(); it < historyvalues.end(); ++it){
         ui->listWidget->insertItem(0,(*it));
     }


}

TimeWindow::~TimeWindow()
{
    delete ui;
}



void TimeWindow::CalculateTime(){
    QString butval = ui->TimeStampInput->toPlainText();

    QRegExp reg("[0-9.]*");
    if(reg.exactMatch(butval)){
       ui->ErrorOutput->setText("");

       uint64_t timestamp = butval.toLong();
       uint64_t sec;
       if(ui->timeformat->currentText() == "Nanoseconds"){
           sec = timestamp /  1000000000ULL;
       }
        else if(ui->timeformat->currentText() == "Milliseconds"){
            sec = ((timestamp + 500) / 1000);
        }else{
            sec = timestamp;
        }
        QDateTime qtimestamp = QDateTime::fromTime_t(sec);

        QString historyvalue = ui->timeformat->currentText()+" " +butval+" UTC:"+qtimestamp.toUTC().toString()+ "    Local:"+qtimestamp.toString();
        ui->listWidget->insertItem(0,historyvalue);

        t->insertRow(butval,ui->timeformat->currentText());
        ui->utcOutput->setText(qtimestamp.toUTC().toString());
        ui->CentralOutput->setText(qtimestamp.toString());
    }else{
        ui->ErrorOutput->setText("Error, Invalid");
    }

}

