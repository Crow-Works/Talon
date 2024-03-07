#include "YAML/YAMLMan.h"
#include "Compiler/Compiler.h"

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
    std::vector<Dependency> dependencies = yamlMan.GetDependencies();
    Config config = yamlMan.GetConfig();

    std::string buildDir = config.BuildDir; 
    std::string dependencyDir = config.DependencyDir;
    std::string libDir = config.LibraryDir;
    bool removeBuildDir = config.RemoveBuildDir;

    for(const auto& dependency : dependencies)
    {
        std::system(("git clone --recursive " + dependency.URL + " " + dependencyDir + "/" + dependency.Name).c_str());
    }

    Compiler* compiler;
    if(!compiler->CompileDependencies(buildDir, dependencyDir, dependencies, removeBuildDir, libDir))
    {
        std::cout << "Compilation failed!" << std::endl;
        return -1;
    }

    std::cout << "Compilation finished successfully!" << std::endl;
    std::cout << "Make sure to link the Compiled libraries in your CMakeLists.txt!" << std::endl;

    return 0;
}
