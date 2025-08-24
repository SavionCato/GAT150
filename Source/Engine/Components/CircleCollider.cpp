#include "EnginePCH.h"
#include "CircleCollider.h"

namespace Rex {

    void CircleCollider2D::Update(float dt) {

        //
    }

    bool CircleCollider2D::CheckCollider(ColliderComponent& other) {

        float distance = (owner->transform.position - other.owner->transform.position).Length();
        auto collider = dynamic_cast<CircleCollider2D*>(&other);

        if (collider) {

            float radii = radius + collider->radius;
            if(distance <= radii) return true;
        }      

        return false;
    }
}