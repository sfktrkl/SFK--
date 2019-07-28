#include "main.h"

int main(int argc, const char *argv[])
{
	std::string fileContents;

	if (argc == 1) 
	{
		std::cout << "HICBIR ARGUMAN BULUNAMADI!!" << std::endl;
		std::cout << "DOSYA ADI VERINIZ" << std::endl;
		std::string fileName;
		std::getline(std::cin, fileName);
		fileContents = OpenFile(fileName.c_str());
	}
	else 
	{
		std::cout << "DOSYA: ";
		for (int i = 1; i < argc; ++i) {
			std::cout << argv[i] << std::endl;
			fileContents = OpenFile(argv[i]);
		}
	}

	std::vector<std::pair<TokenType, std::string>> tokens = Lexer(fileContents);
	std::unordered_map<std::string, Variable> variables = Parser(tokens);

	std::getline(std::cin, fileContents);

	return 0;
}