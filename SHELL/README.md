# SHELL

## 1、介绍

​	本项目是操作系统课后作业，项目小组由三人组成。本项目实现简单shell的一些简单命令，具体实现了包括date、cat、touch、mkdir、cp、rm、mv、echo、cd、ls等命令。main是程序主入口，运行main可执行文件后会打印出命令提示符，提示用户输入命令，用户可以输入如前所述的命令，并看到相应运行结果。



## 2、目录结构

​	SHELL目录下有一个子目录command，一个c文件main.c及其可执行文件main，一个README.md文件。其中command目录下保存了本项目shell中实现的一些命令的源码，command目录下又包含三个子目录，分别是本项目成员的源代码，具体可见文档中。



## 3、提示

​	main文件为程序主入口。

​	mkdir命令创建目录时必须显式指明所创建是目录，例：mkdir dir1/;	mkdir /home/balaa/dir2

​	rm命令必须使用选项-rf，无论待删除文件是一般文件还是目录，例：rm -rf dir1/;	rm -rf file1

​	mv命令修改目录名时仍然要指明待更改目录，例：mv dir1/ dir2/ 