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
        
        std::vector<Dependency> GetDependencies() { return m_Dependencies; }
    private:
        void Trim(std::string& str) const;
        
        std::vector<Dependency> m_Dependencies;
    };
}
