#ifndef RESOURCES_HOLDER_HPP
#define RESOURCES_HOLDER_HPP

#include <map>
#include <memory>
#include <string>
#include <assert.h>
#include <stdexcept>

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
    void load(Identifier id, const std::string& fileName);
    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

private:
    std::map<Identifier, std::unique_ptr<Resource>> resourceMap;
};

#include "inline/ResourceHolder.inl"

#endif //RESOURCES_HOLDER_HPP