#include <stdio.h>
#include <string.h>
#include <ctype.h>

#pragma warning(disable : 4996) 

// [Q1 - 5pts]	Update the struct Order to include the following fields : 
// (Please structure the object to use the least amount of memory.  
// HINT: think back to padding structure.)
//		char name[61];
//		int customerNo;
//		char item[103];
//		char address[128];
//		float cost;
struct Order {
	int orderid;
	char name[61];
	char item[103];
	int customerNo;
	char address[128];
	float cost;
	struct Order* next;
} *Queue = NULL;

void flush();						// forward declaration of functions
void branching(char c);
int insert_order(struct Order* item);
int update_order(struct Order* item);
int cancel_order(int orderid);
int process_order(int numOfItems);

int sizeofOrderStructure();
int insert_update_order_helper(char c);
int process_order_helper();
int cancel_order_helper();

int main() {
	char ch = 'i';

	ungetc('\n', stdin);			// inject input buffer with a return character

	printf("The size of the order structure is %d bytes.\n\n", sizeofOrderStructure());

	do {
		printf("Enter your selection\n");
		printf("\ti: insert a new order.\n");
		printf("\tu: update an order.\n");
		printf("\td: cancel an order.\n");
		printf("\tp: process an order.\n");
		printf("\tq: quit \n");

		flush();							// flush input buffer
		ch = tolower(getchar());			// see tutorial
		branching(ch);
	} while (ch != 113);

	return 0;
}

void flush() {
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}

int sizeofOrderStructure() {
	return sizeof(struct Order);
}

void branching(char c) {					// branch to different tasks
	switch (c) {
	case 'i':
		insert_update_order_helper(c);
		break;
	case 'u':
		insert_update_order_helper(c);
		break;
	case 'd':
		cancel_order_helper();
		break;
	case 'p':
		process_order_helper();
		break;
	case 'q':
		break;
	default:
		printf("Invalid input\n");
	}
}

// [Q2 - 5pts]	Write code to capture customerNo, cost, name, address, and item
// into the new created struct Order pointed by ptr.  Assume name, address, and item
// cannot accept any spaces or return characters.  
int insert_update_order_helper(char c) {

	struct Order *ptr = (struct Order *)malloc(sizeof(struct Order));

	printf("What is the order id? ");
	scanf("%d", &ptr->orderid);

	/* -- START CODING HERE -- */

	printf("What is the Customer's Number? ");
	scanf("%d", &ptr->customerNo);

	printf("What is the Cost of the Item? ");
	scanf("%f", &ptr->cost);

	printf("What is the Customer's Name? ");
	scanf("%s", ptr->name);

	printf("What is the Customer's Address? ");
	scanf("%s", ptr->address);

	printf("What is the Item? ");
	scanf("%s", ptr->item);

	/* -- END CODING HERE -- */

	ptr->next = NULL;

	if (c == 'i') {
		return insert_order(ptr);
	}
	else {
		int value = update_order(ptr);

		if (value == -1) { printf("No Record Found.\n\n"); }

		return update_order(ptr);
	}
}

// [Q3 - 10pts] Implement the insert function.   The function should check 
// if existing order has been made (using the order id).   If an order 
// exist, update the record. Otherwise, insert a new order into the queue 
// – follow FIFO.      
int insert_order(struct Order* item) {

	/* -- START CODING HERE -- */
	struct Order *ptr = Queue, *btr = ptr;

	if (Queue == NULL) {
		item->next = NULL;
		Queue = item;
	}
	else {
		while (ptr != NULL) {
			if (ptr->orderid == item->orderid) {
				update_order(item);
				return 1;
			}
			btr = ptr;
			ptr = ptr->next;
		}
		item->next = btr->next;
		btr->next = item;
	}

	return 0;
	/* -- END CODING HERE -- */
}

// [Q4 - 10pts] Implement the update function.  The function will search 
// the queue using order id to locate the existing order.  If order does 
// not exist, return -1.  Otherwise, update the existing record.  
int update_order(struct Order* item) {

	/* -- START CODING HERE -- */
	struct Order *ptr = Queue;

	if (ptr == NULL) return -1;
	else {
		while (ptr != NULL) {
			if (ptr->orderid == item->orderid) {
				ptr->cost = item->cost;
				ptr->customerNo = item->customerNo;
				ptr->address[128] = item->address[128];
				ptr->name[61] = item->name[61];
				ptr->item[103] = item->item[103];
				return 0;
			}
			ptr = ptr->next;
		}
	}

	return -1;
	/* -- END CODING HERE -- */
}

int cancel_order_helper() {
	int x;

	printf("Please enter the order id: ");
	scanf("%d", &x);

	return cancel_order(x);
}

// [Q5 - 10pts] Implement the cancel function.  The function will search 
// through the queue and locate the order.  If order exist, remove it from 
// the queue.   Otherwise, please display - “Record cannot be found” - on 
// the console.  
int cancel_order(int orderid) {

	/* -- START CODING HERE -- */
	struct Order *ptr = Queue, *btr = ptr;

	if (ptr == NULL) {
		printf("No records exist\n\n");
		return -1;
	}
	else {
		while (ptr != NULL) {
			if (ptr->orderid == orderid) {
				if (ptr == Queue) {
					Queue = ptr->next;
					free(ptr);
					return 0;
				}
				btr->next = ptr->next;
				free(ptr);
				return 0;
			}
			btr = ptr;
			ptr = ptr->next;
		}
	}

	printf("Record cannot be found\n\n");
	return -1;
	/* -- END CODING HERE -- */
}

int process_order_helper() {
	int x;

	printf("How many items will the external system process? ");
	scanf("%d", &x);

	return process_order(x);
}

// [Q6 - 10pts] Implement the process function.   The function will process
// n-number of orders from the queue starting at the beginning.   Each item 
// processed will be displayed and then removed from the linked list.
// If the queue has less items then requested; process all the items in the 
// linked list and then display - "Queue is empty".   You must also consider 
// if the linked list is empty.  If so, please display – “Queue is empty” and return -1.  
int process_order(int numberOfItems) {

	/* -- START CODING HERE -- */
	struct Order *ptr = Queue;
	int total = 0;
	typedef enum { false, true } boolean;
	boolean display = false;

	if (ptr == NULL) {
		printf("Queue is empty\n\n"); 
		return -1;
	}

	while (ptr != NULL) {
		total++;
		ptr = ptr->next;
	}

	ptr = Queue;

	if (numberOfItems > total) {
		numberOfItems = total;
		display = true;
	}

	for (int i = 1; i <= numberOfItems; i++) {
		printf("\nOrder Number: %d\n", ptr->orderid);
		printf("Customer Name: %s\n", ptr->name);
		printf("Customer Number: %d\n", ptr->customerNo);
		printf("Customer Address: %s\n", ptr->address);
		printf("Item: %s\n", ptr->item);
		printf("Cost: $%.2f\n\n", ptr->cost);
		Queue = ptr->next;
		free(ptr);
		ptr = Queue;
	}

	if (display == true) printf("Queue is empty\n\n");
	return 0;
	/* -- END CODING HERE -- */
}