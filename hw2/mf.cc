// Josh Mau
// Jan. 30, 2017
// HW2 -- Analyze standard input and display
//        a summary of results. Displays number
//        of Control (ctrl), Letters (lett), 
//        Numbers (num), Punctuation (punct)
//        Symbols (sym), and Spaces (spc).
//        Capable of One or more files as input.
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){
    if ( argc <= 1 ){
        std::cerr << "USAGE: " << argv[0] << " [File A] [File B] ... [File n]\n";
        return 1;
    }
    /**
     * Variables ctrl, lett, num, punct
     * sym, spc, token all initialized 
     * to 0.
     */
    int ctrl = 0;
    int lett = 0;
    int num = 0;
    int punct = 0;
    int sym = 0; 
    int spc = 0;
    string line;
    
    /**
     * For each argv 1 - max loop and read file
     * line by line and calculate chars
     */
    for ( int i = 1 ; i < argc ; i++){
        ifstream infile;
        infile.open(argv[i]);
        if (!infile.is_open()){
            std::cerr << argv[0] << " Error: Could not read file \"" << argv[i] << "\"\n";
            return 1;
        }
        
        /**
        * While loop takes a file or mulitple files 'line'.
        * and iterates line by line and stores in var 'line'.
        * Loops through each string array by char
        * and determines which type of char each is.
        */
        while (std::getline(infile, line)){
            
        /**
         * Increment control for new line not
         * included for each 'getline'. getline()
         * gets one line but does not add line 
         * terminator -- '\n'
         */
	if ( !infile.eof())
        	ctrl++;
        
        /**
         * for loop iterates through c++ string 'line'
         * and classifies each char as one of the above
         * Variables.
         */
            for ( char c : line){
                /**
                * if current char is a Capital 
                * or a Lower Case Letter.
                */
                if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                    lett++;
                
                /**
                * if current char is a Number.
                */
                else if (c >= '0' && c <= '9')
                    num++;
                
                /**
                * if current char is a Space.
                */
                else if (c == ' ')
                    spc++;
                
                /**
                * if current char is a Punctuation mark.
                */
                else if ((c >= '!' && c <= '#') || (c >= '%' && c <= '*') 
                    || (c >= ',' && c <= '/') || c == ':' || c == ';' 
                    || c == '?' || c == '@' || (c >= '[' && c <= ']') 
                    || c == '_' || c == '{' || c == '}')
                    punct++;
                
                /**
                * if current char is a Symbol.
                */
                else if (c == '$' || c == '+' || (c >= '<' && c <= '>') 
                    || c == '^' || c == '`' || c == '|' || c == '~')
                    sym++;
                
                /**
                * Otherwise current char is a Control.
                */
                else
                    ctrl++;            
            } 
        } 
        infile.close();
    }
        /**
     * Standardizes Output of data.
     */
    std::cout << "Control: " << ctrl << "\n";
    std::cout << "Letter: " << lett << "\n";
    std::cout << "Number: " << num << "\n";
    std::cout << "Punctuation: " << punct << "\n";
    std::cout << "Symbol: " << sym << "\n";
    std::cout << "Space: " << spc << "\n";
}
