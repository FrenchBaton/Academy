#pragma once

enum MENU {
	EXIT,
	SHOW_LIST,
	SEARCH_BY_NAME,
	SEARCH_BY_ID,
	SORT_BY_NAME,
	SORT_BY_AVERAGE,
	ADD_STUDENT
};

Student createStudent(){
	cin.ignore();

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

void searchById(Student*& students, uint size, uint id) {
	for (uint i = 0; i < size; i++) {
		if (students[i].id == id) {
			showStudent(students[i]);
			return;
		}
	}
	cout << "Not found" << endl;
}

void searchByIdAction(Student*& students, uint size) {
	cin.ignore();
	uint input_int;
	cout << "Enter id(0 - Exit): ";
	cin >> input_int;
	while (input_int != 0) {
		searchById(students, size, input_int);
		cout << "Enter id(0 - Exit): ";
		cin >> input_int;
	}
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

void sorting(Student*& students, uint size,void(*sort)(Student* students, uint size)) {
	sort(students, size);

}

void sortByName(Student*& students, uint size) {
	for (uint i = 0; i < size - 1; i++) {
		for (uint j = 0; j < size - 1 - i; j++) {
			if (strcmp(students[j].name, students[j+1].name) > 0) {
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
			<< ", Sort by average - " << SORT_BY_AVERAGE
			<< ", Add a student - " << ADD_STUDENT
			<< " )" << endl;
		
		cin >> input_int;
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
		case SORT_BY_AVERAGE:
			if (size == 0) { break; }
			sortByAverage(students, size);
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
		cin.ignore();
	}
}