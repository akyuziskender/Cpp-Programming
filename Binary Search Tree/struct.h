#ifndef STRUCT_H
#define STRUCT_H
struct number {
	char *phonenum;
	number *next;
};

struct Phone_node {
	char *name;
	number *phonenum;
	Phone_node *right, *left;
};

struct tree {
	Phone_node *root;
	int node_counter;
	void create();
	void close();
	void emptytree(Phone_node *);
	Phone_node *create_node(char *);
	void add(char *, char *);
	bool addNumber(Phone_node *, char *);
	Phone_node *search(char *);
	void print_inorder(Phone_node *);
	bool remove(char *, char);
	bool update(char *, char *);
};
#endif