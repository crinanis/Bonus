//1 ��������� ��������

/*#include <stdio.h>
#define Big 9
#define Small 2
void main ()
{
	int a;
	a = Big + Small;//������
	printf  ("%d\n", a);
}*/


//2  ��������� �� �������, �.�. Big �� ���������
/*#include <stdio.h>
#define Big 9
#define Small 1
#undef Big//������ Big 9
void main ()
{
	int a;
	a = Big + Small;//������
	printf  ("%d\n", a);
}*/


//3 ��������� ��������, ������� ��������� �������� Small (#define Small 5)
/*#include <stdio.h>
#define Big 9
#define Small 1
#define Small 2
#define Small 5
void main ()
{
	int a;
	a = Big + Small;//������
	printf  ("%d\n", a);
}*/


//4 ��������� �� �������, �.�. Small �� ���������
#include <stdio.h>
#define Big 9
#define Small 1
#define Small 5
#undef Small  //������ Small 1??????, �� �����, ���������� ��� 
void main ()
{
	int a;
	a = Big + Small;//������
	printf  ("%d\n", a);
}


//5 ��������� ��������,�.�. #define Small 3 ��������� ����� #undef Small(�������� ��� ����������)
#include <stdio.h>
#define Big 9
#define Small 1
#define Small 5
#undef Small  //������ Small 1?????? 
#define Small 3
void main ()
{
	int a;
	a = Big + Small;//������
	printf  ("%d\n", a);
}

/*����� - � ����� ��������� ����� ���� � �� �� ��� ��������� ���������������� ������� ����������.
	 ��� ������, ��������� ����� ��������� ����� ��������� ����������� ��������� (��. ������ 3).
	 �������� �� ����� ��������, ���� �� ���������� #undef ��� ����� ���� ������������ ��������� (��. ������ 2,4).
�� ������ ��������, ���  #undef �������� ����� ��������� �����������.
�� �� �������� (� ���������� ���� �����), ����������, 
��� #undef �������� ��� ���������� ����������� ��� ��������������, ����������� � #undef.
� ������ �5 ��������� ��������,
�.�. #define Small 3 ��������� ����� #undef Small(�������� ��� ����������). */
