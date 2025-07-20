#ifndef _LIST_H
#   define _LIST_H

typedef struct list {
    void *value;
    struct list *next;
} list;

#define list_val(type, val) \
    new->value = al1(type); \
    *(type*) new->value = val
#define list_new(x) \
    list *new = x;  \
    for (; new->next; new = new->next)

#define list_init(x) list *x = NULL;
// merge/push 1 element to the front of x
#define list_merge_front(x, y) {    \
    y->next = x;                    \
    x = y;                          \
}
#define list_push_front(x, type, val) { \
    list *new = al1(list);              \
    list_val(type, val);                \
    list_merge_front(x, new);           \
}
// merge a list or push n elements (from array or not) to the front of x
#define list_merge_list_front(x, y) {   \
    list_new(y);                        \
    new->next = x;                      \
    x = y;                              \
}
#define list_push_front_arr(x, type, n, arr) {  \
    list *new = al1(list);                      \
    list_val(type, arr[0]);                     \
    list *tmp = new;                            \
    for (long i = 1; i < n; ++i) {              \
        new->next = al1(list);                  \
        new = new->next;                        \
        list_val(type, arr[i]);                 \
    }                                           \
    new->next = x;                              \
    x = tmp;                                    \
}
#define list_push_front_args(x, type, n, ...) { \
    type arr[] = {__VA_ARGS__};                 \
    list_push_front_arr(x, type, n, arr);       \
}
// push right after condition == true
// _____________________________________________________________________________________________
#define list_merge_ptr(x, y) list_merge_front(x->next, y)
#define list_push_ptr(x, type, val) list_push_front(x->next, type, val)
#define list_merge_list_ptr(x, y) list_merge_list_front(x->next, y)
#define list_push_ptr_arr(x, type, n, arr) list_push_front_arr(x->next, type, n, arr)
#define list_push_ptr_args(x, type, n, ...) list_push_front_args(x->next, type, n, __VA_ARGS__)
// _____________________________________________________________________________________________
#define list_pop_front(x) x = x->next
// pop 1 element after x
#define list_pop_ptr(x) list_pop_front(x->next)
// pop elements from x->next to y
#define list_pop_list_ptr(x, y) x->next = y->next

#endif
