#include "main.h"

const std::vector<std::pair<TokenType, std::string>> Lexer(const std::string& fileContents)
{
	std::vector<std::pair<TokenType, std::string>> tokens;
	std::string token = "";
	bool state = false;
	std::string text = "";
	std::string expression = "";
	std::string number = "";
	bool isExpression = false;
	bool variableStarted = false;
	std::string variable = "";

	for (char ch : fileContents)
	{
		token += ch;
		if (token == " ")
		{
			if (state == false)
				token = "";
			else
			{
				text += token;
				token = "";
			}
		}
		else if (token == "\n" || token == "<EOF>")
		{
			if (expression != "" && isExpression == true)
			{
				tokens.push_back(std::make_pair(TokenType::EXPRESSION, expression));
				expression = "";
				isExpression = false;
			}
			else if (expression != "" && isExpression == false)
			{
				tokens.push_back(std::make_pair(TokenType::NUMBER, expression));
				expression = "";
			}
			else if (variable != "")
			{
				tokens.push_back(std::make_pair(TokenType::VARIABLE, variable));
				variable = "";
				variableStarted = false;
			}
			if (token == "<EOF>")
				return tokens;

			token = "";
		}
		else if (token == "=" && state == false)
		{
			tokens.push_back(std::make_pair(TokenType::VARIABLE, variable));
			tokens.push_back(std::make_pair(TokenType::EQUALS, ""));
			variable = "";
			token = "";
			variableStarted = false;
		}
		else if (token == "$" && state == false)
		{
			variableStarted = true;
			token = "";
		}
		else if (variableStarted == true)
		{
			if (token == "<")
				variableStarted = false;
			else
			{
				variable += token;
				token = "";
			}
		}
		else if (token == "YAZDIR")
		{
			tokens.push_back(std::make_pair(TokenType::KEYWORD, token));
			token = "";
		}
		else if (token == "GIRDI")
		{
			tokens.push_back(std::make_pair(TokenType::KEYWORD, token));
			token = "";
		}
		else if (token == "0" || token == "1" || token == "2" || token == "3" || token == "4" || token == "5" || token == "6" || token == "7" || token == "8" || token == "9")
		{
			expression += token;
			token = "";
		}
		else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "%")
		{
			isExpression = true;
			expression += token;
			token = "";
		}
		else if (token == "\"")
		{
			if (state == false)
			{
				state = true;
				token = "";
			}
			else if (state == true)
			{
				tokens.push_back(std::make_pair(TokenType::STRING, text));
				text = "";
				state = false;
				token = "";
			}
		}
		else if (state == true)
		{
			text += token;
			token = "";
		}
	}

	return tokens;
}