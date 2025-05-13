typedef struct Node {
	int coefficient;
	int exponent;
	struct Node *next;
} Node;

typedef struct LinkedList {
	Node* head;
	Node* tail;
} LinkedList;

LinkedList* initList();
int isEmpty(LinkedList* list);
void insertFirst(LinkedList* list, int coefficient, int exponent);
void insertLast(LinkedList* list, int coefficient, int exponent);
void insertAfter(LinkedList* list, int coefficient, int exponent, int coefficientToFind, int exponentToFind);
void insertSorted(LinkedList* list, int coefficient, int exponenet);
void deleteFirst(LinkedList* list);
void deleteLast(LinkedList* list);
void replaceElement(LinkedList* list, int coefficientToReplace, int exponentToReplace, int newCoefficient, int newExponent);
void deleteElement(LinkedList* list, int coefficient, int exponent);
Node* searchElement(LinkedList* list, int coefficient, int exponent);
int containsElement(LinkedList* list, int coefficient, int exponent);
char* toString(LinkedList* list);


