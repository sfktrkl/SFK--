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
	EQUALS,
	EQEQ,
	STATEMENT,
	CONDITION
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

typedef std::vector<std::pair<TokenType, std::string>> toks;
typedef std::unordered_map<std::string, Variable> vars;

void Print(std::string text, bool error = false);
const std::string OpenFile(const char* filename);
const std::string EvaluateExpression(std::string expression);
const void Lexer(const std::string& fileContents, toks& tokens);
const void Conditioner(toks& tokens, std::vector<toks>& ifTokens);
const void Parser(toks& tokens, vars& variables);
const bool checkKey(const vars& variables, const std::string key);
const std::pair<VariableType, std::string> Scan();