/* ************************************************************************************************************************************************ *\

	Related:
		Flyweight = stateless behavior, singleton command
		Chain of Responsibility = obj receives commands, may pass commands on to other obj
		Subclass Sandbox = execute() method defined in many concrete base classes, compose to define behavior

\* ************************************************************************************************************************************************ */
#pragma once

#include "stdafx.h"
#include "QtHeaders.h"

namespace Examples
{
	template<typename T>
	class Editor
	{
		T& data;

		Editor() = delete;
		Editor(const T&) = delete;
		T& operator=(const T&) = delete;
		T& operator=(T&&) = delete;

	public:
		Editor(T&& d) : data(d) {}
		~Editor() = default;

		void setStr(std::string in)
		{
			// some command to Qt like data->getWidget(0)->setText();
		}

		std::string getStr()
		{
			return std::string{"getStr"};
		}
	};
}

namespace DP
{
	template<typename T>
	class Command
	{
	public:
		virtual void execute(T&&) = 0;
		virtual void undo() = 0;
		virtual void redo() = 0;
	};

	template <typename T>
	class WriteCommand : public Command<std::string>
	{
		T& editor;
		std::string oldStr{};
		std::string newStr{};

		WriteCommand() = delete;
		WriteCommand(const T&) = delete;
		T& operator=(const T&) = delete;
		T& operator=(T&&) = delete;

	public:
		WriteCommand(T&& e) : editor(e) {}
		~WriteCommand() = default;

		void execute(std::string&& inputStr)
		{
			oldStr = editor->getStr();
			std::swap(newStr, inputStr);
			editor->setStr(newStr);
		}

		void undo()
		{
			editor->setStr(oldStr);
		}

		void redo()
		{
			editor->setStr(newStr);
		}
	};
}

namespace Examples
{
	template<typename T>
	class TextEditor
	{
		std::list<std::unique_ptr<DP::WriteCommand<T*>>> history;
		T editor;

		TextEditor() = delete;
		TextEditor(const T&) = delete;
		T& operator=(const T&) = delete;
		T& operator=(T&&) = delete;

	public:
		TextEditor(T&& e) : editor(e) {}
		~TextEditor() = default;

		void InputHandler(std::string&& inputStr)
		{
			// get a string being modified, save it, then modify it
			auto& iter = history.emplace_back(std::make_unique<DP::WriteCommand<T*>>(&editor));
			iter->execute(std::forward<std::string>(inputStr));
		}
	};
}
