// represents a single term of a polynomial
typedef struct Node {
	int coefficient;
	int exponent;
	struct Node *next;
} Node;

// contains the terms of a single polynomial as nodes
typedef struct LinkedList {
	Node* head;
	Node* tail;
	int size;
} LinkedList;

LinkedList* initList();

int isEmpty(LinkedList* list);

void insertFirst(LinkedList* list, int coefficient, int exponent);
void insertLast(LinkedList* list, int coefficient, int exponent);
void insertAfter(LinkedList* list, int coefficient, int exponent, int coefficientToFind, int exponentToFind);
void insertSorted(LinkedList* list, int coefficient, int exponent);

void deleteFirst(LinkedList* list);
void deleteLast(LinkedList* list);
void replaceElement(LinkedList* list, int coefficientToReplace, int exponentToReplace, int newCoefficient, int newExponent);
void deleteElement(LinkedList* list, int coefficient, int exponent);

Node* searchElement(LinkedList* list, int coefficient, int exponent);
int containsElement(LinkedList* list, int coefficient, int exponent);

void combineLikeTerms(LinkedList* list);
void removeZeroCoefficients(LinkedList* list);

char* toString(LinkedList* list);

void freeList(LinkedList* list);


