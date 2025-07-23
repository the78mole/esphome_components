# Scripts

This directory contains utility scripts for the ESPHome Components project.

## check-esphome-names.py

Checks for duplicate ESPHome names across all firmware configurations listed in `firmware-files.txt`.

### Usage

```bash
python3 scripts/check-esphome-names.py
```

### Dependencies

- Python 3.6+
- PyYAML: `pip install pyyaml`

### Features

- Reads firmware files from the centralized list
- Extracts ESPHome names from YAML configurations
- Handles template variables (e.g., `${name}`) by looking up substitutions
- Falls back to filename-based names when template variables are not resolved
- Reports duplicate names with clear error messages
- Exits with appropriate error codes for CI/CD integration

### Exit Codes

- `0`: All ESPHome names are unique (success)
- `1`: Duplicate names found or other errors (failure)

### Example Output

```
ESPHome Name Duplicate Checker
==================================================
Checking 8 firmware configurations for duplicate ESPHome names...

  buderus-km271.yaml -> 'buderus-km271'
  buderus-km271_en.yaml -> 'km271-en'
  buderus-km271_en_noimprov.yaml -> 'km271-en-noimprov'
  ...

✅ All ESPHome names are unique!

✅ Check passed: All ESPHome names are unique.
```

### Integration with CI/CD

You can add this script to your GitHub Actions workflow to automatically check for duplicate names:

```yaml
- name: Check for duplicate ESPHome names
  run: python3 scripts/check-esphome-names.py
```
