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

bool generateFieldList(std::string list, std::vector<int>& field_list){
	char delim;

	if(list.find(' ') != std::string::npos){
		list.push_back(' ');
		delim = ' ';
	}else{
		list.push_back(',');
		delim = ',';
	}

	try{
		while(!list.empty()){
			int num = stoi(list.substr(0,list.find(delim)));
			list = list.substr(list.find(delim)+1);
			field_list.push_back(num);
		}
	}catch(...){
		std::cerr<<"Problem in field_list"<<"\nPlease input in the correct format\n";
		return false;
	}
	return true;
}

void FragmentContent(std::vector<std::string> content, std::vector<std::vector<std::string>>& fragment,const char delim){

	for(int i = 0;i<content.size();i++){
		std::string line = content[i];
		std::string col;
		line.push_back(delim);
		while(!line.empty()){
			col = line.substr(0,line.find(delim));
			line = line.substr(line.find(delim)+1);
			fragment[i].push_back(col);
		}
	}

}

void Read_stdinp(std::vector<std::string>& file_content){
	std::string t;
	while(getline(std::cin,t)){
		if(t.empty()){
			break;
		}
		file_content.push_back(t);
	}
}

int main(int argc, char* argv[]){

	if(argc == 1){
		std::cerr<<"Missing Arguments\n";
		return 1;
	}

	std::string file_path = "";
	int n;
	if(*argv[argc-1] != '-'){
		file_path = argv[argc - 1];
		n = argc-2;
	}else{
		n = argc - 1;
	}
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
		//Take input from standard input
		Read_stdinp(file_content);
	}

	//Displaying file content
	// std::cout<<"The file content is: \n";
	// for(int i = 0;i<file_content.size();i++){
	// 	std::cout<<file_content[i]<<"\n";
	// }

	char Delim = '\t';
	std::vector<int> field_list;

	for(int i=0;i<n;i++){
		std::string flag = flag_list[i];
		if(flag.substr(0,2) == "-f"){
			if(!generateFieldList(flag.substr(2),field_list)){
				return 3;
			}
		}
		else if(flag.substr(0,2) == "-d"){
			Delim = flag[2];
		}
	}

	// std::cout<<"Field_list is as follows:\n";
	// for(int i = 0;i<field_list.size();i++){
	// 	std::cout<<field_list[i]<<"\t";
	// }
	// std::cout<<"\n";

	std::vector<std::vector<std::string>> content_fragmented(file_content.size());
	FragmentContent(file_content, content_fragmented, Delim);

	for(int i = 0;i<content_fragmented.size();i++){
		for(int j = 0;j<field_list.size();j++){
			if(field_list[j]<=content_fragmented[0].size()){
				std::cout<<content_fragmented[i][field_list[j]-1]<<Delim;
			}
			else{
				std::cerr<<"\ninvalid fields\n";
				return 4;
			}
		}
		std::cout<<"\n";
	}

	return 0;
}