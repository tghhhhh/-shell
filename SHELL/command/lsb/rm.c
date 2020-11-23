#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

void del_stat(const char* name)
{
	DIR* fl = opendir(name);   //DIR结构体，是一个内部结构
	chdir(name);   //改变当前的工作目录
	
	/*for(struct dirent* dir = readdir(fl); NULL!=dir;)   //dirent结构体，包含了其他文件的名字及指向与这些文件有关的信息的指针
	{                                                     //readdir返回参数dir目录流的下个目录进入点
		if(dir->d_type == DT_DIR)
		{
			if(strcmp(dir->d_name,"..")&&strcmp(dir->d_name,"."))
				del_stat(dir->d_name);
		}
		remove(dir->d_name);
		dir = readdir(fl);
	}
	chdir("..");
	remove(name);*/
	struct dirent* dir = readdir(fl);
	while( NULL!=dir)   //dirent结构体，包含了其他文件的名字及指向与这些文件有关的信息的指针
	{                                                     //readdir返回参数dir目录流的下个目录进入点
		if(dir->d_type == DT_DIR)
		{
			if(strcmp(dir->d_name,"..")&&strcmp(dir->d_name,"."))
				del_stat(dir->d_name);
		}
		remove(dir->d_name);
		dir = readdir(fl);
	}
	chdir("..");
	remove(name);
}

int main(int argc,char *argv[])
{
	if(3 != argc)
	{
		printf("User:./rm -rf xxx\n");
		return -1;
	}
	
	struct stat sta;    
	if(0 > stat(argv[2],&sta))    //stat()获取文件状态
	{
		perror("open");
		return -1;
	}

	if(!S_ISDIR(sta.st_mode))
	{
		remove(argv[2]);
		return 0;
	}
	
	del_stat(argv[2]);
}

