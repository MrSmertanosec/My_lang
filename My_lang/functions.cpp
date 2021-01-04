#include <iostream>
#include <vector>
#include <string>
#include "My_type.h"

std::vector<My_type*> variables;

void get_words(std::vector<std::string>& words, const std::string& line)
{
	for (int i = 0, last_space = -1; i < line.size(); ++i)
	{
		if (isspace(line[i]) || i == line.size() - 1)
		{
			if (i == line.size() - 1)
			{
				words.push_back(line.substr(last_space + 1, i - last_space));
				return;
			}

			if (last_space == -1)
			{
				words.push_back(line.substr(last_space + 1, i));
			}
			else
			{
				words.push_back(line.substr(last_space + 1, i - last_space - 1));
			}

			last_space = i;
		}
	}

}

void separate_with_comma(std::vector<std::string>& var_arr, const std::string word)
{
	int last_comma = -1;

	for (int i = 0; i <= word.size(); ++i)
	{
		if (word[i] == ',')
		{
			if (last_comma == -1)
			{
				var_arr.push_back(word.substr(last_comma + 1, i));
			}
			else
			{
				std::string variable = word.substr(last_comma + 1, i - last_comma - 1);
				var_arr.push_back(variable);
			}

			last_comma = i;
		}

	}

	var_arr.push_back(word.substr(last_comma + 1, word.size() - last_comma - 1));
	
}

bool was_declared(const std::string& word)
{
	for (int j = 0; j < variables.size(); ++j)
	{
		if (variables[j]->get_name() == word)
		{
			return true;
		}

	}

	return false;
}

int find_by_name(const std::string& name)
{
	for (int j = 0; j < variables.size(); ++j)
	{
		if (variables[j]->get_name() == name)
		{
			return j;
		}

	}
}

std::string check_type(const std::string& value)
{
	bool is_double = false;

	if (value.size() == 1 && value[0] == '.')
	{
		return "string";
	}

	for (int i = 0; i < value.size(); ++i)
	{
		if ((value[i] < '0' || value[i] > '9') && value[i] != '.')
		{
			return "string";
		}

		if (value[i] == '.')
		{
			is_double = true;
		}
	}

	if (is_double)
	{
		return "double";
	}
	else
	{
		return "int";
	}
}

void create_var(const std::vector<std::string>& words)
{
	std::vector<std::string> var_arr;

	separate_with_comma(var_arr, words[1]);
	
	for (int i = 0; i < words.size(); ++i)
	{
		if (words[i] == "=")
		{
			std::string type = check_type(words[i + 1]);

			if (!was_declared(var_arr[0]))
			{
				variables.push_back(new My_type(var_arr[0], type, words[i + 1]));
			}
		}
	}
	
	if (var_arr.size() >= 1)
	{
		for (int i = 0; i < var_arr.size(); ++i)
		{
			if (!was_declared(var_arr[i]))
			{
				variables.push_back(new My_type(var_arr[i]));
			}

		}
	}




}

void add(int c, int a, int b) // c = a + b
{
	if (variables[a]->get_type() == "string" || variables[b]->get_type() == "string")
	{
		variables[c]->set_type("string");
		variables[c]->set_value(variables[a]->get_value() + variables[b]->get_value());

		return;
	}

	if (variables[a]->get_type() == "double" || variables[b]->get_type() == "double")
	{
		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(std::stod(variables[a]->get_value()) + std::stod(variables[b]->get_value())));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) + std::stoi(variables[b]->get_value())));


}

void add_with_numbers(int c, int a, int num) // c = a + num
{
	if (variables[a]->get_type() == "string")
	{
		variables[c]->set_type("string");
		variables[c]->set_value(variables[a]->get_value() + std::to_string(num));

		return;
	}

	if (variables[a]->get_type() == "double")
	{
		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(std::stod(variables[a]->get_value()) + num));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) + num));


}

void sub(int c, int a, int b) // c = a - b
{
	if (variables[a]->get_type() == "string" || variables[b]->get_type() == "string")
	{
		return;
	}

	if (variables[a]->get_type() == "double" || variables[b]->get_type() == "double")
	{
		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(std::stod(variables[a]->get_value()) - std::stod(variables[b]->get_value())));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) - std::stoi(variables[b]->get_value())));

}

