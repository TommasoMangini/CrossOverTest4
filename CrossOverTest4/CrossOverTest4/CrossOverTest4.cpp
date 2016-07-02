// CrossOverTest4.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"

#include <iostream>

#include <array>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

#ifdef _WIN32
int wmain(int argc, wchar_t *args[])
#else
int main(int argc, char *args[])
#endif
{
	const int NumberOfLoops = 100;

	auto Task1 = pplx::create_task([=]
	{
		for (int i=0; i!=NumberOfLoops; i++)
		{ 			
			std::wcout << "Task1: " << i << std::endl;
		}

	});

	auto Task2 = pplx::create_task([=]
	{
		for (int i = 0; i != NumberOfLoops; i++)
		{
			std::wcout << "Task2: " << i << std::endl;
		}

	});

	//	(Task1 && Task1).wait(); // Parallel elaboration

	std::array<pplx::task<void>, 2> Tasks = {Task1, Task2 };


	//auto joinTask = when_all(begin(Tasks), end(Tasks));	// It finishes when all the tasks completes successfully

	//auto joinTask = when_any(begin(Tasks), end(Tasks));	// It finishes when any of the tasks completes successfully


	system("pause");
	return 0;
}

