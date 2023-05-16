#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <sstream>
#include <ctime>
#include <experimental/filesystem>
#include <algorithm>

#pragma warning(disable : 4996) //исправление ошибки С4996 связанной с устаревшими библиотеками

using namespace std;
namespace fs = experimental::filesystem; //упрощение для работы с файловой библиотекой
string fil; //переменная для файла

struct datat  // структура для даты
{
    int d;    //день
    int m;    // месяц
    int y;    //год
};
struct Infoyuv // структура для информации
{
    int num;	// номер договора
    string Klient;	// ПИБ клиента
    string Master;	// ПИБ мастера
    datat dat;	//дата изготовления
    string izdelie;	// название изделия
    float sum;	// цена изделия
};


bool shit(); //проверка на числа
void Dannie(Infoyuv m[], int* n); //получение данных
void Vivod(Infoyuv m[], int* n); //вывод данных
void Sort1(Infoyuv m[], int* n); //сортировка данных
void Dobavlenie(Infoyuv m[], int* n);		//добавление данных
int In_int();//проверка на целые числа						
string In_str();//проверка на строки				
float In_float();//проверка на числа с дробью			
int data_d(int mecl, int g);//функция для добавления даты
int data_m();//функция для добавления месяца
int data_y();//функция для добавления года
void PKlient(Infoyuv m[], int* n); //Поиск по имени клиента
void PMaster(Infoyuv m[], int* n); //Поиск по имени мастера и дате
void Sort2(Infoyuv m[], int* n); //сортировка цены по убыванию
void Sort3(Infoyuv m[], int* n); //сортировка цены по возрастанию
void Sort_max(Infoyuv m[], int* n); //максинальные цены
void Sort_min(Infoyuv m[], int* n);//минимальные цены
vector<string> RobotaFile(const fs::path& dir, const vector<string>& ext); //парсинг по заданной директории

int main()
{
    setlocale(LC_CTYPE, "rus");
    SetConsoleCP(1251); //установка кодировки в консоли
    SetConsoleOutputCP(1251); //установка кодировки в консоли
    Infoyuv m[100];		//Массив с данными
    int n(0);		// количество элементов в массиве
    int p; // меню
    while (true) // меню -начало
    {
        system("cls");
        cout << endl << "  --------------------Главное меню программы--------------------";
        cout << endl << "  1: Загрузка данных";
        cout << endl << "  2: Просмотр данных";
        cout << endl << "  3: Добавление новых данных";
        cout << endl << "  4: Заказы конкретного клиента;";
        cout << endl << "  5: Заказы конкретного мастера за указанный период времени";
        cout << endl << "  6: Заказы с максимальной та минимальной ценой";
        cout << endl << "  7: Выход из программы ";
        cout << endl << endl << "  Выберите пункт меню---->"; p = In_int(); p;
        switch (p)
        {
        case 1: { Dannie(m, &n);  system("pause"); break; }

        case 2: {system("cls"); Sort1(m, &n); Vivod(m, &n); system("pause"); break; }

        case 3: {system("cls"); Dobavlenie(m, &n); system("pause"); break; }

        case 4: {system("cls");  PKlient(m, &n); system("pause"); break; }

        case 5: {system("cls");  PMaster(m, &n); system("pause"); break; }

        case 6: {system("cls"); Sort2(m, &n); Sort_max(m, &n); Sort3(m, &n); Sort_min(m, &n); system("pause"); break; }

        case 7: {system("cls"); cout << endl << "   Программа завершает роботу   "; system("pause"); return 0; }
        default: {system("cls"); cout << endl << "   Неправильно выбран пункт меню   "; system("pause"); }
        }
    }
}// меню -конец