void sub_with_numbers(int c, int a, int num) // c = a - num
{
	if (variables[a]->get_type() == "double")
	{

		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(std::stod(variables[a]->get_value()) - num));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) - num));


}

void sub_with_numbers_rev(int c, int num, int b) // c = num - b
{
	if (variables[b]->get_type() == "double")
	{

		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(num - std::stod(variables[b]->get_value())));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(num - std::stoi(variables[b]->get_value())));

}

void mul(int c, int a, int b) // c = a * b
{
	if (variables[a]->get_type() == "string" || variables[b]->get_type() == "string")
	{
		return;
	}

	if (variables[a]->get_type() == "double" || variables[b]->get_type() == "double")
	{
		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(std::stod(variables[a]->get_value()) * std::stod(variables[b]->get_value())));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) * std::stoi(variables[b]->get_value())));

}

void mul_with_numbers(int c, int a, int num) // c = a * num
{
	if (variables[a]->get_type() == "string")
	{
		return;
	}

	if (variables[a]->get_type() == "double")
	{
		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(std::stod(variables[a]->get_value()) * num));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) * num));


}

void div(int c, int a, int b) // c = a / b
{
	if (variables[a]->get_type() == "string" || variables[b]->get_type() == "string")
	{
		return;
	}

	if (variables[a]->get_type() == "double" || variables[b]->get_type() == "double")
	{
		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(std::stod(variables[a]->get_value()) / std::stod(variables[b]->get_value())));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) / std::stoi(variables[b]->get_value())));

}

void div_with_numbers(int c, int a, int num) // c = a / num
{
	if (variables[a]->get_type() == "double")
	{

		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(std::stod(variables[a]->get_value()) / num));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) / num));


}

void div_with_numbers_rev(int c, int num, int b) // c = num / b
{
	if (variables[b]->get_type() == "double")
	{

		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(num / std::stod(variables[b]->get_value())));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(num / std::stoi(variables[b]->get_value())));

}

void remainder(int c, int a, int b) // c = a % b
{
	if (variables[a]->get_type() == "string" || variables[b]->get_type() == "string")
	{
		return;
	}

	if (variables[a]->get_type() == "double" || variables[b]->get_type() == "double")
	{
		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) % std::stoi(variables[b]->get_value())));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) % std::stoi(variables[b]->get_value())));

}

void remainder_with_numbers(int c, int a, int num) // c = a % num
{
	if (variables[a]->get_type() == "double")
	{

		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) % num));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(std::stoi(variables[a]->get_value()) % num));


}

void remainder_with_numbers_rev(int c, int num, int b) // c = num % b
{
	if (variables[b]->get_type() == "double")
	{

		variables[c]->set_type("double");
		variables[c]->set_value(std::to_string(num % std::stoi(variables[b]->get_value())));

		return;
	}

	variables[c]->set_type("int");
	variables[c]->set_value(std::to_string(num % std::stoi(variables[b]->get_value())));

}

