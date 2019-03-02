struct studentInfo{
    char *name;
    char *surname;
    char *email;
    studentInfo *next;
    studentInfo *previous;
};

struct surnameMap{
    char *surname;
    studentInfo *student;
    surnameMap *next;
};
