#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>

bool Read_File(std::string,std::vector<std::string>&);

bool GenerateFieldList(std::string, std::vector<int>&);

void FragmentContent(std::vector<std::string>, std::vector<std::vector<std::string>>&, const char);

void Read_stdinp(std::vector<std::string>&);

int main(int ,char**);