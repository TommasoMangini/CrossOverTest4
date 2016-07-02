// CrossOverTest4.cpp : definisce il punto di ingresso dell'applicazione console.
//

#include "stdafx.h"

#include <iostream>

#include <array>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include <pplx/pplxtasks.h>

using namespace concurrency;
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
	pplx::cancellation_token_source cts;
	auto token = cts.get_token();
	

	auto Task1 = pplx::create_task([=]
	{
		bool moreToDo = true;
		int i = 0;
		while (moreToDo)
		{
			// Check for cancellation.			
			if (token.is_canceled())
			// if (pplx:: is_task_cancellation_requested())	// It doesn't compile on visual studio 2015. Deprecated
			{
				// TODO: Perform any necessary cleanup here...

				// Cancel the current task.
				cancel_current_task();
			}
			else
			{
				// Perform work.								
				std::wcout << "Task1: " << i++ << std::endl;				
				moreToDo = true;
			}
		}		

	}, token);

	//auto Task2 = pplx::create_task([=]
	//{
	//	for (int i = 0; i != NumberOfLoops; i++)
	//	{
	//		std::wcout << "Task2: " << i << std::endl;
	//	}

	//});	

	// Wait for one second and then cancel the task.
	::wait(1000);

	std::wcout << L"Canceling task..." << std::endl;
	cts.cancel();

	//// Wait for the task to cancel.
	//std::wcout << L"Waiting for task to complete..." << std::endl;
	//Task1.wait();

	std::wcout << L"Done." << std::endl;

	//std::array<pplx::task<void>, 2> Tasks = {Task1, Task2 };


	//auto joinTask = when_all(begin(Tasks), end(Tasks));	// It finishes when all the tasks completes successfully
	//	(Task1 && Task1).wait(); // Parallel elaboration equivalent

	//auto joinTask = when_any(begin(Tasks), end(Tasks));	// It finishes when any of the tasks completes successfully


	system("pause");
	return 0;
}

