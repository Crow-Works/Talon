#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace Talon
{
    struct Config
    {
        std::string BuildDir;
        std::string BinaryDir;
        std::string LibraryDir;
        std::string DependencyDir;
        bool ParallelBuild;
    };

    struct Projects
    {
        // ProjecProject  Name, LibraryType
        std::unordered_map<std::string, std::string> Libraries;
        std::string Executable;
    };

    struct Dependency
    {
        std::string Name;
        std::string URL;
    };

    struct Build
    {
        std::vector<std::string> IncludeDirs;
        // Project Name, Directory
        std::vector<std::unordered_map<std::string, std::string>> SourceDirs;
    };

    struct Compiler
    {
        std::string CXXCompiler;
        std::string CCompiler;
        std::string CXXStandards;
        std::string CStandard;
        std::vector<std::string> CompilerFlags;
        std::string OptimizationLevel;
    };

    struct Link
    {
        // Project Name, Dependency
        std::string LinkProjects;
    };    

    class YAMLMan
    {
    public:
        YAMLMan(const std::string& filename);
        
        void ParseYAMLFile();

        std::vector<Dependency> GetDependencies() { return m_Dependencies; }
        Config GetConfig() const { return m_Config; }
        Projects GetProjects() const { return m_Projects; }
        Build GetBuild() const { return m_Build; }
        Compiler GetCompiler() const { return m_Compiler; }
        std::vector<Link> GetLinkProjects() const { return m_LinksProjects; }

    private:
        void ParseConfig(const std::string& line);
        void ParseDependency(const std::string& line);
        void ParseProjects(const std::string& line);
        void ParseBuild(const std::string& line);
        void ParseCompiler(const std::string& line);
        void ParseLink(const std::string& line);

    private:
        Config m_Config;
        Projects m_Projects;
        Build m_Build;
        Compiler m_Compiler;
        std::vector<Dependency> m_Dependencies;
        std::vector<Link> m_LinksProjects;
        std::string m_Filename;

        static std::string Trim(const std::string& str);
    };
}
