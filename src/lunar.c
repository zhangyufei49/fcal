#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fdatefunc.h"

void show_help(const char* name) 
{
	printf("\nUsage:\n\t");
	printf("%s year month day\n\t", name);
	printf("defalut show now date.\n");
	exit(0);
}

int main(int argc,const char* argv[])
{

	SunDate sunDate;
	if (argc < 2) {
		time_t now_time;
		time(&now_time);
		struct tm* now = localtime(&now_time);
		if (now) {
			sunDate.year=(U16)(now->tm_year + 1900);
			sunDate.month=(U8)(now->tm_mon + 1);
			sunDate.day=(U8)now->tm_mday;
		}
	} else if (4 == argc) {
		sunDate.year=(U16)atoi(argv[1]);
		sunDate.month=(U8)atoi(argv[2]);
		sunDate.day=(U8)atoi(argv[3]);
	} else if (!strcmp("--help", argv[1])) {
		show_help(argv[0]);
	} else {
		show_help(argv[0]);
	}

	int tmp;
	LunarDate* pLD=(LunarDate*)malloc(sizeof(LunarDate));
	BL* bl;
	printf("%d-%d-%d\t",sunDate.year,sunDate.month,sunDate.day);
	printf("%s%s年[%s] ",yearToNature(sunDate),yearToEarth(sunDate),yearToAnimal(sunDate));

	tmp=lunarLeapMonth(sunDate.year);
	bl=getLunarBLArray(sunDate.year);

	int ret;
	ret=sunToLunar(pLD,&sunDate,bl,tmp);
	if(ret<0){
		printf("转化失败\n");
		goto do_failed;
	}
	if(tmp){
		if(pLD->month<tmp){
			printf("%s月",monthNameInYear(pLD->month+1));
		}else if(pLD->month>tmp){
			printf("%s月",monthNameInYear(pLD->month));
		}else
			printf("[润]%s月",monthNameInYear(tmp));
	}
	else{
		printf("%s月",monthNameInYear(pLD->month));
	}
	printf("%s\n",dayNameInMonth(pLD->day));

do_failed:
	free(pLD);
	pLD=NULL;
	return 0;
}
