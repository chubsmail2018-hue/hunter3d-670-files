#pragma once

#include <godot_cpp/classes/character_body_3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/vector3.hpp>

namespace godot {

class NativeHunter;

class NativeZombie : public CharacterBody3D {
    GDCLASS(NativeZombie, CharacterBody3D)

public:
    NativeZombie();
    ~NativeZombie() override;

    void _ready() override;
    void _physics_process(double delta) override;

    static void _bind_methods();

    void set_health(real_t p_health);
    real_t get_health() const;
    void set_speed(real_t p_speed);
    real_t get_speed() const;
    void set_coin_reward(int p_coin_reward);
    int get_coin_reward() const;
    void take_damage(float amount);

private:
    void acquire_hunter();

private:
    real_t m_health = 100.0f;
    real_t m_speed = 2.2f;
    int m_coin_reward = 5;
    NativeHunter *m_hunter = nullptr;
};

} // namespace godot
