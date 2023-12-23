#!/usr/bin/env bash
# $0 <project>

# Default variables.
CURRENT_USER_ID=$(id -u)
GROUP_INPUT=$(grep input /etc/group | cut -d':' -f3)
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_DIR="${SCRIPT_DIR}/../projects/${1}"
HOME="${PROJECT_DIR}/home"
ROM_ELF="/src/out/rom.out"
GDB="gdb-multiarch"
shift 1

# Allowing X11 connection.
xhost +local:"${USERNAME}"

# Starting the emulator with the rom.
docker run \
  -it \
  --rm \
  --cap-add=SYS_PTRACE --security-opt seccomp=unconfined \
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
  --entrypoint "${GDB}" \
  platform-sgdk_debug_server "${ROM_ELF}"  "$@"

# Revoking X11 connection.
xhost -local:"${USERNAME}"
