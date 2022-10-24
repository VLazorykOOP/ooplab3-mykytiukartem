// OOPLab3Tpl.cpp : Цей файл містить є шаблоном для 
// виконання лаб. роботи №3. 
// Він містинь функцію "main" з якої починається та закінчується виконання програми.
//

#include <iostream>

// Ваші файли загловки 
//
#include "Lab3Expaple.h"
int main()
{
    std::cout << " Lab #3  !\n";
//  Код виконання завдань
//  Головне меню завдань
//  Функції та класи можуть знаходитись в інших файлах проекту

    int conv = 1;
    if (conv == 1) conv = mainExample1();
    if (conv == 1) conv = mainExample3(); 
    if (conv == 1) conv = mainExample4();

}

