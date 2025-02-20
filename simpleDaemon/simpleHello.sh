#!/bin/bash



PIDFILE="/var/run/hello_world.pid"

daemon() {
    while true; do
        echo "Hello World"
        sleep 1
    done
}

start() {
    if [ -f "$PIDFILE" ] && kill -0 $(cat "$PIDFILE") 2>/dev/null; then
        echo "Daemon is already running."
        exit 1
    fi
    echo "Starting daemon..."
    daemon > /var/log/hello_world.log 2>&1 &
    PID=$!
    echo $PID > "$PIDFILE"
    echo "Daemon started with PID: $PID"
}

stop() {
    if [ ! -f "$PIDFILE" ]; then
        echo "PID file not found. Daemon is not running?"
        exit 1
    fi
    PID=$(cat "$PIDFILE")
    echo "Stopping daemon..."
    kill $PID
    rm -f "$PIDFILE"
    echo "Daemon stopped"
}

case "$1" in
    start)
        start
        ;;
    stop)
        stop
        ;;
    restart)
        stop
        start
        ;;
    *)
        echo "Usage: $0 {start|stop|restart}"
        exit 1
        ;;
esac

exit 0
