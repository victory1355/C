#include <stdio.h>

struct student
{
	int num;
	char name[20];
	float score;
};

int main()
{
	struct student stu;
	struct student *p;
	char *p_ch, p1 = 0x18048000;
	
	printf("the NULL is %p\n", p1);
	p_ch = stu.name;
	printf("the size of stu is %d\n", sizeof stu);
	printf("stu.name address is %p\n", p_ch);
	p = &stu;
	printf("stu address is %p\n", p);
	p += 1;
	printf("stu address +1 is %p\n", p);

	return 0;
}
