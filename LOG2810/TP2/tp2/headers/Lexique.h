#pragma once

#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <unordered_map>

class Lexique {
	
private:
	std::vector<std::string> lexique_;
	std::unordered_map<char, int> alphabet_;

	
public:
	Lexique() = default;
	Lexique(std::string fileName);

	std::vector<std::string> getLexique();
	std::unordered_map<char, int> getAlphabet();
	
};
