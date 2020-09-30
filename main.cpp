#include <iostream>
#include <vector>
#include <fstream>
// Level DB
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/write_batch.h"
#include "leveldb/filter_policy.h"

#include "w2v_bin_helper.hpp"

const long long batch_size = 100000;

int main(int argc, char** argv) {
	// Take three arguments from command line: 
	// W2V Binary file containing embedings
	// LevelDb output database name
	// Citation String [Will be retreivable using "metadata!w2citation" key. 
	// Other information that will be auto extracted from w2v binary file is "metadata!n_words" and "metadata!n_dimension"

	char* w2v_file;
	char* dbName;
	char* citation;

	if(argc != 4) {
		std::cerr << "Need some information from command line. first argument is full path of binary file containing word vectors. Second argument is the name of output database name. Third argument is a string that will be stored in metadata!w2citation key in database that serves as a citation of the w2v article." << std::endl;
		std::cerr << "Correct use: " << argv[0] << " w2v.bin leveldb_name citation " << std::endl; 
		return(-1);
	} 
	else {
		try{
			w2v_file = argv[1];
			dbName = argv[2];
			citation = argv[3];
		}
		catch(...){
			throw("Problem parsing command line!");
		}
	} 

	// Open the database 
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, dbName , &db);


	//  Prepare reading the w2v file.
	std::ifstream ifs(w2v_file, std::ios::in | std::ios::binary);
	W2v_bin_helper w2v;
	
    // long long i ; 
	if (ifs.is_open()){
		// header
		w2v.read_header(ifs);
		// std::cout << w2v.get_n_words() << std::endl;
		// std::cout << w2v.get_n_embeds() << std::endl;
		for( long long i = 0 ; i < w2v.get_n_words() ; i+=batch_size ){
			std::cout << "Batch # " << i/batch_size << std::endl;
			auto v_size = std::min(batch_size, (w2v.get_n_words() - i));
			// std::cout << "Size of vector => " << v_size << std::endl;
			// Create Level DB Batch
			leveldb::WriteBatch batchToWrite;
			for(int j = 0; j < v_size; j++){
				auto temp = w2v.line_parser(ifs);
				// std::cout << temp.vectorAsString() << std::endl;
				batchToWrite.Put(static_cast<leveldb::Slice>( temp.word ), 
					static_cast<leveldb::Slice>( temp.vectorAsString() )) ;	
			}
			// Write it down in db
			leveldb::Status s = db->Write(leveldb::WriteOptions(), &batchToWrite);
			if(! s.ok() ){
				std::cout << "ERROR: Database batch write failed, will exit now!" << std::endl ;
				exit(1);
			}
		}

			// Write metadata

		leveldb::WriteBatch metadataBatchToWrite; 

		metadataBatchToWrite.Put("metadata!citation", static_cast<leveldb::Slice>(citation) );
		metadataBatchToWrite.Put("metadata!n_words", static_cast<leveldb::Slice>(std::to_string(w2v.get_n_words())));
		metadataBatchToWrite.Put("metadata!n_dimensions", static_cast<leveldb::Slice>(std::to_string(w2v.get_n_embeds())));

		leveldb::Status s = db->Write(leveldb::WriteOptions(), &metadataBatchToWrite);

		if(! s.ok() ){
			std::cout << "ERROR: Writing metdata failed, will exit now!" << std::endl ;
			exit(1);
		}

	} else {
		std::cout << "Could Not Open File" << std::endl;
		exit(1);
	}

	return(0);

	// db->Close();

	// ifs.close();
}