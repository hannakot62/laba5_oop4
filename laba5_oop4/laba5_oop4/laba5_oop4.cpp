#include <iostream>
#include <iomanip>
#include <fstream>
#include <list>
#include <string>
#include <memory>
#include <map>
#include<Windows.h>
using namespace std;

class Doctor {
private:
	string surname;
	string specialization;
public:
	Doctor() { surname = "Котягова"; specialization = "хирург"; }
	Doctor(string sur, string spec) { surname = sur; specialization = spec; }
	string GetSurname() { return surname; }
	string GetSpecialization() { return specialization; }
	void SetSurname(string sur) { surname = sur; }
	void SetSpecialization(string spec) { specialization = spec; }
	friend istream& operator>>(istream& s, Doctor& d);
	friend ostream& operator<<(ostream& s, Doctor& d);
	void operator=(Doctor& newD);
};

class Nurse{
private:
	string surname;
	int experience;
public:
	Nurse() { surname = "Котягова"; experience = 1; }
	Nurse(string sur, int ex) { surname = sur; experience = ex; }
	string GetSurname() { return surname; }
	int GetExperience() { return experience; }
	void SetSurname(string sur) { surname = sur; }
	void SetExperience(int ex) { experience = ex; }
	friend istream& operator>>(istream& s, Nurse& d);
	friend ostream& operator<<(ostream& s, Nurse& d);
};

class DutyPair{
private:
	Doctor doctor;
	Nurse nurse;
public:
	DutyPair() {
		doctor.SetSurname("Логунова");
		doctor.SetSpecialization("терапевт");
		nurse.SetSurname("Григорьева");
		nurse.SetExperience(4);
	}
	DutyPair(Doctor doc, Nurse nur) {
		this->doctor.SetSurname(doc.GetSurname());
		this->doctor.SetSpecialization(doc.GetSpecialization());
		this->nurse.SetSurname(nur.GetSurname());
		this->nurse.SetExperience(nur.GetExperience());
	}
	DutyPair(list<Doctor>::iterator doc, list<Nurse>::iterator nur) {
		this->doctor.SetSurname(doc->GetSurname());
		this->doctor.SetSpecialization(doc->GetSpecialization());
		this->nurse.SetSurname(nur->GetSurname());
		this->nurse.SetExperience(nur->GetExperience());
	}
	Doctor& GetDoctor() { return doctor; }
	Nurse& GetNurse() { return nurse; }
	void SetDoctor(Doctor doc) {
		this->GetDoctor().SetSpecialization(doc.GetSpecialization());
		this->GetDoctor().SetSurname(doc.GetSurname());
	}
	void SetNurse(Nurse nur) {
		this->GetNurse().SetSurname(nur.GetSurname());
		this->GetNurse().SetExperience(nur.GetExperience());
	}
};


//получить данные из файла или с клавиатуры
//помощью перегруженного >>
istream& operator>>(istream& s, Doctor& d) {
	cout << "Введите фамилию: ";
	cin >> d.surname;
	cout << "Введите специализацию: ";
	cin >> d.specialization;
	return s;
}
//послать данные в файл или на экран перегруженным <<
ostream& operator<<(ostream& s, Doctor& d) {
	s << setw(20) << d.surname << "|" << setw(20) << d.specialization << "|" << "\n";
	return s;
}

istream& operator>>(istream& s, Nurse& d) {
	cout << "Введите фамилию: ";
	cin >> d.surname;
	cout << "Введите стаж: ";
	cin >> d.experience;
	return s;
}
//послать данные в файл или на экран перегруженным <<
ostream& operator<<(ostream& s, Nurse& d) {
	s << setw(20) << d.surname << "|" << setw(20) << d.experience << "|" << "\n";
	return s;
}

void ShowDoctors(list<Doctor> doctors) {
	cout << "+----------------------------------------+" << endl;
	cout << setw(20) << "Фамилия врача" << "|" << setw(20) << "Специализация" << "|" << endl;
	cout << "+----------------------------------------+" << endl;
	for (auto docs : doctors) {
		cout << docs;
	}
	cout << "+----------------------------------------+" << endl;
}

