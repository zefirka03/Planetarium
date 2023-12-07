#include "Scene.h"

AIR_NAMESPACE_BEGIN

SceneBase::~SceneBase() {
    for (auto system : m_systems)
        delete system.second;
}


void SceneBase::_update_systems() {
	for (auto system : m_systems)
		system.second->update();
}


void SceneBase::_start_systems() {
	for (auto system : m_systems)
		system.second->start();
}

AIR_NAMESPACE_END