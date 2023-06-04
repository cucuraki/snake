//
// Created by manjaro on 6/1/23.
//

#ifndef SNAKE_LINKED_LIST_H
#define SNAKE_LINKED_LIST_H
struct linked_list;
typedef struct linked_list *lst;

struct linked_list* create(int val, struct linked_list* next,struct linked_list* prev);
struct linked_list* create_list(int val);


void push_after(struct linked_list* list,int val);
void push_before(struct linked_list* list,int val);
void remove_from_list(struct linked_list* list,int val);
void pop(struct linked_list* list);
void delete(struct linked_list* list);
void delete_list(struct linked_list* list);
lst get_head(lst node);
lst get_tail(lst node);
int find(lst list, int val);
int get_val(lst list);
int set_val(lst list, int new_val);
void for_each(lst list, void (*f)(int));
void for_each_node(lst list, void (*f)(lst));
#endif //SNAKE_LINKED_LIST_H
