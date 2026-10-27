# Hunter 3D

A Godot 4 survival and exploration prototype project.

## Structure

- `project.godot`: project entry point
- `scenes/MainMenu.tscn`: menu scene
- `scenes/WorldMap.tscn`: playable game world
- `scripts/con.gd`: boot logging and scene transition logic
- `scripts/main_menu.gd`: UI controller
- `scripts/world_map.gd`: world loop and spawn logic
- `gdextension/hunter3d.gdextension`: native extension registration
- `src/`: C++ extension sources

## Build notes

This project includes a Godot GDExtension C++ template for a NativeHunter, NativeZombie, and NativeWorldMap. To compile it, use a proper Godot 4 + godot-cpp toolchain and build the extension output into:

- `bin/hunter3d.windows.debug.x86_64.dll`
- `bin/hunter3d.windows.release.x86_64.dll`
- `bin/hunter3d.linux.debug.x86_64.so`
- `bin/hunter3d.linux.release.x86_64.so`

Open the project in Godot 4.2+ and run it.
