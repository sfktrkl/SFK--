#include "main.h"

const void Conditioner(toks& tokens, std::vector<toks>& ifTokens) 
{
	bool conditionStarted = false;
	bool insideCondition = false;
	size_t conditionNumber = 0;
	size_t conditionFirst = 0;
	size_t i = 0;
	while (i < tokens.size())
	{
		if (tokens[i].first == TokenType::KEYWORD && tokens[i].second == "EGER" && !insideCondition)
		{
			conditionStarted = true;
			conditionFirst = i;
			i++;
		}
		else if (conditionStarted && (tokens[i].first == TokenType::EXPRESSION || tokens[i].first == TokenType::NUMBER) && !insideCondition)
		{
			std::string first, second;
			if (tokens[i].first == TokenType::EXPRESSION)
				first = EvaluateExpression(tokens[i].second);
			else if (tokens[i].first == TokenType::NUMBER)
				first = tokens[i].second;

			if (tokens[i + 2].first == TokenType::EXPRESSION)
				second = EvaluateExpression(tokens[i + 2].second);
			else if (tokens[i + 2].first == TokenType::NUMBER)
				second = tokens[i + 2].second;

			if (tokens[i + 1].first == TokenType::EQEQ)
			{
				if (first == second)
				{
					tokens[i].first = TokenType::CONDITION;
					tokens[i].second = "TRUE";
				}
				else
				{
					tokens[i].first = TokenType::CONDITION;
					tokens[i].second = "FALSE";
				}
			}
			tokens.erase(tokens.begin() + i + 1);
			tokens.erase(tokens.begin() + i + 1);
			i++;
		}
		else if (!conditionStarted && tokens[i].first == TokenType::KEYWORD && tokens[i].second == "BITIR" && insideCondition)
		{
			conditionNumber++;
			insideCondition = false;
			conditionStarted = false;
			tokens.erase(tokens.begin() + i);
		}
		else if ((conditionStarted && tokens[i].first == TokenType::KEYWORD && tokens[i].second == "ISE") || insideCondition)
		{
			if (!insideCondition)
			{
				conditionStarted = false;
				insideCondition = true;
				tokens[conditionFirst].first = TokenType::STATEMENT;
				tokens[conditionFirst].second = std::to_string(conditionNumber);
				ifTokens.push_back( { } );
			}
			else
			{
				ifTokens[conditionNumber].push_back(tokens[i]);
			}
			tokens.erase(tokens.begin() + i);
		}
		else
		{
			i++;
		}
	}
}