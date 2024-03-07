#pragma once

#include <string>
#include <vector>

namespace Talon 
{
    struct Dependency;
    class Compiler
    {
    public:
        Compiler();

        bool CompileDependency(const std::string& buildDir, const std::string& dependencyDir, const Dependency& dependency, const std::string& libDir);
        bool CompileDependencies(const std::string& buildDir, const std::string& dependencyDir, const std::vector<Dependency>& dependencies, bool removeBuildDir, const std::string& libDir);

    private:
        bool MoveLibraries(const std::string& sourceDir, const std::string& targetDir, const std::string& dependencyName);      
    };
}
