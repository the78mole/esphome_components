#!/usr/bin/env python3
"""
Check for duplicate ESPHome names in firmware configurations.

This script reads the firmware files list, extracts the 'name' field from each
ESPHome YAML configuration, and checks for duplicates. If duplicates are found,
it exits with an error code and shows which files contain the duplicate names.

Dependencies:
    - PyYAML: pip install pyyaml

Usage:
    python3 scripts/check-esphome-names.py [firmware-files.txt]
    
    If no file is specified, defaults to firmware-files.txt in workspace root
"""

import os
import sys
import yaml
import argparse
from pathlib import Path
from collections import defaultdict
from typing import Dict, List, Set


def read_firmware_files(firmware_files_path: Path) -> List[str]:
    """Read the firmware files list, filtering out comments and empty lines."""
    if not firmware_files_path.exists():
        print(f"Error: {firmware_files_path} not found!")
        sys.exit(1)
    
    files = []
    with open(firmware_files_path, 'r') as f:
        for line in f:
            line = line.strip()
            # Skip comments and empty lines
            if line and not line.startswith('#'):
                files.append(line)
    
    return files


def extract_esphome_name(yaml_file: Path) -> str:
    """Extract the ESPHome name from a YAML configuration file."""
    try:
        with open(yaml_file, 'r') as f:
            content = f.read()
            
        # Handle template variables by reading substitutions first
        config = yaml.safe_load(content)
        
        if 'esphome' in config and 'name' in config['esphome']:
            name = config['esphome']['name']
            
            # Check if it's a template variable
            if isinstance(name, str) and name.startswith('${') and name.endswith('}'):
                # Extract variable name
                var_name = name[2:-1]  # Remove ${ and }
                
                # Look for substitutions
                if 'substitutions' in config and var_name in config['substitutions']:
                    return config['substitutions'][var_name]
                else:
                    # Try to infer from filename if no substitution found
                    filename_base = yaml_file.stem  # Remove .yaml extension
                    print(f"  Warning: Template variable '{name}' in {yaml_file}, using filename '{filename_base}' as fallback")
                    return filename_base
            else:
                return name
        else:
            print(f"Warning: No esphome.name found in {yaml_file}")
            return None
            
    except FileNotFoundError:
        print(f"Error: File {yaml_file} not found!")
        return None
    except yaml.YAMLError as e:
        print(f"Error parsing YAML in {yaml_file}: {e}")
        return None
    except Exception as e:
        print(f"Error reading {yaml_file}: {e}")
        return None


def check_for_duplicates(firmware_files_path: Path) -> bool:
    """
    Check for duplicate ESPHome names across all firmware configurations.
    
    Args:
        firmware_files_path: Path to the file containing the list of firmware files
    
    Returns:
        bool: True if no duplicates found, False if duplicates exist
    """
    firmware_files = read_firmware_files(firmware_files_path)
    
    # Determine workspace root relative to the firmware files list
    # The firmware-files.txt is now expected to be in the workspace root
    workspace_root = firmware_files_path.parent
    
    # Dictionary to track which files use which names
    name_to_files: Dict[str, List[str]] = defaultdict(list)
    
    print(f"Using firmware files list: {firmware_files_path}")
    print(f"Workspace root: {workspace_root}")
    print(f"Checking {len(firmware_files)} firmware configurations for duplicate ESPHome names...")
    print()
    
    maxlenfilename = max(len(f) for f in firmware_files) if firmware_files else 0
    
    print (f"{'Configuration File'.ljust(maxlenfilename)} | ESPHome Name")
    print (f"{'-'*maxlenfilename}-|{'-'*20}-")
    for firmware_file in firmware_files:
        yaml_path = workspace_root / firmware_file
        
        if not yaml_path.exists():
            print(f"Warning: {yaml_path} does not exist, skipping...")
            continue
            
        esphome_name = extract_esphome_name(yaml_path)
        
        if esphome_name:
            name_to_files[esphome_name].append(firmware_file)
            print(f"{firmware_file.ljust(maxlenfilename)} | {esphome_name}")
    
    print()
    
    # Check for duplicates
    duplicates_found = False


    for name, files in name_to_files.items():
        if len(files) > 1:
            duplicates_found = True
            print(f"❌ ERROR: Duplicate ESPHome name '{name}' found in:")
            for file in files:
                print(f"  - {file}")
            print()
    
    return True if not duplicates_found else False

def main():
    """Main function."""
    parser = argparse.ArgumentParser(
        description='Check for duplicate ESPHome names in firmware configurations.',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python3 scripts/check-esphome-names.py
  python3 scripts/check-esphome-names.py .github/workflows/firmware-files.txt
  python3 scripts/check-esphome-names.py /path/to/custom-firmware-list.txt
        """
    )
    
    parser.add_argument(
        'firmware_files',
        nargs='?',
        help='Path to the file containing the list of firmware files (default: firmware-files.txt)'
    )
    
    args = parser.parse_args()
    
    # Determine the firmware files path
    if args.firmware_files:
        firmware_files_path = Path(args.firmware_files)
        if not firmware_files_path.is_absolute():
            # Make relative paths relative to current working directory
            firmware_files_path = Path.cwd() / firmware_files_path
    else:
        # Default path: firmware-files.txt in workspace root
        script_dir = Path(__file__).parent
        firmware_files_path = script_dir.parent / "firmware-files.txt"
    
    print("ESPHome Name Duplicate Checker")
    print("=" * 50)
    
    success = check_for_duplicates(firmware_files_path)
    
    if success:
        print("\n✅ Check passed: All ESPHome names are unique.")
        sys.exit(0)
    else:
        print("\n❌ Check failed: Duplicate ESPHome names found.")
        sys.exit(1)


if __name__ == "__main__":
    main()
