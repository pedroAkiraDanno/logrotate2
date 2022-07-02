/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * 01-07-2022, v1.0, Pedro Akira Danno Lima
 *
 * Compile: gcc -Wall -O2 logrotate.c -o logrotate
 */




//MACROS 
#define _LARGEFILE_SOURCE
#define _FILE_OFFSET_BITS 64
#define _GNU_SOURCE
#define _XOPEN_SOURCE 600

//header files 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>

//MACROS 
#define BUF_SIZE_IN 2048
#define BUF_SIZE_TS 64
#define VERSION     "1.0"

/* Global Variables */
static char *name = NULL;
static unsigned long MAX_SIZE = 0;


/*Function Prototypes */
  int printLineTS(char *buf, int maxLen, char *extra); // ex: 2020-11-21 09:27:44 > extra   _BUF_SIZE_TS 64
  int loadBuffer(void *buf, int pos, int size); //system call read 
  unsigned long long getFileSize(int fd); // get the size file
  int openOutput(void); //open a file, open a file mean create a pointer to file in memory to hard disk 
  void rotateLog(int *fd); //if MAX_SIZE > file log switch to another file 
  void process(void);
  void help();








//
 int
printLineTS(char *buf, int maxLen, char *extra)
{
       time_t t = time(NULL);
       struct tm *p_tm = localtime(&t);
       return snprintf(buf, maxLen, "%04d-%02d-%02d %02d:%02d:%02d%s", p_tm->tm_year+1900, p_tm->tm_mon+1, p_tm->tm_mday, p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec, extra);
}





//
 int
loadBuffer(void *buf, int pos, int size)
{
    ssize_t r = 0;
    r =  read(0, buf + pos, size - pos);
    return r;

}
// warning then compile gcc https://stackoverflow.com/questions/9148134/declared-with-attribute-warn-unused-result-wunused-result



//
 unsigned long long
getFileSize(int fd)
{
    struct stat sb;
    int res = fstat(fd, &sb);
    if (res != 0) {
        fprintf(stderr, "Error fstat res(%d): %d (%s)\n", res, errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return sb.st_size;
}




//
 int
openOutput(void)
{
    int fd = -1;
    // Open Output File
    fd = open(name, O_CREAT|O_APPEND|O_WRONLY|O_LARGEFILE, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if (fd < 0) {
        fprintf(stderr, "Error open: %d (%s)\n", errno, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return fd;
}






//
 void 
rotateLog(int *fd)
{
    if (*fd == -1) {
        *fd = openOutput();
    } else {
        unsigned long long fileSize = getFileSize(*fd);
        if (fileSize > MAX_SIZE) {
            char newname[2048];
            close(*fd);
            *fd = -1;
            snprintf(newname, sizeof(newname), "%s.old", name);
            rename(name, newname);
            *fd = openOutput();
        }
    }
}




//
void
process(void) 
{
    ssize_t readed = 0;
    ssize_t  r2;
    int fd = -1;
    int i;
    int head = 0;
    int eol = 0;
    int newlined = 0;
    char bufin[BUF_SIZE_IN];
    char bufts[BUF_SIZE_TS];
    //
    memset(bufin, 0, sizeof(bufin));
    while ((readed = loadBuffer(bufin, head, sizeof(bufin)-1)) > 0) {
        bufin[readed] = 0;
        for (i = 0; i < readed; i++) {
            if (bufin[i] == 10 || bufin[i] == 13 || bufin[i] == 0) { // EOL
                bufin[i] = 0; // EOB
                r2 = write(fd, bufin + head, i - head);
                if (eol == 0) {
                    r2 = write(fd, "\n", 1);
                }
                head = i+1;
                eol++; newlined=0;
            } else {
                if (!newlined) {
                    int len = printLineTS(bufts, sizeof(bufts), " > ");
                    rotateLog(&fd);
                    r2 = write(fd, bufts, len);
                    newlined++;
                }
                eol = 0;
            }
        }
        if (!eol) {
            r2 = write(fd, bufin + head, readed - head);
        }
        head = 0;
    }
    if (newlined) {
        r2 = write(fd, "\n", 1);
    }
}





 void help(){

    //fprintf(output, "logrotate utility is designed to simplify the administration of log files.\n\n");
    printf("Logrotate utility is designed to simplify the administration of log files.\n\n");

    printf("Usage:\n");
    printf("  logrotate [OPTIONS]... \n");
    printf("  ./process-to-log | ./logrotate <pathname> <size-limit-bytes> \n\n\n");    
    


    printf("Compile:\n");
    printf("  gcc -Wall -O2 logrotate.c -o logrotate\n\n\n");



    printf("Simple Example run:\n");
    printf("  ./test1 | ./logrotate file.log 1000\n"); 
    printf("  firt argv file.log file name\n");   
    printf("  second argv 1000 = bytes of size file file.log\n\n\n");    



    printf("Full Example run:\n");
    printf("  step 1 create test1.sh:\n");
    printf("  touch test1\n");     
    printf("  #!/bin/bash\n  for (( ; ; ))  \n  do  \n  echo \"test\"  \n  sleep 10  \n  done  \n\n");

    printf("  step 2 give permision to file test1.sh:\n");    
    printf("  chmod +x test1\n\n");

    printf("  step 3 compile logrotate:\n");    
    printf("  gcc -Wall -O2 logrotate.c -o logrotate\n\n");

    printf("  step 4 exec with argvs logrotate:\n");    
    printf("  ./test1 | ./logrotate file.log 1000\n\n\n");


    printf("For more informations access doc in <https://github.com/pedroAkiraDanno/logrotate2> \n\n\n");

    

 }



//
/*main*/
int
main(int argc, char *argv[])
{


    //to help(void)
    if (strcmp(argv[1], "help" ) == 0 || strcmp(argv[1], "--help" ) == 0 || strcmp(argv[1], "-h" ) == 0 ){
        help();
        exit(EXIT_SUCCESS);                
    }


    //
    // Check Params
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <pathname> <size-limit-bytes>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    //
    name = argv[1];
    MAX_SIZE = atol(argv[2]);
    //
    process();
    //
    exit(EXIT_SUCCESS);
}









/*
STEPS by STEPS on Linux Environment (completed)


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

*/




//END