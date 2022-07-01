# logrotate

Log Rotate based on filesize with Timestamp of lines, open source C code (Apache License, Version 2.0). Do not require any external code/lib.

---

## How works:

Read from stdin and output lines with timestamp in an output file (pathname), rotating them when file size exceeds specified size in bytes.

## STEPS (completed)
    sudo su - 
    apt-get install -y
    cd ~

    rm -fr logrotate/
    git clone https://github.com/pedroAkiraDanno/logrotate.git
    cd logrotate/src/
    chmod +x process-to-log test1

    gcc -Wall -O2 logrotate.c -o logrotate

    ./test1 | ./logrotate6 file.log 100 10 0



## Running Syntax
    old versions
        ./process-to-log | ./logrotate <pathname> <size-limit-bytes>
    new versions
        ./process-to-log | ./logrotate6 <pathname> <size-limit-bytes>  <LOGFILEGROUP> <archiveLogEnabled>



## Example output file:

    2013-06-02 00:47:51 > Lorem ipsum dolor sit amet, consectetur adipiscing elit.
    2013-06-02 00:47:51 > Pellentesque in mi ac tellus porttitor condimentum.

---
Inspired in [rotatelogs](http://httpd.apache.org/docs/2.2/programs/rotatelogs.html) , [cronolog](http://cronolog.org/) and [logrotete](https://github.com/ggrandes/logrotate), this is C-minimalistic version.
