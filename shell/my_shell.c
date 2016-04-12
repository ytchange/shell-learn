#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
	while(1)
	{
		printf("my_shell@centos#:");
		fflush(stdout);
		char buf[1024];
		memset(buf,'\0',sizeof(buf));
		ssize_t size=read(0,buf,sizeof(buf));
		buf[size-1]='\0';
		int _end=strlen(buf)-1;
		char *str[64];
		int index=0;
		while(_end>=0)
		{
			if(isspace(buf[_end-1]))
			{
				str[index]=&buf[_end];
				index++;
			}
			if(isspace(buf[_end]))
			{
				buf[_end]='\0';
			}
			_end--;
		}
		str[index++]=buf;//把第一个字符串放入str中
		str[index]=NULL;
	//以上将字符串逆序存放在str内
		int start=0;
		int end=index-1;
		void swap(char **p1,char **p2)
		{
			char *tmp=*p1;
			*p1=*p2;
			*p2=tmp;
		}
		while(start<end)
		{
			swap(&str[start++],&str[end--]);
		}
	//将字符串正序
		//for(index=0;str[index]!=NULL;index++)
		//{
		//	printf("%s\n",str[index]);
		//}
		if(strcmp(str[0],"cd")==0)
		{
			chdir(str[1]);
			continue;
		}
		pid_t id=fork();
		if(id<0)
		{
			perror("fork");
			return 1;
		}
		else if(id==0)
		{
			execvp(str[0],str);
		}
		else
		{
			pid_t ret=waitpid(id,NULL,0);
		}
	}
	return 0;
}

