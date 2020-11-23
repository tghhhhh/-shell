#include<stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<string.h>
int createDir(const char *sPathName){  
      char DirName[256];  
      strcpy(DirName, sPathName);  
      int i,len = strlen(DirName);
	  //printf("len=%d\n",len);	
		
      for(i=1; i<len; i++){
		//printf("%c\n",DirName[i]); 
          if(DirName[i]=='/'){
              DirName[i] = 0; 
              if(access(DirName, NULL)!=0){  
                  if(mkdir(DirName, 0755)==-1){   
                      printf("mkdir   error\n");   
                      return -1;   
                  }  
              }  
              DirName[i] = '/';  
          }  
      }  

      return 0;  
  } 

void main(int argc,char **argv){
	createDir(argv[1]); 
}
