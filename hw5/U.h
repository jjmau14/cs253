//	Josh Mau / 830802582
//	Mar 16, 2017
// 	U.h -- Header file for Object Oriented
//			UTF-8 character number from files

#ifndef U_H_INCLUDED
#define U_H_INCLUDED

#include <string>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

class U {
	public:
		// -----------------------------------------------------
		U(){}										
		U(const U &u) : properties_file(u.properties_file), utf_string(u.utf_string){}
		U(std::string p, std::string u) : properties_file(p), utf_string(u){}
		U& operator=(const U &u){
			properties_file = u.properties_file;
			utf_string = u.utf_string;
			return *this;
		}
		~U(){}
		// -----------------------------------------------------
		void readFile(std::string fileName){}

		void propfile(std::string fileName){
			clear_properties();
			std::ifstream propfile;
			propfile.open(fileName);
			std::string line = "";
			if (!propfile.is_open())
				throw "Properties file could not be opened!";
			while(std::getline(propfile, line)){
				std::string temp_string = "";
				int hex_value = 0;
				int semi_colon_count = 0;
				    for (char c : line){
				        if (c == ';')
				            break;
				        else
				            temp_string += c;
				    }
					std::istringstream iss(temp_string);
					iss >> std::hex >> hex_value;
					temp_string = "";
				    for (char c : line){
				        if (c == ';')
				            semi_colon_count++;
				        else if (semi_colon_count == 2)
				            temp_string += c;
				        else if(semi_colon_count > 2)
				            break;
				    }
				    utf_char_prop[hex_value] = temp_string;
				    propNames.insert(temp_string);
			}
			for (auto property_name : propNames){
				prop_counts[property_name] = 0;
			}
			propfile.close();
		}

		int size() { return utf_size; }

		std::string get(){return "";}
		std::string get(int index){return "";}
		std::string get(int start, int end){return "";}

		int propcount(std::string property){
			if (prop_counts.find(property) != prop_counts.end())
				return prop_counts.find(property)->second;
			return 0;
		}

		std::set<std::string> props(){return std::set<std::string>;}

	private:
		std::string properties_file;
		std::string utf_string;
		int utf_size = 0;
		std::set<std::string> propNames;
		std::vector<std::string> utf_chars;
		std::map<int, std::string> utf_char_prop;
		std::map<std::string, int> prop_counts;
		void clear_properties(){
			propNames.clear();
			utf_char_prop.clear();
			utf_chars.clear();
		}			
};

#endif
