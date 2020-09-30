#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>
#include "w2v_bin_helper.hpp"

W2v_bin_helper::W2v_bin_helper(){};
W2v_bin_helper::~W2v_bin_helper(){};

void W2v_bin_helper::read_header(std::ifstream &ifs){

	char c;
	std::stringstream s1, s2;
	while(c != ' '){
			ifs.read( reinterpret_cast<char *>(&c), sizeof(c) ) ;
			s1 << c ;
		}
	n_words = std::stoll(s1.str()) ;

	while(c != '\n'){
		ifs.read( reinterpret_cast<char *>(&c), sizeof(c) ) ;
		s2 << c ;
	}

	n_embeds = std::stoll(s2.str());
};

wvector W2v_bin_helper::line_parser(std::ifstream &ifs){
	wvector wv;
	char c;
	std::stringstream s1;

	while(c != ' '){
		ifs.read( reinterpret_cast<char *>(&c), sizeof(c) ) ;
		if(c != ' '){
			s1 << c ;
		}
	}
	wv.word = s1.str() ;

	float f;

	for(int i = 0; i < n_embeds ; i++){
		ifs.read(reinterpret_cast<char*>(&f), sizeof(float));
		wv.values.push_back(f);
	}

	ifs.read( reinterpret_cast<char *>(&c), sizeof(c) );

	if(c != '\n'){
		ifs.seekg( -sizeof(c), std::ios::cur);
	}
	
	return wv;
}

long long W2v_bin_helper::get_n_words(){
	return(n_words);
}

long long W2v_bin_helper::get_n_embeds(){
	return(n_embeds);
}