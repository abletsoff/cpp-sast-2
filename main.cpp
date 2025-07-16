#include <libwebsockets.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include "handlers.h"

static int interrupted = 0;

static void sigint_handler(int sig) {
    interrupted = 1;
}

static int callback_ws(struct lws *wsi, enum lws_callback_reasons reason,
                      void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_RECEIVE:
            handle_ws_message(wsi, (const char*)in, len);
            break;
        default:
            break;
    }
    return 0;
}

static struct lws_protocols protocols[] = {
    {
        "vuln-protocol",
        callback_ws,
        0,
        4096,
    },
    { NULL, NULL, 0, 0 }
};

int main() {
    signal(SIGINT, sigint_handler);

    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));
    info.port = 9000;
    info.protocols = protocols;
    info.gid = -1;
    info.uid = -1;

    struct lws_context *context = lws_create_context(&info);
    if (!context) {
        fprintf(stderr, "lws init failed\n");
        return 1;
    }

    printf("WebSocket server started on port 9000\n");
    while (!interrupted)
        lws_service(context, 100);

    lws_context_destroy(context);
    return 0;
}
