#include "native_hunter.hpp"

#include "native_zombie.hpp"

using namespace godot;

NativeHunter::NativeHunter() {}

NativeHunter::~NativeHunter() {}

void NativeHunter::_ready() {
    CharacterBody3D::_ready();
    add_to_group("player");
}

void NativeHunter::_physics_process(double delta) {
    if (delta <= 0.0) {
        return;
    }

    update_movement(delta);
    update_camera_look();
}

void NativeHunter::_unhandled_input(const Ref<InputEvent> &event) {
    if (event.is_valid() == false) {
        return;
    }

    Ref<InputEventMouseMotion> motion = event;
    if (motion.is_valid()) {
        Vector2 rel = motion->get_relative();
        m_yaw -= rel.x * m_mouse_sensitivity;
        m_pitch -= rel.y * m_mouse_sensitivity;
        m_pitch = Math::clamp(m_pitch, -80.0f, 80.0f);
    }
}

void NativeHunter::_bind_methods() {
    ClassDB::bind_method(D_METHOD("add_coins", "amount"), &NativeHunter::add_coins);
    ClassDB::bind_method(D_METHOD("fire_gun"), &NativeHunter::fire_gun);
    ClassDB::bind_method(D_METHOD("swing_sword"), &NativeHunter::swing_sword);

    ClassDB::bind_method(D_METHOD("set_speed", "value"), &NativeHunter::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &NativeHunter::get_speed);
    ClassDB::bind_method(D_METHOD("set_jump_velocity", "value"), &NativeHunter::set_jump_velocity);
    ClassDB::bind_method(D_METHOD("get_jump_velocity"), &NativeHunter::get_jump_velocity);
    ClassDB::bind_method(D_METHOD("set_mouse_sensitivity", "value"), &NativeHunter::set_mouse_sensitivity);
    ClassDB::bind_method(D_METHOD("get_mouse_sensitivity"), &NativeHunter::get_mouse_sensitivity);
    ClassDB::bind_method(D_METHOD("set_coins", "value"), &NativeHunter::set_coins);
    ClassDB::bind_method(D_METHOD("get_coins"), &NativeHunter::get_coins);
    ClassDB::bind_method(D_METHOD("set_current_weapon", "value"), &NativeHunter::set_current_weapon);
    ClassDB::bind_method(D_METHOD("get_current_weapon"), &NativeHunter::get_current_weapon);

    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "jump_velocity"), "set_jump_velocity", "get_jump_velocity");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "mouse_sensitivity"), "set_mouse_sensitivity", "get_mouse_sensitivity");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "coins"), "set_coins", "get_coins");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "current_weapon"), "set_current_weapon", "get_current_weapon");

    BIND_ENUM_CONSTANT(WEAPON_GUN);
    BIND_ENUM_CONSTANT(WEAPON_SWORD);
}

void NativeHunter::set_speed(real_t p_speed) { m_speed = p_speed; }
real_t NativeHunter::get_speed() const { return m_speed; }

void NativeHunter::set_jump_velocity(real_t p_jump_velocity) { m_jump_velocity = p_jump_velocity; }
real_t NativeHunter::get_jump_velocity() const { return m_jump_velocity; }

void NativeHunter::set_mouse_sensitivity(real_t p_mouse_sensitivity) { m_mouse_sensitivity = p_mouse_sensitivity; }
real_t NativeHunter::get_mouse_sensitivity() const { return m_mouse_sensitivity; }

void NativeHunter::set_coins(int p_coins) { m_coins = p_coins < 0 ? 0 : p_coins; }
int NativeHunter::get_coins() const { return m_coins; }

void NativeHunter::set_current_weapon(int p_weapon) { m_current_weapon = p_weapon; }
int NativeHunter::get_current_weapon() const { return m_current_weapon; }

void NativeHunter::add_coins(int amount) {
    if (amount < 0) {
        return;
    }
    m_coins += amount;
}

void NativeHunter::update_movement(double delta) {
    if (Input::get_singleton() == nullptr) {
        return;
    }

    Vector3 direction = Vector3();
    if (Input::get_singleton()->is_action_pressed("move_forward")) {
        direction.z -= 1.0f;
    }
    if (Input::get_singleton()->is_action_pressed("move_back")) {
        direction.z += 1.0f;
    }
    if (Input::get_singleton()->is_action_pressed("move_left")) {
        direction.x -= 1.0f;
    }
    if (Input::get_singleton()->is_action_pressed("move_right")) {
        direction.x += 1.0f;
    }

    if (direction.length_squared() > 0.0001f) {
        direction = direction.normalized() * m_speed;
        Vector3 velocity = get_velocity();
        velocity.x = direction.x;
        velocity.z = direction.z;
        set_velocity(velocity);
    } else {
        Vector3 velocity = get_velocity();
        velocity.x = 0.0f;
        velocity.z = 0.0f;
        set_velocity(velocity);
    }

    if (!is_on_floor()) {
        Vector3 velocity = get_velocity();
        velocity.y -= 9.8f * static_cast<real_t>(delta);
        set_velocity(velocity);
    } else if (Input::get_singleton()->is_action_just_pressed("jump")) {
        Vector3 velocity = get_velocity();
        velocity.y = m_jump_velocity;
        set_velocity(velocity);
    }

    move_and_slide();
}

void NativeHunter::update_camera_look() {
    Node *camera_node = get_node_or_null("Camera3D");
    if (camera_node == nullptr) {
        return;
    }

    Camera3D *camera = Object::cast_to<Camera3D>(camera_node);
    if (camera == nullptr) {
        return;
    }

    Vector3 rotation = get_rotation_degrees();
    rotation.y = Math::rad_to_deg(m_yaw);
    set_rotation_degrees(rotation);

    Vector3 cam_rotation = camera->get_rotation_degrees();
    cam_rotation.x = m_pitch;
    camera->set_rotation_degrees(cam_rotation);
}

void NativeHunter::fire_gun() {
    Node *camera_node = get_node_or_null("Camera3D");
    if (camera_node == nullptr) {
        return;
    }
    Camera3D *camera = Object::cast_to<Camera3D>(camera_node);
    if (camera == nullptr) {
        return;
    }

    RayCast3D *ray = memnew(RayCast3D);
    ray->set_target_position(Vector3(0.0f, 0.0f, -50.0f));
    ray->set_global_position(camera->get_global_position());
    add_child(ray);
    ray->force_raycast_update();

    if (ray->is_colliding()) {
        Object *collider = ray->get_collider();
        if (collider != nullptr) {
            NativeZombie *zombie = Object::cast_to<NativeZombie>(collider);
            if (zombie != nullptr) {
                zombie->take_damage(35.0f);
            }
        }
    }

    ray->queue_free();
}

void NativeHunter::swing_sword() {
    Array zombies = get_tree()->get_nodes_in_group("zombies");
    for (int i = 0; i < zombies.size(); ++i) {
        Object *obj = zombies[i];
        if (obj == nullptr) {
            continue;
        }

        NativeZombie *zombie = Object::cast_to<NativeZombie>(obj);
        if (zombie == nullptr) {
            continue;
        }

        if (get_global_position().distance_to(zombie->get_global_position()) <= 3.5f) {
            zombie->take_damage(50.0f);
        }
    }
}
