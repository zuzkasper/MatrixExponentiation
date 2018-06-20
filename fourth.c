#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int **createArray(char*buffer, int *val, int *expVal){
	int i=0;
	char*str=(char*)malloc(sizeof(char)*100);
	while (buffer[i]!='\n'){
		str[i]=buffer[i];
		++i;
	}
	++i;
	int n=atoi(str);
	*val=n;
	int temp=0;
	int j=0;
	int k=0;
	int index=0;

	int**arr=(int**)malloc(sizeof(int*)*n);
	for(j=0; j<n;++j){
		arr[j]=malloc(sizeof(int)*n);
		if(arr[j]==NULL){
			printf("ERROR: OUT OF MEMORY");
			return NULL;
		}
	}
	j=0;
	while(j<n){
		if (buffer[i]=='\t'){
			temp=atoi(str);
			while(index>=0){
				str[index]='\0';
				--index;
			}
			arr[j][k]=temp;
			index=0;
			++i;
			++k;
		}else if (buffer[i]=='\n'){
			
			temp=atoi(str);
			while(index>=0){
				str[index]='\0';
				--index;
			}
			*(arr[j]+k)=temp;
			index=0;
			++i;
			k=0;
			++j;
		}
		else{
			str[index]=buffer[i];
			++index;
			++i;
		}
	}
	index=0;
	while(str[index]!='\0'){
		str[index]='\0';
		++index;
	}
	index=0;
	if (buffer[i]=='\n'){
		++i;
	}
	while (buffer[i]!='\n'&&buffer[i]!='\0'){
		str[index]=buffer[i];
		++i;
		++index;
	}

	int exp=atoi(str);
	*expVal=exp;	
	return arr;
}
int multiplyItem(int **array, int **array2, int i, int j, int n){
	int a=0;
	int sum=0;
	
	int c=0;
	
	for (a=0; a<n; ++a){
		c=array[i][a]*array2[a][j];
		sum+=c;
	}
	return sum;
}
int **multiply (int **array,int exp, int n){
	int i,j;
	int**newArray=(int**)malloc(sizeof(int*)*n);
	for(j=0; j<n;++j){
		newArray[j]=(int*)malloc(sizeof(int)*n);
		if(newArray[j]==NULL){
			printf("ERROR: OUT OF MEMORY");
			return NULL;
		}
	}
	if (exp==0){
		for (i=0; i<n; ++i){
			for (j=0; j<n; ++j){
				newArray[i][j]=1;
			}
		}
		return newArray;
	}
	if (exp==1){
		for (i=0; i<n; ++i){
			for (j=0; j<n; ++j){
				newArray[i][j]=(array[i][j]);
			}
		}
		return newArray;
	}

	int **recursiveArray=(int**)malloc(sizeof(int*)*n);
	for(j=0; j<n;++j){
		recursiveArray[j]=(int*)malloc(sizeof(int)*n);
		if(recursiveArray[j]==NULL){
			printf("ERROR: OUT OF MEMORY");
			return NULL;
		}
	}

	recursiveArray=multiply(array,exp-1,n);

	for (i=0; i<n; ++i){
		for (j=0; j<n; ++j){
			newArray[i][j]=multiplyItem(array,recursiveArray, i, j, n);
		}
	}
	return newArray;
}
int main (int argc, char* argv[]){
	int n=0;
	int j=0;
	int exp=1;
 	int fd =open (argv[1], O_RDONLY);
	if (fd==-1){
		return -1;
	}
	int i=0;
	int numBytes=100;
	char*buffer=(char*) malloc(sizeof(char)*numBytes);
	for (i=0; i<99; ++i){
		buffer[i]='\0';
	}
	read(fd, buffer, numBytes);

	int**arr=createArray(buffer, &n, &exp);
	arr=multiply(arr, exp, n);
	for(i=0; i<n; ++i){
		for (j=0; j<n; ++j){
			printf("%d\t",(int)*(arr[i]+j));
		}
		printf("\n");
	}
	free(buffer);
	return 0;
}

	
