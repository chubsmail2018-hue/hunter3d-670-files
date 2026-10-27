# Hunter 3D export instructions

This repository contains an export preset for a Windows Desktop build, but a real `.exe` cannot be produced in this environment without the Godot editor and export templates installed locally.

To generate the executable on a Windows machine:

1. Install Godot 4.2.x and export templates.
2. Open the project in Godot.
3. From the menu, use `Project > Export` and select the `Windows Desktop` profile.
4. Or run this script from a command prompt:

   build_windows.bat

The resulting output will be written to:

- `build/Windows/Hunter3D.exe`

Note: The export preset is included in this repo, but the binary itself must be produced by the Godot export pipeline on a machine with the editor installed.
