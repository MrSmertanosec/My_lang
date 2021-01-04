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


void get_words(std::vector<std::string>&, const std::string&);
void create_var(const std::vector<std::string>&);
std::string check_type(const std::string&);
bool was_declared(const std::string&);
int find_by_name(const std::string&);

void add(int, int, int);
void add_with_numbers(int, int, int);

void sub(int, int, int);
void sub_with_numbers(int, int, int);
void sub_with_numbers_rev(int, int, int);

void mul(int, int, int);
void mul_with_numbers(int, int, int);

void div(int, int, int);
void div_with_numbers(int, int, int);
void div_with_numbers_rev(int, int, int);

void assign_variable(const std::vector<std::string>&);

void print_var(const std::string&);

bool check_with_numbers(const My_type&, double, const std::string&);
bool check_condition(const std::vector<std::string>&);

void get_variables();
int get_variables_size();
