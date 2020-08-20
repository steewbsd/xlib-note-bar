echo "Compiling the program..."

g++ -o notebarexec bar/* *.h *.cpp -lX11 -lpthread

echo "Adding XEPHYR env variable"

XEPHYR=$(whereis -b Xephyr | cut -f2 -d' ')

echo "Starting X server..."

xinit ./xinitrc -- \
    "$XEPHYR" \
        :100 \
        -ac \
        -screen 800x600 \
        -host-cursor
