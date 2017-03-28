// Josh Mau
// Mar 16, 2017
// U.h -- Header file for Object Oriented
//		Read and categorize UTF-8 characters
// 		from multiple files.

#ifndef U_H_INCLUDED
#define U_H_INCLUDED

#include <string>
#include <vector>
#include <set>
#include <map>

class U {
	public:
		// Constructors and Destructor -------------------------

		// Default Constructor -- Accumulated String (utf_string) is empty.
                // No properties file passed (yet).
		U();
            
		// Copy Constructor -- Copy an existing U object to a new object of type: U.
		U(const U &);

		// Test Constructor -- Take a property file and literal string.
        // Requires properties filename as first arg, and literal string
        // As second arg.
		U(std::string, std::string);

		// Assignment Operator
		U &operator=(const U &);
	       
		// Destructor -- No dynamic data
		~U();

		// Methods of Class 'U' --------------------------------
		void readfile(const std::string);
        
        // Parse std::string into utf characters...
        void read_string(const std::string); 

		// Parse Properties file -- 
		void propfile(const std::string);
		
		// return size (stored per data object in private vars)
		int size() const;
    
		std::string get();
		std::string get(const int);
		std::string get(const int, const int);
		
		// Loops through all property counts until it finds the method
		// parameter or hits the end of the map.
		int propcount(std::string) const ;
        
		// Returns reference to the set of all property names
		std::set<std::string> props() const;
        
        // Public Variables
		std::string properties_file;
                std::string string_literal;
		std::set<std::string> propNames;
		std::vector<std::string> utf_chars;
		std::map<int, std::string> utf_char_prop;
		std::map<std::string, int> prop_counts;
		std::map<int, std::vector<int>> utf_string;
                int utf_index = 0;
		void clear_properties();	
        
    private:
        // Nothing for now...
    
};

#endif
