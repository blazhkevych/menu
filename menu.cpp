﻿#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include <algorithm>
// ссылка на видосик по меню
//https://web.microsoftstream.com/video/6ff1b395-350d-4129-90a7-3be68affe30a?search=%D1%81%2B%2B%202 закончил на 1:08:57
using namespace std;
#define MENUTOP 4 // отодвигаем меню сверху на 4
#define MENULEFT 20 // отодвигаем меню снизу на 20
#define BACKGROUND 1 // константа для изменения заднего фона
#define FOREGROUND 15 // константа для изменения переднего фона
#define SELECTITEM 4 // цвет выбраного меню
void gotorc(short r, short c) { // ходим по экрану, по рядкам и колонкам 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // окно вывода сохраненное в хендл 
	SetConsoleCursorPosition(handle, { c,r }); // установка курсора в необходимую позицию
}
void Color(unsigned short Back, unsigned short Forg) { // устанавливает цвет заднего фона и переднего фона
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); // ловим хендл 
	unsigned short c = ((Back & 0x0F) << 4) + (Forg & 0x0F); // определяем цвет
	SetConsoleTextAttribute(handle, c);
}
void paintmenu(const char** s, int sizem, int  pm) { // рисуем меню
	system("cls"); // очищает экран при заходе в меню
	gotorc(MENUTOP, MENULEFT); // размещаем меню в определенной позиции
	Color(BACKGROUND, FOREGROUND); // функция колор должна установить дефолтное значение 
	cout << "------Menu-------\n"; // первая строка меню
	for (size_t i = 0; i < sizem; i++) // выводим само меню, тоесть рисуем рядки из "const char** s"
	{
		gotorc(MENUTOP + i + 1, MENULEFT); // указываем позицию вывода сиаута из 33 строчки(cout << s[i] << endl;)
		cout << (i == pm ? Color(BACKGROUND, SELECTITEM), "=>" : "  "); // // активное меню будет подсвечивать другим цветом
		cout << s[i] << endl;
		Color(BACKGROUND, FOREGROUND); //цвет по дефолту
	}
}
int menu(const char** s, int sizem, int  pm = 0) { // меню, реакции на клавиши
	char c = 80; // любая буква для инициализации
	while (true) // бесконечный цикл, проверяем что вводят
	{
		if (c == 72 || c == 80) paintmenu(s, sizem, pm); // перерисовываем меню при движении курсора
		c = _getch(); // считать команду с клавиатуры, букву которую нажали, кладем ее в "с"
		switch (c) // обрабатываем нажатую кнопку
		{
		case 27: //код кнопки "esc" 27
			return -1; // программу закрываем 
		case 80: //down
			pm++; // пункт меню увеличиваем принажатии кнопки вниз
			if (pm == sizem) pm = 0; // чтобы не выскочить за пределы меню на послднем обнуляем переменную
			break; // чтобы выйти из свича
		case 72: //up
			if (pm == 0) pm = sizem;
			pm--;
			break;
		case 13: //enter
			return pm; // возвражаем выбранный пункт меню
		}
	}
}
void Task1() {
	int a;
	cin >> a;
	cout << a << "Task1\n";
}
void Task2() {
	cout << "Task2\n";
}
void Task3() {
	cout << "Task3\n";
}
void Task4() {
	cout << "Task4\n";
}
int main() {
	Color(BACKGROUND, FOREGROUND);
	system("cls"); // очищаем экран (clear screen)
	const char* s[]{ // массив для пунктов меню, динам, так как хз сколько их будет.
		"Task 1",
		"Task 2",
		"Task 3",
		"Task 4",
	};
	int sizem = sizeof(s) / 4; //переменная которая будет знать сколько элементов в нашем меню
	int pm = 0; // пункт меню которое выбрал пользователь, по дефолту ноль
	while (true) // создаем вечный цикл
	{
		pm = menu(s, sizem, pm);
		system("cls"); // очищаем экран (clear screen)
		switch (pm) // прилетел пункт меню, в зависимости от значения идем по кейсам
		{
		case -1: return 0;
		case 0:
			Task1();
			break;
		case 1:
			Task2();
			break;
		case 2:
			Task3();
			break;
		case 3:
			Task4();
			break;
		}
		Color(BACKGROUND, 2); //цвет текста в выбранном меню
		cout << "done\n"; // вывод в выбранном пункте меню
		_getch(); // ждем и считываем кнопку
	}
}