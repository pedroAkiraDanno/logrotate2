# logrotate

Log Rotate based on filesize with Timestamp of lines, open source C code (Apache License, Version 2.0). Do not require any external code/lib.

For more information look at our
docs located at [doc](https://github.com/pedroAkiraDanno/logrotate2/tree/main/doc/main) and [wiki]() .

---

## How works:

Read from stdin and output lines with timestamp in an output file (pathname), rotating them when file size exceeds specified size in bytes.


## About versions (for more infos check [CHANGELOG.md](https://github.com/pedroAkiraDanno/logrotate2/blob/main/CHANGELOG.md))
    v0.1.0 - dont recomend to use, is forks about old project - have a lot problemas and bugs to fix 
    v0.2.0 - first version that can use - like a fork in project ggrandes/logrotate -every thing is OK to use     **explain- will create just 2 files. ex: file.log when full create file.log.old and when full switch to the first file again file.log


## Compile (handmade)

    gcc -Wall -O2 logrotate.c -o logrotate

## Running

    ./process-to-log | ./logrotate <pathname> <size-limit-bytes>


## Running Example

    ./process-to-log | ./logrotate file.log 100    

## Example output file:

    2013-06-02 00:47:51 > Lorem ipsum dolor sit amet, consectetur adipiscing elit.
    2013-06-02 00:47:51 > Pellentesque in mi ac tellus porttitor condimentum.



## Examples Running options:
    ./logrotate help     
    ./logrotate --help    
    ./logrotate -h    

    ./logrotate version    
    ./logrotate --version    
    ./logrotate --v    

    ./logrotate copyright    
    ./logrotate --copyright                        





## STEPS by STEPS on Linux Environment (completed)
    sudo su - 
    sudo apt-get install gcc -y

    cd ~
    rm -fr logrotate2/
    git clone https://github.com/pedroAkiraDanno/logrotate2.git
    cd logrotate2/src/
    chmod +x process-to-log test1

    gcc -Wall -O2 logrotate.c -o logrotate
    #OR
    gcc logrotate.c  -o logrotate    

    ./test1 | ./logrotate file.log 100






---
Inspired in [rotatelogs](http://httpd.apache.org/docs/2.2/programs/rotatelogs.html) , [cronolog](http://cronolog.org/) , [logrotete](https://github.com/ggrandes/logrotate) and [rsyslog](https://www.rsyslog.com/), this is C-minimalistic version.
