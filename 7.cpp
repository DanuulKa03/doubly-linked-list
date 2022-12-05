#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>

using namespace std;

struct Schoolboy
{
	string surname = { 0 };
	string name = { 0 };
	string patronymic = { 0 };
	string numberClass = { 0 };
	string phoneNumber = { 0 };
	//представим, что это оценка за ОГЭ, поэтому она будет одна)
	int grades[4] = { 0 }; //математика, физика, русский язык,литература
};

Schoolboy structureInput();

class List
{
public:
	List();
	~List();

	void pop_front();

	void push_back(Schoolboy data);

	int GetSize() { return Size; };

	Schoolboy& operator[](const int index);

	bool SaveFile();

	void consoleOutput();

	void subConsolOutput(int index);

	bool readingFile();

	bool dataSearch();

	bool searchKey();

private:
	class Node
	{
	public:
		Node* pNext, *pPrev;
		Schoolboy data;
		Node(Schoolboy data = Schoolboy(), Node* pNext = nullptr, Node* pPrev = nullptr) { // T data = T() чтобы внутри data небыло мусора 
			this->data = data; //мы ведь когда создаем экземпляр Node в скобках указываем аргументы этого экземпляра.
			this->pNext = pNext; //И чтобы присвоить этим данным какое-то значение надо использовать this а потом данные которые хотим изменить, так как это конструктор
			this->pPrev = pPrev;
		}
	};

	int Size; //чтобы хранить количество элементов в нашем списке
	Node* head, *footer; //чтобы знать существует ли у нас поле. Это очень удобно. Он будет в себе хранить первое поле в списке.
	//это будет целым обьектом. Внутри самого класса. А не выброшанный где-то в памяти
};


List::List() //когда мы только создаем нашь экземпляр класса List в котором хранится Node (поля) мы сразу записываем туда всю информацию
{
	Size = 0;
	head = nullptr;
	footer = nullptr;
}

List::~List()
{
}

void List::pop_front()
{
	Node* temp = head; //мы берем и копируем наше первое поле, берем его данные, прям из памяти 

	head = head->pNext; //а далее вместо него записываем наше следующее поле

	delete temp;

	Size--;
}

void List::push_back(Schoolboy data)
{
	if (head == nullptr) {
		head = new Node(data); //так как мы создаем первый элемент нашего List второй аргумент указывать не надо. Ведь это первый сезданный элемент

		//здесь мы пишем Node<T> так как нам не известно какое поле у data
		//мы записываем сразу в этот указатель новый созданный элемент
	}
	else {
		Node* current = this->head; //это временная переменная для временного перемещения по указателям
		while (current->pNext != nullptr) { //он присвает сначала указатель первого значения head, самого первого поля. Берет у него его значение pNext
			current = current->pNext; //присваивает себе пока значение следующего поля пока не найдет последний
		}
		current->pNext = new Node(data,nullptr,current); //теперь в него записываем новое созданое поле
		footer = current->pNext;
		//почему это работает
		//это всего лишь указатель на обьект, то есть это не сам элемент а просто указатель на него
		//когда мы изменем значение здесь, то изменеться адрес именного самого элемента в памяти
	}
	Size++;
}

Schoolboy& List::operator[](const int index)
{
	int counter = 0;
	if (index <= Size/2) 
	{
		Node* current = this->head; //это временная переменная для временного перемещения по указателям
		while (current != nullptr)
		{
			if (counter == index) {
				return current->data;
				//опять же, здесь мы берем просто указатель в котором храниться тот самый элемент и выводим его
			}
			current = current->pNext;
			counter++;
		}
	}
	else 
	{
		counter = Size - 1;
		Node* current = this->footer; //это временная переменная для временного перемещения по указателям
		while (current != nullptr)
		{
			if (counter == index) {
				return current->data;
				//опять же, здесь мы берем просто указатель в котором храниться тот самый элемент и выводим его
			}
			current = current->pPrev;
			counter--;
		}
	}
}

