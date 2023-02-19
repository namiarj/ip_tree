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
    uint64_t protos;
    char src_s[16];
    char dst_s[16];
    struct node *left;
    struct node *right;
};

struct node* binarytree_find(struct node*, const uint32_t, const uint32_t);
void binarytree_free(struct node*);
struct node* binarytree_init(const uint32_t, const uint32_t);
struct node* binarytree_insert(struct node*, const uint32_t, const uint32_t);
void binarytree_print(FILE*, struct node*);

#endif
