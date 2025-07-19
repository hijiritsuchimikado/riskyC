#ifndef _LIST_H
#   define _LIST_H

typedef struct list {
    void *value;
    struct list *next;
} list;

#define list_new(node1, node2, type, val)           \
    list *new = __builtin_alloca(sizeof(list));     \
    new->value = __builtin_alloca(sizeof(type));    \
    *(type*) new->value = val;                      \
    new->next = node2;                              \
    node1 = new
#define list_pos(x, pos)            \
    list *tmp = x;                  \
    for (long i = 0; i < pos; ++i)  \
        tmp = tmp->next

#define list_init(x) x = NULL;
#define list_push_front(x, type, val) {list_new(x, x, type, val);}
// push right after condition == true
// _________________________________________________________________________________
#define list_push_ptr(x, type, val) {list_new(x->next, x->next, type, val);}
#define list_push_pos(x, type, val, pos) {  \
    list_pos(x, pos);                       \
    list_push_ptr(tmp, type, val);          \
}
// _________________________________________________________________________________
#define list_pop_front(x) x = x->next
// delete nodes from after x to y
#define list_pop_ptr(x, y) x->next = y->next
// delete a node from after pos
#define list_pop_pos(x, pos) {      \
    list_pos(x, pos);               \
    list_pop_ptr(tmp, tmp->next);   \
}

#endif
