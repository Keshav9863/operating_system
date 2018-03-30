#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
struct data
{
	int range;
	int data[100];
}obj;
int average;
int maximum;
int minimum;
void *Average_t1(void *obj1)
{
	struct data *arg=obj1;
	int range,sum=0,i;
	range = arg->range;
	for(i=0;i<range;i++)
	{
		sum = sum + arg->data[i];
	}
	average = sum/range;
}
void *Minimum_t2(void *obj1)
{
	struct data *arg=obj1;
	int range,min,i;
	range=arg->range;
	min=0;
	for(i=0;i<range;i++)
	{
		if(arg->data[min]> arg->data[i])
		{
			min = i;
		}
	}
	minimum = arg->data[min];
}
void *Maximum_t3(void *obj1)
{
	struct data *arg=obj1;
	int range,max,i;
	range=arg->range;
	max=0;
	for(i=0;i<range;i++)
	{
		if(arg->data[max] < arg->data[i])
		{
			max = i;
		}
	}
	maximum = arg->data[max];
}
int main()
{
	int i;
	printf("Enter range of integer values :");
	scanf("%d",&obj.range);
	printf("Enter Values:\n");
	for(i=0;i<obj.range;i++)
	{
		scanf("%d",&obj.data[i]);
	}
	pthread_t p1,p2,p3;
	pthread_create(&p1,NULL,Average_t1,&obj);
	pthread_join(p1,NULL);
	pthread_create(&p2,NULL,Minimum_t2,&obj);
	pthread_join(p2,NULL);
	pthread_create(&p3,NULL,Maximum_t3,&obj);
	pthread_join(p3,NULL);
	printf("The average value is  %d\n",average);
	printf("The minimum value is  %d\n",minimum);
	printf("The maximum value is  %d\n",maximum);
}
