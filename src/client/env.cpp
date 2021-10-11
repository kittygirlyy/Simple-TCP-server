#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <Windows.h>
#include "env.h"



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                              ENV.cpp/ENV.h                                                     //             //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getuser() {

	std::string up, pa;
	up = getenv("USERPROFILE");
	pa = getenv("PATH");
	std::cout << "[" << pa << "&" << "up" << "]";
}