void ShowNurses(list<Nurse> nurses) {
	cout << "+----------------------------------------+" << endl;
	cout << setw(20) << "Фамилия медсестры" << "|" << setw(20) << "Стаж работы" << "|" << endl;
	cout << "+----------------------------------------+" << endl;
	for (auto docs : nurses) {
		cout << docs;
	}
	cout << "+----------------------------------------+" << endl;
}

void ShowSchedule(map<int, DutyPair> schedule) {
	cout << "+------------------------------------------------------------+" << endl;
	cout << setw(20) << "Число" << "|" << setw(20) << "Врач" << "|" << setw(20) << "Медсестра" << "|" << endl;
	cout << "+------------------------------------------------------------+" << endl;
	map<int, DutyPair>::iterator mapPtr;
	mapPtr = schedule.begin();
	for (int i = 0; i < schedule.size();i++) {
		cout << setw(20) << mapPtr->first << "|" << setw(20) << mapPtr->second.GetDoctor().GetSurname() << "|" << setw(20) << mapPtr->second.GetNurse().GetSurname() << "|" << endl;
		mapPtr++;
	}
	cout << "+------------------------------------------------------------+" << endl;
}

void AddDoctor(list<Doctor>& docs) {
	Doctor d;
	cin >> d;
	docs.push_back(d);
}

void AddNurse(list<Nurse>& docs) {
	Nurse d;
	cin >> d;
	docs.push_back(d);
}

void ShowDayDuty(map<int, DutyPair> dutySchedule) {
	cout << "Введите ключ: ";
	int day;
	cin >> day;
	//Находим значение по заданному ключу
	map<int, DutyPair>::iterator mapPtr;
	mapPtr = dutySchedule.find(day);
	if (mapPtr != dutySchedule.end())
		cout << "Дежурят: " << mapPtr->second.GetDoctor().GetSurname() << "(врач) и " << mapPtr->second.GetNurse().GetSurname() << "(медсестра)" << endl;
	else cout << "Дежурство в этот день не назначено\n";
}

void AddDuty(list<Doctor>& doctors, list<Nurse>& nurses, map<int, DutyPair>& dutySchedule) {
	ShowDoctors(doctors);
	string dSur, nSur;
	int day;
	cout << "Введите фамилию врача: ";
	cin >> dSur;
	list<Doctor>::iterator itDoc = doctors.begin();
	for (; itDoc != doctors.end(); itDoc++) {
		if (itDoc->GetSurname() == dSur) {
			break;
		}
	}
	if (itDoc == doctors.end()) {
		cout << "Такого врача нет" << endl;
	}

	ShowNurses(nurses);
	cout << "Введите фамилию медсестры: ";
	cin >> nSur;
	list<Nurse>::iterator itNur = nurses.begin();
	for (; itNur != nurses.end(); itNur++) {
		if (itNur->GetSurname() == nSur) {
			break;
		}
	}
	if (itNur == nurses.end()) {
		cout << "Такой медсестры нет" << endl;
	}
	if (itNur == nurses.end() || itDoc == doctors.end()) {
		cout << "Некорректно были введены фамилии медперсонала" << endl;
	}
	else {
		cout << "Введите день: " << endl;
		cin >> day;
		if (dutySchedule.find(day)!=dutySchedule.end()) {
			cout << "Дежурство на этот день уже назначено" << endl;
		}
		else {
			dutySchedule.insert(pair<int, DutyPair>(day, DutyPair(itDoc, itNur)));
			cout << "Дежурство добавлено" << endl;
		}
	}
}

