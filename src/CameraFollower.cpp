#include "../header/CameraFollower.h"
#include "../header/Camera.h"
#include <string>

using namespace std;

CameraFollower::CameraFollower(GameObject& go) : Component(go)
{

}

void CameraFollower::Update(float dt)
{
    associated.box.x = Camera::GetInstance().pos.x;
    associated.box.y = Camera::GetInstance().pos.y;
}

void CameraFollower::Render()
{

}

bool CameraFollower::Is(const char* type)
{
    string str_type = type;
    return str_type == "CameraFollower";
}