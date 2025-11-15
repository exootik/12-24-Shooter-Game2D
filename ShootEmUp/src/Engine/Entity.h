#pragma once

class Scene;
class Sprite;
class Color;
class Animation;
class MyWindow;

#include "DrawableShapes.h"

class Entity
{
    enum COLLIDER_SHAPES
    {
        CIRCLE, RECT
    };

    struct Target 
    {
		Vect2 position;
        float distance;
		bool isSet;
    };

protected:

    Sprite* m_pSprite;
    RectShape* m_pShape;

    DrawableShape* m_pColliderShape;
    COLLIDER_SHAPES m_colliderShape;

    float m_width, m_height;
    
    Vect2 m_direction;
	Target m_target;
    float m_speed;
    int m_tag;
    std::list<int> m_tagWithoutCollision;

    Vect2 m_colliderPos;
    Vect2 m_pos;
    Vect2 m_scale;
    Vect2 m_origin;
    
    const char* m_name;

    bool m_hasCollision;
    bool m_isColliderDisplay;
    bool m_colliderhasSameSize; // false if you change collider size

    int m_layer;
    Animation* m_pCurrentAnimation;
    int m_currentFrameIndex; 
    float m_currentFrameTime;

    bool m_toDestroy;

    Scene* m_pScene;

public:
    // Set Entity Position & Direction

	bool GoToDirection(float x, float y, float speed = -1.f);
    bool GoToPosition(float x, float y, float speed = -1.f);
    
    void SetPosition(float x, float y);
    void SetPosition(float x, float y, float ratioX, float ratioY );
    void SetPosition(Vect2 pos);
    Vect2 GetPosition();
    Vect2 GetPositionWithCustomOrigin(float ratioX, float ratioY);

    // Settter & Getter

	void SetDirection(float x, float y, float speed = -1.f);
	void SetSpeed(float speed) { m_speed = speed; }
    float GetSpeed() { return m_speed; }

	void SetTag(int tag) { m_tag = tag; }
    int GetTag() { return m_tag; }

    void SetName(const char* name) { m_name = name; }
    const char* GetName() { return m_name; }

    void SetScale(Vect2 scale);
    void SetScale(float scaleX, float scaleY);
    Vect2 GetScale() { return m_scale; }
    
    void SetWidth(float width);
    void SetHeight(float height);
    void SetSize(float width, float height);
    float GetWidth() { return m_width * m_scale.m_x; }
    float GetHeight() { return m_height * m_scale.m_y; }

    void SetOrigin(Vect2 origin) { m_origin = origin; }
    Vect2 GetOrigin() { return m_origin; }
    
    void SetLayer(int layer);
    int GetLayer() { return m_layer; }

    void SetSprite(Sprite* pSprite);
    Sprite* GetSprite() { return m_pSprite; }
    RectShape* GetRect() { return m_pShape; }

    //Collision

    bool HasCollision() { return m_hasCollision; }
    bool IsColliding(Entity* other);
	bool IsInside(float x, float y);
    
    bool IsCollidingRect(Entity* other);
    bool IsCollidingCircle(Entity* other);
	
    bool IsInsideRect(float x, float y);
	bool IsInsideCircle(float x, float y);


    void ShowCollision(bool show) { m_isColliderDisplay = show; }
    bool AllowedCollision(Entity* pEntity);
    void AddTagWithoutCollision(int tag) { m_tagWithoutCollision.push_back(tag); }

    //Collider

    //Set Collision Position (0.0) is top Left Corener of the Entity
    void SetCollisionPosition(Vect2 pos) { m_colliderPos = pos; }
    // If not set based on the entity
    void SetCollisionSize(float width, float height = 0.f);
    //// If not set based on the entity
    void SetCollisionScale(float scale) { m_pColliderShape->SetScale(scale,scale); }
    //// If not set based on the entity
    template <typename T>
    T GetColliderShape();
    // Reset Collider Pos,Size,Color,Scale same as the Entity
    void SetColliderOnEntity(); 

	bool IsTag(int tag) const { return m_tag == tag; }

	void Destroy() { m_toDestroy = true; }
	bool ToDestroy() const { return m_toDestroy; }

	template<typename T>
	T* GetScene() const;
    Scene* GetScene() const;

	float GetDeltaTime() const;
	
    bool PlayAnimation(const char* animationName);
    void StopAnimation();

    template<typename T>
    T* CreateEntity(float width, float height, int layer, const Color& color);

    template<typename T>
    T* CreateEntity(float width, float height, Sprite* pSprite, int layer);

    Entity(float width, float height, int layer, bool hasCollision, const Color& color, Scene* pScene, COLLIDER_SHAPES shape = CIRCLE);

protected:
    Entity() = default;
    ~Entity() = default;

    virtual void OnDraw(MyWindow* pWindow) {};
    virtual void OnUpdate() {};
    virtual void OnFixedUpdate() {};
    virtual void OnCollision(Entity* collidedWith) {};
	virtual void OnInitialize() {};

    DrawableShape* SetColliderCircle(Color& colliderColor, float radius);
    DrawableShape* SetColliderRect(Color& colliderColor, float width, float height);

private:
    void Update();
    void FixedUpdate();
    void DrawCollider(MyWindow* pWindow);

    friend class GameManager;
    friend Scene;
    friend class WindowSFML;
    friend class WindowRender;
};

#include "Entity.inl"