void assign_variable(const std::vector<std::string>& words)
{
	if (words[0] == "inc")
	{
		add_with_numbers(find_by_name(words[1]), find_by_name(words[1]), 1);
		return;
	}

	if (words[0] == "dec")
	{
		sub_with_numbers(find_by_name(words[1]), find_by_name(words[1]), 1);
		return;
	}

	if (words[3] == "+")
	{
		if (words[2][0] >= '0' && words[2][0] <= '9')
		{
			add_with_numbers(find_by_name(words[0]), find_by_name(words[4]), std::stoi(words[2]));

			return;
		}

		if (words[4][0] >= '0' && words[4][0] <= '9')
		{
			add_with_numbers(find_by_name(words[0]), find_by_name(words[2]), std::stoi(words[4]));

			return;
		}

		add(find_by_name(words[0]), find_by_name(words[2]), find_by_name(words[4]));
	}

	if (words[3] == "-")
	{
		if (words[2][0] >= '0' && words[2][0] <= '9')
		{
			sub_with_numbers_rev(find_by_name(words[0]), std::stoi(words[2]), find_by_name(words[4]));

			return;
		}

		if (words[4][0] >= '0' && words[4][0] <= '9')
		{
			sub_with_numbers(find_by_name(words[0]), find_by_name(words[2]), std::stoi(words[4]));

			return;
		}

		sub(find_by_name(words[0]), find_by_name(words[2]), find_by_name(words[4]));
	}

	if (words[3] == "*")
	{
		if (words[2][0] >= '0' && words[2][0] <= '9')
		{
			mul_with_numbers(find_by_name(words[0]), find_by_name(words[4]), std::stoi(words[2]));

			return;
		}

		if (words[4][0] >= '0' && words[4][0] <= '9')
		{
			mul_with_numbers(find_by_name(words[0]), find_by_name(words[2]), std::stoi(words[4]));

			return;
		}

		mul(find_by_name(words[0]), find_by_name(words[2]), find_by_name(words[4]));
	}


	if (words[3] == "/")
	{
		if (words[2][0] >= '0' && words[2][0] <= '9')
		{
			div_with_numbers_rev(find_by_name(words[0]), std::stoi(words[2]), find_by_name(words[4]));

			return;
		}

		if (words[4][0] >= '0' && words[4][0] <= '9')
		{
			div_with_numbers(find_by_name(words[0]), find_by_name(words[2]), std::stoi(words[4]));

			return;
		}

		div(find_by_name(words[0]), find_by_name(words[2]), find_by_name(words[4]));
	}

	if (words[3] == "%")
	{
		if (words[2][0] >= '0' && words[2][0] <= '9')
		{
			remainder_with_numbers_rev(find_by_name(words[0]), std::stoi(words[2]), find_by_name(words[4]));

			return;
		}

		if (words[4][0] >= '0' && words[4][0] <= '9')
		{
			remainder_with_numbers(find_by_name(words[0]), find_by_name(words[2]), std::stoi(words[4]));

			return;
		}

		remainder(find_by_name(words[0]), find_by_name(words[2]), find_by_name(words[4]));
	}
}


void print_var(const std::string& word)
{
	int i = find_by_name(word);

	std::cout << variables[i]->get_value();
}

bool check_with_numbers(const My_type& var, double num, const std::string& op)
{
	if (op == "<")
	{
		return (std::stod(var.get_value()) < num);
	}

	if (op == ">")
	{
		return (std::stod(var.get_value()) > num);
	}

	if (op == "<=")
	{
		return (std::stod(var.get_value()) <= num);
	}

	if (op == ">=")
	{
		return (std::stod(var.get_value()) >= num);
	}

	if (op == "==")
	{
		return (std::stod(var.get_value()) == num);
	}

	if (op == "!=")
	{
		return (std::stod(var.get_value()) != num);
	}
}

bool check_condition(const std::vector<std::string>& words)
{
	if (!was_declared(words[3]))
	{
		return check_with_numbers(*variables[find_by_name(words[1])], std::stod(words[3]), words[2]);
	}

	if (!was_declared(words[1]))
	{
		return check_with_numbers(*variables[find_by_name(words[3])], std::stod(words[1]), words[2]);
	}

	My_type* var1 = variables[find_by_name(words[1])];
	My_type* var2 = variables[find_by_name(words[3])];

	if (words[2] == "<")
	{
		return (*var1 < *var2);
	}

	if (words[2] == ">")
	{
		return (*var2 < *var1);
	}

	if (words[2] == "<=")
	{
		return (*var1 <= *var2);
	}

	if (words[2] == ">=")
	{
		return (*var2 < *var1);
	}

	if (words[2] == "==")
	{
		return (*var2 == *var1);
	}

	if (words[2] == "!=")
	{
		return !(*var2 == *var1);
	}
}

void get_variables()
{
	for (int i = 0; i < variables.size(); ++i)
	{
		std::cout << "Name: " << variables[i]->get_name()
			<< " | Type: " << variables[i]->get_type()
			<< " | Value: " << variables[i]->get_value();


		std::cout << "\n\n";
	}
}


int get_variables_size()
{
	return variables.size();
}