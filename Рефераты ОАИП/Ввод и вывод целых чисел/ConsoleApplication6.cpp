#include <stdio.h> 
#include <iostream>
using namespace std;

void main()
{
    setlocale(LC_ALL, "Ru");
    FILE* fp;
    fopen_s(&fp, "file.txt", "w");

    if (fp == NULL)
    {
        printf("Файл не может быть открыт.");
        exit(1);
    } else cout << "Файл открыт. Введите числа. Прекращение ввода - 999.\n";

    int n=0;

    do
    {
        cin >> n;
        if (n == 999) break; //для того, чтобы 999 не было записано в файл
        _putw(n, fp); 
    
    } while (n != 999);
    cout << "Числа успешно записаны в файл.";

    fclose(fp);   
}
/*Программа, демонстрирующая работу функции putw()*/

//#include <stdio.h> 
//#include <iostream>
//using namespace std;
//
//void main()
//{
//    setlocale(LC_ALL, "Ru");
//    FILE* fp;
//    fopen_s(&fp, "file.txt", "r");
//
//    cout << "Вывод чисел, записанных в файл:\n";
//
//    int k;
//    while (1)
//    {
//        k = _getw(fp);
//
//        if (k == EOF)
//        {
//            if (feof(fp) != 0)
//            {
//                cout << "\nЧтение файла закончено.";
//                break;
//            }
//            else
//            {
//                cout << "\nОшибка чтения из файла.";
//                break;
//            }
//        }
//        cout << k << " ";
//    }
//    fclose(fp);
//}