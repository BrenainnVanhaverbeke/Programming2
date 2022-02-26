// 1DAE GD10 - Brenainn Vanhaverbeke

#include "pch.h"
#include "main.h"
#include <iostream>
#include "Person.h"
#include "DAEStudent.h"

int main()
{
	Person* pPerson{ new Person("Mashed", "Potato") };
	pPerson->Identify();
	delete pPerson;
	std::cout << "\n\n";

	DAEStudent* pStudent{ new DAEStudent("Lick", "DeezNuts", DAEStudent::Major::GD) };
	pStudent->Identify();
	delete pStudent;
	pStudent = nullptr;
	std::cout << "\n\n";

	//Polymorphism

	pPerson = new DAEStudent("Nibble", "DeezNuts", DAEStudent::Major::GGP);
	pPerson->Identify();
	delete pPerson;
	pPerson = nullptr;
}