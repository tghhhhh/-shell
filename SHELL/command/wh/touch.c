#include<stdio.h>
#include<getopt.h>
#include<sys/types.h>
#include<time.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/time.h>
#include<sys/stat.h>

//定义创建文件时的模式，此处对用户，组，其他设置的权限都是可读可写。
#define MODE_RW_UGO (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH |S_IWOTH)
// 如果有(-c)选项，并且不存在命令行中输入的文件名，则不创建 
static bool no_create;

//mytouch命令核心的核心模块，用于创建或者更新文件的时间戳。
static bool mytouch(const char *file){
    int fd = -1;
    if (!no_create)    {
        fd = open(file, O_CREAT | O_WRONLY, MODE_RW_UGO);
    }    

    return true;
}

int main(int argc, char **argv){
    int c;
    bool ok = true;
    no_create = false;

    //从命令行中得到命令的选项，即以'-'开头的参数。目前只支持三种选型-a, -c, -m。
    while ((c = getopt(argc, argv, "acm")) != -1)    {
		if(c=='c')
			no_create=true;
		else 
			printf("fault option!");
    }
    
    //如果optind == argc，代表少输入文件名字
    if (optind == argc){
        printf("missing file operand\n");
    }    

    //针对多个文件名字调用mytouch函数
    for (; optind < argc; ++optind){
        ok &= mytouch(argv[optind]);
    }
   	exit(ok ? EXIT_SUCCESS : EXIT_FAILURE);
}
