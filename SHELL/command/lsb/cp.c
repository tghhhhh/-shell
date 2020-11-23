#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

#define BUFFER_SIZE 4096
#define COPY_MODE 0644

/*
    usage1 : cp file1 file2
    usage2 : cp file1 file2 -rf
*/
int main(int argc, char * argv[])
{
    int in_fd, out_fd, n_chars;
    char buf[BUFFER_SIZE];
    bool fgFileExist = false;
    char input;

    if(argc < 3)
    {
        printf("usage : %s source destination\n", argv[0]);
        return -1;
    }

    if(-1 == (in_fd = open(argv[1], O_RDONLY)) )
    {
        printf("Open File error\n");
        return -1;
    }

    if(0 == access(argv[2], F_OK))
        fgFileExist = true;
    else
        fgFileExist = false;

    while((n_chars = read(in_fd, buf, BUFFER_SIZE))>0)
    {
        if(true == fgFileExist)
        {
            printf("File exist, do you want to overwrite ? (y/n) : ");
            while('q'!= (input=getchar()))
            {
                if('\n' == input || '\r' == input)
                    continue;

                if('y' == input)
                {       
                    if(-1 == (out_fd = open(argv[2], O_WRONLY)) )
                    {
                        printf("Create File error\n");
                        return -1;
                    }

                    if(write(out_fd, buf, n_chars) != n_chars)
                    {
                        printf("Write File error\n");
                        return -1;
                    }
                    break;
                }
                else if('n' == input)
                {
                    break;
                }
                else
                {
                    printf("input error\n");
                }
            }
        }       
        else
        {        
            if(-1 == (out_fd = creat(argv[2], COPY_MODE)) )
            {
                printf("Create File error\n");
                return -1;
            }

            if(write(out_fd, buf, n_chars) != n_chars)
            {
                printf("Write File error\n");
                return -1;
            }
        }
    }

    if(n_chars == -1)
    {
        printf("Read error\n");
        return -1;
    }

    close(in_fd);
    close(out_fd);
}

