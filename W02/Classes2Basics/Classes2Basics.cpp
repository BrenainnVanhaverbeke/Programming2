//Brenainn Vanhaverbeke - 1DAEGD10

#include "pch.h"
#include "Classes2Basics.h"
#include "Time.h"
#include "Square.h"
#include "Container.h"
#include <iostream>

int main()
{
	TestSquares();
	TestTimes();
	TestContainer();
}

void TestSquares()
{
	std::cout << "--> Squares with constructor delegation";
	Square* square1{ new Square(10.0f) };
	Square* square2{ new Square{10.0f, 20.0f, 20.0f} };
	square1->Print();
	square2->Print();
	delete square1;
	square1 = nullptr;
	delete square2;
	square2 = nullptr;
	std::cout << std::endl;
}

void TestTimes()
{
	std::cout << "Comparing Time objects" << std::endl;
	PrintInstancesCntr("Calling before Time object creation");
	Time* time1{ new Time{20, 30, 11} };
	Time* time2{ new Time{20, 30, 11} };
	PrintInstancesCntr("Calling halfway through object creation");
	Time* time3{ new Time{40, 15, 8} };
	Time* time4{ new Time{45, 20, 20} };
	CompareTimes(time1, time2);
	CompareTimes(time2, time3);
	PrintInstancesCntr("Calling after comparisons");
	delete time1;
	time1 = nullptr;
	delete time2;
	time2 = nullptr;
	PrintInstancesCntr("Calling after partial deletions");
	delete time3;
	time3 = nullptr;
	std::cout << std::endl;
	PrintInstancesCntr("Calling after deletions");
}

void CompareTimes(const Time* t1, const Time* t2)
{
	t1->Print();
	t2->Print();
	if (t1->GetHours() == t2->GetHours() && t1->GetMinutes() == t2->GetMinutes() && t1->GetSeconds() == t2->GetSeconds())
		std::cout << "Time objects are equal." << std::endl;
	else
		std::cout << "Time objects aren't equal." << std::endl;
}

void PrintInstancesCntr(const std::string& message)
{
	std::cout << message << ", number of Time objects: " << Time::GetNrInstances() << std::endl;
}

void TestContainer()
{
	std::cout << "\n-- Container tests --\n";
	// Define a Container object
	const int cap{ 5 };
	std::cout << "Create container with capacity of " << cap << " elements\n";
	Container* pContainer{ new Container{cap} };
	PrintContainer(pContainer);

	// Add some values to the container
	int actNr{ 0 };
	std::cout << "\nPush back of " << (cap - 1) << " elements\n";
	for (int idx{ 1 }; idx < cap; ++idx)
	{
		pContainer->PushBack(rand() % 21);
		++actNr;
	}
	PrintContainer(pContainer);

	std::cout << "\nChange the value of the elements (using Set)\n";
	for (int idx{ 0 }; idx < actNr; ++idx)
	{
		pContainer->Set(idx, rand() % 21);
	}
	PrintContainer(pContainer);

	std::cout << "\nPush back another " << (cap - 1) << " elements\n";
	for (int i{ 1 }; i < cap; ++i)
	{
		pContainer->PushBack(rand() % 21);
		++actNr;
	}
	PrintContainer(pContainer);
	delete pContainer;
}

void PrintContainer(const Container* pContainer)
{
	std::cout << "-- Print container --\n";
	std::cout << "   Capacity: " << pContainer->Capacity() << std::endl;
	std::cout << "   Size: " << pContainer->Size() << std::endl;
	std::cout << "   Get the elements (using Get and Size)\n   ";
	for (int idx{ 0 }; idx < pContainer->Size(); ++idx)
	{
		std::cout << pContainer->Get(idx) << " ";
	}
	std::cout << std::endl;
}

