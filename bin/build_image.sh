#!/usr/bin/env bash

# Default variables.
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
SGDK_PLATFORM_DOCKER_BASE_DIR="${SCRIPT_DIR}/../platform"
DOWNLOAD_DIR="${SCRIPT_DIR}/../downloads"
SGDK_PACKAGE_SRC="https://github.com/Stephane-D/SGDK/releases/download/v2.00/sgdk200.7z"
SGDK_PACKAGE_FILE="${DOWNLOAD_DIR}/sgdk.7z"
SGDK_PACKAGE_TARGET="${SGDK_PLATFORM_DOCKER_BASE_DIR}/sgdk"

# Gathering and unpacking sgdk library.
[[ -f "${SGDK_PACKAGE_FILE}" ]] || wget -O "${SGDK_PACKAGE_FILE}"  "${SGDK_PACKAGE_SRC}" 
rm -rf "${SGDK_PACKAGE_TARGET}" && 7z x "${SGDK_PACKAGE_FILE}" -o"${SGDK_PACKAGE_TARGET}"

# Changing folder to start the building process.
cd "${SGDK_PLATFORM_DOCKER_BASE_DIR}" || exit
docker compose build
