#ifndef LIST_H
#define LIST_H
#include "nodes.h"

struct List{
    surnameMap *head;
    int surnamecount;
    void create();
    surnameMap *create_node(char *);
    bool insertNewRecord(char *, char *);
    bool create_email(surnameMap *, char *, char *);
    void insertAll();
    bool deleteStudent(char *, char *);
    bool deleteSurnameNode(char *);
    bool updateList(char *, char *);
    void writeToFile();
    void printList();
    void deleteAll();
    void close();
    // These will be deleted !!!
    int search(surnameMap *, char *);
    void list();
};
#endif
