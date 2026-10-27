#!/usr/bin/env bash
#
# rpi_setup.sh - Bootstrap the Raspberry Pi 3 for the mini-arcade cabinet.
#
# Installs the emulator frontend/cores and the Python serial dependencies used
# by scripts/serial_gamepad_bridge.py, then grants the current user access to
# the serial device used by the SG2000X.
#
# Usage:
#   chmod +x scripts/rpi_setup.sh
#   sudo ./scripts/rpi_setup.sh
#
# Tested target: Raspberry Pi OS (Bookworm) on a Raspberry Pi 3.

set -euo pipefail

if [[ "${EUID}" -ne 0 ]]; then
  echo "This script must be run as root (use sudo)." >&2
  exit 1
fi

TARGET_USER="${SUDO_USER:-${USER}}"

echo "==> Updating package lists"
apt-get update

echo "==> Upgrading installed packages"
apt-get upgrade -y

echo "==> Installing emulator frontend and cores"
apt-get install -y \
  retroarch \
  emulationstation \
  libretro-core-info

echo "==> Installing Python serial dependencies and joystick tools"
apt-get install -y \
  python3 \
  python3-pip \
  python3-serial \
  joystick \
  jstest

echo "==> Adding ${TARGET_USER} to the dialout group (serial access)"
usermod -aG dialout "${TARGET_USER}"

echo "==> Installing the serial gamepad bridge"
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
if [[ -f "${SCRIPT_DIR}/serial_gamepad_bridge.py" ]]; then
  install -m 0755 "${SCRIPT_DIR}/serial_gamepad_bridge.py" /usr/local/bin/serial_gamepad_bridge.py
else
  echo "    serial_gamepad_bridge.py not found next to this script; skipping install."
fi

cat <<'EOF'

==> Setup complete.

Next steps:
  1. Log out and back in (or reboot) so the dialout group change applies.
  2. Plug in the SG2000X and confirm it appears, e.g.:
       ls -l /dev/ttyACM* /dev/ttyUSB*
  3. Run the bridge against the detected port:
       python3 /usr/local/bin/serial_gamepad_bridge.py --port /dev/ttyACM0
  4. Launch RetroArch/EmulationStation and map the resulting input.

If audio is routed over HDMI, force it with:
  sudo raspi-config   # System Options > Audio > HDMI
EOF
