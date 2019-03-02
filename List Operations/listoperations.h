#ifndef LIST_H
#define LIST_H
#include "nodes.h"

struct List{
    Phone_node *head, *tail;
    int personcount;
    void create();
    Phone_node *create_node(char *);
    void close();
    void makeEmpty();
    bool addPerson(char *);
    bool addNumber(char *, char *, char *);
    void removePerson(char *);
    void removeNumber(char *);
    void updatePerson(char *);
    void updateNumber(char *);
    int search(char *);
    void list();
    int listNumbers(char *);
};
#endif