void EditDuty(list<Doctor>& doctors, list<Nurse>& nurses, map<int, DutyPair>& dutySchedule) {
	int day;
	string dSur, nSur;
	ShowSchedule(dutySchedule);
	cout << "Введите день: " << endl;
	cin >> day;
	map<int, DutyPair>::iterator dutyToEdit = dutySchedule.find(day);
	if (dutyToEdit == dutySchedule.end()) {
		cout << "Дежурство в этот день не назначено" << endl;
	}
	else {
		cout << "Выберите поле для редактирования:" << endl;
		cout << "1. День" << endl;
		cout << "2. Врач" << endl;
		cout << "3. Медсестра" << endl;
		cout << "4. Выход" << endl;
		int menu;
		int working = 1;
		while (working) {
			cin >> menu;
			switch (menu)
			{
			case 1: {
				int newDay;
				cout << "Введите день: ";
				cin >> newDay;
				if (dutySchedule.find(newDay) == dutySchedule.end()) {
					Doctor doc = dutyToEdit->second.GetDoctor();
					Nurse nur = dutyToEdit->second.GetNurse();
					dutySchedule.erase(dutyToEdit);
					dutySchedule.insert(pair<int, DutyPair>(newDay, DutyPair(doc, nur)));
				}
				else {
					cout << "В этот день дежурство уже назначено" << endl;
				}
				working = 0;
				break;
			}
			case 2: {
				ShowDoctors(doctors);
				cout << "Введите фамилию врача: ";
				cin >> dSur;
				list<Doctor>::iterator it = doctors.begin();
				for (; it != doctors.end(); it++) {
					if (it->GetSurname() == dSur) break;
				}
				if (it != doctors.end()) {
					dutyToEdit->second.SetDoctor(*it);
				}
				else {
					cout << "Такого врача нет" << endl;
				}
				working = 0;
				break;
			}
			case 3: {
				ShowNurses(nurses);
				cout << "Введите фамилию медсестры: ";
				cin >> nSur;
				list<Nurse>::iterator it = nurses.begin();
				for (; it != nurses.end(); it++) {
					if (it->GetSurname() == nSur) break;
				}
				if (it != nurses.end()) {
					dutyToEdit->second.SetNurse(*it);
				}
				else {
					cout << "Такой медсестры нет" << endl;
				}
				working = 0;
				break;
			}
			default:
				working = 0;
				break;
			}

		}
	}
}

void DeleteDuty(map<int, DutyPair>& dutySchedule) {
	ShowSchedule(dutySchedule);
	cout << "Выберите дату для удаления: ";
	int day;
	cin >> day;
	map<int, DutyPair>::iterator dutyToDelete = dutySchedule.find(day);
	if (dutyToDelete != dutySchedule.end())
		dutySchedule.erase(dutyToDelete);
	else cout << "В этот день девурство не было назначено" << endl;
}

void DeleteDoctor(list<Doctor>& doctors, map<int, DutyPair>& dutySchedule) {
	ShowDoctors(doctors);
	string dSur;
	cout << "Введите фамилию врача: ";
	cin >> dSur;
	list<Doctor>::iterator it = doctors.begin();
	for (; it != doctors.end(); it++) {
		if (it->GetSurname() == dSur) break;
	}
	if (it != doctors.end()) {
		doctors.erase(it);
		map<int, DutyPair>::iterator iter = dutySchedule.begin();
		for (; iter != dutySchedule.end(); iter++) {
			if (iter->second.GetDoctor().GetSurname() == dSur) {
				dutySchedule.erase(iter);
				iter = dutySchedule.begin();
			}
		}
	}
	else {
		cout << "Такого врача нет" << endl;
	}
}

void DeleteNurse(list<Nurse>& nurses, map<int, DutyPair>& dutySchedule) {
	ShowNurses(nurses);
	string nSur;
	cout << "Введите фамилию медсестры: ";
	cin >> nSur;
	list<Nurse>::iterator it = nurses.begin();
	for (; it != nurses.end(); it++) {
		if (it->GetSurname() == nSur) break;
	}
	if (it != nurses.end()) {
		nurses.erase(it);
		map<int, DutyPair>::iterator iter = dutySchedule.begin();
		for (; iter != dutySchedule.end(); iter++) {
			if (iter->second.GetNurse().GetSurname() == nSur) {
				dutySchedule.erase(iter);
				iter = dutySchedule.begin();
			}
		}
	}
	else {
		cout << "Такой медсестры нет" << endl;
	}
}

