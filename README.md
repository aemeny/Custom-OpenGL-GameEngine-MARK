# OpenGL Game Demake

This is a custom-built game engine developed using **OpenGL**, **SDL2**, and **GLEW**. The engine supports 3D rendering, basic physics, collision detection, GUI rendering, and more.

## Features
- **3D Graphics**: Render models, textures, and shaders.
- **Physics**: Includes rigid body dynamics and AABB collision detection.
- **Input Handling**: Supports keyboard, mouse, and controller input.
- **GUI Support**: On-screen interactable elements with an orthographic projection.
- **Portals**: Fully functional portal mechanics inspired by the game *Portal*.

---

## Controls

### Keyboard and Mouse
- **W/A/S/D**: Move forward, left, backward, and right.
- **Mouse**: Look around.
- **Esc**: Exit the game.

### Controller (Optional)
- **Left Joystick**: Move the player.
- **Right Joystick**: Control camera rotation.

---

## How to Use
- Requires files not uploaded to GitHub can be found here:
https://www.dropbox.com/scl/fo/6jlkhsnxr6qj5gu88ypyd/AICyoORrTY4v8P11_kq5TBM?rlkey=mx4zf96zam6337l2fh6jtddtp&st=jirop9ap&dl=0

- **Models** file should be added to \Engine-COMP703\Samples folder, alongside the Textures folder
- **Bin** & **Lib** files should be added to Engine-COMP703\contrib\windows-cl-amd64 folder, alongside the include folder

- The VS Code project file can be opened within \Engine-COMP703\Engine-COMP703. The project can be run from within this IDE.
- Alternatively if a build is created, it can be accessed in \Engine-COMP703\Engine-COMP703\x64 folder. Any build files within \Debug or \Release should be moved out to the \x64 file, and the glew32.dll & SDL2.dll's should be moved within this folder also.
