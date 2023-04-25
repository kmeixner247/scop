#include "scop.hpp"


static size_t find_character(const std::string &s, char c) {
	return (s.find(c));
}

static void cut_string_after_pos(std::string &s, size_t pos) {
	s = s.substr(pos + 1);
}

static std::vector<std::string> split_string_by(std::string &str, char del) {
	std::vector<std::string> v_tokens;
	size_t pos;
	while (1) {
		pos = find_character(str, del);
		if (pos > 0)
			v_tokens.push_back(str.substr(0, pos));
		if (pos == std::string::npos)
			break ;
		cut_string_after_pos(str, pos);
	}
	return v_tokens;
}

static void trim_whitespace_after(std::string *s) {
	size_t pos = (*s).find_last_not_of(" \t\n\v\f\r");
	if (pos != std::string::npos && pos != (*s).size() - 1)
		(*s).erase((*s).begin() + pos, (*s).end());
}

static std::vector<std::vector<std::string> > get_trimmed_lines(std::string filename) {
	std::ifstream infile;
	std::string line;
	std::vector<std::vector<std::string> > v_lines;

	infile.open(filename);
	while (infile) {
		std::getline(infile, line);
		trim_whitespace_after(&line);
		if (infile)
			v_lines.push_back(split_string_by(line, ' '));
	}
	infile.close();
	return v_lines;
}

void parse(std::string filename, t_data *data) {
	std::vector<std::vector<std::string> > v_lines = get_trimmed_lines(filename);
	t_vbo_element e;
	int index = 0;
	for (std::vector<std::vector<std::string > >::iterator it = v_lines.begin(); it != v_lines.end(); it++)
	{
		std::vector<std::string> line = *it;
		if (!line.size())
			continue ;
		if (!line.at(0).compare("v")) {
			if (line.size() != 4) {
				std::cerr << "VERTICES LINE WRONG, I SHOULD PROBABLY THROW AN EXCEPTION HERE" << std::endl;
				return ;
			}
			e.vertex.x = std::stof(line.at(1));
			e.vertex.y = std::stof(line.at(2));
			e.vertex.z = std::stof(line.at(3));
			data->vbo.push_back(e);
		}
		if (!line.at(0).compare("vt")) {
			e.texcoords.x = std::stof(line.at(1));
			e.texcoords.y = std::stof(line.at(2));
			data->vbo.push_back(e);
		}
		if (!line.at(0).compare("f")) {
			t_face face;
			face.size = line.size() - 1;
			face.raw = line;
			data->v_faces.push_back(face);
		}
	}
	for (std::vector<t_face>::iterator it = data->v_faces.begin(); it != data->v_faces.end(); it++) {
		(*it).offset = data->v_indices.size();
		for (int i = 1; i <= (*it).size; i++) {
			std::vector<std::string> elements = split_string_by((*it).raw.at(i), '/');
			index = std::stoi(elements[0]) - 1;
			data->v_indices.push_back(index);
			(*it).vertices.push_back(data->vbo[index].vertex);
			if (elements.size() > 1)
				(*it).texcoords.push_back(data->vbo[index].texcoords);
		}
		(*it).normal = ft::crossproduct((*it).vertices[0], (*it).vertices[1]);
	}
}
