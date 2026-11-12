#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "${BASH_SOURCE[0]}")"
export META_OUTPUT_ROOT_FOLDER="$(realpath --relative-to=ext/rusefi/firmware generated)/"
export AUTOMATION_REF="${AUTOMATION_REF:-$(git branch --show-current)}"
cd ext/rusefi/firmware
exec bash bin/compile.sh ../../../meta-info.env -j12 "$@"
