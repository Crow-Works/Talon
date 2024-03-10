#include "YAML/YAMLMan.h"

#include <iostream>

void PrintParsedYAML(const std::string& filename)
{

    using namespace Talon;
    YAMLMan yamlMan(filename);
    yamlMan.ParseYAMLFile();
    Config config = yamlMan.GetConfig();
    Projects proj = yamlMan.GetProjects();
    Build build = yamlMan.GetBuild();
    Compiler comp = yamlMan.GetCompiler();
    std::vector<Link> lnk = yamlMan.GetLinkProjects();
    std::vector<Dependency> dependencies = yamlMan.GetDependencies();


    std::cout << "CONFIG:" << std::endl;
    std::cout << "\tBuild Directory: " << config.BuildDir << std::endl;
    std::cout << "\tDependency Directory: " << config.DependencyDir << std::endl;
    std::cout << "\tLibrary Directory: " << config.LibraryDir << std::endl;
    std::cout << "\tBinary Directory: " << config.BinaryDir << std::endl;
    std::cout << "\tBuild in parallel: " << (config.ParallelBuild ? "true" : "false") << "\n==============" << std::endl;


    std::cout << "PROJECTS:" << std::endl;
    // Print Libraries
    std::cout << "\tLibraries:\n\t{" << std::endl;
    for (const auto& library : proj.Libraries) 
    {
        std::cout << "\t    -" << library.first << ": " << library.second << std::endl;
    }
    std::cout << "\t}" << std::endl;
    // Print Executable
    std::cout << "\tExecutable: " << proj.Executable << "\n==============" << std::endl;
    

    std::cout << "DEPENDENCIES:" << std::endl;
    for(const auto& dependency : dependencies)
    {
        std::cout << "\tDependency: " << dependency.Name << " \n\tURL: " << dependency.URL << "\n\t--------------" << std::endl;
    }
    std::cout << "==============" << std::endl;

    std::cout << "BUILD:" << std::endl;
    for(const auto& dir : build.IncludeDirs)
    {
        std::cout << "Include Directory: " << dir << std::endl;
    }
    for(const auto& dir : build.SourceDirs)
    {
        std::cout << "Project: " << dir.first << " Source Directory: " << dir.second << std::endl;
    }
    std::cout << "==============" << std::endl;


    std::cout << "COMPILER:" << std::endl;
    std::cout << "\tCXXCompiler: " << comp.CXXCompiler << std::endl;
    std::cout << "\tCCompiler: " << comp.CCompiler << std::endl;
    std::cout << "\tCXXStandard: " << comp.CXXStandard << std::endl;
    std::cout << "\tCStandard: " << comp.CStandard << std::endl;
    std::cout << "\tCompilerFlags: " << std::endl;
    for(const auto& flag : comp.CompilerFlags)
    {
        std::cout << "\t" << flag << std::endl;
    }
    std::cout << "\tOptimizationLevel: " << comp.OptimizationLevel << "\n==============" << std::endl;

    std::cout << "LINK:" << std::endl;
    for(const auto& linkProj : lnk)
    {
        std::cout << "\tLink '" << linkProj.LinkSrc << "' into " << linkProj.LinkTarget << std::endl;
    }
    std::cout << "==============" << std::endl;
}

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cerr << "Usage: Talon <filename>.yaml" << std::endl;
        return -1;
    }

    std::string filename(argv[1]);

    PrintParsedYAML(filename);

    return 0;
}
