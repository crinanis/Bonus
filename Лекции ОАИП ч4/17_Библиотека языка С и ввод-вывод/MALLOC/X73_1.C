/* x73_1.c */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <malloc.h>
//#include <alloc.h>
void main(void)
{
 int i, *d;

/* malloc � realloc ������� ������� � ������������� */
/* ��������� � � ������ */
/* � ���������� �� ����� ������������ ���� �������� ��� �������� */
/* ������� �������� ������� �� ���������� malloc � realloc � ���, */
/* ��� ��� ���������� ��� ������������� ��������� ��� ������ */
/* ��� ������ ��������� */

	//clrscr();
	printf("��������� ������ malloc\n\n");
	d = malloc(10 * sizeof(int));
	if(!d)
		exit(1);
	for( i=0; i<10; i++)
		d[i] = i*i;
	for( i=0; i<5; i++)
		printf("d[%2d]=%4d\td[%2d]=%4d\n",i,d[i],i+5,d[i+5]);
/* ���������� ������ */
free(d);
getch();

printf("\n��������� ������ realloc\n\n");
d = realloc(d, 20 * sizeof(int));
if(!d)
	exit(1);
for( i=10; i<20; i++)
	d[i]=i*i;
for( i=0; i<10; i++)
	printf("d[%2d]=%4d\td[%2d]=%4d\n",i,d[i],i+10,d[i+10]);
/* ���������� ������ */
free(d);
getch();
}

