if [[ $(grep -i Microsoft /proc/version) ]]; then
    echo "Bash is running on WSL"
fi