void EditDoctor(list<Doctor>& doctors, map<int, DutyPair>& dutySchedule) {
	ShowDoctors(doctors);
	string dSur;
	cout << "Введите фамилию врача: ";
	cin >> dSur;
	list<Doctor>::iterator it = doctors.begin();
	for (; it != doctors.end(); it++) {
		if (it->GetSurname() == dSur) break;
	}
	if (it != doctors.end()) {
		map<int, DutyPair>::iterator iter = dutySchedule.begin();
		cout << "Выберите поле для редактирования:" << endl;
		cout << "1. Фамилия" << endl;
		cout << "2. Специализация" << endl;
		cout << "3. Выход" << endl;
		int menu;
		int working = 1;
		while (working) {
			cin >> menu;
			switch (menu)
			{
			case 1: {
				cout << "Введите новую фамилию: ";
				string surname;
				cin >> surname;
				it->SetSurname(surname);
				for (; iter != dutySchedule.end(); iter++) {
					if (iter->second.GetDoctor().GetSurname() == dSur) {
						iter->second.GetDoctor().SetSurname(surname);
					}
				}
				working = 0;
				break;
			}
			case 2: {
				cout << "Введите новую специализацию: ";
				string specialization;
				cin >> specialization;
				it->SetSpecialization(specialization);
				for (; iter != dutySchedule.end(); iter++) {
					if (iter->second.GetDoctor().GetSurname() == dSur) {
						iter->second.GetDoctor().SetSpecialization(specialization);
					}
				}
				working = 0;
				break;
			}
			default: {
				working = 0;
				break;
			}
			}
		}
	}
	else cout << "Такого врача нет" << endl;
}

