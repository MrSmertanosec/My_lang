#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include "My_type.h"

bool was_if = false;
bool was_else = false;
bool condition = true;
bool condition_loop = true;
bool loop_commands = false;
bool was_loop = false;
std::vector<std::string> lines;

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

	get_words(words, line);

	if (words[0] == "var")
	{
		create_var(words);
	}
	
	if (was_declared(words[0]) || words[0] == "inc" || words[0] == "dec")
	{
		assign_variable(words);
	}

	if (words[0] == "print")
	{
		if (words[1][0] == '"' && words[words.size() - 1][words[words.size() - 1].size() - 1] == '"')
		{
			std::string output = line.substr(7, line.size() - 8);
			std::cout << output;
		}

		if (was_declared(words[1]))
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

		if (check_condition(words))
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
		if (check_condition(words))
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

//int main(int argc, char** argv)
int main()
{
	std::string line;
	std::ifstream My_file;

	//if (argv[1] == nullptr)
	//{
	//	std::cout << "Unable to execute: Wrong path or file format\n";
	//	return 0;
	//}

	//My_file.open(argv[1]);
	My_file.open("C:\\Users\\yegan\\Desktop\\My_lang.txt");

	if (My_file.is_open())
	{
		while (std::getline(My_file, line))
		{
			my_main(line);
		}

		if (line != "end")
		{
			std::cout << "The program should finish with ""end"" keyword";
		}

		//get_variables();

		My_file.close();
	}

	return 0;
}