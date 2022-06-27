#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component {
    public:
        Component(GameObject& associated);
        virtual ~Component();
        void virtual Update(float dt) = 0; // pure
        void virtual Render() = 0; // pure
        bool virtual Is(const char* type) = 0; // pure

    protected:
        GameObject& associated;
};

#endif // COMPONENT_H