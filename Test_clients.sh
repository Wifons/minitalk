#!/bin/bash

SERVER_PID=$1

if [ -z "$SERVER_PID" ]; then
    echo "Usage: ./Test_clients.sh <SERVER_PID>"
    exit 1
fi

MESSAGES=("Hello" "42" "Multithread" "Client 1" "Test message" "Concurrency" "Overflow 1" "Overflow 2" "Overflow 3" "Overflow 4" "Overflow 5")

echo "Launching clients..."
for msg in "${MESSAGES[@]}"; do
    ./client "$SERVER_PID" "$msg" &
    echo "[TEST] Client PID: $! -> Sending message: $msg"
    sleep 0.1
done

wait

echo "All clients finished sending messages."
