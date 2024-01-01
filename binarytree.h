#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdio.h>
#include <stdint.h>

struct addr {
    uint32_t src: 32;
    uint32_t dst: 32;
};

struct node {
    struct addr addr;
    uint32_t count;
    uint64_t bytes;
    char src_s[16];
    char dst_s[16];
    struct node *left;
    struct node *right;
};

struct node *bt_find(struct node*, const uint32_t, const uint32_t);
void bt_free(struct node*);
struct node *bt_init(const uint32_t, const uint32_t);
struct node *bt_insert(struct node*, const uint32_t, const uint32_t);
void bt_print(FILE*, struct node*);

#endif
