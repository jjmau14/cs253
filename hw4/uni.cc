// Josh Mau
// Jan. 23, 2017
// HW4 -- Count characters in files
//          passed with properties file.
//          UTF characters included.
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <set>

using namespace std;

static bool contains (string s, std::vector<string> vect){
    for ( auto v : vect ){
        if (v == s)
            return true;
    }
    return false;
}

int main(int argc, char* argv[]){
    
    int currElem;                       // Current Element of argv[] 
    vector<string> options;             // String values of options
    ifstream properties;                // Properties file name
    ifstream currFile;                  // Current file being read
    vector<string> files;               // Files to execute code on
    map<int, string> props;             // Map of ASCII int values to 
    set<string> propNames;              // Set containing names of props
    map<string, int> propCounts;        // Count of each type of property
    string tempString;                  // Temporary string used throughout
    int tempInt;                        // Temporary int value
    
    
    // Storing elements in propper data structures -----------------------------------

    for (currElem = 1 ; currElem < argc ; currElem++){
        if (argv[currElem][0] == '-')
            options.push_back(argv[currElem]);
        else 
            break;
    }
    
    for (auto &x : options){
        x = x.substr(1);
    }

    if ( currElem == argc ){
        std::cerr << argv[0] << ": No properties files passed!\n";
        return 1;
    }
    
    properties.open(argv[currElem]);
    if ( !properties.is_open()){
        std::cerr << argv[0] << ": Could not open properties file: \"" << argv[currElem] << "\"\n";
        return 1;
    }
    
    /* Read file line by line, convert string to int and
     * store values to strings in props map */
    while(std::getline(properties, tempString)){
        string tempVal = "";
        int semicCount = 0;
            for (char c : tempString){
                if (c == ';')
                    break;
                else
                    tempVal += c;
            }
            if (tempVal.length() < 4){
                cerr << argv[0] << ": Illegal properties value in \"" << tempVal << "\" in \"" << argv[currElem] << "\"\n"; 
                return 1;
            }
            string temp = "";
            for (char c : tempString){
                if (c == ';')
                    semicCount++;
                if (semicCount == 2){
                    temp += c;
                }else if(semicCount > 2)
                    break;
            }
            
        istringstream iss(tempVal);
        if (iss >> hex >> tempInt){
            temp = temp.substr(1);
            props[tempInt] = temp;
            propNames.insert(temp);
            //cout << "[" << tempInt << "]: " << props[tempInt] << endl;
        }
    }
    
    properties.close();

    /* Initialize all propNames in set to 0 count */
    for ( auto name : propNames ){
        //cout << name << endl;
        propCounts[name] = 0;
    }
    if ( currElem + 1 == argc ){
        std::cerr << argv[0] << ": No files passed!\n";
        return 1;
    }

    /* Store files names to be read into files vector */
    for (int filesIndex = (currElem + 1) ; filesIndex < argc ; filesIndex++){
        files.push_back(argv[filesIndex]);
    }

    // Sort data ---------------------------------------------------------------------

    for ( auto fileName : files ){
        currFile.open(fileName);
        if ( !currFile.is_open()){
            std::cerr << argv[0] << ": Could not open file: \"" << fileName << "\"\n";
            return 1;
        }
        
        while (getline(currFile, tempString)){
            if ( props.find('\n') != props.end() && !currFile.eof()){
                string key = props.at('\n');
                propCounts.at(key) += 1;
            }
            int i = 0;
            int flag = 0;
            for ( char c : tempString ){
                if (flag > 0){
                    // If the next bit doesn't begin with 10xxxxxx error out
                    if ( ((c&0x000000FF)&0xC0) != 0x80){
                        std::cerr << "Error in byte: " << hex << (c&0x000000FF) << endl;
                        return 1;
                    }
                    flag--;     // decrement flag
                    i++;        // incrememnt current index of tempString
                    continue;   // skip byte (already been read) 
                }
                
                // For Range U+0000 - U+007F
                if (c >= 0x0000 && c <= 0x007F){
                    if ( props.find(c) != props.end()){ // If that number is in list of properties
                        string key = props.at(c);       // Get property of the Unicode character (like Lu or Cc)
                        propCounts.at(key) += 1;        // Increment counter for that property
                    }
                }else{
                    // Convert to unsigned int
                    unsigned int a = (c&0x000000FF);
                    
                    // For Range U+0080 - U+07FF
                    if ((a&0xE0) == 0xC0){
                        flag = 1;       // Skip next byte
                        a &= 0x1F;      // Remove first 3 bits 110xxxxx
                        a <<= 6;        // Shift left 6 for next byte
                        a |= ((tempString[i+1]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                        //cout << hex << a << endl;
                    }
                    
                    // For Range U+0800 = U+FFFF
                    else if ((a&0xF0) == 0xE0){
                        flag = 2;       // Skip next two bytes
                        a &= 0x0F;      // Remove first 4 bits 1110xxxx
                        a <<= 6;        // Shift left 6 for next byte
                        a |= ((tempString[i+1]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                        a <<= 6;        // Shift left 6 for next byte
                        a |= ((tempString[i+2]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                        //cout << hex << a << endl;
                    }
                    
                    // For Range U+10000 - U+1FFFFF
                    else if ((a&0xF8) == 0xF0){
                        flag = 3;       // Skip next three bytes
                        a &= 0x07;      // Remove first five bits 11110xxx
                        a <<= 6;        // Shift left 6 for next byte
                        a |= ((tempString[i+1]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                        a <<= 6;        // Shift left 6 for next byte
                        a |= ((tempString[i+2]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                        a <<= 6;        // Shift left 6 for next byte
                        a |= ((tempString[i+3]&(0x000000FF)) & 0x3F );  // Remove first two bits (10xxxxxx) of next unicode character and OR it with currenct value
                        //cout << hex << a << endl; 
                    }
                    
                    if ( props.find(a) != props.end()){     // If that number is in list of properties
                        string key = props.at(a);           // Get property of the Unicode character (like Lu or Cc)
                        propCounts.at(key) += 1;            // Increment counter for that property
                    }
                }
                i++;    // Increment Index Counter
            }
        }
        currFile.close();   // Close file
    }
        
    // -------------------------------------------------------------------------------
        
    // Print Based on options --------------------------------------------------------
        
    if ( contains("all", options) ){
        for ( auto x : propCounts ){
            cout << x.first << ": " << x.second << endl;
        }
        return 0;
    }else{
        for ( auto option : options ){
            if (propCounts.find(option) != propCounts.end())
                cout << option << ": " << propCounts[option] << endl;
            else {
                cerr << argv[0] << ": option \"" << option << "\" was not specified in the properties file\n";
            }
        }
    }
            
    // -------------------------------------------------------------------------------
    return 0;
    
}
