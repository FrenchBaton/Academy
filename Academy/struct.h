#pragma once

typedef unsigned int uint;
typedef unsigned short ushort;

struct Date
{
	ushort day;
	ushort month;
	ushort year;
};

struct Student
{
	uint id;
	float average;
	Date birthdayDate;
	char* name;
};
