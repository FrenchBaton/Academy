#pragma once

enum MENU {
	EXIT,
	SHOW_LIST,
	SEARCH_BY_NAME,
	SEARCH_BY_ID,
	SORT_BY_NAME,
	SORT_BY_ID,
	SORT_BY_AVERAGE,
	DEL_STUDENT,
	ADD_STUDENT
};

Student createStudent(){
	Student std{};
	static uint id = 100;
	std.id = id++;

	const int N = 20;
	char n[N];
	cout << "Enter name: ";
	cin.getline(n, N);
	std.name = new char[strlen(n) + 1];
	strcpy_s(std.name, strlen(n) + 1, n);
	//cin.ignore();

	cout << "Enter average: ";
	cin >> std.average;

	cout << "Enter birthdayDate (year month day): ";
	cin >> std.birthdayDate.year;
	cin >> std.birthdayDate.month;
	cin >> std.birthdayDate.day;

	cout << "\n";
	return std;
}


void clearNames(Student*& students, uint size) {
	for (uint i = 0; i < size; i++) {
		delete[] students[i].name;
	}
}

void clear(Student*& students, uint size) {
	clearNames(students, size);
	delete[] students;
}

void showStudent(const Student& std) {
	cout << std.id << '\t'
		<< std.name << '\t'
		<< std.average << '\t'
		<< std.birthdayDate.day << '.'
		<< std.birthdayDate.month << '.'
		<< std.birthdayDate.year << endl;
}

void showListOfStudents(Student*& students, uint size) {
	cout << "id" << '\t'
		<< "name" << '\t'
		<< "average" << '\t'
		<< "day" << '.'
		<< "month" << '.'
		<< "year" << endl;
	for (uint i = 0; i < size; i++) {
		showStudent(students[i]);
	}
}

uint searchId(Student*& students, uint size, uint id) {
	for (uint i = 0; i < size; i++) {
		if (students[i].id == id) {
			return i;
		}
	}
	cout << "Not found" << endl;
	return size;
}

void searchByIdAction(Student*& students, uint size) {
	uint input_int;
	do {
		cout << "Enter id(0 - Exit): ";
		cin >> input_int;
		if (input_int != 0 && searchId(students, size, input_int) != size) {
			showStudent(students[searchId(students, size, input_int)]);
		}
	} while (input_int != 0);
}

void searchByName(Student*& students, uint size, char* name) {
	for (uint i = 0; i < size; i++) {
		if (strcmp(students[i].name, name) == 0) {
			showStudent(students[i]);
			return;
		}
	}
	cout << "Not found" << endl;
}

void searchByNameAction(Student*& students, uint size) {
	cin.ignore();
	const int MAX_SIZE_INPUT_STR = 20;
	char input_char[MAX_SIZE_INPUT_STR];


	cout << "Enter name(\"ex\" - Exit): ";
	cin.getline(input_char, MAX_SIZE_INPUT_STR);
	while (strcmp(input_char, "ex") != 0) {
		searchByName(students, size, input_char);
		cout << "Enter name(\"ex\" - Exit): ";
		cin.getline(input_char, MAX_SIZE_INPUT_STR);
	}
}

//void sorting(Student*& students, uint size,void(*sort)(Student* students, uint size)) {
//	sort(students, size);
//
//}

void sortByName(Student*& students, uint size) {
	for (uint i = 0; i < size - 1; i++) {
		for (uint j = 0; j < size - 1 - i; j++) {
			if (strcmp(students[j].name, students[j + 1].name) > 0) {
				swap(students[j], students[j + 1]);
			}
		}
	}
}

void sortById(Student*& students, uint size) {
	for (uint i = 0; i < size - 1; i++) {
		for (uint j = 0; j < size - 1 - i; j++) {
			if (students[j].id > students[j + 1].id) {
				swap(students[j], students[j + 1]);
			}
		}
	}
}

void sortByAverage(Student* students, uint size) {
	for (uint i = 0; i < size - 1; i++) {
		for (uint j = 0; j < size - 1 - i; j++) {
			if (students[j].average < students[j + 1].average) {
				swap(students[j], students[j + 1]);
			}
		}
	}
}

void addStudent(Student*& students, uint& size)
{
	Student* students_upd = new Student[size + 1];
	for (int i = 0; i < size; i++)
	{
		students_upd[i] = students[i];
	}
	students_upd[size] = createStudent();
	size++;
	delete[] students;
	students = students_upd;
	showListOfStudents(students, size);
}

void delStudent(Student*& students, uint& size)
{
	if (size-1 == 0) { 
		delete[] students;
		students = nullptr;
		size--;
		return; 
	}
	uint input_int;
	cout << "Enter id: ";
	cin >> input_int;
	if (searchId(students, size, input_int) != size) {
		uint idx = searchId(students, size, input_int);
		Student* students_upd = new Student[size - 1];
		for (int i = 0; i < size-1; i++)
		{
			students_upd[i] = (idx != i) ? (students[i]) : (students[size - 1]);
		}
		size--;
		delete[] students;
		students = students_upd;
		sortById(students, size);
	}
	showListOfStudents(students, size);
}

void action() {
	static uint size;
	static Student* students;
	
	uint input_int;
	while (true) {
		cout << "What do you want to do?" << endl;
		cout << "(Exit - " << EXIT
			<< ", Show list of students - " << SHOW_LIST
			<< ", Search by name - " << SEARCH_BY_NAME
			<< ", Search by ID - " << SEARCH_BY_ID
			<< ", Sort by name - " << SORT_BY_NAME
			<< ", Sort by id - " << SORT_BY_ID
			<< ", Sort by average - " << SORT_BY_AVERAGE
			<< ", Delete a student - " << DEL_STUDENT
			<< ", Add a student - " << ADD_STUDENT
			<< " )" << endl;
		
		cin >> input_int;
		cin.ignore();
		switch (input_int) {
		case EXIT:
			clear(students, size);
			return;
			break;
		case SHOW_LIST:
			if (size == 0) { break; }
			showListOfStudents(students, size);
			cout << "\n";
			break;
		case SEARCH_BY_NAME:
			if (size == 0) { break; }
			searchByNameAction(students, size);
			cout << "\n";
			break;
		case SEARCH_BY_ID:
			if (size == 0) { break; }
			searchByIdAction(students, size);
			cout << "\n";
			break;
		case SORT_BY_NAME:
			if (size == 0) { break; }
			sortByName(students, size);
			cout << "\n";
			break;
		case SORT_BY_ID:
			if (size == 0) { break; }
			sortById(students, size);
			cout << "\n";
			break;
		case SORT_BY_AVERAGE:
			if (size == 0) { break; }
			sortByAverage(students, size);
			cout << "\n";
			break;
		case DEL_STUDENT:
			if (size == 0) { break; }
			delStudent(students, size);
			cout << "\n";
			break;
		case ADD_STUDENT:
			addStudent(students, size);
			cout << "\n";
			break;
		default:
			cout << "Error. Try again" << endl;
			break;
		}
		
	}
}