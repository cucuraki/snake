//
// Created by manjaro on 6/1/23.
//
#include "linked_list.h"
#include "stdlib.h"

struct linked_list {
    struct linked_list *next;
    struct linked_list *previous;
    int value;
};


struct linked_list *create(int val, struct linked_list *next, lst prev) {
    struct linked_list *node =
            (struct linked_list *)
                    malloc(sizeof(struct linked_list));
    node->next = next;
    node->value = val;
    node->previous = prev;
    return node;
}

struct linked_list *create_list(int val) {
    struct linked_list *node =
            (struct linked_list *)
                    malloc(sizeof(struct linked_list));
    node->value = val;
    node->next = NULL;
    node->previous = NULL;
    return node;
};

void destroy(struct linked_list *node) {
    free(node);
}

void push_after(struct linked_list *list, int val) {
    list->next = create(val, list->next, list);
}

void push_before(struct linked_list *list, int val){
    list->previous = create(val, list, list->previous);
};

void remove_from_list(struct linked_list *list, int val) {
    lst tmp = list;
    while (tmp) {
        if (tmp->value == val) {
            pop(tmp);
            return;
        }
        tmp = tmp->next;
    }
    tmp = list;
    while (tmp) {
        tmp = tmp->previous;
        if (tmp->value == val) {
            pop(tmp);
            return;
        }
    }
}

void pop(struct linked_list *list) {
    if (!list->previous) {
        destroy(list);
        return;
    }
    lst tmp = list;
    list->previous->next = list->next;
    destroy(tmp);
}

void delete_list(struct linked_list *list) {
    struct linked_list *tmp;
    list = get_head(list);
    while (list) {
        tmp = list->next;
        destroy(list);
        list = tmp;
    }
}

lst get_head(lst node){
    while (node -> previous){
        node = node->previous;
    }
    return node;
}

lst get_tail(lst node){
    while(node->next){
        node = node->next;
    }
    return node;
}

int find(lst list, int val){
    list = get_head(list);
    while(list){
        if(list->value == val)
            return 1;
        list = list->next;
    }
    return 0;
}

int get_val(lst list){
    return list->value;
}
int set_val(lst list, int new_val){
    int tmp = list->value;
    list->value = new_val;
    return tmp;
}
void for_each(lst list, void (*f)(int)){
    list = get_head(list);
    while (list){
        f(list->value);
        list = list->next;
    }
}

void for_each_node(lst list, void (*f)(lst)){
    list = get_head(list);
    while (list){
        f(list);
        list = list->next;
    }
}
