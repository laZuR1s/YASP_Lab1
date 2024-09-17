#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

// Номер 18
// Лазарев А.А
// Напишите программу для ввода шестнадцатеричного числа в строку, приведения его в десятичную и его вывода

const int N = 16;
int main_menu(const char* message);    // Основное меню
int output_menu(const char* message);  // Меню выбора вывода
std::string num_get(std::istream& stream, const char* message); // Ввод числа с передачей способа ввода по параметру
int char_to_int(char chr); // Преобразование символа char в int путем преобразований
int hex_to_dec(std::string hex); // Преобразование числа в десятичное 
void print_dec(int dec, std::ostream& file_out); // Вывод числа с передай способа вывода по параметру

int main()
{
	SetConsoleOutputCP(1251); // Русская локализация
	std::ifstream file_inp("input_file.txt"); // Обьявление файлов на ввод/вывод
	std::ofstream file_out("output_file.txt");

	short choice{};
	do
	{
		choice = main_menu(""); // Вызов меню и выбор пункта
		if (choice != 3)
		{
			short option = output_menu(""); // Вызов дополнительного меню и выбор пункта

			std::string hex; 
			switch (choice)
			{
			case 1:
				hex = num_get(file_inp, ""); // Считываем число из файла
				std::cout << '\n';
				break;
			case 2:
				hex = num_get(std::cin, "\nВведите число: "); // Считываем число из файла
				break;
			default:
				break;
			}
			int dec = hex_to_dec(hex); // Преобразуем введенное число из шестнадцатиричной системы в десятичную

			switch (option)
			{
			case 1:
				print_dec(dec, file_out); // Вывод десятичного числа
				break;
			case 2:
			{
				std::cout << "Десятичная форма: ";
				print_dec(dec, std::cout); // Вывод десятичного числа
				std::cout << '\n';
			}
			break;
			default:
				break;
			}
		}
	} while (choice != 3);

	std::cin.get();
}

int output_menu(const char* message)
{
	std::cout << "\nМетод вывода\n";
	std::cout << "\n-----------------------------------------------------\n";
	std::cout << "1. Вывод в файл\n";
	std::cout << "2. Вывод в консоль\n";
	std::cout << "-----------------------------------------------------\n";
	int choice;
	while (!(std::cin >> choice && choice >= 1 && choice <= 2)) // Валидация введенных данных
	{
		std::cout << "Ошибка ввода!" << '\n';
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message << "\n>>> ";
	}

	std::cin.ignore(std::cin.rdbuf()->in_avail());
	return choice;
}


int main_menu(const char* message)
{
	std::cout << "\nМеню\n";
	std::cout << "\n-----------------------------------------------------\n";
	std::cout << "1. Ввод шестнадцатиричного числа с файла\n";
	std::cout << "2. Ввод шестнадцатиричного числа с клавиатуры\n";
	std::cout << "3. Выйти из программы\n";
	std::cout << "-----------------------------------------------------\n";
	int choice;
	while (!(std::cin >> choice && choice >= 1 && choice <= 3)) // Валидация введенных данных
	{
		std::cout << "Ошибка ввода!" << '\n';
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::cout << message << "\n>>> ";
	}
	return choice;
}


std::string num_get(std::istream& stream, const char* message)
{
	std::string hex{};
	bool isCool = true;
	do
	{
		isCool = true;
		std::cout << message;
		stream >> hex;
		for (int i = 0; i < hex.length(); ++i) {
			  

			if (!((hex[i] >= '0' && hex[i]<= '9') || (hex[i] >= 'A' && hex[i]<= 'F')||(hex[i]>='a'&&hex[i]<='f'))) // Валидация введенных данных
			{ 
				isCool = false;
				std::cout << "Ошибка: допустимы только символы 0-9, A-F.\n";
				hex = "";
				break;
			}
		}
	} while (!isCool);

	return hex;
}

int char_to_int(char chr)
{
	int num{};
	if (chr >= '0' && chr <= '9') // Преобразование буквенных символов в число путем вычитания символов 'F'=70; 'A'=65;
		num = chr - '0';
	else if (chr >= 'A' && chr <= 'F')
		num = chr - 'A' + 10;
	else if (chr >= 'a' && chr <= 'f')
		num = chr - 'a' + 10;
	return num;
}

int hex_to_dec(std::string hex)
{
	int dec{};
	int size = hex.length();
	for (int i = 0, j = size - 1; i < size; ++i, --j) {
		dec += char_to_int(hex[i]) * pow(N, j);
	}
	return dec;
}

void print_dec(int dec, std::ostream& ostr)
{
	ostr << dec;
}