void EditNurse(list<Nurse>& nurses, map<int, DutyPair>& dutySchedule) {
	ShowNurses(nurses);
	string nSur;
	cout << "Введите фамилию медсестры: ";
	cin >> nSur;
	list<Nurse>::iterator it = nurses.begin();
	for (; it != nurses.end(); it++) {
		if (it->GetSurname() == nSur) break;
	}
	if (it != nurses.end()) {
		map<int, DutyPair>::iterator iter = dutySchedule.begin();
		cout << "Выберите поле для редактирования:" << endl;
		cout << "1. Фамилия" << endl;
		cout << "2. Стаж" << endl;
		cout << "3. Выход" << endl;
		int menu;
		int working = 1;
		while (working) {
			cin >> menu;
			switch (menu)
			{
			case 1: {
				cout << "Введите новую фамилию: ";
				string surname;
				cin >> surname;
				it->SetSurname(surname);
				for (; iter != dutySchedule.end(); iter++) {
					if (iter->second.GetNurse().GetSurname() == nSur) {
						iter->second.GetNurse().SetSurname(surname);
					}
				}
				working = 0;
				break;
			}
			case 2: {
				cout << "Введите новый стаж: ";
				int experience;
				cin >> experience;
				it->SetExperience(experience);
				for (; iter != dutySchedule.end(); iter++) {
					if (iter->second.GetNurse().GetSurname() == nSur) {
						iter->second.GetNurse().SetExperience(experience);
					}
				}
				working = 0;
				break;
			}
			default: {
				working = 0;
				break;
			}
			}
		}
	}
	else cout << "Такого врача нет" << endl;

}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	list<Doctor> doctors;
	list<Nurse> nurses;
	map<int, DutyPair> dutySchedule;

	doctors.push_back(Doctor());
	doctors.push_back(Doctor("Мальцев", "гинеколог"));
	doctors.push_back(Doctor("Литов", "кардиолог"));
	doctors.push_back(Doctor("Санкович", "психиатр"));
	doctors.push_back(Doctor("Юрьева", "педиатр"));
	list<Doctor>::iterator pDoc = doctors.begin();

	nurses = {
		Nurse("Шальц", 2),
		Nurse("Шусев", 1),
		Nurse("Каспер", 3),
		Nurse("Кулак", 1),
		Nurse("Паркер", 1),
		Nurse("Харитонова", 5),
	};
	nurses.push_back(Nurse("Минькова", 2));
	nurses.push_back(Nurse("Когеев", 1));
	nurses.push_back(Nurse("Гудкова", 5));
	list<Nurse>::iterator pNur = nurses.begin();

	dutySchedule.insert(pair<int, DutyPair>(1, DutyPair()));
	dutySchedule.insert(pair<int, DutyPair>(2, DutyPair(doctors.front(), nurses.front())));
	dutySchedule.insert(pair<int, DutyPair>(3, DutyPair(pDoc, pNur)));
	advance(pDoc, 1);//2
	advance(pNur, 1);//2
	dutySchedule.insert(pair<int, DutyPair>(4, DutyPair(pDoc, pNur)));
	advance(pNur, 1);//3
	advance(pDoc, 1);//3
	dutySchedule.insert(pair<int, DutyPair>(5, DutyPair(pDoc, pNur)));
	advance(pNur, 1);//4
	advance(pDoc, 2);//5
	dutySchedule.insert(pair<int, DutyPair>(6, DutyPair(pDoc, pNur)));
	advance(pNur, 1);//5
	advance(pDoc, -1);//4
	dutySchedule.insert(pair<int, DutyPair>(7, DutyPair(pDoc, pNur)));
	advance(pNur, 1);//6
	advance(pDoc, -1);//3
	dutySchedule.insert(pair<int, DutyPair>(8, DutyPair(pDoc, pNur)));
	advance(pDoc, 2);//5
	advance(pNur, 1);//7
	dutySchedule.insert(pair<int, DutyPair>(9, DutyPair(pDoc, pNur)));
	advance(pDoc, -4);//1
	advance(pNur, 2);//9
	dutySchedule.insert(pair<int, DutyPair>(10, DutyPair(pDoc, pNur)));

	int menu;
	while (true)
	{
		cout << "+-------------------------------------------------------------+" << endl;
		cout << "| 1. Вывести список докторов                                  |" << endl;
		cout << "| 2. Вывести список медсестер                                 |" << endl;
		cout << "| 3. Вывести график дежурств на месяц (не все дни заняты)     |" << endl;
		cout << "| 4. Узнать, кто дежурит в определенный день                  |" << endl;
		cout << "| 5. Добавить дежурство                                       |" << endl;
		cout << "| 6. Редактировать существующее дежурство                     |" << endl;
		cout << "+-------------------------------------------------------------+" << endl;
		cout << "| 7. Добавить доктора                                         |" << endl;
		cout << "| 8. Добавить медсестру                                       |" << endl;
		cout << "| 9. Удалить дежурство                                        |" << endl;
		cout << "| 10. Удалить медсестру                                       |" << endl;
		cout << "| 11. Удалить доктора                                         |" << endl;
		cout << "| 12. Редактировать медсестру                                 |" << endl;
		cout << "| 13. Редактировать доктора                                   |" << endl;
		cout << "| 14. Выход                                                   |" << endl;
		cout << "+-------------------------------------------------------------+" << endl;
		cin >> menu;
		if (cin.fail()) {//если есть ошибка
			cin.clear();//Очистить биты ошибок
			cout << "Неправильный ввод данных\n";
		}

		switch (menu)
		{
		case 1: {
			ShowDoctors(doctors);
			break;
		}
		case 2: {
			ShowNurses(nurses);
			break;
		}
		case 3: {
			ShowSchedule(dutySchedule);
			break;
		}
		case 4:
		{
			ShowDayDuty(dutySchedule);
			break;
		}
		case 5:
		{
			AddDuty(doctors, nurses, dutySchedule);
			break;
		}
		case 6: {
			EditDuty(doctors, nurses, dutySchedule);
			break;
		}
		case 7: {
			AddDoctor(doctors);
			break;
		}
		case 8: {
			AddNurse(nurses);
			break;
		}
		case 9: {
			DeleteDuty(dutySchedule);
			break;
		}
		case 10: {
			DeleteNurse(nurses, dutySchedule);
			break;
		}
		case 11: {
			DeleteDoctor(doctors, dutySchedule);
			break;
		}
		case 12: {
			EditNurse(nurses, dutySchedule);
			break;
		}
		case 13: {
			EditDoctor(doctors, dutySchedule);
			break;
		}
		default:
		{
			return 0;
		}
		}
		system("pause");
		system("cls");
	}
}