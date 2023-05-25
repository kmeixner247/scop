#include "../Material.hpp"
#include <fstream>

int main() {
    std::ifstream file("test.mtl");
    // std::string fileContents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::string line;
    std::string_view lineView;
    while (std::getline(file, line)) {
        lineView = line;
        auto commentPos = lineView.find('#');
        if (commentPos != lineView.npos)
            lineView.remove_suffix(lineView.size() - commentPos);
        auto endPos = lineView.find_last_not_of(" \t\n\v\f\r");
        if (endPos <= lineView.size())
            lineView.remove_suffix(lineView.size() - endPos);
        if (lineView.starts_with("newmtl"))
            std::cout << lineView << std::endl;

    }
}