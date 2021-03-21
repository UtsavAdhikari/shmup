#pragma once

#include <map>
#include <memory>
#include <stdexcept>

template <typename Resource, typename Identifier>
class ResourceBank
{
public:
    void load(Identifier id, const std::string& filename)
    {
        printf("Loading resource: \"%s\"\n", filename.c_str());
        auto resource = std::make_shared<Resource>();

        // TODO: probably not throw
        if (! resource->loadFromFile(filename))
            throw std::runtime_error("Failed to load resource: " + filename);

        m_resourceMap.insert({id, std::move(resource)});
    }

    Resource& get(Identifier id)
    {
        auto found = m_resourceMap.find(id);
        
        if (found == m_resourceMap.end())
            throw std::runtime_error("Failed to find resource: " + std::to_string((int)id));

        return *found->second;
    }

    const Resource& get(Identifier id) const
    {
        auto found = m_resourceMap.find(id);
        
        if (found == m_resourceMap.end())
            throw std::runtime_error("Failed to find resource: " + std::to_string((int)id));

        return *found->second;
    }

private:
    std::map<Identifier, std::shared_ptr<Resource>> m_resourceMap;

};