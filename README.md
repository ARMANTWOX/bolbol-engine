# bolbol-engine (minimal)

# bolbol-engine (minimal)

this project contains a small OpenGL renderer in `opengl/` and a `main.cpp` that opens a GLFW window and draws a rotating triangle.

MSYS2 + g++ build instructions (Windows)

```powershell
pacman -Syu
# close and reopen the MSYS2 MinGW 64-bit shell after the update
pacman -S --needed base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-pkg-config mingw-w64-x86_64-glfw mingw-w64-x86_64-glad mingw-w64-x86_64-glm
```

3. Configure and build with CMake from the project root (inside the MINGW64 shell):

```powershell
mkdir build; cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release
```

4. Run the binary (from the build folder):

```powershell
./bolbol.exe
```

Notes
- The project uses FetchContent to fetch GLFW/glad if they are not available; when using MSYS2, installing the mingw packages provides those libraries and headers and CMake should pick them up.
- If your editor shows missing includes, ensure it is using the MSYS2 MinGW include paths or configure your project's includePath to the mingw64 include directories (e.g., C:/msys64/mingw64/include).
- Next steps you might want: add file-based shader loading, texture support via `stb_image`, and a simple mesh/asset loader.
