#include "opengltings/glHelper.h"

std::string ShaderReader(std::string p_file) {
    std::string e_source {};
    while(std::getline(p_file, line)){
        e_source += line + "\n";
    }
    return e_source;
}
