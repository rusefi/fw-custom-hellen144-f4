#!/usr/bin/env bash
set -euo pipefail
exec bash "$(dirname "${BASH_SOURCE[0]}")/compile_firmware.sh" ../simulator/build/rusefi_simulator.linux "$@"