bool List::SaveFile()
{
	ofstream fout("MyFile.txt", ios::app);
	if (!fout.is_open() || head == nullptr) return false;

	for (int i = 0; i < Size; i++) {

		fout << (*this)[i].surname << " ";

		fout << (*this)[i].name << " ";

		fout << (*this)[i].patronymic << " ";

		fout << (*this)[i].numberClass << " ";

		fout << (*this)[i].phoneNumber << " ";

		for (int j = 0; j < 4; j++) {
			fout << (*this)[i].grades[j];
			if (j + 1 < 4) fout << " ";
		}

		fout << "\n";
	}
	fout.close();
	return true;
}

void List::consoleOutput()
{
	cout << endl << "|    Фамилия    |    Имя    |     Отчество    |№ класса|Номер телеф| Оценка Мат/Физ/Рус/Лит |\n";
	for (int i = 0; i < Size; i++)
	{
		cout << "|"; cout.width(15); cout << (*this)[i].surname << "|";
		cout.width(11); cout << (*this)[i].name << "|";
		cout.width(17); cout << (*this)[i].patronymic << "|";
		cout.width(8); cout << (*this)[i].numberClass << "|";
		cout.width(11); cout << (*this)[i].phoneNumber << "|";
		for (int j = 0; j < 4; j++) 
		{
			cout.width(6);
			cout << (*this)[i].grades[j];
		} 
		cout << "|" << endl;
	}
}

void List::subConsolOutput(int index)
{
	cout << endl << "|    Фамилия    |    Имя    |     Отчество    |№ класса|Номер телеф| Оценка Мат/Физ/Рус/Лит |\n|";
	cout.width(15); cout << (*this)[index].surname << "|";
	cout.width(11); cout << (*this)[index].name << "|";
	cout.width(17); cout << (*this)[index].patronymic << "|";
	cout.width(8); cout << (*this)[index].numberClass << "|";
	cout.width(11); cout << (*this)[index].phoneNumber << "|";
	for (int j = 0; j < 4; j++)
	{
		cout.width(6);
		cout << (*this)[index].grades[j];
	}
	cout << "|" << endl;
}

bool List::readingFile()
{
	ifstream fin("MyFile.txt");
	if (!fin.is_open()) return false;

	Schoolboy data;
	while(fin)
	{
		fin >> data.surname;
		fin >> data.name;
		fin >> data.patronymic;
		fin >> data.numberClass;
		fin >> data.phoneNumber;
		for (int j = 0; j < 4; j++) {
			fin >> data.grades[j];
		}
		if (!fin.eof()) { push_back(data); }
	}
	fin.close();
	return true;
}

bool List::dataSearch()
{
	string str;
	int temp = 0;
	bool flag = 0;
	cout << "По какому полю вы хотите осуществить поиск?\nВвод: ";
	cout << "	1) фамилия\n";
	cout << "	2) имя\n";
	cout << "	3) отчество\n";
	cout << "	4) класс\n";
	cout << "	5) номер телефона\nВвод: ";
	cin >> temp;
	cout << "Введите значение поля\nВвод: ";
	cin >> str;
	switch (temp)
	{
	case 1:
		for (int i = 0; i < Size; i++) 
		{
			if (strcmp((*this)[i].surname.c_str(), str.c_str()) == 0) 
			{
				subConsolOutput(i);
				flag = 1;
			}
		}
		break;

	case 2:
		for (int i = 0; i < Size; i++)
		{
			if (strcmp((*this)[i].name.c_str(), str.c_str()) == 0)
			{
				subConsolOutput(i);
				flag = 1;
			}
		}
		break;

	case 3:
		for (int i = 0; i < Size; i++)
		{
			if (strcmp((*this)[i].patronymic.c_str(), str.c_str()) == 0)
			{
				flag = 1;
				subConsolOutput(i);
			}
		}
		break;

	case 4:
		for (int i = 0; i < Size; i++)
		{
			if (strcmp((*this)[i].numberClass.c_str(), str.c_str()) == 0)
			{
				flag = 1;
				subConsolOutput(i);
			}
		}
		break;

	case 5:
		for (int i = 0; i < Size; i++)
		{
			if (strcmp((*this)[i].phoneNumber.c_str(), str.c_str()) == 0)
			{
				flag = 1;
				subConsolOutput(i);
			}
		}
		break;

	default:
		break;
	}
	if (flag) return 1;
	return 0;
}

