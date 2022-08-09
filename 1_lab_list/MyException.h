#pragma once
#include <iostream>
#include <string>

using namespace std;

class MyException : public exception {
public:
	MyException(const char* msg) : message(msg) {};
	const char* what() {
		return message;
	}
private:
	const char* message;
};
