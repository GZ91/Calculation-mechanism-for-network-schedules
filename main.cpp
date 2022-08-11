#include <iostream>
#include <fstream>
#include "nlohmann\json.hpp"

using json = nlohmann::json;

int main()
{
	std::ifstream f("example.json");
	if (f.fail()) return 1; //Если файл не найден
	json data = json::parse(f);
	if(data["active"])
		std::cout << "YES!!!" << std::endl;
	else std::cout << "NO!!!!" << std::endl;
	return 0;
}
