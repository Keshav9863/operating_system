#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
struct rage
{
	int startI;
	int endI;
}obj;
int data[100];
int final[100];
void *sort1(void *obj1)
{
	int endI,i,j,temp;
	struct rage *arg=obj1;
	endI = arg->endI;
	for(i=0;i<=endI;i++)
	{
		for(j=0;j<=endI-i-1;j++)
		{
			if(data[j]>data[j+1])
			{
				temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
			}
		}
	}
	printf("1st Half sorted Array by Thread sort1:\n");
	for(i=0;i<=endI;i++)
	{
		printf("%d  ",data[i]);
	}
}
void *sort2(void *obj1)
{
	int temp,i,j,startI,endI,min;
	struct rage *arg = obj1;
	startI = arg->startI;
	endI = arg->endI;
	for(i=startI;i<=endI;i++)
	{
		min = i;
		for(j=i;j<=endI;j++)
		{
			if(data[min]>data[j])
			{
				min = j;
			}
		}
		temp = data[min];
		data[min] = data[i];
		data[i] = temp;
	}
	printf("\n2nd Half Sorted Array by Thread sort2:\n");
	for(i=startI;i<=endI;i++)
	{
		printf("%d  ",data[i]);
	}
}
void *merge(void *obj1)
{
	int i,start1,end1,start2,end2,index=0; //start1,end1 are the indexes of 1st sub array start2,end2 indexes of array2
	struct rage *arg = obj1;
	start1=0;
	end1=arg->startI;
	start2=arg->startI+1;
	end2=arg->endI;
	while(start1<=end1 && start2<=end2)
	{
		if(data[start1] > data[start2])
		{
			final[index] = data[start2];
			start2 = start2+1;
		}
		else
		{
			final[index] = data[start1];
			start1 = start1+1;
		}
		index = index+1;
	}
	while(start1<=end1)
	{
		final[index] = data[start1];
		index = index+1;
		start1 = start1+1;
	}
	while(start2<=end2)
	{
		final[index] = data[start2];
		index = index+1;
		start2 = start2+1;
	}
	printf("\nFinal Sorted Array Merged By MergeThread is :\n");
	for(i=0;i<index;i++)
	{
		printf("%d ",final[i]);
	}
	printf("\n");
}
int main()
{
	int i,range,mid;
	pthread_t p1,p2,p3;
	printf("Enter Range of Elements :");
	scanf("%d",&range);
	printf("Enter Values \n:");
	for(i=0;i<range;i++)
	{
		scanf("%d",&data[i]);
	}
	mid=(range)/2;
	obj.startI=0;
	obj.endI=mid-1;                      //As index is starting from 0
	pthread_create(&p1,NULL,sort1,&obj);
	pthread_join(p1,NULL);
	obj.startI=mid;
	obj.endI=range-1;
	pthread_create(&p2,NULL,sort2,&obj);
	pthread_join(p2,NULL);
	obj.startI=mid-1;
	obj.endI=range-1;
	pthread_create(&p3,NULL,merge,&obj);
	pthread_join(p3,NULL);
}
