#pragma once
#include <exception>

class Bad_Login : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Error: login is busy";
	}
};

class Bad_Name : public std::exception
{
public:
	const char* what() const noexcept override
	{
		return "Error: name is busy";
	}
};

