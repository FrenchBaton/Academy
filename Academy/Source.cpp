#include <iostream>
using namespace std;
#include "struct.h"
#include "function.h"



int main() {
	/*Student s1 = createStudent();
	Student s2 = createStudent();
	showStudent(s1);
	showStudent(s2);*/

	uint size;
	cout << "Enter size: ";
	cin >> size;

	Student* students = new Student[size];

	for (uint i = 0; i < size; i++) {
		students[i] = createStudent();
	}
	cout << "\n";
	action(students, size);


	cout << "\n";
	

	clear(students, size);
	return 0;
}