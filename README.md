# Quick Color Manager
QuickColorManager is a tool that allows users to quickly change, modify or apply different physical monitor settings such as brightness, contrast or color balances, as well as saving them into profiles.
### Key features
- Set or view the physical settings on any connected monitors
- Save settings to profiles and load them
- Check which settings are or aren't supported by your monitors
- Lightweight utility made to be scriptable and to manage settings and switch between them as fast as possible
## Architecture overview
QuickColorManager is structured as a layered console application that separates user interaction, application workflows, domain logic, and platform-specific system calls.
- CLI Layer: Handles exclusively command-line argument parsing, input validation, and user-facing output.
- Application Layer: Orchestrates high-level workflows such as listing monitors, applying settings, and loading/saving profiles. Is also responsible for error handling.
- Domain/Platform layer: Defines abstractions for monitors, settings and profiles which encapsulate filesystem calls and Windows API calls. Domain and platform logic are mixed for simplicity.   

This separation improves maintainability and is designed to make future updates like a GUI or multi-platform support easier to reason about.
## Command line version  
https://github.com/tismaximo/QuickColorManager/releases/tag/1.0.1  
This release is currently being false flagged as a trojan by Microsoft. If you can't download it directly from the release, you might have to compile the project yourself.  

You will need to install the [Microsoft Visual C++ Libraries](https://learn.microsoft.com/es-es/cpp/windows/latest-supported-vc-redist?view=msvc-170#latest-supported-redistributable-version) and the [Windows SDK](https://developer.microsoft.com/es-es/windows/downloads/windows-sdk/) if you don't already have them.  
You can compile this project in Visual Studio 2022 or with CMake by running:  
```
cd build  
cmake .. -G "Visual Studio 17 2022" -A x64  
cmake --build . --config Release
```
### Available commands:  
- `list devices`: Lists all available devices. This command will give you the `device-id` parameter which will be passed to the next commands to specify the device to operate on.  
- `list settings`: Lists all available settings. There will always be atleast one default settings option for each device.  
- `list args`: Lists the arguments that can be taken in by `set` and `get` (brightness, contrast, etc.).  
- `set <device-id> {<arg-1> <number> <arg-2> <number>...}`: Set one or more device settings to the specified values.  
Example usage: `set 1 -brightness 80 -contrast 60 -blue 75`  
- `get <device-id> {<arg-1> <arg-2>...} (--all --maxvalues)`: Get one or more device settings.  
The `--all` flag will give values for all settings.  
The `--maxvalues` flag will give the maximum admitted values for each selected setting.  
Example usage: `get 1 brightness contrast blue`  
Example usage: `get 1 --all --maxvalues`
- `save <device-id> <alias>`: Saves the device's currently applied settings to an alias.  
- `load <device-id> <alias>`: Loads settings from the alias into the specified device.
- `test`: Runs a test which will tell you which (if any) features are supported by your devices.
## Notes
- Most devices don't support changing gamma through the physical monitor settings. Gamma could be implemented in the future by setting gamma ramps directly to the GPU through the Direct3D library but this is also often not supported.  
- Most laptops dont support any physical settings.
