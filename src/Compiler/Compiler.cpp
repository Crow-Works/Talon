#include "Compiler/Compiler.h"
#include "YAML/YAMLMan.h"

#include <iostream>
#include <filesystem>

namespace Talon 
{
    bool Compiler::CompileDependency(const std::string& buildDir, const std::string& dependencyDir, const Dependency& dependency, const std::string& libDir)
    {
        std::string dependencyBuildDir = buildDir + "/dependencies/" + dependency.Name;
        std::string command = "cmake -G Ninja -S " + dependencyDir + "/" + dependency.Name + " -B " + dependencyBuildDir;

        // Execute the CMake command for the dependency
        int result = std::system(command.c_str());
        if (result != 0) 
        {
            std::cerr << "Error: Failed to generate build files for dependency " << dependency.Name << std::endl;
            return false;
        }

        // Execute the compilation command for the dependency
        command = "cmake --build " + dependencyBuildDir;
        result = std::system(command.c_str());
        if (result != 0) 
        {
            std::cerr << "Error: Failed to compile dependency " << dependency.Name << std::endl;
            return false;
        }

        // Move the output static library to the specified directory
        std::filesystem::create_directory(libDir);

        MoveLibraries(dependencyBuildDir, libDir, dependency.Name);
        
        std::cout << "Dependency " << dependency.Name << " compiled successfully." << std::endl;
        return true;
    }

    bool Compiler::CompileDependencies(const std::string& buildDir, const std::string& dependencyDir, const std::vector<Dependency>& dependencies, bool removeBuildDir, const std::string& libDir)
    {
        for (const auto& dependency : dependencies) 
        {
            if (!CompileDependency(buildDir, dependencyDir, dependency, libDir)) 
            {
                return false; // Abort if any dependency compilation fails
            }
        }
        
        if(removeBuildDir)
            std::filesystem::remove_all(buildDir);
        return true;
    }

    bool Compiler::MoveLibraries(const std::string& sourceDir, const std::string& targetDir, const std::string& dependencyName)
    {
        for (const auto& entry : std::filesystem::recursive_directory_iterator(sourceDir)) 
        {
            if (entry.is_regular_file() && entry.path().extension() == ".a") 
            {
                try 
                {
                    // Construct the full target file path by appending the original filename to the target directory
                    std::filesystem::path targetFile = std::filesystem::path(targetDir) / entry.path().filename();
                    std::filesystem::copy(entry, targetFile, std::filesystem::copy_options::overwrite_existing);
                    //return true; // Only move one library file
                } 
                catch (const std::exception& e) 
                {
                    std::cout << "Failed to move library file for dependency " << dependencyName << ": " << e.what() << std::endl;
                    return false;
                }
            }
        }
        return true;
    }
}
