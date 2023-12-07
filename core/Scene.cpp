#include "Scene.h"

AIR_NAMESPACE_BEGIN

SceneBase::~SceneBase() {
    for (System* system : m_systems)
        delete system;
}


void SceneBase::_update_systems() {
	for (System* system : m_systems)
		system->update();
}


void SceneBase::_start_systems() {
	for (System* system : m_systems)
		system->start();
}

AIR_NAMESPACE_END