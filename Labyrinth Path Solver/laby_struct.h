typedef struct d {
	int x;
	int y;
	int right;
	int left;
	int down;
	int up;
	int camefrom;
}StackDataType, position;

struct Node {
	StackDataType data;
	Node *next;
};

struct Stack {
	Node *head;

	void create();
	void close();
	void push(StackDataType);
	StackDataType top();
	StackDataType pop();
	bool isempty();
};