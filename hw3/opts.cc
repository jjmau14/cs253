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
        std::cerr << __FILE__ << ": No properties files passed!\n";
        return 1;
    }
    
    properties.open(argv[currElem]);
    if ( !properties.is_open()){
        std::cerr << __FILE__ << ": Could not open properties file: \"" << argv[currElem] << "\"\n";
        return 1;
    }
    
    /* Read file line by line, convert string to int and
     * store values to strings in props map */
    while(std::getline(properties, tempString)){
        istringstream iss(tempString.substr(0,2));
        if (iss >> hex >> tempInt){
            props[tempInt] = tempString.substr(3);
            propNames.insert(tempString.substr(3));
        }
    }
    
    properties.close();

    /* Initialize all propNames in set to 0 count */
    for ( auto name : propNames )
        propCounts[name] = 0;
    
    if ( currElem + 1 == argc ){
        std::cerr << __FILE__ << ": No files passed!\n";
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
            std::cerr << __FILE__ << ": Could not open file: \"" << fileName << "\"\n";
            return 1;
        }
        
        while (getline(currFile, tempString)){
            if ( props.find('\n') != props.end() && !currFile.eof()){
                string key = props.at('\n');
                propCounts.at(key) += 1;
            }
            for ( char c : tempString ){
                if (!(c >= 0 && c < 128)){
                    cerr << __FILE__ << ": could not read character in file \"" << fileName << "\"\n";
                    return 1;
                }
                if ( props.find(c) != props.end()){
                    string key = props.at(c);
                    propCounts.at(key) += 1;
                }
            }
        }
        currFile.close();
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
                cerr << __FILE__ << ": option \"" << option << "\" was not specified in the properties file\n";
            }
        }
    }
            
    // -------------------------------------------------------------------------------
    return 0;
    
}