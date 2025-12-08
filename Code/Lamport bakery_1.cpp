#include <windows.h>
#include <stdio.h>
int x = 0, y = 1;
void T1()
{
	while(1)
		{
			x = y + 1;
			printf("%4d",x);
		}
}
void T2()
{
	while(1)
		{
			y = 2;
			y = y * 2;
		}
}
void T3()
{
	while(1)
		{
			y = 5;
			y = y + 10;
		}
}
// 2 3 5 11 13 15 
int main()
{
	HANDLE h1, h2, h3, h4;
	DWORD Id;
	h1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)T1,NULL,0,&Id);
	h2=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)T2,NULL,0,&Id);
	h3=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)T3,NULL,0,&Id);
	WaitForSingleObject(h1,INFINITE);
	WaitForSingleObject(h2,INFINITE);
	WaitForSingleObject(h3,INFINITE);
	return 0;
}