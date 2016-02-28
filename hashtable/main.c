//
//  main.c
//  hashtable
//
//  Created by Gabriel Carrillo on 2/26/16.
//  Copyright © 2016 Gabriel Carrillo. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define SLOT_COUNT    10
#define HASH_MULTIPLIER 31

typedef struct lnode {
    char *key;
    int item;
    struct lnode *prev;
    struct lnode *next;
} lnode_t;

lnode_t *htable[SLOT_COUNT];

void htable_init() {
    int i;
    
    for (i = 0; i < SLOT_COUNT; i++) {
        htable[i] = NULL;
    }
}

// Hash function example from "The Practice of Programming"
int htable_hash(char *k) {
    unsigned int h;
    unsigned char *p;
    
    h = 0;
    
    for (p = (unsigned char *)k; *p != '\0'; p++) {
        h = HASH_MULTIPLIER * h + *p;
    }
    
    return h % SLOT_COUNT;
}

void htable_insert(char *key, int item) {
    lnode_t *old_head;
    lnode_t *new_head;
    int idx;
    
    idx = htable_hash(key);
    old_head = htable[idx];
    new_head = (lnode_t *)malloc(sizeof(lnode_t));
    memset(new_head, 0, sizeof(lnode_t));
    
    new_head->key = key;
    new_head->item = item;
    new_head->next = old_head;
    new_head->prev = NULL;
    htable[idx] = new_head;
    
    if (old_head) {
        old_head->prev = new_head;
    }
}

int htable_retrieve(char *key) {
    lnode_t *cur_node;
    
    cur_node = htable[htable_hash(key)];
    
    while (cur_node != NULL) {
        if (cur_node->key == key) {
            return cur_node->item;
        } else {
            cur_node = cur_node->next;
        }
    }
    
    return -1;
}

int main(int argc, const char * argv[]) {
    int val;
    
    // insert code here...
    printf("Hello, World - from hashtable!\n");
    
    htable_init();
    
    htable_insert("one", 1);
    htable_insert("one", 3);
    htable_insert("two", 2);
    
    val = htable_retrieve("one");
    printf("Value for key %s is: %d\n", "one", val);
    
    val = htable_retrieve("two");
    printf("Value for key %s is: %d\n", "two", val);
    
    
    return 0;
}
