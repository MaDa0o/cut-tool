#include "cut.h"

//Important points
//read input from file if the file is given else take input from standard input if no file given or - is given
//-f specifies field list that tells which fields from each line are to be printed (fields are seperated by a delimiter)
//-d option specifies the delimiter to be used to identify fields (default is a tab)

bool Read_File(std::string file_path, std::vector<std::string>& file_content){
	std::ifstream file(file_path);

	if(file.is_open()){
		std::string line;
		while ( file ) {
			std::getline(file,line);
			// std::cout<<line<<"\n";
			file_content.push_back(line);
		}
	}
	else{
		std::cerr<<"No such file\n";
		return false;
	}
	file_content.pop_back();

	return true;
}

int main(int argc, char* argv[]){

	if(argc == 1){
		std::cerr<<"Missing Arguments\n";
		return 1;
	}

	std::string file_path = "";
	file_path = argv[argc - 1];
	int n = argc-2;
	char* flag_list[n];
	for(int i = 0; i < n ; i++){
		flag_list[i] = argv[n-i];
	}

	// std::cout<<"file path is:"<<file_path<<"\n";
	// std::cout<<"list of flags are:\n";
	// for(int i = 0; i < argc-2 ; i++){
	// 	std::cout<<flag_list[i]<<" ";
	// }
	// std::cout<<"\n";

	std::vector<std::string> file_content;

	if(!file_path.empty() && file_path != "-"){
		bool status = Read_File(file_path, file_content);
		if(!status){
			return 2;
		}
	}else{
		//to be implemented
		std::cout<<"no file specified\n";
		return 1;
	}

	//Displaying file content
	// std::cout<<"The file content is: \n";
	// for(int i = 0;i<file_content.size();i++){
	// 	std::cout<<file_content[i]<<"\n";
	// }

	char Delim = '\t';
	int colnum;

	for(int i=0;i<n;i++){
		std::string flag = flag_list[i];
		if(flag.substr(0,2) == "-f"){
			colnum = std::stoi(flag.substr(2));
		}
	}

	for(int i = 0;i<file_content.size();i++){
		std::string line = file_content[i];
		std::string col;
		int inc = 0;
		while(inc != colnum){
			col = line.substr(0,line.find(Delim));
			line = line.substr(line.find(Delim)+1);
			inc++;
		}
		std::cout<<col<<"\n";
	}

	return 0;
}