# logrotate

Log Rotate based on filesize with Timestamp of lines, open source C code (Apache License, Version 2.0). Do not require any external code/lib.

---

## How works:

Read from stdin and output lines with timestamp in an output file (pathname), rotating them when file size exceeds specified size in bytes.

## Compile (handmade)

    gcc -Wall -O2 logrotate.c -o logrotate

## Running

    ./process-to-log | ./logrotate <pathname> <size-limit-bytes>


## Running Example

    ./process-to-log | ./logrotate file.log 100    

## Example output file:

    2013-06-02 00:47:51 > Lorem ipsum dolor sit amet, consectetur adipiscing elit.
    2013-06-02 00:47:51 > Pellentesque in mi ac tellus porttitor condimentum.



## STEPS by STEPS on Linux Environment (completed)
    sudo su - 
    sudo apt-get install gcc -y
    cd ~

    rm -fr logrotate/
    git clone https://github.com/pedroAkiraDanno/logrotate.git
    cd logrotate/src/
    chmod +x process-to-log test1

    gcc -Wall -O2 logrotate.c -o logrotate

    ./test1 | ./logrotate file.log 100






---
Inspired in [rotatelogs](http://httpd.apache.org/docs/2.2/programs/rotatelogs.html) , [cronolog](http://cronolog.org/) , [logrotete](https://github.com/ggrandes/logrotate) and [rsyslog](https://www.rsyslog.com/), this is C-minimalistic version.