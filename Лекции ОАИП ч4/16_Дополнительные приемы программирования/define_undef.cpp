//1 Программа работает

/*#include <stdio.h>
#define Big 9
#define Small 2
void main ()
{
	int a;
	a = Big + Small;//ничего
	printf  ("%d\n", a);
}*/


//2  Программа не работет, т.к. Big не определен
/*#include <stdio.h>
#define Big 9
#define Small 1
#undef Big//отмена Big 9
void main ()
{
	int a;
	a = Big + Small;//ничего
	printf  ("%d\n", a);
}*/


//3 Программа работает, берется последнее значение Small (#define Small 5)
/*#include <stdio.h>
#define Big 9
#define Small 1
#define Small 2
#define Small 5
void main ()
{
	int a;
	a = Big + Small;//ничего
	printf  ("%d\n", a);
}*/


//4 Программа не работет, т.к. Small не определен
#include <stdio.h>
#define Big 9
#define Small 1
#define Small 5
#undef Small  //отмена Small 1??????, по моему, отменяется все 
void main ()
{
	int a;
	a = Big + Small;//ничего
	printf  ("%d\n", a);
}


//5 Программа работает,т.к. #define Small 3 определен после #undef Small(отменила все предыдущее)
#include <stdio.h>
#define Big 9
#define Small 1
#define Small 5
#undef Small  //отмена Small 1?????? 
#define Small 3
void main ()
{
	int a;
	a = Big + Small;//ничего
	printf  ("%d\n", a);
}

/*Вывод - в одной программе можно одно и то же имя константы идентифицировать разными значениями.
	 При работе, программа будет принимать самое последнее определение константы (см. задачу 3).
	 Пограмма не будет работать, если мы используем #undef для любой выше определенной константы (см. задачу 2,4).
На лекции говорили, что  #undef отменяет самое последнее определенее.
Но на практике (в написанных выше кодах), получается, 
что #undef отменяет все предыдущие определения для идентификатора, записанного в #undef.
В задаче №5 программа работает,
т.к. #define Small 3 определен после #undef Small(отменила все предыдущее). */
