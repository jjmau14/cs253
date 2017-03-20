// Josh Mau
// Mar 16, 2017
// U.h -- Header file for Object Oriented
//		UTF-8 character number from files

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
		// Constructors and Destructor -------------------------

		// Default Constructor -- Accumulated String (utf_string) is empty.
		U(){utf_string = "";}	
		
		// Copy Constructor -- Copy an existing U object to a new object of type: U.
		U(const U &u) : properties_file(u.properties_file), utf_string(u.utf_string){}

		// Test Constructor -- Take a property file and literal string.
		U(std::string p, std::string u) : properties_file(p), utf_string(u){}

		// Assignment Constructor
		U& operator=(const U &rhs){
			properties_file = rhs.properties_file;
			utf_string = rhs.utf_string;
			return *this;
		}
	
		// Destructor -- No dynamic data
		~U(){}

		// Methods of Class 'U' --------------------------------
		void readFile(std::string fileName){}

		// Parse Properties file -- 
		void propfile(std::string fileName){
			clear_properties();			// if propfile is called more than once, clear existing data
			std::ifstream propfile;
			propfile.open(fileName);	// open property file
			std::string line = "";
			if (!propfile.is_open())	// throw error if could not open property file
				throw "Properties file could not be opened!";

			while(std::getline(propfile, line)){	// Read property file line by line
				std::string temp_string = "";	
				int hex_value = 0;
				int semi_colon_count = 0;
				    for (char c : line){
				        if (c == ';')
				            break;
				        else
				            temp_string += c;		// store hex code as string until first semicolon
				    }
					std::istringstream iss(temp_string);	// ISS -- istringstream, parse string to hex code for storage
					iss >> std::hex >> hex_value;
					temp_string = "";						// reset temp_string for new data (property name)
				    for (char c : line){					// Loop through line
				        if (c == ';')						// Read data starting at semicolon 2 and ending at 3 (property names ie. 'Lu')
				            semi_colon_count++;
				        else if (semi_colon_count == 2)		// If not hit 3rd semicolon yet, keep adding char to string
				            temp_string += c;
				        else if(semi_colon_count > 2)		// On third semicolon, break and add to the following data members
				            break;
				    }
				    utf_char_prop[hex_value] = temp_string;		// Maps hex code to a property value (ie. 0x0066 mapped to Lu -- 'A')
				    propNames.insert(temp_string);				// Adds property names to set (not multiset. aka add unique names only)
			}
			for (auto property_name : propNames){
				prop_counts[property_name] = 0;					// Init all properties to count of 0
			}
			propfile.close();		// Close property file
		}
		
		// return size (stored per data object in private vars)
		int size() { return utf_size; }

		std::string get(){return utf_string;}
		std::string get(int index){return "";}
		std::string get(int start, int end){return "";}
		
		// Loops through all property counts until it finds the method
		// 	parameter or hits the end of the map.
		int propcount(std::string property){
			if (prop_counts.find(property) != prop_counts.end())	// if passed prop name == current item in map
				return prop_counts.find(property)->second;			// return that property->second (first = name; second = count)
			return 0;												// else not found (aka return 0)
		}
		
		// Returns set of all property names
		std::set<std::string> props(){return propNames;}

	private:
		std::string properties_file;
		std::string utf_string;
		int utf_size;
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
