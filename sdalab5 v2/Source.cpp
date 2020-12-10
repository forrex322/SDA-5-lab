#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <fstream>
#define hashtab_size 113

using namespace std;

struct Array {
    int key;
    int array[hashtab_size];
    int record[20];
};


void search(int ary[], int hFn, int size) {
    int element, pos, n = 0;

    printf("Введiть ключ який потрiбно знайти:\n");
    scanf_s("%d", &element);

    pos = element % hFn;

    while (n++ != size) {
        if (ary[pos] == element) {
            printf("Eлемент знайдено на індексі %d\n", pos);
            break;
        }
        else
            if (ary[pos] == INT_MAX || ary[pos] != INT_MIN)
                pos = (pos + 1) % hFn;
    }
    if (--n == size) printf("Елемент не знайдено у хеш-таблиці\n");
}


int main()
{
    Array a;
    ofstream f1("File.txt");
    int m, double_hashing, pos, l = 0;
    setlocale(LC_ALL, "ukr");
    printf("Введiть к-ть даних:");
    cin >> m;

    for (int i = 0; i < m; i++) {
        printf("Введiть ключ:\n");
        cin >> a.record[i];
        a.array[i] = a.record[i] % hashtab_size;
        l++;
    }
    f1 << "Кількість входженнь у файл: " << l << endl;
    cout << "Кількість входженнь у файл: " << l << endl;
    double_hashing = abs(a.array[0] - a.array[1]);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {

            if (a.array[i] == a.array[j] && i != j) {
                a.array[j] += double_hashing;
                break;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        printf("#%.2i  %i\n", a.array[i],a.record[i]);
        //cout << "#" << a.array[i] << " " << a.record[i] << endl;
        f1 << "#" << a.array[i] << " " << a.record[i] << endl;
    }


    //printf("Введiть ключ який потрiбно знайти:");
    //cin >> a.key;

    search(a.record,double_hashing,m);

    //for (int i = 0; i < m; i++) {
    //    if (a.key == a.record[i]) {
    //       printf("#%.2i  %i\n", a.array[i], a.record[i]);
    //        //cout << "#" << a.array[i] << " " << a.record[i] << endl;
    //    }
    //}

    

    printf("Введiть позицiю яку потрiбно видалити:");
    cin >> pos;

    for (int i = 0; i < hashtab_size; i++) {
        if (pos == a.array[i]) {
            a.record[i] = NULL;
            printf("\nПозиція %i видаленна\n", a.array[i]);
            //cout << "Pos " << i << " deleted " << a.array[i] << endl;
            printf("#%.2i  %i\n", a.array[i],a.record[i]);
            //cout << "#" << a.array[i] << " " << a.record[i] << endl;
            break;
        }
        if (i >= m) {
            printf("Позицію не знайденно.");
            break;
        }
    }


    f1.close();

    return 0;
}