#pragma once

#include <godot_cpp/classes/node_3d.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/vector3.hpp>

namespace godot {

class NativeWorldMap : public Node3D {
    GDCLASS(NativeWorldMap, Node3D)

public:
    NativeWorldMap();
    ~NativeWorldMap() override;

    void _ready() override;
    static void _bind_methods();

    void set_zombie_scene(const Ref<PackedScene> &p_scene);
    Ref<PackedScene> get_zombie_scene() const;

private:
    Ref<PackedScene> m_zombie_scene;
};

} // namespace godot
