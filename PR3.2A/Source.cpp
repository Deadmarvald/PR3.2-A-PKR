#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Spec {
	COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS,
	PHYSICS_INFORMATICS, WORK_TRAINING
};

string specStr[] = { "Комп\'ютерні науки", "Інформатика",
"Математика та економіка", "Фізика та інформатика","Трудове навчання" };

struct Student
{
	string secondname;
	unsigned kurs;
	Spec spec;
	int physics;
	int math;
	int inf;
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
void Sort(Student* s, const int N);
int BinSearch(Student* s, const int N, const int inf, const int kurs, const string secondname);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;

	cout << "Введіть N = "; cin >> N;

	Student* s = new Student[N];

	int inf;
	int kurs;
	string secondname;
	int found;

	int menuItem;

	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << "\t[1] - Введення даних з клавіатури" << endl;
		cout << "\t[2] - Вивід даних на екран" << endl;
		cout << "\t[3] - Фізичне впорядкування даних" << endl;
		cout << "\t[4] - Вивід впорядкованих даних" << endl;
		cout << "\t[5] - Бінарний пошук студента" << endl << endl;
		cout << "\t[0] - Exit" << endl << endl;
		cout << "Ваш вибір: "; cin >> menuItem;
		cout << endl << endl << endl;

		switch (menuItem)
		{
		case 1:
			Create(s, N);
			break;
		case 2:
			Print(s, N);
			break;
		case 3:
			Sort(s, N);
			break;
		case 4:
			PrintIndexSorted(s, IndexSort(s, N), N);
			break;
		case 5:
			cout << "Введіть ключі пошуку: " << endl;
			cout << "\tВведіть оцінку з інформатики: "; cin >> inf;
			cout << "\tВведіть курс: "; cin >> kurs;

			cin.get();
			cin.sync();

			cout << "\tПрізвище: "; getline(cin, secondname);
			cout << endl;
			if ((found = BinSearch(s, N, inf, kurs, secondname)) != -1)
			{
				cout << "Знайдено студента в позиції " << found + 1 << endl;
			}
			else
			{
				cout << "Шуканого cтудента не знайдено" << endl;
			}
			break;
		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				<< "Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);

	system("pause");
	return 0;
}

void Create(Student* s, const int N)
{
	int spec;

	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;

		cin.get();
		cin.sync();

		cout << "\tпрізвище: "; getline(cin, s[i].secondname);
		cout << "\tКурс: "; cin >> s[i].kurs;
		cout << "\tСпеціальність:\n [0]Комп\'ютерні науки\n [1]Інформатика\n"
			<< " [2]Математика та економіка\n [3]Фізика та інформатика\n"
			<< " [4]Трудове навчання\n Твій вибір: "; cin >> spec;

		s[i].spec = (Spec)spec;

		switch (s[i].spec)
		{
		case COMPUTER_SCIENCE:
			cout << "\tОцінка з фізики: "; cin >> s[i].physics;
			cout << "\tОцінка з математики: "; cin >> s[i].math;
			cout << "\tОцінка з інформатики: "; cin >> s[i].inf;
			break;
		case INFORMATICS:
			cout << "\tОцінка з фізики: "; cin >> s[i].physics;
			cout << "\tОцінка з математики: "; cin >> s[i].math;
			cout << "\tОцінка з інформатики: "; cin >> s[i].inf;
			break;
		case MATH_ECONOMICS:
		case PHYSICS_INFORMATICS:
		case WORK_TRAINING:
			cout << "\tОцінка з фізики: "; cin >> s[i].physics;
			cout << "\tОцінка з математики: "; cin >> s[i].math;
			cout << "\tОцінка з інформатики: "; cin >> s[i].inf;
			break;
		}
		cout << endl;
	}
}

void Print(Student* s, const int N)
{
	cout << "========================================================================================="
		<< endl;
	cout << "| № |   Прізвище   | Курс |      Спеціальність      | Фізика | Математика | інформатики |"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(12) << left << s[i].secondname << " "
			<< "|   " << setw(1) << right << s[i].kurs << "  "
			<< "| " << setw(23) << left << specStr[s[i].spec] << " "
			<< "|    " << setw(1) << right << s[i].physics << "   "
			<< "|      " << setw(1) << left << s[i].math << "     ";

		switch (s[i].spec)
		{
		case COMPUTER_SCIENCE:
			cout << "|       " << setw(1) << right << s[i].inf << "     |" << endl;
			break;
		case INFORMATICS:
			cout << "|       " << setw(1) << right << s[i].inf << "     |" << endl;
			break;
		case MATH_ECONOMICS:
		case PHYSICS_INFORMATICS:
		case WORK_TRAINING:
			cout << "|       " << setw(1) << right << s[i].inf << "     |" << endl;
			break;
		}
	}
	cout << "========================================================================================="
		<< endl;
	cout << endl;
}

void Sort(Student* s, const int N)
{
	Student temp;

	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - i - 1; j++)
		{
			if ((s[j].inf > s[j + 1].inf)
				||
				(s[j].inf == s[j + 1].inf &&
					s[j].kurs > s[j + 1].kurs)
				||
				(s[j].inf == s[j + 1].inf &&
					s[j].kurs == s[j + 1].kurs &&
					s[j].secondname > s[j + 1].secondname))
			{
				temp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = temp;
			}
		}
	}
}

int BinSearch(Student* s, const int N, const int profpred, const int kurs, const string secondname)
{
	int L = 0, R = N - 1, m;

	do {
		m = (L + R) / 2;
		if (s[m].inf == profpred && s[m].kurs == kurs && s[m].secondname == secondname)
		{
			return m;
		}
		if ((s[m].inf < profpred)
			||
			(s[m].inf == profpred &&
				s[m].kurs < kurs)
			||
			(s[m].inf == profpred &&
				s[m].kurs == kurs &&
				s[m].secondname < secondname))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);

	return -1;
}

int* IndexSort(Student* s, const int N)
{
	int value, i, j;
	int* I = new int[N];

	for (int i = 0; i < N; i++)
	{
		I[i] = i;
	}

	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1; j >= 0 && (s[I[j]].inf > s[value].inf) ||
			(s[I[j]].inf == s[value].inf &&
				s[I[j]].kurs > s[value].kurs) ||
			(s[I[j]].inf == s[value].inf &&
				s[I[j]].kurs == s[value].kurs &&
				s[I[j]].secondname > s[value].secondname); j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}


void PrintIndexSorted(Student* s, int* I, const int N)
{
	cout << "========================================================================================="
		<< endl;
	cout << "| № |   Прізвище   | Курс |      Спеціальність      | Фізика | Математика | інформатики |"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(12) << left << s[i].secondname << " "
			<< "|   " << setw(1) << right << s[i].kurs << "  "
			<< "| " << setw(23) << left << specStr[s[i].spec] << " "
			<< "|    " << setw(1) << right << s[i].physics << "   "
			<< "|      " << setw(1) << left << s[i].math << "     ";

		switch (s[I[i]].spec)
		{
		case COMPUTER_SCIENCE:
			cout << "|       " << setw(1) << right << s[I[i]].inf << "     |" << endl;
			break;
		case INFORMATICS:
			cout << "|       " << setw(1) << right << s[I[i]].inf << "     |" << endl;
			break;
		case MATH_ECONOMICS:
		case PHYSICS_INFORMATICS:
		case WORK_TRAINING:
			cout << "|       " << setw(1) << right << s[I[i]].inf << "     |" << endl;
			break;
		}
	}
	cout << "========================================================================================="
		<< endl;
	cout << endl;
}