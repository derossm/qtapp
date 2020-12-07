/* ************************************************************************************************************************************************ *\

	Related:
		Flyweight = stateless behavior, singleton command
		Chain of Responsibility = obj receives commands, may pass commands on to other obj
		Subclass Sandbox = execute() method defined in many concrete base classes, compose to define behavior

\* ************************************************************************************************************************************************ */
#pragma once

#include "stdafx.h"

namespace DP
{
class Command
{
public:
	virtual ~Command() {}

	virtual void execute() = 0;
	virtual void undo() = 0;
};

class WriteCommand : public Command
{
	std::string oldStr;

public:
	void execute(std::string&& inputStr) {}
	void undo () {}
};
}

namespace Examples
{
class TextEditor
{
	std::list<std::unique_ptr<DP::Command>> history;

	std::string InputHandler(std::string&& inputStr)
	{
		// get a string being modified, save it, then modify it
		auto write = std::make_unique<DP::WriteCommand>();
		std::string outputStr = write->execute(std::forward(inputStr));
		history.push_back(write);
		return outputStr;
	}
};
}
