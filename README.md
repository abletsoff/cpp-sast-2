# Vulnerable WebSocket Server (C++)

This project is a deliberately vulnerable WebSocket server written in C++ using `libwebsockets`, designed for testing SAST tools.

## ⚠️ WARNING
**Do not deploy this on a public or production-facing machine.** This code contains numerous critical vulnerabilities intended for static analysis testing only.

## 🛠 Features
- Stack buffer overflow
- Heap use-after-free
- Format string vulnerability
- Hardcoded credentials
- Command injection
- Path traversal
- Insecure randomness
- Double free

## 🧱 Requirements
- CMake >= 3.10
- `libwebsockets` development headers
  sudo apt install libwebsockets-dev

## 🧪 Build Instructions
    git clone <this-repo>
    cd vuln_ws_server
    mkdir build && cd build
    cmake ..
    make
    ./vuln_ws_server

## 🔌 WebSocket Usage
Connect to `ws://localhost:9000` using any WebSocket client. Supported messages:

- `admin_login:<password>` – checks hardcoded password
- `ping:<host>` – pings host (vulnerable to command injection)
- `save_file:<path>` – writes file (vulnerable to path traversal)
- `get_token` – returns insecure random token

## 🧪 SAST Focus
This app is useful for testing:
- False positives vs true positives
- Detection of compound bugs (e.g. memory + logic flaws)
- Path-based and taint-based analysis

## 📜 License
MIT License
