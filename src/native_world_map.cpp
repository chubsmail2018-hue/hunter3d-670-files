#include "native_world_map.hpp"

#include "native_zombie.hpp"

using namespace godot;

NativeWorldMap::NativeWorldMap() {}

NativeWorldMap::~NativeWorldMap() {}

void NativeWorldMap::_ready() {
    if (m_zombie_scene.is_valid() == false) {
        UtilityFunctions::printerr("NativeWorldMap: zombie_scene is invalid.");
        return;
    }

    RandomNumberGenerator rng;
    rng.randomize();

    for (int i = 0; i < 10; ++i) {
        Node *instance = m_zombie_scene->instantiate();
        if (instance == nullptr) {
            continue;
        }

        NativeZombie *zombie = Object::cast_to<NativeZombie>(instance);
        if (zombie == nullptr) {
            instance->queue_free();
            continue;
        }

        zombie->set_global_position(Vector3(rng.randf_range(-30.0f, 30.0f), 0.0f, rng.randf_range(-30.0f, 30.0f)));
        add_child(zombie);
    }
}

void NativeWorldMap::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_zombie_scene", "value"), &NativeWorldMap::set_zombie_scene);
    ClassDB::bind_method(D_METHOD("get_zombie_scene"), &NativeWorldMap::get_zombie_scene);
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_SCENE, "zombie_scene"), "set_zombie_scene", "get_zombie_scene");
}

void NativeWorldMap::set_zombie_scene(const Ref<PackedScene> &p_scene) {
    m_zombie_scene = p_scene;
}

Ref<PackedScene> NativeWorldMap::get_zombie_scene() const {
    return m_zombie_scene;
}
