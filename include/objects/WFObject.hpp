#pragme once

#include <vector>
#include "../math/vec3.hpp"
#include "../math/vec2.hpp"
class WFObject {
private:
    std::vector<ft::vec3> _v_vertices;
    std::vector<ft::vec3> _v_texcoords;
    std::vector<ft::vec3> _v_normals;
    std::vector<int> _v_indices;
public:
    WFObject();
    WFObject(std::string const &path);
};