void Dannie(Infoyuv m[], int* n)
{
    system("cls");


    int k(0); //счетчик для вывода
    string s; //переменная для ввода информации с файла
    int vb = 2;
    auto print_files = [](const auto& aVector) { //функция для вывода спарсинного результата RobotaFile
        for (auto& f : aVector) {
            cout << f << endl;
        }
    };
    if (char(cin.peek()) == '\n')     cin.ignore();
    cout << endl;
    cout << "Использовать текущую директорию,введите 1" << endl;
    cout << "Ввести свою директорию,введите 2" << endl;
    cout << "Cоздать или перезаписать файл введите 3" << endl;
    cout << "Введите действие--->";
    vb = In_int();
    while (true == true) {
        if (vb == 1) {
            auto dr = fs::current_path(); //текущая директория
            auto files = RobotaFile(dr, { ".txt" }); //парсинг папки
            system("cls");
            cout << "-----Список файлов-----" << endl;
            print_files(files); //результат прасинга
            cout << endl;
            cout << "Введите название и расширение нужного файла--- ";
            if (char(cin.peek()) == '\n')     cin.ignore();
            getline(cin, fil); //имя нужного файла
            break;
        }
        else if (vb == 2) {
            if (char(cin.peek()) == '\n')     cin.ignore();
            cout << "Введите название диска,например <C:\\\\>: ";
            string root1;
            getline(cin, root1);
            fs::path root{ root1 };
            cout << "Введите путь к каталогу,например <deb\\\\deb1\\\\deb\\\\>: ";
            string dir1;
            getline(cin, dir1);
            fs::path dir{ dir1 };
            fs::path pathToDB = root / dir; //создание пути
            auto zb = pathToDB;
            auto files = RobotaFile(zb, { ".txt" }); //парсинг пути
            system("cls");
            cout << "-----Список файлов-----" << endl;
            print_files(files); //результат парсинга
            cout << endl;
            cout << "Введите название нужного файла--- ";
            if (char(cin.peek()) == '\n')     cin.ignore();
            string fil1;
            getline(cin, fil1);
            fil = root1 + dir1 + fil1; //создание конечного пути к заданному файлу
            break;
        }
        else if (vb == 3) {
            if (char(cin.peek()) == '\n')     cin.ignore();
            cout << "ЕСЛИ ВВЕСТИ ИМЯ И ДИРЕКТОРИЮ СУЩЕСТВУЮЩЕГО ФАЙЛА ТО ФАЙЛ ПЕРЕЗАПИШЕТСЯ!!!!! " << endl;
            cout << "Введите название диска,например <C:\\\\>: ";
            string root1;
            getline(cin, root1);
            cout << "Введите путь к каталогу,например <deb\\\\deb1\\\\deb\\\\>: ";
            string dir1;
            getline(cin, dir1);
            cout << "Введите название нового файла--- ";
            if (char(cin.peek()) == '\n')     cin.ignore();
            string fil1;
            getline(cin, fil1);
            fil = root1 + dir1 + fil1; //создание конечного пути к заданному файлу
            ofstream f(fil, ios::out);
            system("cls");




            char c('y'); //Перемення для продолжения записи
            int k2 = *n; //счетчики
            int g, mecl, d;
            cout << endl << "   Добавление новых данных   " << endl << endl;
            

                int z = 0;
 
                        cout << endl << "Введите номер договора  ";
                        int i = In_int();
                        while (z == 0) //проверка на уникальность номера
                        {
                                    if (i < 0) {
                                        cout << endl << "Номер договора должен быть положительным.  Повторите ввод  "; i = In_int();
                                    }
                                    else if (i > 0) {
                                        z++;
                                    }
                        }
                        m[k2].num = i; f << m[k2].num << '\n';
                   

                    if (char(cin.peek()) == '\n')     cin.ignore();
                    cout << endl << "Введите фамилию и инициалы клиента: ";  m[k2].Klient = In_str(); f << m[k2].Klient << '\n';
                    //if (char(cin.peek()) == '\n')     cin.ignore();
                    cout << endl << "Введите фамилию и инициалы мастера: "; m[k2].Master = In_str(); f << m[k2].Master << '\n';
                    //if (char(cin.peek()) == '\n')     cin.ignore();
                    cout << endl << "---Введите дату продажи---" << endl;

                    g = data_y(); //инициализация года
                    m[k2].dat.y = g; //добавление года в массив
                    mecl = data_m();
                    m[k2].dat.m = mecl;
                    mecl;
                    d = data_d(mecl, g);
                    d;
                    m[k2].dat.d = d;
                    f << m[k2].dat.d << '\n';
                    f << m[k2].dat.m << '\n';
                    f << m[k2].dat.y << '\n';
                    if (char(cin.peek()) == '\n')     cin.ignore();
                    cout << endl << "Введите название изделия: "; m[k2].izdelie = In_str(); f << m[k2].izdelie << '\n';
                    cout << endl << "Введите цену изделия: ";

                    float x; x = In_float();
                    m[k2].sum = x; f << m[k2].sum;


                    k2++;
                    if (char(cin.peek()) == '\n')     cin.ignore();
                    system("cls");

                *n = k2;
                f.close();
                break;

            }


            else {
                cout << "Вводить нужно 1,2 или три!!!" << endl;
            }
        }
        fstream f;
        f.open(fil, ios::in);
        cout << endl << "  загрузка данных   " << endl << endl;
        if (!f.is_open())
        {
            cout << endl << "   Ошибка считывания файла   "; return;
        }
        else
        {
            const char* c_inp;
            while (!f.eof())
            {
                getline(f, s);  c_inp = s.c_str();  m[k].num = atoi(c_inp);
                getline(f, s); 	m[k].Klient = s;
                getline(f, s); 	m[k].Master = s;
                getline(f, s);  c_inp = s.c_str();  m[k].dat.d = atoi(c_inp);
                getline(f, s);  c_inp = s.c_str();  m[k].dat.m = atoi(c_inp);
                getline(f, s);  c_inp = s.c_str();  m[k].dat.y = atoi(c_inp);
                getline(f, s); 	m[k].izdelie = s;
                getline(f, s);  const char* c_inp = s.c_str();  m[k].sum = atof(c_inp);
                k++;


            }
            cout << endl << "   файл считан успешно   " << endl << endl;
            f.close();
            *n = k;
            return;
        }
    }

