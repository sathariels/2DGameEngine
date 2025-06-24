#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <string>

// Forward declaration
class Component;
class Transform;

class GameObject {
public:
    GameObject(const std::string& name = "GameObject");
    ~GameObject();

    // Component management
    template<typename T, typename... Args>
    T* AddComponent(Args&&... args);
    
    template<typename T>
    T* GetComponent();
    
    template<typename T>
    bool HasComponent();
    
    template<typename T>
    void RemoveComponent();

    // GameObject management
    void SetActive(bool active);
    bool IsActive() const;
    
    void SetName(const std::string& name);
    const std::string& GetName() const;
    
    // Transform is so common, provide direct access
    Transform* GetTransform();
    
    // Update all components
    void Update(float deltaTime);
    void Render();
    
    // Unique ID for this GameObject
    unsigned int GetID() const;

private:
    std::string name;
    bool isActive;
    unsigned int id;
    
    // Component storage
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;
    
    // Cache transform for quick access
    Transform* transform;
    
    // Static ID counter
    static unsigned int nextID;
    
    void InitializeTransform();
};

// Template implementations (must be in header)
template<typename T, typename... Args>
T* GameObject::AddComponent(Args&&... args) {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
    
    std::type_index typeIndex(typeid(T));
    
    // Don't allow duplicate components of the same type
    if (components.find(typeIndex) != components.end()) {
        return static_cast<T*>(components[typeIndex].get());
    }
    
    auto component = std::make_unique<T>(std::forward<Args>(args)...);
    T* componentPtr = component.get();
    
    // Set the owner
    componentPtr->SetOwner(this);
    
    components[typeIndex] = std::move(component);
    
    return componentPtr;
}

template<typename T>
T* GameObject::GetComponent() {
    static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");
    
    std::type_index typeIndex(typeid(T));
    auto it = components.find(typeIndex);
    
    if (it != components.end()) {
        return static_cast<T*>(it->second.get());
    }
    
    return nullptr;
}

template<typename T>
bool GameObject::HasComponent() {
    std::type_index typeIndex(typeid(T));
    return components.find(typeIndex) != components.end();
}

template<typename T>
void GameObject::RemoveComponent() {
    std::type_index typeIndex(typeid(T));
    components.erase(typeIndex);
}

#endif // GAMEOBJECT_H