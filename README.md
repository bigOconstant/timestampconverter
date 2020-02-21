# timestampconverter
QT Tool to convert unix times to human readable times for bug fixing. 

Especially useful for monitoring Influxdb logs

Example time in nanoseconds `1581417272788691567`

gives the output `Tue Feb 11 10:34:32 2020 GMT`

[Download Mac release here](https://github.com/camccar/timestampconverter/releases)

![screenshot](https://raw.githubusercontent.com/camccar/timestampconverter/master/screenshot.png)

## Make a release build

command I use `/Users/caleb/Qt/5.12.7/clang_64/bin/macdeployqt /build-releasedir/timeStampConverter.app -dmg`

### Where is the database store?

on mac it's in `~/Library/Application Support/timeStampConverter`


