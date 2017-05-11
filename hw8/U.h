// Josh Mau
// Mar 30, 2017
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
    std::string utf_file_name;
    std::map<int, std::vector<int>> utf_string;
    std::map<int, int> codepoint_map;
    int utf_index = 0;
    
    public:
		class uitor {
        		const U* u;
        		int index = 0;
    		public:
       	 		uitor(U* u_ = nullptr, int index_ = 0) : u(u_), index(index_){ }
       	 		uitor(const uitor& itor) : u(itor.u),index(itor.index){ }
       	 		uitor &operator=(const uitor& itor);
       	 		uitor &operator++();
       	 		uitor operator++(int);
       	 		uitor &operator--();
       	 		uitor operator--(int);
       	 		int operator*()const;
       	 		bool operator==(const uitor &rhs) const;
       	 		bool operator!=(const uitor &rhs) const;
    	   		~uitor(){};
		};
        
		// Constructors and Destructor -------------------------
		U();                      // Default Constructor
		U(const U &);             // Copy Constructor
		U(std::string);           // Test Constructor (Takes a string literal)
        U(const char* begin, const char* end);
		~U();                     // Destructor
		
        uitor begin();
        uitor end();
        int front();
        int back();
        
		// BEGIN Operators: -----------------------------------------
		// Assignment Operators
		U &operator=(const U &);  		// Assigns this to a U::U)
		U &operator=(const std::string &); 	// Assigns this to a std::string
		
		// Concatenation Operators
		U operator+(const U &)const;
		U operator+(const std::string &)const;
		friend U operator+(const std::string &, const U &);
		
		// Append Operators
		U &operator+=(const std::string &);
		U &operator+=(const U &);
		
		// Subscripting Operator
		std::string operator[](const int)const;
		
		// ostream
		friend std::ostream &operator<<(std::ostream &, const U &);
		
		// Boolean Evaluation
		operator bool()const;
		
		// Comparison 
		bool operator==(const U &)const;
		bool operator==(const std::string &)const;
		friend bool operator==(const std::string &, const U &);
		bool operator!=(const U &)const;
		bool operator!=(const std::string &)const;
		friend bool operator!=(const std::string &, const U &);
		
		// U class methods		
		void readfile(const std::string);         // Calls read_string on each line of a file
        void read_string(const std::string);      // Parses UTF-8 characters from string
		void append(const std::string);           // Calls read_string for a passed string (append to utf_string)
    
		std::string get()const;                        // Returns full utf_string
		std::string get(const int)const;               // Returns UTF-8 character at index of utf_string
		std::string get(const int, const int)const;    // Returns half open interval of UTF-8 characters
		
        int codepoint(const int)const;                // Returns the codepoint of the UTF-8 character at index
        
        int size() const;                         // Total size of utf_string (utf_index)
    
        bool empty()const;                             // QUESTION: is the utf_string empty?
        void clear();                             // CAUTION: Clears entire utf_string
        
};

#endif
