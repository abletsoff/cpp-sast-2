#pragma once
#include <libwebsockets.h>
#include <string>

void handle_ws_message(struct lws* wsi, const char* msg, size_t len);
