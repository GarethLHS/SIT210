#include <iostream>
#include <map>
#include <string>
using namespace std;

void print_Moorse_code(const map<char,string> m)
{
	for (const auto [key, value] : m){
			cout << '[' << key << "]\t" << value << '\n';
	}
	return;
}

void convert_name2Moorse_Code_and_Print(string name){

	// I need to iterate  through eveny character of the string intil the \0
	// and print the moorse code out for each character.
	//
	//for (int i = 0; i < name.len();i++)
	//	for(int m =0 m< moorse_code[letter].len(); m++){
	//		print morse code for each letter " "
	//	}	
		
		
	return ;
}

int main(){

	
	map<char,string> moorse_code{ \
			{'A',".-"}, \
			{'B',"-..."}, \
			{'C',"-.-."}, \
			{'B',"-..."}, \
			{'C',"-.-."}, \
			{'D',"-.." }, \
			{'E',"."   }, \
			{'F',"..-."}, \
			{'G',"--." }, \
			{'H',"...."}, \
			{'I',".."  }, \
			{'J',".---"}, \
			{'K',"-.-" }, \
			{'L',".-.."}, \
			{'M',"--"  }, \
			{'N',"-."  }, \
			{'O',"---" }, \
			{'P',".--."}, \
			{'Q',"--.-"}, \
			{'R',".-." }, \
			{'S',"..." }, \
			{'T',"-"   }, \
			{'U',"..-" }, \
			{'V',"...-"}, \
			{'W',".-- "}, \
			{'X',"-..-"}, \
			{'Y',"-.--"}, \
			{'Z',"--.."}  \
			};


	//print_Moorse_code(moorse_code);
	
	cout << moorse_code['G'] << "\n" ;
	cout << moorse_code['A'] << "\n" ;
	cout << moorse_code['R'] << "\n" ;
	cout << moorse_code['E'] << "\n" ;
	cout << moorse_code['T'] << "\n" ;
	cout << moorse_code['H'] << "\n" ;
	
	cout << "\n";

	return 0;
}

