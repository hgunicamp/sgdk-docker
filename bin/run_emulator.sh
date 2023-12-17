#!/usr/bin/env bash
# $0 <project>

# Default variables.
CURRENT_USER_ID=$(id -u)
GROUP_INPUT=$(grep input /etc/group | cut -d':' -f3)
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_DIR="${SCRIPT_DIR}/../projects/${1}"
HOME="${PROJECT_DIR}/home"
ROM_FILE="/src/out/rom.bin"
BLASTEM="/usr/games/blastem"
MODE="${2}"

# Allowing X11 connection.
xhost +local:"${USERNAME}"

# Starting the emulator with the rom.
docker run \
  -it \
  --rm \
  --device /dev/dri \
  --device /dev/input \
  -u "${CURRENT_USER_ID}:${GROUP_INPUT}" \
  -e DISPLAY="${DISPLAY}" \
  -e XDG_RUNTIME_DIR="${XDG_RUNTIME_DIR}" \
  -e HOME=/home/remote \
  -v "${XDG_RUNTIME_DIR}:${XDG_RUNTIME_DIR}" \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v "${PROJECT_DIR}:/src" \
  -v "${HOME}:/home/remote" \
  --entrypoint "${BLASTEM}" \
  platform-sgdk_debug_server "${ROM_FILE}" "${MODE}"

# Revoking X11 connection.
xhost -local:"${USERNAME}"

