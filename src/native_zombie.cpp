#include "native_zombie.hpp"

#include "native_hunter.hpp"

using namespace godot;

NativeZombie::NativeZombie() {}

NativeZombie::~NativeZombie() {
    m_hunter = nullptr;
}

void NativeZombie::_ready() {
    CharacterBody3D::_ready();
    add_to_group("zombies");
    acquire_hunter();
}

void NativeZombie::_physics_process(double delta) {
    if (delta <= 0.0) {
        return;
    }

    if (m_hunter == nullptr) {
        acquire_hunter();
        if (m_hunter == nullptr) {
            return;
        }
    }

    Vector3 dir = m_hunter->get_global_position() - get_global_position();
    dir.y = 0.0f;
    real_t length = dir.length();
    if (length > 0.0001f) {
        dir /= length;
        Vector3 velocity = get_velocity();
        velocity.x = dir.x * m_speed;
        velocity.z = dir.z * m_speed;
        velocity.y -= 9.8f * static_cast<real_t>(delta);
        set_velocity(velocity);
        move_and_slide();

        Vector3 look_target = m_hunter->get_global_position();
        look_target.y = get_global_position().y;
        look_at(look_target, Vector3(0.0f, 1.0f, 0.0f));
        Vector3 rotation = get_rotation_degrees();
        rotation.x = 0.0f;
        rotation.z = 0.0f;
        set_rotation_degrees(rotation);
    }
}

void NativeZombie::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_health", "value"), &NativeZombie::set_health);
    ClassDB::bind_method(D_METHOD("get_health"), &NativeZombie::get_health);
    ClassDB::bind_method(D_METHOD("set_speed", "value"), &NativeZombie::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &NativeZombie::get_speed);
    ClassDB::bind_method(D_METHOD("set_coin_reward", "value"), &NativeZombie::set_coin_reward);
    ClassDB::bind_method(D_METHOD("get_coin_reward"), &NativeZombie::get_coin_reward);
    ClassDB::bind_method(D_METHOD("take_damage", "amount"), &NativeZombie::take_damage);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "health"), "set_health", "get_health");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "coin_reward"), "set_coin_reward", "get_coin_reward");
}

void NativeZombie::set_health(real_t p_health) { m_health = p_health < 0.0f ? 0.0f : p_health; }
real_t NativeZombie::get_health() const { return m_health; }

void NativeZombie::set_speed(real_t p_speed) { m_speed = p_speed; }
real_t NativeZombie::get_speed() const { return m_speed; }

void NativeZombie::set_coin_reward(int p_coin_reward) { m_coin_reward = p_coin_reward < 0 ? 0 : p_coin_reward; }
int NativeZombie::get_coin_reward() const { return m_coin_reward; }

void NativeZombie::take_damage(float amount) {
    if (amount < 0.0f) {
        amount = 0.0f;
    }

    m_health -= amount;
    if (m_health <= 0.0f) {
        m_health = 0.0f;
        if (m_hunter != nullptr) {
            m_hunter->add_coins(m_coin_reward);
        }
        queue_free();
    }
}

void NativeZombie::acquire_hunter() {
    SceneTree *tree = get_tree();
    if (tree == nullptr) {
        return;
    }

    Array players = tree->get_nodes_in_group("player");
    if (players.size() <= 0) {
        return;
    }

    Object *object = players[0];
    if (object == nullptr) {
        return;
    }

    NativeHunter *hunter = Object::cast_to<NativeHunter>(object);
    if (hunter == nullptr) {
        return;
    }

    m_hunter = hunter;
}
