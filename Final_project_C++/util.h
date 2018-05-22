#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
//using namespace std;

void trimSpace(std::string& s);

void csvPrint(std::vector <std::vector<std::string>> & csvData);

void csvRead(std::string& filename, char sep, std::vector<std::vector<std::string>> & csvData);

bool validSlots(std::string s);

bool validTaskName(std::string s);

bool validSequenceNumber(std::string s);

bool validItemName(std::string s);

bool validCustomerName(std::string s);

bool validProductName(std::string s);