bool List::searchKey()
{
	bool flag = 0;
	string str;
	cout << "Введите номер телефона для удаления поля\nВвод: ";
	cin >> str;
	for (int i = 0; i < Size; i++) 
	{
		if (strcmp((*this)[i].phoneNumber.c_str(), str.c_str()) == 0) 
		{

			flag = 1;
			int counter = 0;
			if (i <= Size / 2) 
			{
				Node* current = this->head; //это временная переменная для временного перемещения по указателям
				while (current != nullptr)
				{
					if (counter == i) 
					{
						current->pNext->pPrev = current->pPrev;
						current->pPrev->pNext = current->pNext;
						delete current;
						return true;
					}
					current = current->pNext;
					counter++;
				}
			}
			else
			{
				counter = Size - 1;
				Node* current = this->footer; //это временная переменная для временного перемещения по указателям
				while (current != nullptr)
				{
					if (counter == i) 
					{
						current->pNext = current->pPrev;
						current->pPrev = current->pNext;
						delete current;
						return true;
					}
					current = current->pPrev;
					counter--;
				}
			}
			Size--;
		}
	}
	if (!flag) return false;
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List lst;

	int menu = 1;
	while (menu)
	{
		cout << endl << "Выберите номер функции" << endl;
		cout << "	1) Начальное формирование данных" << endl;
		cout << "	2) добавление новых данных" << endl;
		cout << "	3) поиск данных по ключу" << endl;
		cout << "	4) удаление данных по ключу" << endl;
		cout << "	5) вставка данных в упорядоченный по первому полю список, не нарушая порядка"<< endl;
		cout << "	6) сортировка по одному полю" << endl;
		cout << "	7) сортировка списка по двум полям" << endl;
		cout << "	8) вывод списка на экран" << endl;
		cout << "	9) сохранение данных в текстовый файл" << endl;
		cout << "Ввод : ";
		cin >> menu;
		switch (menu)
		{
		case 1:
			if (lst.readingFile()) cout << "\nСтроки записаны в систему\n";
			else cout << "\nОшибка открытия файла\n";
			break;

		case 2:

			lst.push_back(structureInput());
			break;

		case 3:

			if (!lst.dataSearch()) cout << endl << "Не удалось найти структуру" << endl;
			break;

		case 4:
			if (lst.searchKey()) cout << endl << "Поле удалено" << endl;
			else cout << endl << "Поле было не найдено" << endl;
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			
			lst.consoleOutput();
			break;

		case 9:

			if (lst.SaveFile()) cout << "Структуры записаны в файл" << endl;

			else cout << "Ошибка создания|открытия файла" << endl;

			break;

		default:
			break;
		}
	}
	return 0;
}

Schoolboy structureInput()
{
	Schoolboy Temp;
	cout << endl << "Введите все новые данные" << endl;
	cout << "	Фамилия\nВвод: ";
	cin >> Temp.surname;
	cout << "	Имя\nВвод: ";
	cin >> Temp.name;
	cout << "	Отчество\nВвод: ";
	cin >> Temp.patronymic;
	cout << "	Номер класса\nВвод: ";
	cin >> Temp.numberClass;
	cout << "	Номер телефона\nВвод: ";
	cin >> Temp.phoneNumber;
	cout << "	Оценка за математику\nВвод: ";
	cin >> Temp.grades[0];
	cout << "	Оценка за физику\nВвод: ";
	cin >> Temp.grades[1];
	cout << "	Оценка за русский язык\nВвод: ";
	cin >> Temp.grades[2];
	cout << "	Оценка за литературу\nВвод: ";
	cin >> Temp.grades[3];
	return Temp;
}
