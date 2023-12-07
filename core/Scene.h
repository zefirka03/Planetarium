#pragma once
#include "AirUtils.h"
#include "ECS.h"

#include <vector>

AIR_NAMESPACE_BEGIN

class SceneBase {
public:
    virtual void start() = 0;
    ~SceneBase();

protected:
    std::vector<System*> m_systems;

private:
    friend class Game;
    void _update_systems();
    void _start_systems();
};


template <typename... Systems>
class Scene : public SceneBase {
public:
    Scene() {
        (m_systems.emplace_back(new Systems()), ...);
    }
};

AIR_NAMESPACE_END
