# Quick Color Manager
Tool to quickly change, modify or apply different monitor settings such as brightness, contrast or color balances using DDC/CI.
## Command line version  
https://github.com/tismaximo/QuickColorManager/releases/tag/v1.0.0 (Currently being false positived as a trojan. for now, you will have to compile the Visual Studio project yourself to make it work on your machine)  
### Available commands:  
- `list devices`: Lists all available devices. This command will give you the `device-id` parameter which will be passed to the next commands to specify the device to operate on.  
- `list settings`: Lists all available settings. There will always be atleast one default settings option for each device.  
- `set <device-id> {-brightness -contrast -gamma -red -green -blue} <number>`: Set one or more device settings to the specified values.  
Example usage: `set 1 -brightness 80 -contrast 60 -blue 75`  
- `get <device-id> {-brightness -contrast -gamma -red -green -blue} (--all --maxvalues)`: Get one or more device settings.  
The `--all` flag will return all settings. The `--maxvalues` flag will return the maximum admitted values for each setting.  
Example usage: `get 1 -brightness -contrast -blue`  
Example usage: `get 1 --all --maxvalues`
- `save <device-id> <alias>`: Saves the device's currently applied settings to an alias.  
- `load <device-id> <alias>`: Loads settings from the alias into the specified device.
- `test`: Runs a test which will tell you which (if any) features are supported by your devices.
## GUI Version
WIP
## Notes
- Most devices don't support gamma as a DDC/CI feature. Gamma could be implemented in the future by setting gamma ramps directly to the GPU through the Direct3D library but this is also often not supported.  
- Most laptops dont support any DDC/CI features.
