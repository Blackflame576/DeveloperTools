if [[ $(grep -i Microsoft /proc/version) ]]; then
    sudo apt-get update -y && sudo apt-get install -yqq daemonize dbus-user-session fontconfig
    sudo daemonize /usr/bin/unshare --fork --pid --mount-proc /lib/systemd/systemd --system-unit=basic.target
fi