#include "opengltings/glHelper.h"

std::string ShaderReader(std::string p_file) {
    std::string e_source, e_line {};

    std::ifstream theFile(p_file);
    if(theFile.is_open()){
        while(std::getline(theFile, e_line)){
            e_source += e_line + "\n";
        }
        theFile.close();
    }
    else {
        std::cerr << "error opening file";
    }
    return e_source;
}
