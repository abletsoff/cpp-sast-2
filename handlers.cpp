#include "handlers.h"
#include "utils.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstdlib>

void handle_ws_message(struct lws* wsi, const char* msg, size_t len) {
    char buffer[128];
    strcpy(buffer, msg); // Buffer overflow vulnerability

    printf(buffer); // Format string bug

    if (strstr(buffer, "admin_login:") == buffer) {
        const char* password = "admin123"; // hardcoded credential
        if (strcmp(buffer + 12, password) == 0) {
            lws_write(wsi, (unsigned char*)"Admin access granted", 21, LWS_WRITE_TEXT);
        } else {
            lws_write(wsi, (unsigned char*)"Access denied", 13, LWS_WRITE_TEXT);
        }
    }

    if (strstr(buffer, "save_file:") == buffer) {
        const char* filename = buffer + 10;
        std::ofstream file(filename); // Path traversal
        file << "You have been hacked!\n";
        file.close();
    }

    if (strstr(buffer, "ping:") == buffer) {
        char cmd[256];
        sprintf(cmd, "ping -c 1 %s", buffer + 5); // Command injection
        system(cmd);
    }

    if (strstr(buffer, "get_token") != nullptr) {
        int token = rand(); // insecure randomness
        char token_msg[64];
        sprintf(token_msg, "Token: %d", token);
        lws_write(wsi, (unsigned char*)token_msg, strlen(token_msg), LWS_WRITE_TEXT);
    }

    char* data = (char*)malloc(64);
    strcpy(data, "tempdata");
    free(data);
    printf("%s\n", data); // use-after-free
}
