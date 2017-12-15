#include <stdio.h>

struct student
{
	char num[10];
	char name[20];
	float math;
	float physics;
	float chemical;
};	

int main()
{
	struct student stu[10];
	int i, j, min_student;
	float temp, average[10] = {0}, max_score;

	printf("input information as 1554 zhan 89 96 36\n");
	for(i=0;i<10;i++)
		scanf("%s %s %f %f %f"
			, stu[i].num, stu[i].name, 
		&stu[i].math, &stu[i].physics, &stu[i].chemical);
	
	for(i=0;i<10;i++)
	{
		average[i] += stu[i].math+stu[i].physics+stu[i].chemical;
		average[i] /=3;
		max_score = 60;	
		for(j=0;j<i;j++)
			if(average[j] <= max_score)
			{
				max_score = average[j];
				min_student = j;
			}
	}

	for(i=0;i<10;i++)
	{
		for(j=0;j<9-i;j++)
		{
			if(average[j]>average[j+1])
			{
				temp = average[i];
				average[i] = average[i+1];
				average[i] = temp;
			}
		}
	}
	printf("the student average score is following\n");
	for(i=0;i<10;i++)
	{
		printf("%-6.2f", average[i]);
	}
	printf("\n");
	printf("the last low score\n");
	printf("%s %s  %-5.1f%-5.1f%-5.1f%-5.1f\n", stu[min_student].num, 
		stu[min_student].name, stu[min_student].math,
		stu[min_student].physics,stu[min_student].chemical,
		max_score);

	return 0;
}
