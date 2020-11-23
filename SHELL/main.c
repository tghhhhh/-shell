#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<pwd.h>
#define NUM 1024

int mystrtok(char *argv[],char *string);//将string字符串以“ ”切割为几部分保存在argv中
char *getUsername(char buffer[NUM]);//获取用户名等信息，返回命令提示符

int main(int argc, char *arga[]){
	pid_t pid;
	int status;//判断切分字符是否成功
	char *argv[NUM];//保存切割的字符串数组
	char buffer[NUM];//保存命令提示符
	char str[NUM];//保存输入命令
	
	//循环打印命令提示符
	while(1){
		printf("~[%s",getUsername(buffer));

		//键入待执行命令
		fgets(str,NUM,stdin);
		//printf("%s",str);
		
		/******去掉最后的换行符******/
		char *d= (char *)malloc((strlen(str)-1)*sizeof(char));
    	memcpy(d,str,(strlen(str)-1));
    	/******去掉最后的换行符******/
    	
		status=mystrtok(argv,d);//把待执行命令分割，存储到argv中		
		//printf("%s \t",argv[0]);

		if(status!=0)
			printf("Fail to getargv!\n");
			
		pid=fork();
		if(pid==-1)
			printf("Your fork filed!\n");
		else if(pid==0){
			/****王浩******/
			if(strcmp(argv[0],"touch")==0)
				execv("./command/wh/touch",argv);
			else if(strcmp(argv[0],"mkdir")==0)
				execv("./command/wh/mkdir",argv);
			else if(strcmp(argv[0],"cat")==0)
				execv("./command/wh/cat",argv);
			else if(strcmp(argv[0],"date")==0)
				execv("./command/wh/date",argv);
			/****侯泽浩****/
			else if(strcmp(argv[0],"cd")==0)
				chdir(argv[1]);
			else if(strcmp(argv[0],"echo")==0)
				execv("./command/hzh/hzh",argv);
			else if(strcmp(argv[0],"ls")==0)
				execv("./command/hzh/hzh",argv);
			/*****李帅博*****/
			else if(strcmp(argv[0],"rm")==0)
				execv("./command/lsb/rm",argv);
			else if(strcmp(argv[0],"mv")==0)
				execv("./command/lsb/mv",argv);
			else if(strcmp(argv[0],"cp")==0)
				execv("./command/lsb/cp",argv);
			/******调试过程使用*******/
			else if(strcmp(argv[0],"ll")==0)
				execlp("ls","ls","-la",NULL);
			else printf("俺没有实现这个命令哇！！太难了！！\n");
		}else{
			if(wait(&status)==-1){
				printf("wait failed!\n");
				exit;
			}
		}
	}
	return 0;
}


///分割字数串，把命令提示符后键入的命令分割开
int mystrtok(char *argv[],char *string){
	int i=0;
	char delim[]=" ";

	argv[0]=strtok(string,delim);//strtok函数首次使用	
	while(argv[i]!=NULL){
		argv[++i]=strtok(NULL,delim);//strtok再次使用把s设成NULL
	}
	return 0;
}

///获取用户名，显示在命令提示符中
char *getUsername(char buffer[NUM]){
	uid_t userid;
	char *username;
	char *hosthome;
	char *ptr,*p;
	char buf1[1024],buf2[1024];
	char *delim=".";
	int id;

	/********命令提示符**********/	
	/**用户名**/
	username=getenv("USER");//获取用户名
	strcpy(buffer,username);//用buffer保存用户名
	strcat(buffer,"@");//在用户名后添加@，例如：test@
	
	/**主机名**/
	id=gethostname(buf1,sizeof buf1);//获取主机名
	p=strtok(buf1,delim);/*对主机名进行截取，截取出主机名即可，例如：
gethostname()获取到localhost.localdomain,截取出localhost即可*/
	strcat(buffer,p);//将主机名添加到用户名@后，例如：test@localhost
	
	/**路径**/
	getcwd(buf2,sizeof(buf2));//获取当前路径
	ptr=strrchr(buf2,'/');//从后向前以/分割路径字符串				
	if(strcmp(ptr,"/")==0){
		ptr="/";//若在根目录，显示/
	}else if(strcmp(ptr,"~")==0){
		ptr="~";//若在家目录。显示～
	}else{
		ptr=strtok(ptr,"/");//其他目录则截取，取最后一个目录名
	}
	strcat(buffer," ");
	strcat(buffer,ptr);
	
	/**sharp或者bang符号**/
	if(strcmp(username,"root")==0)
		strcat(buffer,"]# ");
	else
		strcat(buffer,"]$ ");
	return buffer;
}
