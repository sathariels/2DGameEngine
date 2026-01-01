#include "../include/GameObject.h"
#include "../include/Component.h"
#include "../include/Transform.h"
#include <iostream>

unsigned int GameObject::nextID = 1;

GameObject::GameObject(const std::string &name)
    : name(name), isActive(true), id(nextID++), transform(nullptr) {

  // Every GameObject has a Transform
  InitializeTransform();
}

GameObject::~GameObject() {
  // Components are unique_ptrs so they clean themselves up
  components.clear();
}

void GameObject::InitializeTransform() {
  // Manually add Transform to ensure it's always the first component
  // and we cache the pointer
  auto transformComponent = std::make_unique<Transform>();
  transform = transformComponent.get();
  transformComponent->SetOwner(this);

  std::type_index typeIndex(typeid(Transform));
  components[typeIndex] = std::move(transformComponent);
}

void GameObject::SetActive(bool active) { isActive = active; }

bool GameObject::IsActive() const { return isActive; }

void GameObject::SetName(const std::string &n) { name = n; }

const std::string &GameObject::GetName() const { return name; }

Transform *GameObject::GetTransform() { return transform; }

unsigned int GameObject::GetID() const { return id; }

void GameObject::Update(float deltaTime) {
  if (!isActive)
    return;

  // Update all components
  for (auto &pair : components) {
    if (pair.second->IsActive()) {
      pair.second->Update(deltaTime);
    }
  }
}

void GameObject::Render() {
  if (!isActive)
    return;

  // Render all components
  for (auto &pair : components) {
    if (pair.second->IsActive()) {
      pair.second->Render();
    }
  }
}
