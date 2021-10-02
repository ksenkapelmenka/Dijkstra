#include <cstdio>
#include <fstream>
#include <iostream>
using namespace std;

int main()
{   ifstream in("input1.txt");
    if (in.is_open())
    {
//Вначале посчитаем сколько чисел в файле
        int count = 0;// число чисел в файле
        int t;//Временная переменная
        while (!in.eof())
        {
            in >> t;
            count++;
        }
//Число чисел посчитано, теперь нам нужно понять сколько чисел в одной строке
//Для этого посчитаем число пробелов до знака перевода на новую строку

//Вначале переведем каретку в потоке в начало файла
        in.seekg(0, ios::beg);
        //in.clear();
        int count_space = 0; //Число пробелов в первой строчке вначале равно 0
        char symbol;
        while (!in.eof())
        {
            in.get(symbol);
            if (symbol == ' ') count_space++;
            if (symbol == '\n') break;
        }
//Опять переходим в потоке в начало файла
        in.seekg(0, ios::beg);
        //in.clear();
        int n = count / (count_space + 1);//число строк
        int m = count_space + 1;//число столбцов
        double **a;
        a = new double*[n];
        for (int i = 0; i<n; i++) a[i] = new double[m];
//Считаем матрицу из файла
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                in >> a[i][j];
//Выведем матрицу
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                cout << a[i][j] << "\t";
            cout << "\n";
        }
        int d[n]; // минимальное расстояние
        int v[n]; // посещенные вершины
        int temp;
        int minindex;
        int min;
        int begin_index = 0;
//Инициализация вершин и расстояний
        for (int i = 0; i<n; i++)
        {
            d[i] = 10000;
            v[i] = 1;
        }
        d[begin_index] = 0;
// Шаг алгоритма
        do {
            minindex = 10000;
            min = 10000;
            for (int i = 0; i<n; i++)
            { // Если вершину ещё не обошли и вес меньше min
                if ((v[i] == 1) && (d[i]<min))
                { // Переприсваиваем значения
                    min = d[i];
                    minindex = i;
                }
            }
// Добавляем найденный минимальный вес к текущему весу вершины
// и сравниваем с текущим минимальным весом вершины
            if (minindex != 10000)
            {
                for (int i = 0; i<n; i++)
                {
                    if (a[minindex][i] > 0)
                    {
                        temp = min + a[minindex][i];
                        if (temp < d[i])
                        {
                            d[i] = temp;
                        }
                    }
                }
                v[minindex] = 0;
            }
        } while (minindex < 10000);
// Вывод кратчайших расстояний до вершин
        printf("\nShortest distance to the top: \n");
        for (int i = 0; i<n; i++)
            printf("%5d ", d[i]);
// Восстановление пути
        int ver[n]; // массив посещенных вершин
        int end;
        end = n - 1; // индекс конечной вершины
        ver[0] = n ; // начальный элемент - это конечная вершина
        int k = 1; // индекс предыдущей вершины
        int weight = d[end]; // вес конечной вершины
        while (end != begin_index) // пока не дошли до начальной вершины
        {
            for (int i = 0; i<n; i++) // просматриваем все вершины
                if (a[i][end] != 0) // если связь есть
                {
                    int temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
                    if (temp == d[i]) // если вес совпал с рассчитанным, значит из этой вершины и был переход
                    {
                        weight = temp; // сохраняем новый вес
                        end = i; // сохраняем предыдущую вершину
                        ver[k] = i + 1; // и записываем ее в массив
                        k++;
                    }
                }
        }
// Вывод пути (начальная вершина оказалась в конце массива из k элементов)
        printf("\nShortest path output: \n");
        for (int i = k - 1; i >= 0; i--)
            printf("%3d ", ver[i]);
        for (int i = 0; i<n; i++) delete[] a[i];
        delete[] a;
        in.close();//под конец закроем файла
    }
    else
    {
//Если открытие файла прошло не успешно
        cout << "Файл не найден.";
    }
    return 0;
}