#include"log.h"
FILE* fd;
// ------------
// creat LogFile
// ------------
void creatLog()
{
    fd = fopen("log.txt" , "w");
}
// ------------
// write to log
// ------------
void writeToLog(char* msg)
{
    //fwrite(msg, sizeof(char), strlen(msg), fd);
    int i;
    for(i=0;i<strlen(msg);i++)
        if(msg[i]=='\n')
            fputs("\\n", fd);
        else
            fputc(msg[i], fd);
    fputs("\n", fd);
}
// ------------
// close LogFile
// ------------
void closeLog()
{
    fclose(fd);
}