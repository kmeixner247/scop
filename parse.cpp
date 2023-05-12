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

static void trim_whitespace_after(std::string &s) {
	size_t pos = s.find_last_not_of(" \t\n\v\f\r");
	if (pos != std::string::npos && pos != s.size() - 1)
		s.erase(s.begin() + pos + 1, s.end());
}

static std::vector<std::vector<std::string> > get_trimmed_lines(const std::string &filename) {
	std::ifstream infile;
	std::string line;
	std::vector<std::vector<std::string> > v_lines;

	infile.open(filename);
	while (infile) {
		std::getline(infile, line);
		trim_whitespace_after(line);
		if (infile) {
			v_lines.push_back(split_string_by(line, ' '));
		}
	}
	infile.close();
	return v_lines;
}

void parse(const std::string &filename, t_data &data) {
	std::vector<std::vector<std::string> > v_lines = get_trimmed_lines(filename);
	
	t_vbo_element e;
	for (std::vector<std::string> &line : v_lines) {
		if (line.size() == 0)
			continue;
		if (line[0].compare("v") == 0) {
			ft::vec3 vertex;
			vertex.x = std::stof(line.at(1));
			vertex.y = std::stof(line.at(2));
			vertex.z = std::stof(line.at(3));
			data.v_vertices.push_back(vertex);
		}
		if (line[0].compare("vt") == 0) {
			ft::vec2 texcoords;
			texcoords.x = std::stof(line.at(1));
			texcoords.y = std::stof(line.at(2));
			data.v_texcoords.push_back(texcoords);
		}
		if (line[0].compare("vn") == 0) {
			ft::vec3 normal;
			normal.x = std::stof(line.at(1));
			normal.y = std::stof(line.at(2));
			normal.z = std::stof(line.at(3));
			data.v_normals.push_back(normal);
		}
		if (line[0].compare("f") == 0) {
			t_face face;
			face.size = line.size() - 1;
			face.raw = line;
			data.v_faces.push_back(face);	
		}
	}
	// for (auto &&line : v_lines) {
	// 	if (!line.size())
	// 		continue ;
	// 	if (!line.at(0).compare("v")) {
	// 		if (line.size() != 4) {
	// 			std::cerr << "VERTICES LINE WRONG, I SHOULD PROBABLY THROW AN EXCEPTION HERE" << std::endl;
	// 			return ;
	// 		}
	// 		e.vertex.x = std::stof(line.at(1));
	// 		e.vertex.y = std::stof(line.at(2));
	// 		e.vertex.z = std::stof(line.at(3));
	// 		data.vbo.push_back(e);
	// 	}
	// 	if (!line.at(0).compare("vt")) {
	// 		e.texcoords.x = std::stof(line.at(1));
	// 		e.texcoords.y = std::stof(line.at(2));
	// 		data.vbo.push_back(e);
	// 	}
	// 	if (!line.at(0).compare("f")) {
	// 		t_face face;
	// 		face.size = line.size() - 1;
	// 		face.raw = line;
	// 		data.v_faces.push_back(face);
	// 	}
	// }
	//create vbo here i guess lol
	int lol = 0;
	for (t_face &face : data.v_faces) {
		int v_index = -1;
		int t_index = -1;
		int n_index = -1;
		face.offset = data.v_indices.size();
		for (int i = 1; i <= face.size; i++) {;
			std::vector<std::string> elements = split_string_by(face.raw.at(i), '/');
			v_index = std::stoi(elements[0]) - 1;
			e.vertex = data.v_vertices[v_index];
			if (elements.size() > 1) {
				t_index = std::stoi(elements[1]) - 1;
				if (data.v_texcoords.size() > 0)
					e.texcoords = data.v_texcoords[t_index];
				else
					e.texcoords = ft::vec2(0.0f);
			}
			if (elements.size() > 1) {
				n_index = std::stoi(elements[1]) - 1;
				e.normal = data.v_normals[n_index];
			}
			data.v_indices.push_back(lol++);
			data.vbo.push_back(e);
		}
		// face.normal = ft::crossproduct(face.vertices[0], face.vertices[1]);
	}
}
