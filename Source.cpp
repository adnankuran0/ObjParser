#include "ObjParser.h"


void main()
{
	ObjParser parser;

	parser.loadOBJ("test.obj");


	std::vector<float> data = parser.getData();

	for (int i = 0; i < data.size(); i++)
	{
		std::cout << data[i] << std::endl;
	}


	std::cin.get();
}