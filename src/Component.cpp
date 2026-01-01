#include "../include/Component.h"

Component::Component() : owner(nullptr), isActive(true) {}

Component::~Component() {}

void Component::SetOwner(GameObject *owner) { this->owner = owner; }

GameObject *Component::GetOwner() const { return owner; }

void Component::SetActive(bool active) { this->isActive = active; }

bool Component::IsActive() const { return isActive; }
