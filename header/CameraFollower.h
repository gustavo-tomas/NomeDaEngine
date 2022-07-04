#ifndef CAMERAFOLLOWER_H
#define CAMERAFOLLOWER_H

#include "Component.h"

class CameraFollower : public Component {
    public:
        CameraFollower(GameObject& go);
        void Update(float dt);
        void Render();
        bool Is(const char* type);
};

#endif // CAMERAFOLLOWER_H