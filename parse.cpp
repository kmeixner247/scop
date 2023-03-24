#include "test.hpp"

static std::vector<std::string> my_split(std::string line, char del) {
	std::vector<std::string> v_tokens;
	size_t pos;
	// if (line.at(line.length()-1) == '\n'){
	// 	std::cerr << "nope" << std::endl;
	// 	line.pop_back();
	// }
	while(1) {
		pos = line.find(del);
		v_tokens.push_back(line.substr(0, pos));
		if (pos == std::string::npos)
			break ;
		else
		{
			pos++;
			line = line.substr(pos, std::string::npos);
		}
	}
	return v_tokens;
}

void parse(std::string filename, t_data *data) {
	// std::ifstream infile(filename);
	std::ifstream infile;
	infile.open(filename);
	std::string line;
	std::vector<std::string> v_file;
	std::vector<std::vector<std::string> > v_lines;
	while (infile) {
		std::getline(infile, line);
		// std::cout << line << std::endl;
		if (infile)
			v_lines.push_back(my_split(line, ' '));
	}
	infile.close();
	for (std::vector<std::vector<std::string > >::iterator it = v_lines.begin(); it != v_lines.end(); it++)
	{
		if (!(*it).size())
			continue ;
		if (!(*it).at(0).compare("v")){
			if ((*it).size() != 4) {
				std::cerr << "VERTICES LINE WRONG, I SHOULD PROBABLY THROW AN EXCEPTION HERE" << std::endl;
				return ;
			}
			// data->v_vertices.push_back(std::stof((*it).at(1)));
			// data->v_vertices.push_back(std::stof((*it).at(2)));
			// data->v_vertices.push_back(std::stof((*it).at(3)));
			float fX = std::stof((*it).at(1));
			float fY = std::stof((*it).at(2));
			float fZ = std::stof((*it).at(3));
			if (fX > data->maxX)
				data->maxX = fX;
			if (fX < data->minX)
				data->minX = fX;
			if (fY > data->maxY)
				data->maxY = fY;
			if (fY < data->minY)
				data->minY = fY;
			if (fZ > data->maxZ)
				data->maxZ = fZ;
			if (fZ < data->minZ)
				data->minZ = fZ;
			data->v_vertices.push_back(fX);
			data->v_vertices.push_back(fY);
			data->v_vertices.push_back(fZ);
		}
		if (!(*it).at(0).compare("f")){
			t_face face;
			face.offset = data->v_indices.size();
			face.size = (*it).size() - 1;
			for (int i = 1; i <= face.size; i++)
				data->v_indices.push_back(std::stoi((*it).at(i)) - 1);
			data->v_faces.push_back(face);
		}
		// for (std::vector<std::string>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
		// 	std::cout << *it2 << ' ';
		// std::cout << std::endl;
	}
	// for (std::vector<std::string>::iterator it=file.begin(); it != file.end(); it++)
	// 	std::cout << *it;
	// std::vector<std::string> test = my_split(file.at(0), ' ');
	// for (std::vector<std::string>::iterator it=test.begin(); it != test.end(); it++)
	// 	std::cout << *it << std::endl;
	// std::cout << file;
}

// int main(){
// 	t_data data;
// 	parse("resources/42.obj", &data);
// 	std::cerr << data.v_vertices.size() << std::endl;
// 	std::cerr << data.v_indices.size() << std::endl;
// 	std::cerr << data.v_faces.size() << std::endl;
// 	for (std::vector<t_face>::iterator it=data.v_faces.begin(); it != data.v_faces.end(); it++){
// 		for (int i = 0; i < (*it).size; i++) {
// 			std::cerr << data.v_indices[(*it).offset + i] << ',';
// 		}
// 		std::cerr << std::endl;
// 	}
// 	for (int i = 0; i < data.v_vertices.size(); i++){
// 		std::cerr << data.v_vertices[i] << ',';
// 		if (i % 3 == 2)
// 			std::cerr << std::endl;
// 	}
// 	return 0;
// }