/* x73_1.c */
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> 
#include <malloc.h>
//#include <alloc.h>
void main(void)
{
 int i, *d;

/* malloc и realloc создают область и устанавливают */
/* указатель в еЄ начало */
/* в дальнейшем мы можем пользоватьс€ этой областью как массивом */
/* отличие обычного массива от созданного malloc и realloc в том, */
/* что дл€ последнего нет необходимости указывать его размер */
/* при записи программы */

	//clrscr();
	printf("–ј—Ў»–я≈“ ѕјћя“№ malloc\n\n");
	d = malloc(10 * sizeof(int));
	if(!d)
		exit(1);
	for( i=0; i<10; i++)
		d[i] = i*i;
	for( i=0; i<5; i++)
		printf("d[%2d]=%4d\td[%2d]=%4d\n",i,d[i],i+5,d[i+5]);
/* освободить пам€ть */
free(d);
getch();

printf("\n–ј—Ў»–я≈“ ѕјћя“№ realloc\n\n");
d = realloc(d, 20 * sizeof(int));
if(!d)
	exit(1);
for( i=10; i<20; i++)
	d[i]=i*i;
for( i=0; i<10; i++)
	printf("d[%2d]=%4d\td[%2d]=%4d\n",i,d[i],i+10,d[i+10]);
/* освободить пам€ть */
free(d);
getch();
}

