#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/extension.hpp>

#include "native_hunter.hpp"
#include "native_world_map.hpp"
#include "native_zombie.hpp"

using namespace godot;

void initialize_hunter3d_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    ClassDB::register_class<NativeHunter>();
    ClassDB::register_class<NativeZombie>();
    ClassDB::register_class<NativeWorldMap>();
}

void uninitialize_hunter3d_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {
GDExtensionBool GDE_EXPORT hunter3d_library_init(
    GDExtensionInterfaceGetProcAddress p_get_proc_address,
    GDExtensionClassLibraryPtr p_library,
    GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
    init_obj.register_initializer(initialize_hunter3d_module);
    init_obj.register_terminator(uninitialize_hunter3d_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
    return init_obj.init();
}
}
