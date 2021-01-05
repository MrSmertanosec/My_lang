#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "My_type.h"

bool was_if = false; // check if currently in IF
bool was_else = false; // check if currently in ELSE
bool condition = true; // check if condition is true or false
bool condition_loop = true; // check if condition set by loop is true or false
bool loop_commands = false; // check if all commands of loop are saved and can be used again
bool was_loop = false; // check if currently in LOOP
std::vector<std::string> lines; //saved loop commands

void my_main(std::string& line)
{
	if (loop_commands)
	{
		lines.push_back(line);
	}

	if (line == "loop end")
	{
		loop_commands = false;

		if (was_loop)
		{
			my_main(lines[0]);
		}

		was_loop = false;
		return;
	}

	if (line.empty())
	{
		if (was_else)
		{
			condition = true;
		}

		
		was_if = false;
		was_else = false;

		return;
	}

	std::vector<std::string> words;



	if ((was_if && !condition) || (was_else && condition))
	{
		return;
	}

	if (was_loop && !condition_loop)
	{
		return;
	}

	get_words(words, line); // separating line into words

	if (words[0] == "var")
	{
		create_var(words); // declaring variable
	}
	
	if (was_declared(words[0]) || words[0] == "inc" || words[0] == "dec")
	{
		assign_variable(words); // initializing variable
	}

	if (words[0] == "print")
	{
		if (words[1][0] == '"' && words[words.size() - 1][words[words.size() - 1].size() - 1] == '"') // print text
		{
			std::string output = line.substr(7, line.size() - 8);
			std::cout << output;
		}

		if (was_declared(words[1])) // print variable value
		{
			print_var(words[1]);
		}
	}

	if (words[0] == "endl")
	{
		std::cout << "\n";
	}

	if (words[0] == "if")
	{
		was_if = true;

		if (check_condition(words)) // checking condition for if
		{
			condition = true;
			return;
		}
		else
		{
			condition = false;
			return;
		}
	
	}

	if (words[0] == "else")
	{
		was_else = true;
		return;
	}

	if (words[0] == "loop")
	{
		if (check_condition(words)) // checking condition for loop
		{
			if (lines.empty())
			{
				loop_commands = true;
				was_loop = true;
				lines.push_back(line);
				return;
			}

			condition_loop = true;

			for (int i = 1; i < lines.size(); ++i)
			{
				my_main(lines[i]);
			}
		}
		else
		{
			condition_loop = false;
			return;
		}
	}

}

////////////////////////////////////////////////////////

int main(int argc, char** argv)
{
	std::string line;
	std::ifstream My_file;

	if (argv[1] == nullptr)
	{
		std::cout << "Unable to execute: Wrong path or file format\n";
		return 0;
	}

	My_file.open(argv[1]);

	if (My_file.is_open())
	{
		while (std::getline(My_file, line))
		{
			my_main(line); // passing line
		}

		if (line != "end")
		{
			std::cout << "The program should finish with ""end"" keyword";
		}

		My_file.close();
	}

	return 0;
}