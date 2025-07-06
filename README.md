
# internalTemplate
A template that build a DLL with a simple injector. The project includes a few utilities for math and memory manipulation and hooks for different graphics API's.
- Supports x64 and x86
- only supports Multi-Byte Character Set



## Installation
To build the project you need the following:
- **Visual Studio 2022** with:
  - "Desktop development with C++" workload
  - Windows 10 SDK
- OpenGL
- DirectX 9 to 12
- Vulkan
## Usage
- Specify the exe name and the dll name in the injectorA.cpp
- Write your code (mainly in the internalTemplate/src/main.cpp)
- compile in VS and run the injector from the build folder
## Features
**Math**
- Vec2, Vec3 and Vec4
- calculate distance (in 3D space)
- calculate angles (get viewangles with two positions)
- World to Screen (for OpenGL and DirectX)
---
**Functions**
- FindDMAAddy
- NopBytes and PatchBytes (manipulation bytes from the process)
- NopBytes and PatchBytes as classes
- ScanBasic and ScanInternal (pattern scanners)
---
**Renderers**  
The system automatically routes your drawing calls (and others) to the correct renderer based on which hook was initialized.

- DirectX9 (mostly implemented)
- DirectX10 (non existed, for now)
- DirectX11 (non existed, for now)
- DirectX12 (non existed, for now)
- OpenGL (mostly implemented)
- Vulkan (non existed, for now)
## License
This project is licensed under the MIT License.
See the [LICENSE](./LICENSE) file for details.
## Acknowledgements
This project includes third-party components licensed under separate terms.
See [THIRD_PARTY_NOTICES.md](./THIRD_PARTY_NOTICES.md) for more information.


- [MinHook](https://github.com/TsudaKageyu/minhook)
- [Dear ImGui](https://github.com/ocornut/imgui)
- [JSON for Modern C++](https://github.com/nlohmann/json)