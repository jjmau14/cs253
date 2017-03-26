// Josh Mau
// Mar 16, 2017
// U.cc -- Implementation of U.h methods

#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "U.h"

using namespace std;

// Default Constructor -- Accumulated String (utf_string) is empty.
U::U(){
    properties_file = "";
}	

// Copy Constructor -- Copy an existing U object to a new object of type: U.
U::U(const U &rhs) : properties_file(rhs.properties_file), string_literal(rhs.string_literal), propNames(rhs.propNames),
    utf_chars(rhs.utf_chars), utf_char_prop(rhs.utf_char_prop), prop_counts(rhs.prop_counts), utf_string(rhs.utf_string),
    utf_index(rhs.utf_index){
    // Nothing left to do...
}
// Test Constructor -- Take a property file and literal string.
U::U(std::string p, std::string u) : properties_file(p), string_literal(u){
    propfile(properties_file);	
    read_string(string_literal);
}

// Assignment Operator
U &U::operator=(const U &rhs) {
    properties_file = rhs.properties_file;
    string_literal = rhs.string_literal;
    propNames = rhs.propNames;
    utf_chars = rhs.utf_chars;
	utf_char_prop = rhs.utf_char_prop;
	prop_counts = rhs.prop_counts;
    utf_string = rhs.utf_string;
    utf_index = rhs.utf_index;
    return *this;
}

// Destructor -- No dynamic data
U::~U(){}

// Methods of Class 'U' --------------------------------
void U::readfile(std::string fileName){
    std::ifstream readfile(fileName);
    std::string line = "";			
    
    if (!readfile)
        throw std::string("File \"" + fileName + "\" could not be opened!");
    
    while(std::getline(readfile, line)){
        read_string(line);
        if ( utf_char_prop.find('\n') != utf_char_prop.end() && !readfile.eof()){
            std::string key = utf_char_prop.at('\n');
            prop_counts.at(key) += 1;
            utf_string[utf_index] = '\n';
            utf_index++;
        }
    }
}
        
void U::read_string(const std::string line){
    int i = 0;
    int flag = 0;
    for ( char c : line ){
        if (flag > 0){
            // If the next bit doesn't begin with 10xxxxxx error out
            if ( ((c&0x000000FF)&0xC0) != 0x80){
                throw std::string("Error in byte");
                return;
            }
            flag--;     // decrement flag
            i++;        // incrememnt current index of tempString
            continue;   // skip byte (already been read) 
        }
        
        // For Range U+0000 - U+007F
        if (c >= 0x0000 && c <= 0x007F){
            if ( utf_char_prop.find(c) != utf_char_prop.end()){ 	// If that number is in list of properties
                    std::string key = utf_char_prop.at(c);       		// Get property of the Unicode character (like Lu or Cc)
                    prop_counts.at(key) += 1;        					// Increment counter for that property
                    utf_string[utf_index] = c;
                    utf_index++;
                }
            }else{
            // Convert to unsigned int
            unsigned int a = (c&0x000000FF);
            
            // For Range U+0080 - U+07FF
            if ((a&0xE0) == 0xC0){
                flag = 1;                                 // Skip next byte
                a &= 0x1F;                                // Remove first 3 bits 110xxxxx
                a <<= 6;                                  // Shift left 6 for next byte
                a |= ((line[i+1]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                std::stringstream s;
                s << std::hex << a;
                utf_string[utf_index] = a;
                utf_index++;
            }
            // For Range U+0800 = U+FFFF
            else if ((a&0xF0) == 0xE0){
                flag = 2;                                 // Skip next two bytes
                a &= 0x0F;                                // Remove first 4 bits 1110xxxx
                a <<= 6;                                  // Shift left 6 for next byte
                a |= ((line[i+1]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                a <<= 6;                                  // Shift left 6 for next byte
                a |= ((line[i+2]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                std::stringstream s;
                s << std::hex << a;
                utf_string[utf_index] = a;
                utf_index++;
            }
            
            // For Range U+10000 - U+1FFFFF
            else if ((a&0xF8) == 0xF0){
                flag = 3;                                 // Skip next three bytes
                a &= 0x07;                                // Remove first five bits 11110xxx
                a <<= 6;                                  // Shift left 6 for next byte
                a |= ((line[i+1]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                a <<= 6;                                  // Shift left 6 for next byte
                a |= ((line[i+2]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                a <<= 6;                                  // Shift left 6 for next byte
                a |= ((line[i+3]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                std::stringstream s;
                s << std::hex << a;
                utf_string[utf_index] = a;
                utf_index++;
            }
            
            if ( utf_char_prop.find(a) != utf_char_prop.end()){   // If that number is in list of properties
                std::string key = utf_char_prop.at(a);            // Get property of the Unicode character (like Lu or Cc)
                prop_counts.at(key) += 1;           			  // Increment counter for that property
            }
        }
        i++;    // Increment Index Counter
    }
}

// Parse Properties file -- 
void U::propfile(std::string fileName){
    clear_properties();			// if propfile is called more than once, clear existing data
    std::ifstream propfile(fileName);	// open property file
    std::string line = "";
    if (!propfile)	// throw error if could not open property file
        throw std::string("Properties file \"" + fileName + "\" could not be opened!");
		
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
        
        utf_char_prop[hex_value] = temp_string;		// Maps hex code to a property value (ie. 0x0065 mapped to Lu -- 'A')
        propNames.insert(temp_string);				// Adds property names to set (not multiset. aka add unique names only)
    }	

    for (auto property_name : propNames)
        prop_counts[property_name] = 0;					// Init all properties to count of 0
        
    propfile.close();		// Close property file
}
		
// return size (stored per data object in private vars)
int U::size() { 
    return utf_index;
}

std::string U::get(){
    std::string accum_string = "";
    for (int i = 0 ; i <= size() ; i++){
        accum_string += get(i);
    }
    return accum_string;
}

std::string U::get(int index){
    std::stringstream s;
    s << utf_string[index];
    return s.str();
}

std::string U::get(int start, int end){
    std::string interval_string = "";
    for (int i = start ; i < end ; i++)
        interval_string += get(i);
    return interval_string;
}
            
            
// Loops through all property counts until it finds the method
// 	parameter or hits the end of the map.
int U::propcount(std::string property) const {
    if (prop_counts.find(property) != prop_counts.end())	// if passed prop name == current item in map
        return prop_counts.find(property)->second;			// return that property->second (first = name; second = count)
    return 0;												// else not found (aka return 0)
}
    
// Returns set of all property names
std::set<std::string> U::props() const {return propNames;}

void U::clear_properties(){
    propNames.clear();
    utf_char_prop.clear();
    prop_counts.clear();
}		