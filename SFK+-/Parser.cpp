#include "main.h"

const void Parser(toks& tokens, vars& variables)
{
	std::vector<toks> ifTokens;
	Conditioner(tokens, ifTokens);

	std::size_t i = 0;
	while (i < tokens.size())
	{
		if (tokens[i].first == TokenType::KEYWORD && tokens[i].second == "YAZDIR")
		{
			if (tokens.size() > i + 1)
			{
				if (tokens[i + 1].first == TokenType::STRING)
					Print(tokens[i + 1].second);
				else if (tokens[i + 1].first == TokenType::NUMBER)
					Print(tokens[i + 1].second);
				else if (tokens[i + 1].first == TokenType::EXPRESSION)
				{
					try
					{
						std::string result = EvaluateExpression(tokens[i + 1].second);
						Print(result);
					}
					catch (const char* result)
					{
						Print(result, true);
						return;
					}
				}
				else if (tokens[i + 1].first == TokenType::VARIABLE)
				{
					if (checkKey(variables, tokens[i + 1].second))
						Print(variables[tokens[i + 1].second].getValue());
					else
					{
						Print("SOZ DIZIMI HATASI : DEGISKEN BULUNAMADI", true);
						return;
					}
				}
				else
				{
					Print("SOZ DIZIMI HATASI: YAZDIR FONKSIYONU HATALI PARAMETRE GIRISI!", true);
					return;
				}
				i += 1;
			}
			else
			{
				Print("SOZ DIZIMI HATASI: YAZDIR FONKSIYONU PARAMETREYI BULAMADI!", true);
				return;
			}
		}
		else if (tokens[i].first == TokenType::VARIABLE)
		{
			if (!checkKey(variables, tokens[i].second))
				variables[tokens[i].second] = Variable();

			if (tokens.size() > i + 1)
			{
				if (tokens[i + 1].first == TokenType::EQUALS)
				{
					if (tokens.size() > i + 2)
					{
						if (tokens[i + 2].first == TokenType::STRING)
							variables[tokens[i].second].setData(VariableType::STRING, tokens[i + 2].second);
						else if (tokens[i + 2].first == TokenType::NUMBER)
							variables[tokens[i].second].setData(VariableType::NUMBER, tokens[i + 2].second);
						else if (tokens[i + 2].first == TokenType::EXPRESSION)
						{
							try
							{
								std::string result = EvaluateExpression(tokens[i + 2].second);
								variables[tokens[i].second].setData(VariableType::NUMBER, result);
							}
							catch (const char* result)
							{
								Print(result, true);
								return;
							}
						}
						else if (tokens[i + 2].first == TokenType::VARIABLE)
						{
							if (checkKey(variables, tokens[i + 2].second))
								variables[tokens[i].second].setData(variables[tokens[i + 2].second].getType(), variables[tokens[i + 2].second].getValue());
							else
							{
								Print("SOZ DIZIMI HATASI : DEGISKEN BULUNAMADI", true);
								return;
							}
						}
						i += 1;
					}
					else
					{
						Print("SOZ DIZIMI HATASI: DEGISKEN PARAMETRESI BULUNAMADI!", true);
						return;
					}
					i += 1;
				}
			}
		}
		else if (tokens[i].first == TokenType::KEYWORD && tokens[i].second == "GIRDI")
		{
			if (tokens.size() > i + 1)
			{
				if (tokens[i + 1].first == TokenType::STRING)
				{
					Print(tokens[i + 1].second);

					if (tokens.size() > i + 2)
					{
						if (tokens[i + 2].first == TokenType::VARIABLE)
						{
							std::pair<VariableType, std::string> input = Scan();

							if (checkKey(variables, tokens[i + 2].second))
								variables[tokens[i + 2].second].setData(input.first, input.second);
							else
							{
								variables[tokens[i + 2].second] = Variable();
								variables[tokens[i + 2].second].setData(input.first, input.second);
							}
						}
						else
						{
							Print("SOZ DIZIMI HATASI: GIRDI FONKSIYONU DEGISKEN BULUNAMADI!", true);
							return;
						}
						i += 1;
					}
					else
					{
						Print("SOZ DIZIMI HATASI: DEGISKEN PARAMETRESI BULUNAMADI!", true);
						return;
					}
					i += 1;
				}
				else
				{
					Print("SOZ DIZIMI HATASI: GIRDI FONKSIYONU HATALI PARAMETRE(MESAJ)!", true);
					return;
				}

			}
			else
			{
				Print("SOZ DIZIMI HATASI: MESAJ BULUNAMADI!", true);
				return;
			}
		}
		else if (tokens[i].first == TokenType::STATEMENT)
		{
			if (tokens[i + 1].first == TokenType::CONDITION && tokens[i + 1].second == "TRUE")
			{
				Parser(ifTokens[std::stoi(tokens[i].second)], variables);
				i += 1;
			}
			else if (tokens[i + 1].first == TokenType::CONDITION && tokens[i + 1].second == "FALSE")
			{
				i += 1;
			}
			else
			{
				Print("SOZ DIZIMI HATASI: KOSUL BULUNAMADI!", true);
				return;
			}
		}
		i += 1;
	}

}