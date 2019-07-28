#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

enum class TokenType
{
	KEYWORD,
	STRING,
	NUMBER,
	EXPRESSION,
	VARIABLE,
	EQUALS
};

enum class VariableType
{
	NONE,
	STRING,
	NUMBER
};

class Variable
{
private:
	VariableType variableType;
	std::string value;
public:
	Variable() : value(""), variableType(VariableType::NONE) {}
	Variable(VariableType type, std::string data) : value(data), variableType(type) {}
	~Variable() {}

	void setData(VariableType type, std::string data) { this->variableType = type; this->value = data; }
	std::string getValue() const { return this->value; }
	VariableType getType() const { return this->variableType; }
};

void Print(std::string text, bool error = false);
const std::string OpenFile(const char* filename);
const std::string EvaluateExpression(std::string expression);
const std::vector<std::pair<TokenType, std::string>> Lexer(const std::string& fileContents);
const std::unordered_map<std::string, Variable> Parser(std::vector<std::pair<TokenType, std::string>>& tokens);
const bool checkKey(const std::unordered_map<std::string, Variable>& variables, const std::string key);
const std::pair<VariableType, std::string> Scan();
