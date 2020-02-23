# Timestampconverter
QT Tool to convert unix times to human readable times for bug fixing. 

Especially useful for monitoring Influxdb logs

Example time in nanoseconds `1581417272788691567`

gives the output `Tue Feb 11 10:34:32 2020 GMT`

History is stored in a local sqlite db file.

Only the last 100 records persist in the database so that the database doesn't grow forever. 

### How do I delete history records?
The backspace or delete key will delete the selected record

### Other keypresses
Enter or return on a historical record will load it into the main ui just like clicking a record will

### What is the maximum time?
around the year 2100

## Where do I get a build?

[Download Mac release here](https://github.com/camccar/timestampconverter/releases)

![screenshot](https://raw.githubusercontent.com/camccar/timestampconverter/master/screenshot.png)

## Make a release build

command I use `/Users/caleb/Qt/5.12.7/clang_64/bin/macdeployqt /build-releasedir/timeStampConverter.app -dmg`

### Where is the database stored?

On mac it's in `~/Library/Application Support/timeStampConverter`

### How do I remove the database
on a mac terminal `rm -rf ~/Library/Application\ Support/timeStampConverter`

## How could I contribute?

I could use someone to make windows and linux builds. 


