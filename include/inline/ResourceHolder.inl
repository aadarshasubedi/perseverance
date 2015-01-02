
template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string &fileName) {
    std::unique_ptr<Resource> newResource(new Resource);
    if (!newResource->loadFromFile(fileName)) {
        throw new std::runtime_error("ResourceHolder::load - Unable to load " + fileName);
    }
    auto inserted = resourceMap.insert(std::make_pair(id, std::move(newResource)));
    assert(inserted.second && "Resource already exists in holder");
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
    auto foundEntry = resourceMap.find(id);
    assert(resourceMap.end() != foundEntry);
    return *foundEntry->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
    auto foundEntry = resourceMap.find(id);
    assert(resourceMap.end() != foundEntry);
    return *foundEntry->second;
}