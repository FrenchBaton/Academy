#include <iostream>
using namespace std;
#include "struct.h"
#include "function.h"



int main() {
	uint size;
	cout << "Enter size: ";
	cin >> size;

	Student* students = new Student[size];

	for (uint i = 0; i < size; i++) {
		students[i] = createStudent();
	}
	cout << "\n";
	action(students, size);
	return 0;
}