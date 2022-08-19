/*
File Name: Logger.h
Project Name: The balloon
Author(s)
Main: Hyunjin Kim
All content 2021 DigiPen (USA) Corporation, all rights reserved.
 */
#pragma once
#include <chrono>
#include <string>
//#include <fstream>

namespace DOG 
{
	class Logger
	{
	public:
		enum class Severity { Verbose, Debug, Event, Error };

		Logger(Severity severity, std::chrono::system_clock::time_point start_t);
		~Logger();

		void LogError(std::string text) { Log(Severity::Error, text); }
		void LogEvent(std::string text) { Log(Severity::Event, text); }
		void LogDebug(std::string text) { Log(Severity::Debug, text); }
		void LogVerbose(std::string text) { Log(Severity::Verbose, text); }
		void ShowProgress(std::string text, double current, double entire);

	private:
		void Log(Severity, std::string message);

		Severity minLevel;

		std::chrono::system_clock::time_point startTime;
		double GetElaspedTime();
	};
}