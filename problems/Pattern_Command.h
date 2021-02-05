/* ************************************************************************************************************************************************ *\

	Related:
		Flyweight = stateless behavior, singleton command
		Chain of Responsibility = obj receives commands, may pass commands on to other obj
		Subclass Sandbox = execute() method defined in many concrete base classes, compose to define behavior

\* ************************************************************************************************************************************************ */
#pragma once

#include "stdafx.h"
//#include "QtHeaders.h"

namespace Examples
{
	template<typename T>
	class Editor
	{
		T& data;

		using type = T;

		Editor() = delete;
		Editor(const T&) = delete;
		T& operator=(const T&) = delete;
		T& operator=(T&&) = delete;

	public:
		Editor(T&& d) : data(d) {}
		~Editor() = default;

		template<typename U>
		requires std::is_convertible_v<U, std::string>
		void set(U&& in)
		{
			// some command to Qt like data->getWidget(0)->setText();
			in = std::string{"implementSetTODO"};
		}

		template<typename U>
		requires std::is_convertible_v<U, std::string>
		U get()
		{
			return std::string{"implementGetTODO"};
		}
	};
}

namespace DP
{
	template<typename T>
	class Command
	{
	public:
		virtual ~Command() = default;

		virtual void execute(T&&) = 0;
		virtual void undo() = 0;
		virtual void redo() = 0;
	};

	template <typename T, typename U>
	requires std::is_convertible_v<U, std::string>
	class WriteCommand final : public Command<U>
	{
		// each command object holds a reference to the one editor object stored in the commander
		// might be better to have it as a shared_ptr, so this command obj could be given to other commanders
		// with a shared_ptr in the commander, passing another shared_ptr out with the command obj
		// otherwise these reference addresses could become invalidated
		// OR does the new commander want to change the editor anyway?
		T& editor;
		U oldValue{};
		U newValue{};

		WriteCommand() = delete;
		WriteCommand(const T&) = delete;
		T& operator=(const T&) = delete;
		T& operator=(T&&) = delete;

	public:
		WriteCommand(T&& e) : editor(e) {}
		~WriteCommand() = default;

		virtual void execute(U&& in) override
		{
			oldValue = editor->get<U>();
			newValue = in;
			editor->set<U>(std::forward<U>(in));
		}

		virtual void undo() override
		{
			editor->set<U>(U{oldValue});
		}

		virtual void redo() override
		{
			editor->set<U>(U{newValue});
		}
	};
}

namespace Examples
{
	template<typename T>
	requires std::is_same_v<T, Editor<typename T::type>>
	class TextEditor
	{
		std::list<std::unique_ptr<DP::WriteCommand<T*, std::string>>> history;
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
			auto& iter = history.emplace_back(std::make_unique<DP::WriteCommand<T*, std::string>>(&editor));
			iter->execute(std::forward<std::string>(inputStr));
		}
	};
}
