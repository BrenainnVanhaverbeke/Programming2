#pragma once
#include "Person.h"

class DAEStudent final : public Person
{

public:
	enum class Major
	{
		GD,
		SD,
		GGP,
		VFX,
		IGP,
		ANIM,
		ENUMEND
	};

	DAEStudent(const std::string& firstName,
		const std::string& lastName, Major major);
	~DAEStudent();

	void Identify() const;
	std::string GetName() const;

private:
	Major m_Major;
	std::string GetMajorString() const;
};