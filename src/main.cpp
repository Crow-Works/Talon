#include "YAML/YAMLMan.h"

#include <iostream>

int main(int argc, char* argv[])
{
    using namespace Talon;
    if(argc != 2)
    {
        std::cerr << "Usage: Talon <filename>.yaml" << std::endl;
        return -1;
    }

    std::string filename(argv[1]);

    YAMLMan yamlMan(filename);
    yamlMan.ParseYAMLFile();
    Config config = yamlMan.GetConfig();
    Projects proj = yamlMan.GetProjects();
    std::vector<Dependency> dependencies = yamlMan.GetDependencies();

    std::cout << "CONFIG:" << std::endl;
    std::cout << "\tBuild Directory: " << config.BuildDir << std::endl;
    std::cout << "\tDependency Directory: " << config.DependencyDir << std::endl;
    std::cout << "\tLibrary Directory: " << config.LibraryDir << std::endl;
    std::cout << "\tBinary Directory: " << config.BinaryDir << std::endl;
    std::cout << "\tBuild in parallel: " << (config.ParallelBuild ? "true" : "false") << std::endl;

    std::cout << "PROJECTS:" << std::endl;

    // Print Libraries
    std::cout << "\tLibraries:" << std::endl;
    for (const auto& library : proj.Libraries) 
    {
        std::cout << "\t- " << library.first << ": " << library.second << std::endl;
    }

    // Print Executable
    std::cout << "\tExecutable: " << proj.Executable << std::endl;
    
    std::cout << "DEPENDENCIES:" << std::endl;
    for(const auto& dependency : dependencies)
    {
        std::cout << "\tDependency: " << dependency.Name << " \n\tURL: " << dependency.URL << "\n=======" << std::endl;
    }

    return 0;
}
