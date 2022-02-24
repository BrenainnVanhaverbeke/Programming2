#pragma once
#include <string>

class Time;
class Container;

void TestSquares();
void TestTimes();
void CompareTimes(const Time* t1, const Time* t2);
void PrintInstancesCntr(const std::string& message);
void TestContainer();
void PrintContainer(const Container* c);