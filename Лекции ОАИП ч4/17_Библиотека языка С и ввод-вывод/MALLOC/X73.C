/* X73.C */ 
#include <stdio.h>
#include <string.h>
#define STOP " " /*  */
#define BLOCK 15
#define LIM 40
#define MAX 3
#define DRAMA 20000
void main(void)
{
char store[BLOCK];
char symph[LIM];
char *end;
char *starts[MAX];
char *malloc();
int index = 0;
int count;
	starts[0] = store;
	end =starts[0] + BLOCK - 1;
	printf("�������� max %d ����.",MAX);
	puts("������� �� ������.");
	while(strcmp(fgets(symph,LIM,stdin),STOP) != 0 && index < MAX)
		{
		if(strlen(symph) > end - starts[index])
			{
			puts("��������� ����� �������������� ������");
			starts[index] = malloc(BLOCK);
			end = starts[index] + BLOCK - 1;
			for(count = 0; count < DRAMA; count++);
				puts("������� ����� �������");
			}
		strcpy(starts[index],symph);
		starts[index + 1] = starts[index] + strlen(symph) + 1;
		if(++index < MAX)
			printf("��� %d -� ���. �����������, ���� ������.\n",index);
		}
		printf("��� %d -� ��� � ���������.\n",index);
		puts("������, ��� ��� � ��������:");
		for(count = 0; count < index; count++)
		puts(starts[count]);
}


