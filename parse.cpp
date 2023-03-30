#include "scop.hpp"

static std::vector<std::string> my_split(std::string line, char del) {
	std::vector<std::string> v_tokens;
	size_t pos;
	while(1) {
		pos = line.find(del);
		if (pos) {
			v_tokens.push_back(line.substr(0, pos));
			if (pos == std::string::npos)
				break ;
		}
		pos++;
		line = line.substr(pos, std::string::npos);
	}
	return v_tokens;
}

void parse(std::string filename, t_data *data) {
	std::ifstream infile;
	int pos;
	infile.open(filename);
	std::string line;
	std::vector<std::vector<std::string> > v_lines;
	while (infile) {
		std::getline(infile, line);
		pos = line.find_last_not_of(" \t\n\v\f\r");
		if (pos != std::string::npos && pos != line.size() - 1)
			line.erase(line.begin() + pos, line.end());
		if (infile)
			v_lines.push_back(my_split(line, ' '));
	}
	infile.close();
	for (std::vector<std::vector<std::string > >::iterator it = v_lines.begin(); it != v_lines.end(); it++)
	{
		std::vector<std::string> line = *it;
		if (!line.size())
			continue ;
		if (!line.at(0).compare("v")){
			if (line.size() != 4) {
				std::cerr << "VERTICES LINE WRONG, I SHOULD PROBABLY THROW AN EXCEPTION HERE" << std::endl;
				return ;
			}
			float fX = std::stof(line.at(1));
			float fY = std::stof(line.at(2));
			float fZ = std::stof(line.at(3));
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
		if (!line.at(0).compare("f")){
			t_face face;
			face.offset = data->v_indices.size();
			face.size = line.size() - 1;
			for (int i = 1; i <= face.size; i++) {
				data->v_indices.push_back(std::stoi(line.at(i)) - 1);
			}
			data->v_faces.push_back(face);
		}
	}
}