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

    struct Config
    {
        std::string DependencyDir;
        std::string BuildDir;
        std::string LibraryDir;
        bool RemoveBuildDir;
    };

    class YAMLMan
    {
    public:
        YAMLMan(const std::string& filename);
        
        void ParseYAMLFile();
        void ParseConfig(const std::string& line);
        void ParseDependency(const std::string& line);

        std::vector<Dependency> GetDependencies() { return m_Dependencies; }
        Config GetConfig() const { return m_Config; }

    private:
        Config m_Config;
        std::vector<Dependency> m_Dependencies;
        std::string m_Filename;

        static std::string Trim(const std::string& str);
    };
}
