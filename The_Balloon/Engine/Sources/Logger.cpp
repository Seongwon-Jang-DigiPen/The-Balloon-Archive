/*
File Name: Logger.cpp
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#include <iostream>
#include "../Headers/Logger.h"

DOG::Logger::Logger(Logger::Severity severity, std::chrono::system_clock::time_point start_t)
	:minLevel(severity), startTime(start_t)
{}
DOG::Logger::~Logger()
{}


void DOG::Logger::ShowProgress(std::string text, double current, double entire)
{
	system("cls");
	std::cout << text + "\n\n";

	double percentage = (double)current / entire * 100.0;
	for (int i = 0; i < 100; i += 10)
		i <= percentage ? std::cout << "бс" : std::cout << "бр";
	std::cout << std::endl;
	std::cout << percentage << " %" << std::endl;
}

void DOG::Logger::Log(DOG::Logger::Severity sev, std::string message)
{
	if (minLevel <= sev)
	{
		std::string label;

		switch (sev)
		{
		case DOG::Logger::Severity::Verbose: label = "Verb\t"; break;
		case DOG::Logger::Severity::Debug: label = "Debug\t"; break;
		case DOG::Logger::Severity::Event: label = "Event\t"; break;
		case DOG::Logger::Severity::Error: label = "Error\t"; break;
		default:
			break;
		}

		std::cout << label << message << std::endl;
	}
}

double DOG::Logger::GetElaspedTime() 
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	return std::chrono::duration<double>(now - startTime).count();
}