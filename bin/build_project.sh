#!/usr/bin/env bash
# $0 [shell]

# Default variables.
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_DIR="${SCRIPT_DIR}/../projects/${1}"
LOCAL_USER="$(id -u):$(id -g)"
shift 1

# Creating the project folder if necessary.
[[ -d "${PROJECT_DIR}" ]]  || mkdir -p "${PROJECT_DIR}/home"

# Using the SGDK original image to build the project.
docker run \
  -u root \
  --rm \
  -v "${PROJECT_DIR}:/src" \
  platform-sgdk_lib "$@"

# Fixing files permission.
# The SGDK container creates files using "ROOT" user.
sudo chown -R "${LOCAL_USER}" "${PROJECT_DIR}"
