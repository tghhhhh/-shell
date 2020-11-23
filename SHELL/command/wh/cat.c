#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include<math.h>
# define BUFFER_LEN 4096
/***打印文件内容，一行行打印****/
void showText(char *filename,int sw){//sw是用来确定选项
	char szTest[BUFFER_LEN]="";
	int i=0;//选项-n时使用
 
	FILE *fp = fopen(filename, "r");
	//printf("%s",filename);
	if(NULL == fp){
		printf("failed to open dos.txt\n");
		return;
	}
 	
	while(!feof(fp)){
		fgets(szTest, sizeof(szTest) - 1, fp);//包含了换行符
		if(sw==0)//表示无选项
       		printf("%s", szTest);
       	if(sw==1){//表示有选项-n
            printf("%d  %s", i, szTest); //输出
            i++;
      	 }
      	if(sw==2){//表示由选项-b
       		if(strcmp(szTest,"\n")!=0){
       			printf("%d  %s", i, szTest);
       			i++;
       		}else printf("%s", szTest);
      	}
	} 
	fclose(fp);
}

int main(int argc, char *argv[]){
	//表示没有cat命令没有参数的情况，直接从标准输入读入数据并在标准输出输出
	if (argc == 1){
		while(1){
			char a[256];
			fgets(a,256,stdin);
			printf("%s",a);
		}
	//有参数时
	}else{
		int sw=0;
		char *ch[]={"n","b","s","E","T"};
		
		//遍历cat命令后选项增加sw的值确定有那些选项
		int k=1,i;
		while(k<argc){
			if(strpbrk(argv[k],"-")!=0){
				i=0;
				while(i<5){
					if(strpbrk(argv[k],ch[i])!=0)
						sw+=(int)pow(2,i);//nbsET分别代表1 2 4 8 16，每有一个函数sw加上相应的值
					i++;
				}
			}
			k++;
		}
		
		//从cat命令后遍历有多少个文件需要读取
		int j=1;
		while(j<argc){
			if(strpbrk(argv[j],"-")==0){
				showText(argv[j],sw);
			}
			j++;
		}
			
	}
	return 0;
 }
