#include "../include/GameObject.h"
#include "../include/Component.h"
#include "../include/Transform.h"

unsigned int GameObject::nextID = 1;

GameObject::GameObject(const std::string &name)
    : name(name), isActive(true), pendingDestroy(false), id(nextID++),
      engine(nullptr), transform(nullptr) {

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

bool GameObject::IsActive() const { return isActive && !pendingDestroy; }

void GameObject::SetName(const std::string &n) { name = n; }

const std::string &GameObject::GetName() const { return name; }

Transform *GameObject::GetTransform() { return transform; }

Engine *GameObject::GetEngine() const { return engine; }

void GameObject::SetEngine(Engine *e) { engine = e; }

void GameObject::MarkForDestroy() { pendingDestroy = true; }

bool GameObject::IsPendingDestroy() const { return pendingDestroy; }

unsigned int GameObject::GetID() const { return id; }

void GameObject::Update(const UpdateContext &ctx) {
  if (!IsActive())
    return;

  // Update all components
  for (auto &pair : components) {
    if (pair.second->IsActive()) {
      pair.second->Update(ctx);
    }
  }
}

void GameObject::Render(const RenderContext &ctx, float alpha) {
  if (!IsActive())
    return;

  // Render all components
  for (auto &pair : components) {
    if (pair.second->IsActive()) {
      pair.second->Render(ctx, alpha);
    }
  }
}

void GameObject::OnCollisionEnter(GameObject *other) {
  for (auto &pair : components)
    if (pair.second->IsActive()) pair.second->OnCollisionEnter(other);
}

void GameObject::OnCollisionStay(GameObject *other) {
  for (auto &pair : components)
    if (pair.second->IsActive()) pair.second->OnCollisionStay(other);
}

void GameObject::OnCollisionExit(GameObject *other) {
  for (auto &pair : components)
    if (pair.second->IsActive()) pair.second->OnCollisionExit(other);
}
