#include "pch.h"
#include "DAEStudent.h"
#include <iostream>

DAEStudent::DAEStudent(const std::string& firstName, const std::string& lastName, Major major)
	: Person(firstName, lastName)
	, m_Major{ major }
{
	std::cout << "Student Constructor\n";
}

DAEStudent::~DAEStudent()
{
	std::cout << "Student Destructor\n";
}

void DAEStudent::Identify() const
{
	std::cout << "I am a derived class DAEStudent object. My name is " << GetName();
}

std::string DAEStudent::GetName() const
{
	std::string name{ Person::GetName() };
	name += " and my major is " + GetMajorString();
	name += "\n";
	return name;
}

std::string DAEStudent::GetMajorString() const
{
	switch (m_Major)
	{
	case DAEStudent::Major::GD:
		return "GD";
	case DAEStudent::Major::SD:
		return "SD";
	case DAEStudent::Major::GGP:
		return "GGP";
	case DAEStudent::Major::VFX:
		return "VFX";
	case DAEStudent::Major::IGP:
		return "IGP";
	case DAEStudent::Major::ANIM:
		return "ANIM";
	default:
		return "Error";
	}
}
