#!/usr/bin/env bash
# $0 [shell]

# Default variables.
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
PROJECT_DIR="${SCRIPT_DIR}/../projects/${1}"
LOCAL_USER="$(id -u):$(id -g)"

# Starting a new container.
docker run \
  -u root \
  --rm \
  -v "${PROJECT_DIR}:/src" \
  platform-sgdk_lib

# Fixing files permission.
# The SGDK container creates files using "ROOT" user.
sudo chown -R "${LOCAL_USER}" "${PROJECT_DIR}"
