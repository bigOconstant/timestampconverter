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
  //  alignLeftAction->setIcon(QIcon(":/icons/alignLeft.png"));

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
        QString buttvalor = butval;
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
        QDateTime qtimestamp = QDateTime::fromTime_t(sec);


        ui->listWidget->insertItem(0,ui->timeformat->currentText()+" " +buttvalor+" UTC:"+qtimestamp.toUTC().toString()+ "    Local:"+qtimestamp.toString());
        ui->utcOutput->setText(qtimestamp.toUTC().toString());
        ui->CentralOutput->setText(qtimestamp.toString());
    }else{
        ui->ErrorOutput->setText("Error, Invalid");
    }

}

