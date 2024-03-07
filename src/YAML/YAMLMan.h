#pragma once

#include <string>
#include <vector>

namespace Talon
{
    struct Dependency
    {
        std::string Name;
        std::string URL;
    };

    class YAMLMan
    {
    public:
        YAMLMan(const std::string& filename);
        
        void ParseYAMLFile(const std::string& filename);
        void ParseConfig(const std::string& line);
        void ParseDependency(const std::string& line);

        std::vector<Dependency> GetDependencies() { return m_Dependencies; }
        std::string GetDependencyDir() const { return m_DependencyDir; }

    private:
        std::string m_Filename;
        std::string m_DependencyDir;
        std::vector<Dependency> m_Dependencies;
    };
}
