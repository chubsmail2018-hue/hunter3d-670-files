#pragma once

#include <godot_cpp/classes/character_body_3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/ray_cast_3d.hpp>
#include <godot_cpp/classes/camera_3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/vector3.hpp>

namespace godot {

class NativeHunter : public CharacterBody3D {
    GDCLASS(NativeHunter, CharacterBody3D)

public:
    enum WeaponType {
        WEAPON_GUN = 0,
        WEAPON_SWORD = 1
    };

    NativeHunter();
    ~NativeHunter() override;

    void _ready() override;
    void _physics_process(double delta) override;
    void _unhandled_input(const Ref<InputEvent> &event) override;

    static void _bind_methods();

    void set_speed(real_t p_speed);
    real_t get_speed() const;
    void set_jump_velocity(real_t p_jump_velocity);
    real_t get_jump_velocity() const;
    void set_mouse_sensitivity(real_t p_mouse_sensitivity);
    real_t get_mouse_sensitivity() const;
    void set_coins(int p_coins);
    int get_coins() const;
    void set_current_weapon(int p_weapon);
    int get_current_weapon() const;
    void add_coins(int amount);

private:
    void update_movement(double delta);
    void update_camera_look();
    void fire_gun();
    void swing_sword();

private:
    real_t m_speed = 7.0f;
    real_t m_jump_velocity = 5.5f;
    real_t m_mouse_sensitivity = 0.0025f;
    int m_coins = 0;
    int m_current_weapon = WEAPON_GUN;
    real_t m_pitch = 0.0f;
    real_t m_yaw = 0.0f;
};

} // namespace godot
