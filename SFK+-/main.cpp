#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::string OpenFile(const char* filename)
{
	std::ifstream file(filename);
	std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	return str;
}

const std::vector<std::string> Lexer(const std::string& fileContents)
{
	std::vector<std::string> tokens;
	std::string token = "";
	bool state = false;
	std::string text = "";

	for (char ch : fileContents)
	{
		token += ch;
		if (token == " ")
		{
			if (state == false)
				token = "";
			else
			{
				text += ch;
				token = "";
			}
		}
		else if (token == "\n")
			token = "";
		else if (token == "YAZDIR")
		{
			tokens.push_back(token);
			token = "";
		}
		else if (token == "\"")
		{
			if (state == false)
				state = true;
			else if (state == true)
			{
				tokens.push_back(text);
				text = "";
				state = false;
				token = "";
			}
		}
		else if (state == true)
		{
			text += ch;
			token = "";
		}
	}

	//for (std::string tok : tokens)
	//	std::cout << tok << std::endl;

	return tokens;
}

void Parser(std::vector<std::string> tokens)
{
	//for (std::string tok : tokens)
	//	std::cout << tok << std::endl;
	int i = 0;
	while (i < tokens.size())
	{
		if (tokens[i] == "YAZDIR")
		{
			if (tokens.size() > i + 1)
			{
				if (tokens[i + 1] != "")
				{
					std::cout << tokens[i + 1] << std::endl;
					i += 2;
				}
			}
			else
			{
				std::cout << "------------------------------------------------------------" << std::endl;
				std::cout << "SOZ DIZIMI HATASI: YAZDIR FONKSIYONU PARAMETREYI BULAMADI!!!" << std::endl;
				return;
			}
			
		}
	}
}

int main(int argc, const char *argv[])
{
	std::string fileContents;

	if (argc == 1) 
	{
		std::cout << "No Arguments passed!!" << std::endl;
		std::cout << "Give A File Name" << std::endl;
		std::string fileName;
		std::getline(std::cin, fileName);
		fileContents = OpenFile(fileName.c_str());
	}
	else 
	{
		std::cout << "Arguments: ";
		for (int i = 1; i < argc; ++i) {
			std::cout << argv[i] << std::endl;
			fileContents = OpenFile(argv[i]);
		}
	}

	std::vector<std::string> tokens = Lexer(fileContents);
	Parser(tokens);

	std::getline(std::cin, fileContents);

	return 0;
}