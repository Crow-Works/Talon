#include "YAML/YAMLMan.h"

#include <iostream>



int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "Usage: Talon <filename>.yaml" << std::endl;
        return -1;
    }

    std::string filename(argv[1]);

    Talon::YAMLMan yamlMan(filename);

    std::vector<Talon::Dependency> dependencies = yamlMan.GetDependencies();
        
    std::cout << "Dependencies:" << std::endl;
    for(const auto& dependency : dependencies)
    {
        std::cout << "Name: " << dependency.Name << ", URL: " << dependency.URL << std::endl;
    }

    return 0;
}
