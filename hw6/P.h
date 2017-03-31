// Josh Mau
// Mar 16, 2017
// P.h -- Header file for Object Oriented
//		Read and categorize UTF-8 characters
// 		from multiple files.

#ifndef P_H_INCLUDED
#define P_H_INCLUDED

#include <string>
#include <vector>
#include <set>
#include <map>

class P {
	public:
		// Constructors and Destructor -------------------------

		// Default Constructor -- Accumulated String (utf_string) is empty.
                // No properties file passed (yet).
		P();
            
		// Copy Constructor -- Copy an existing U object to a new object of type: U.
		P(const P &);

		// Test Constructor
		P(std::string);

		// Assignment Operator
		P &operator=(const P &);
	       
		// Destructor -- No dynamic data
		~P();

		// Methods of Class 'P' --------------------------------
		void readfile(const std::string);
        
        // Returns reference to the set of all property names
		std::set<std::string> props() const;
 
        int count(int codepoint) const;
        
		// Loops through all property counts until it finds the method
		// parameter or hits the end of the map.
		int count(std::string) const;
               
		// return size (stored per data object in private vars)
		int size() const;
        
        bool empty() const;
        
        void clear();
        
        void clear_properties();
        
        // Public Variables
		std::string properties_file_name;
		std::set<std::string> unique_properties;
		std::map<int, std::string> hex_to_property;
		std::map<std::string, int> property_counts;
        
    private:
        // Nothing for now...
    
};

#endif
