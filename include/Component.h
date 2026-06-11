#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;
struct UpdateContext;
struct RenderContext;

class Component {
public:
    Component();
    virtual ~Component();

    // Core lifecycle methods. Engine systems (input, renderer, fonts,
    // textures) arrive through the contexts — no globals.
    virtual void Update(const UpdateContext& ctx) {}
    virtual void Render(const RenderContext& ctx, float alpha) {}

    // Collision callbacks (fired by Physics system)
    virtual void OnCollisionEnter(GameObject* other) {}
    virtual void OnCollisionStay(GameObject* other)  {}
    virtual void OnCollisionExit(GameObject* other)  {}

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
