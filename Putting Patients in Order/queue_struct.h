enum compleints {
	RED = 1, 
	YELLOW, 
	GREEN
};

struct Patient {
	int patient_number;
	int arriving_time;
	int treatment_time;
	int compleint;
	Patient *next;
};

// Queue struct definition
struct Queue {
	Patient *front;
	Patient *back;
	void create();
	void close();
	void enqueue(Patient *);
	void dequeue();
	Patient *first();
	bool isempty();
};
