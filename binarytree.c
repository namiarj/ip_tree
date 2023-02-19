#include "binarytree.h"
#include "clog.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>

struct node *
binarytree_find(struct node *nd, const uint32_t src, const uint32_t dst) {
    const struct addr addr = {src, dst};
    register uint64_t a = *(uint64_t*)&addr;
    register int64_t b;
    while (nd) {
        b = a - *(uint64_t*)&nd->addr;
        if (b < 0) {
            nd = nd->left;
        }
        else if (b > 0) {
            nd = nd->right;
        }
        else {
            return nd;
        }
    }
    return nd;
}

void
binarytree_free(struct node *nd) {
    if (nd->left) {
        binarytree_free(nd->left);
    }
    if (nd->right) {
        binarytree_free(nd->right);
    }
    free(nd);
}

struct node *
binarytree_init(const uint32_t src, const uint32_t dst) {
    struct node *new = malloc(sizeof(struct node));
    if (new == NULL) {
        FATAL("malloc returned null");
    }
    bzero(new, sizeof(struct node));
    new->addr.src = src;
    new->addr.dst = dst;
    inet_ntop(AF_INET, &src, new->src_s, 16);
    inet_ntop(AF_INET, &dst, new->dst_s, 16);
    return new;
}

struct node *
binarytree_insert(struct node *nd, const uint32_t src, const uint32_t dst) {
    const struct addr addr = {src, dst};
    register uint64_t a = *(uint64_t*)&addr;
    register int64_t b;
    struct node *prev;
    bool is_left;

    while (nd) {
        prev = nd;
        b = a - *(uint64_t*)&nd->addr;
        if (b < 0) {
            is_left = true;
            nd = nd->left;
        }
        else if (b > 0) {
            is_left = false;
            nd = nd->right;
        }
    }
    if (is_left) {
        prev->left = binarytree_init(src, dst);
        return prev->left;
    }
    else {
        prev->right = binarytree_init(src, dst);
        return prev->right;
    }
}

void
binarytree_print(FILE *fp, struct node *nd) {

    fprintf(fp, "%s,%s,%"PRIu64",%"PRIu64",%"PRIu32"\n", nd->src_s,
        nd->dst_s, nd->protos, nd->bytes, nd->count);

    if (nd->left) {
        binarytree_print(fp, nd->left);
    }
    if (nd->right) {
        binarytree_print(fp, nd->right);
    }
}
