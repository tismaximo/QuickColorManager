# Quick Color Manager
Tool to quickly change, modify or apply different physical monitor settings such as brightness, contrast or color balances.
## Command line version  
https://github.com/tismaximo/QuickColorManager/releases/tag/v1.0.0  
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
- `set <device-id> {-brightness -contrast -gamma -red -green -blue} <number>`: Set one or more device settings to the specified values.  
Example usage: `set 1 -brightness 80 -contrast 60 -blue 75`  
- `get <device-id> {-brightness -contrast -gamma -red -green -blue} (--all --maxvalues)`: Get one or more device settings.  
The `--all` flag will give values for all settings.  
The `--maxvalues` flag will give the maximum admitted values for each selected setting.  
Example usage: `get 1 -brightness -contrast -blue`  
Example usage: `get 1 --all --maxvalues`
- `save <device-id> <alias>`: Saves the device's currently applied settings to an alias.  
- `load <device-id> <alias>`: Loads settings from the alias into the specified device.
- `test`: Runs a test which will tell you which (if any) features are supported by your devices.
## GUI version
WIP
## Notes
- Most devices don't support changing gamma through the physical monitor settings. Gamma could be implemented in the future by setting gamma ramps directly to the GPU through the Direct3D library but this is also often not supported.  
- Most laptops dont support any physical settings.
