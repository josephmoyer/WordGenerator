#include <fstream>
#include <iostream>
#include <string>

const int NUMBEROFWORDS = 32154;
int main()
{
	std::cout << "Word Generator\n\n";
	//Initialize Word List
	std::string* wordList = new std::string[NUMBEROFWORDS];
	std::ifstream File;
	File.open("wordlist.dat");
	if (File.is_open())
	{
		for (int count = 0; count < NUMBEROFWORDS; count++)
		{
			std::getline(File, wordList[count]);
		}
	}
	File.close();

	std::string letter_list;
	int maxlength;
	int minlength;

	std::ifstream save;
	save.open("save.dat");
	if (save.is_open())
	{
		std::string input;
		std::getline(save, input);
		maxlength = atoi(input.c_str());

		std::getline(save, input);
		minlength = atoi(input.c_str());

		std::getline(save, input);
		letter_list = input;
	}
	else
	{
		std::cout << "How long can the words be? ";
		std::cin >> maxlength;

		std::cout << "How long must the words be? ";
		std::cin >> minlength;

		std::cout << "Please put in list of acceptable characters with no spaces between and press enter: ";
		std::cin >> letter_list;
	}
	save.close();

	//Generate words
	int j = letter_list.length();
	int indices[NUMBEROFWORDS];
	for (int count = 0; count < NUMBEROFWORDS; count++)
	{
		std::string word = "";
		indices[count] = NULL;
		for (int i = 0; i < maxlength&&i < wordList[count].length(); i++)
		{
			for (int w = 0; w < j; w++)
			{
				if (wordList[count][i] == letter_list[w])
				{
					word += letter_list[w];
				}
			}
		}
		if (wordList[count] == word&&wordList[count].length()>=minlength)
			indices[count] = count;
	}
	
	//Print
	char input=NULL;

	while (input != 'F' && input != 'B' && input != 'C')
	{
		std::cout << "\nDo you want to print to file, console or both? (F,C,B)?\n";
		std::cin >> input;
	}

	if (input == 'F')
	{
		std::ofstream File;
		File.open("genoutput.txt");
		if (File.is_open())
		{
			for (int count = 0; count < NUMBEROFWORDS; count++)
			{
				if (indices[count] != NULL)
				{
					File << wordList[count] << "\n";
				}
			}
		}
		File.close();
	}
	else if (input == 'B')
	{
		std::ofstream File;
		File.open("genoutput.txt");
		if (File.is_open())
		{
			for (int count = 0; count < NUMBEROFWORDS; count++)
			{
				if (indices[count] != NULL)
				{
					File << wordList[count] << "\n";
					std::cout << wordList[count] << "\n";
				}
			}
		}
		File.close();
	}
	else if (input == 'C')
	{
		for (int count = 0; count < NUMBEROFWORDS; count++)
		{
			if (indices[count] != NULL)
			{
				std::cout << wordList[count] << "\n";
			}
		}
	}

	char tmpe_input;
	std::cout << "\nPlease press any key and enter to exit.\n";
	std::cin >> tmpe_input;
	std::cout << "Thank you.";

	delete[] wordList;
	return 0;
}