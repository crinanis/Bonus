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
	printf("Назовите max %d имен.",MAX);
	puts("Вводите по одному.");
	while(strcmp(fgets(symph,LIM,stdin),STOP) != 0 && index < MAX)
		{
		if(strlen(symph) > end - starts[index])
			{
			puts("Необходим поиск дополнительной памяти");
			starts[index] = malloc(BLOCK);
			end = starts[index] + BLOCK - 1;
			for(count = 0; count < DRAMA; count++);
				puts("Немного места найдено");
			}
		strcpy(starts[index],symph);
		starts[index + 1] = starts[index] + strlen(symph) + 1;
		if(++index < MAX)
			printf("Это %d -е имя. Продолжайте, если хотите.\n",index);
		}
		printf("Это %d -е имя и последнее.\n",index);
		puts("Хорошо, вот что я получила:");
		for(count = 0; count < index; count++)
		puts(starts[count]);
}


