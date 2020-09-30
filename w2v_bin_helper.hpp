#ifndef W2V_BIN_HELPER
#define W2V_BIN_HELPER

#include<iostream>
#include<vector>
#include<string>
#include<sstream>

struct wvector {
	std::string word;
	std::vector<float> values;
	std::string toString(){
		std::stringstream ss ;
		ss << word << " " ;
		for(auto & temp: values){
			ss << temp << " ";
		}
		return  ss.str();
	};
	std::string vectorAsString(){
		std::stringstream ss ;
		for(auto it = values.begin(); it != values.end(); ++it){
			std::next(it) == values.end() ? ss << *it : ss << *it << " "; 
		}
		return  ss.str();		
	}
};

class W2v_bin_helper
{
	long long n_words;
	long long n_embeds;	
public:
	W2v_bin_helper();
	~W2v_bin_helper();
	// read header provided with file pointer
	void read_header(std::ifstream &ifs);
	// read one line provided with file pointer
	wvector line_parser(std::ifstream &ifs);
	// Guide how to go throug line and print.
	void simple_printer();
	long long get_n_words();
	long long get_n_embeds();
};

#endif