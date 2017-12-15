#include <stdio.h>

struct animal
{
	char color[10];
	struct 
	{
		int hight;
		int eight;
	}body;
	union
	{
		char class[10];
		int sex;
	}attribute;
}car = {
	.color = "red",
	.body = {.hight = 150},
	.attribute = {.sex = 120},	
};
	
int main()
{

//	strcpy(car.attribute.class,"maoke");

	printf("the color is %s\n", car.color);
	printf("the hight is %d\n", car.body.hight);
	printf("the eight is %d\n", car.body.eight);
	printf("the attribute is %d\n", car.attribute.sex);
	
	return 0;
}
