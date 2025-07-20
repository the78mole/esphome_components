#!/usr/bin/env bash

set -euo pipefail

echo "Starting post-create setup..."

# Install act for local GitHub Actions testing
echo "Installing act..."
# Options:
# -b /usr/local/bin : Install to /usr/local/bin (globally available)
# -d : Enable debug logging
# -f : Force installation
# [tag] : Specific version (e.g., v0.2.26)
curl --proto '=https' --tlsv1.2 -sSf https://raw.githubusercontent.com/nektos/act/master/install.sh | bash -s -- -b /usr/local/bin

# Make act available in PATH
echo "Making act available in PATH..."
if [ -f "/usr/local/bin/act" ]; then
    echo "act successfully installed at /usr/local/bin/act"
else
    echo "Warning: act installation may have failed"
fi

# Verify installation
echo "Verifying act installation..."
act --version || echo "act not found in PATH"

echo "Post-create setup completed!"
