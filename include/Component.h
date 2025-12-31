#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component {
public:
    Component();
    virtual ~Component();

    // Core lifecycle methods
    virtual void Update(float deltaTime) {}
    virtual void Render() {}

    // Owner management
    void SetOwner(GameObject* owner);
    GameObject* GetOwner() const;

    // Component state
    void SetActive(bool active);
    bool IsActive() const;

protected:
    GameObject* owner;
    bool isActive;
};

#endif // COMPONENT_H
