#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

class My_type
{
private:
	std::string name;
	std::string type;
	std::string value;

public:
	My_type(const std::string& name)
	{
		this->name = name;
		this->type = "NULL";
		this->value = "NULL";
	}

	My_type(const std::string& name, const std::string& type, const std::string& value)
	{
		this->name = name;
		this->type = type;
		this->value = value;
	}

	My_type(const My_type& var)
	{
		this->name = var.name;
		this->type = var.type;
		this->value = var.value;

	}

	void set_type(const std::string& type)
	{
		this->type = type;
	}

	void set_value(const std::string& value)
	{
		this->value = value;
	}

	const std::string& get_name() const
	{
		return this->name;
	}

	const std::string& get_type() const
	{
		return this->type;
	}

	const std::string& get_value() const
	{
		return this->value;
	}



	bool operator <(const My_type& var)
	{
		if (this->type == "string")
		{
			return (this->value < var.value);
		}

		if (this->type == "double" || var.type == "double")
		{
			return (std::stod(this->value) < std::stod(var.value));
		}

		return (std::stoi(this->value) < std::stoi(var.value));
	}

	bool operator <=(const My_type& var)
	{
		return (*this < var || *this == var);
	}

	bool operator ==(const My_type& var)
	{
		if (this->type == "string")
		{
			return (this->value == var.value);
		}

		if (this->type == "double" || var.type == "double")
		{
			return (std::stod(this->value) == std::stod(var.value));
		}

		return (std::stoi(this->value) == std::stoi(var.value));
	}

	My_type* operator =(const My_type& var)
	{
		return new My_type(var);
	}
};


void get_words(std::vector<std::string>&, const std::string&); // saving words separated with space
void create_var(const std::vector<std::string>&); // declare variable
std::string check_type(const std::string&); // checking variable type
bool was_declared(const std::string&); // checking if variable was declared
int find_by_name(const std::string&); // finding variable index in variables vector 

void add(int, int, int); // sum 2 variables
void add_with_numbers(int, int, int); // sum 1 variable with number

void sub(int, int, int); // sub 2 variables
void sub_with_numbers(int, int, int);// sub 1 variable with number
void sub_with_numbers_rev(int, int, int);// sub 1 variable with number

void mul(int, int, int);
void mul_with_numbers(int, int, int);

void div(int, int, int);
void div_with_numbers(int, int, int);
void div_with_numbers_rev(int, int, int);

void assign_variable(const std::vector<std::string>&); // initializing variable

void print_var(const std::string&); // print variable

bool check_with_numbers(const My_type&, double, const std::string&); // comparing variables values with numbers
bool check_condition(const std::vector<std::string>&);

void get_variables();
int get_variables_size();