void Vivod(Infoyuv m[], int* n) //Функция вывода информации
{
    cout << endl << "       Данные о заказах   " << endl << endl;
    if (*n == 0) //Проверка на пустоту
        cout << endl << endl << "Массив данных пуст" << endl << endl;
    else // оформление меню
    {
        cout.setf(ios::left); cout.width(4); cout << "№";
        cout.setf(ios::left); cout.width(20); cout << "КЛИЕНТ";
        cout.setf(ios::left); cout.width(20); cout << "МАСТЕР";
        cout.setf(ios::left); cout.width(12); cout << "ДАТА";
        cout.setf(ios::left); cout.width(20); cout << "ОБЪЕКТ";
        cout.setf(ios::left); cout.width(10); cout << "СУММА" << endl;
        cout << endl;

        for (int i = 0; i < *n; i++) //вывод информации
        {
            cout.setf(ios::left); cout.width(4); cout << m[i].num;
            cout.setf(ios::left); cout.width(20); cout << m[i].Klient;
            cout.setf(ios::left); cout.width(20); cout << m[i].Master;
            cout.width(2); cout << m[i].dat.d << ".";
            cout.width(2); cout << m[i].dat.m << ".";
            cout << m[i].dat.y << "   ";
            cout.setf(ios::left); cout.width(20); cout << m[i].izdelie;
            cout.setf(ios::left); cout.width(10); cout << m[i].sum << " гривен" << endl;

        }
    }
}
void Sort1(Infoyuv m[], int* n) //сортировка пузырьком
{
    int i, j; //переменныые для циклов
    Infoyuv t; //буферный счетчик для перемещения элементов по списку
    for (i = 0; i < *n - 1; i++)// сортировка по номеру заказа
        for (j = 0; j <= *n - 2; j++) {
            if (m[j].num > m[j + 1].num)
            {
                t = m[j]; m[j] = m[j + 1]; m[j + 1] = t;

            }
        }
    return;
}
void Dobavlenie(Infoyuv m[], int* n)
{

    fstream f(fil, ios::app); //Открытие файла в режиме записи (fil-файл который мы загружали)
    char c('y'); //Перемення для продолжения записи
    int k; k = *n; //счетчики
    int g, mecl, d;
    cout << endl << "   Добавление новых данных   " << endl << endl;
    if (!f.is_open()) //проверка на целосность
    {
        cout << endl << "   Ошибка открытия файла   "; return;
    }
    else
    {
       
        int z = 0;
        while (c == 'y') //ввод и добавления данных в файл
        {
                if (char(cin.peek()) == '\n')     cin.ignore();
                cout << endl << "Введите номер договора  ";
                int i = In_int();
                while (z == 0) //проверка на уникальность номера
                {
                    for (int ii = 0; ii < *n; ii++) {
                        if (i == m[ii].num) {
                            cout << endl << "Номер договора должен быть уникальным.  Повторите ввод  "; i = In_int();
                        }
                        else {
                            while(i < 0) {
                                cout << endl << "Номер договора должен быть положительным.  Повторите ввод  "; i = In_int();
                            }
                            if (i > 0) {
                                z++;
                            }
                        }
                    }

                }
                m[k].num = i; f << '\n' << m[k].num << '\n';
            

            
            if (char(cin.peek()) == '\n')     cin.ignore();
            cout << endl << "Введите фамилию и инициалы клиента: ";  m[k].Klient = In_str(); f << m[k].Klient << '\n';
            //if (char(cin.peek()) == '\n')     cin.ignore();
            cout << endl << "Введите фамилию и инициалы мастера: "; m[k].Master = In_str(); f << m[k].Master << '\n';
            //if (char(cin.peek()) == '\n')     cin.ignore();
            cout << endl << "---Введите дату продажи---" << endl;

            g = data_y(); //инициализация года
            m[k].dat.y = g; //добавление года в массив
            mecl = data_m();
            m[k].dat.m = mecl;
            mecl;
            d = data_d(mecl, g);
            d;
            m[k].dat.d = d;
            f << m[k].dat.d << '\n';
            f << m[k].dat.m << '\n';
            f << m[k].dat.y << '\n';
            if (char(cin.peek()) == '\n')     cin.ignore();
            cout << endl << "Введите название изделия: "; m[k].izdelie = In_str(); f << m[k].izdelie << '\n';
            cout << endl << "Введите цену изделия: ";

            float x; x = In_float();
            m[k].sum = x; f << m[k].sum;


            k++;
            if (char(cin.peek()) == '\n')     cin.ignore();
            cout << endl << "Хотите добавить еще одну запись y/n: ";
            cin >> c;
            system("cls");
        }
        *n = k;

        f.close();
        return;
    }
}
bool shit(string& f) { //проверка на строку
    return f.find_first_not_of("0123456789") == string::npos;
}
int In_int() //функция проверки на целочисленный тип
{
    char s[256]; //буфер для проверки
    char s1[256]; //буфер для проверки
    int i, k(1); //счетчик и инициализатор 

    while (k != 0)
    {
        k = 0;
        cin >> s;   i = atoi(s); //atoi - превращение строки в число
        if (i == 0) k = 1; //Некорректный ввод в atoi дает 0
        else
        {
            itoa(i, s1, 10); //itoa - конвертирует число в 10-чную систему
            if (strcmp(s, s1) != 0) k = 1; //strcmp - сравнивает строки и дает 0 в случае совпадения
        }

        if (k == 1) cout << endl << "Некорректный ввод целого числа.  Повторите ввод  ";

    }
    return i;
}
string In_str() //проверка на строку
{
    string buf; //сама строка
    while (true == true) {
        getline(cin, buf);
        if (shit(buf) == false) { //проверка на цифры. Если есть цифры- True.
            break;
        }
        else {
            cout << "Вводить надо буквы!!" << endl;
            cout << "Введите ещё раз: ";
        }
    }
    return buf;

}
float In_float() //проверка на дробь
{
    char s[256];
    char s1[256];
    char* s3; char* end;
    int k = 1;
    float x, y;
    cin >> s; s3 = s;
    while (k != 0)
    {
        k = 0;

        if (atof(s) == 0) k = 1;
        else
        {
            y = strtod(s3, &end); //strtod - превращает строку в double

            if (strlen(end) != 0) k = 1; //strlen - измеряет колличество символов
        }
        if (k == 1) { cout << endl << "Некорректный ввод действительного числа. Повторите ввод " << endl; cin >> s; s3 = s; }
    }

    x = atof(s); //atof - превращает строку во float

    return x;
}
int data_m() { //функция для месяца
    int n = 2;

    while (true == true) {
        cout << "Введите месяц: "; n = In_int();
        if (n > 0 && n <= 12) {
            break;
        }
        else {
            cout << "Введите месяц правильно!!!" << endl;
        }
    }
    return n;
}
int data_y() { //функция для года
    time_t now = time(0);  //получения года из системы
    tm* ltm = localtime(&now);//получения года из системы
    int vr = 1900 + ltm->tm_year; //получения года из системы
    int n = 2;
    while (true == true) {
        cout << "Введите год: "; n = In_int();
        if (n > 2011 && n <= vr) {
            break;
        }
        else {
            cout << "Введите год правильно!!!" << endl;
        }
    }
    return n;
}
void PKlient(Infoyuv m[], int* n) //поиск по имени клиента
{
    string s;
    int k(0);
    cout << endl << "------Поиск заказов конкретного клиента------" << endl << endl;
    if (*n == 0) cout << endl << endl << "       Массив данных пуст" << endl << endl;
    else
    {

        if (char(cin.peek()) == '\n')     cin.ignore();
        cout << endl << "Введите ПИБ клиента: "; s = In_str(); cout << endl; //Ввод имени
        cout.setf(ios::left); cout.width(4); cout << "№";
        cout.setf(ios::left); cout.width(20); cout << "КЛИЕНТ";
        cout.setf(ios::left); cout.width(20); cout << "МАСТЕР";
        cout.setf(ios::left); cout.width(12); cout << "ДАТА";
        cout.setf(ios::left); cout.width(20); cout << "ОБЪЕКТ";
        cout.setf(ios::left); cout.width(10); cout << "СУММА" << endl;
        cout << endl;
        for (int i = 0; i < *n; i++) //Поиск по массиву
            if (m[i].Klient == s)
            {
                cout.setf(ios::left); cout.width(4); cout << m[i].num;
                cout.setf(ios::left); cout.width(20); cout << m[i].Klient;
                cout.setf(ios::left); cout.width(20); cout << m[i].Master;
                cout.width(2); cout << m[i].dat.d << ".";
                cout.width(2); cout << m[i].dat.m << ".";
                cout << m[i].dat.y << "   ";
                cout.setf(ios::left); cout.width(20); cout << m[i].izdelie;
                cout.setf(ios::left); cout.width(10); cout << m[i].sum << endl;
                k++;
            }

        if (k == 0) cout << endl << "Клиента с именем < " << s << " > не было" << endl;
    }
    return;
}
int data_d(int mecl, int g) { //функция для ввода дней
    int d;
    while (true == true) {
        if (g % 4 != 0) { // проверка на высокосный год
            if (mecl == 2) { //проверка на февраль
                cout << "Введите день: "; d = In_int();
                if (d > 28 || d < 0) { //проверка правильности ввода даты для февраля
                    cout << "Попробуйте снова" << endl;
                }
                else {
                    break;
                }
            }
            if (mecl % 2 != 0 && mecl != 2) { //проверка на колличество дней в остальных месяцах
                cout << "Введите день: "; d = In_int();
                if (d <= 30 && d > 0) {
                    break;
                }
                else {
                    cout << "Попробуйте снова" << endl;
                }

            }
            else if (mecl % 2 == 0 && mecl != 2) {
                cout << "Введите день: "; d = In_int();
                if (d <= 31 && d > 0) {
                    break;
                }
                else {
                    cout << "Попробуйте снова" << endl;
                }
            }
        }
        else { //если год выскосный

            if (mecl % 2 != 0) {
                cout << "Введите день: "; d = In_int();
                if (d <= 30 && d > 0) {
                    break;
                }
                else {
                    cout << "Попробуйте снова" << endl;
                }

            }
            else {
                cout << "Введите день: "; d = In_int();
                if (d <= 31 && d > 0) {
                    break;
                }
                else {
                    cout << "Попробуйте снова" << endl;
                }
            }
        }
    }
    return d;
}
void PMaster(Infoyuv m[], int* n) { //поиск по имени мастера и дате
    string s;
    datat p1, p2;
    int k(0);
    int f;
    cout << endl << " Работы, сделанные указанным мастером в указанный период времени  " << endl << endl;
    if (*n == 0) { cout << endl << endl << "       Массив данных пуст" << endl << endl; return; }

    if (char(cin.peek()) == '\n')     cin.ignore();
    cout << endl << "Введите Фамилию и инициалы мастера: "; s = In_str(); 
    for (int i = 0; i < *n; i++) if (m[i].Master == s) k++; //поиск по имени мастера
    if (k == 0)
        cout << endl << " Мастер " << s << " не работает в ювелирной мастерской  " << endl << endl;
    else
    {
        cout << endl << "Введите первую дату ";
        cout << endl; p1.y = data_y(); p1.y;
        cout << endl; p1.m = data_m(); p1.m;
        cout << endl; p1.d = data_d(p1.m,p1.y); p1.d;
        cout << endl << "Введите вторую дату ";
        cout << endl; p2.y = data_y(); p2.y;
        cout << endl; p2.m = data_m(); p2.m;
        cout << endl; p2.d = data_d(p2.m, p2.y); p2.d;
        system("cls");
        cout << endl << " -------Работы мастера " << s << " с " << p1.d << "." << p1.m << "." << p1.y << " по " << p2.d << "." << p2.m << "." << p2.y << "-------" << endl << endl;
        k = 0;
        for (int i = 0; i < *n; i++) //поиск по заданному промежутку дат
        {
            f = 0;
            if (m[i].Master == s)
            {

                if (m[i].dat.y >= p1.y && m[i].dat.y <= p2.y) { //+

                    if (m[i].dat.y >= p1.y && m[i].dat.m >= p1.m) {

                        if (m[i].dat.d >= p1.d || m[i].dat.m >= p2.m) {
                            f++; 
                        }
                    }
                    if (m[i].dat.y <= p2.y && m[i].dat.m <= p2.m) {

                        if (m[i].dat.d <= p2.d || m[i].dat.m <= p2.m) {
                            f++;

                        }
                    }
                }
                if (f == 2)
                {
                    cout.setf(ios::left); cout.width(4); cout << m[i].num;
                    cout.setf(ios::left); cout.width(20); cout << m[i].Klient;
                    cout.setf(ios::left); cout.width(20); cout << m[i].Master;
                    cout.width(2); cout << m[i].dat.d << ".";
                    cout.width(2); cout << m[i].dat.m << ".";
                    cout << m[i].dat.y << "   ";
                    cout.setf(ios::left); cout.width(20); cout << m[i].izdelie;
                    cout.setf(ios::left); cout.width(10); cout << m[i].sum << endl;
                    k++;
                }
            }


        }
        if (k == 0)
            cout << endl << " Мастер " << s << " в указанный период времени не работал  " << endl << endl;

    }

    return;
}
void Sort2(Infoyuv m[], int* n) //сортировка пузырьком
{
    int i, j; //переменныые для циклов
    Infoyuv t; //буферный счетчик для перемещения элементов по списку
    for (i = 0; i < *n - 1; i++)
        for (j = 0; j <= *n - 2; j++) {
            if (m[j].sum < m[j + 1].sum)// сортировка по цене(возрастание)
            {
                t = m[j]; m[j] = m[j + 1]; m[j + 1] = t;

            }
        }
    return;
}
void Sort3(Infoyuv m[], int* n) //сортировка пузырьком
{
    int i, j; //переменныые для циклов
    Infoyuv t; //буферный счетчик для перемещения элементов по списку
    for (i = 0; i < *n - 1; i++)// сортировка по номеру заказа
        for (j = 0; j <= *n - 2; j++) {
            if (m[j].sum > m[j + 1].sum) // сортировка по цене(убывание)
            {
                t = m[j]; m[j] = m[j + 1]; m[j + 1] = t;

            }
        }
    return;
}
void Sort_max(Infoyuv m[], int* n) { //сортировка по максимальной цене
    int i;
    int k = 0;
    if (*n != 0) {
        cout << "-------Максимальная цена---------" << endl;
        cout.setf(ios::left); cout.width(4); cout << "№";
        cout.setf(ios::left); cout.width(20); cout << "КЛИЕНТ";
        cout.setf(ios::left); cout.width(20); cout << "МАСТЕР";
        cout.setf(ios::left); cout.width(12); cout << "ДАТА";
        cout.setf(ios::left); cout.width(20); cout << "ОБЪЕКТ";
        cout.setf(ios::left); cout.width(10); cout << "СУММА" << endl;
        cout << endl;
        for (i = 0; i < *n - 1; i++) {
            if (m[0].sum == m[i].sum) {
                k++;
                cout.setf(ios::left); cout.width(4); cout << m[i].num;
                cout.setf(ios::left); cout.width(20); cout << m[i].Klient;
                cout.setf(ios::left); cout.width(20); cout << m[i].Master;
                cout.width(2); cout << m[i].dat.d << ".";
                cout.width(2); cout << m[i].dat.m << ".";
                cout << m[i].dat.y << "   ";
                cout.setf(ios::left); cout.width(20); cout << m[i].izdelie;
                cout.setf(ios::left); cout.width(10); cout << m[i].sum << " гривен" << endl;
            }
        }
    }
    else {
        cout << "Массив данных пуст" << endl;
    }
}
void Sort_min(Infoyuv m[], int* n) { //сортировка по минимальной цене
    int i;
    int k = 0;
    if (*n != 0) {
        cout << "-------Минимальная цена---------" << endl;
        cout.setf(ios::left); cout.width(4); cout << "№";
        cout.setf(ios::left); cout.width(20); cout << "КЛИЕНТ";
        cout.setf(ios::left); cout.width(20); cout << "МАСТЕР";
        cout.setf(ios::left); cout.width(12); cout << "ДАТА";
        cout.setf(ios::left); cout.width(20); cout << "ОБЪЕКТ";
        cout.setf(ios::left); cout.width(10); cout << "СУММА" << endl;
        cout << endl;
        for (i = 0; i < *n - 1; i++) {
            if (m[0].sum == m[i].sum) {
                k++;
                cout.setf(ios::left); cout.width(4); cout << m[i].num;
                cout.setf(ios::left); cout.width(20); cout << m[i].Klient;
                cout.setf(ios::left); cout.width(20); cout << m[i].Master;
                cout.width(2); cout << m[i].dat.d << ".";
                cout.width(2); cout << m[i].dat.m << ".";
                cout << m[i].dat.y << "   ";
                cout.setf(ios::left); cout.width(20); cout << m[i].izdelie;
                cout.setf(ios::left); cout.width(10); cout << m[i].sum << " гривен" << endl;
            }
        }
    }
}
//ЭТУ ФУНКЦИЮ НЕ ТРОГРАТЬ И НЕ ИЗМЕНЯТЬ,НИКОГДА В ЖИЗНИ!!!!!!!!!!!!!!!!!!!!!!!!! 
vector<string> RobotaFile(const fs::path& dir, const vector<string>& ext)
{
    vector<string> files;
    for (auto& p : fs::recursive_directory_iterator(dir)) //парсинг по заданной директории
    {
        if (fs::is_regular_file(p)) { //проверка на существование заданной директории
            if (ext.empty() || find(ext.begin(), ext.end(), p.path().extension().string()) != ext.end()) { //сам парсинг
                files.push_back(p.path().string());
            }
        }
    }
    return files;
}
