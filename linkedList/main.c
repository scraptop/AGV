/*
 * main.c
 * http://www.learn-c.org/en/Linked_lists
 */
#include <stdio.h>
#include <stdlib.h> // Linked list

#include "header_uart_hc06.h" // Uart

#include "driverlib/adc.h"
#include "driverlib/timer.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

// Struct för noder, enkellistad

typedef struct node {
    int val;
    struct node * next;
} node_t;


static void init_linkedList(void){

	node_t * head = NULL;
	head = malloc(sizeof(node_t));

	if (head == NULL) {
	  //  return 1;
	}

	head->val = 1;
	head->next = NULL;

}

static void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
}

// Add / Insert last in list / push
static void push(node_t * head, int val) {
    node_t * current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    /* now we can add a new variable */
    current->next = malloc(sizeof(node_t));
    current->next->val = val;
    current->next->next = NULL;
}

// Delete
static int pop(node_t ** head) {
    int retval = -1;
    node_t * next_node = NULL;

    if (*head == NULL) {
        return -1;
    }

    next_node = (*head)->next;
    retval = (*head)->val;
    free(*head);
    *head = next_node;

    return retval;
}



int main(void) {
	init_linkedList();

    node_t * test_list = malloc(sizeof(node_t));
    test_list->val = 1;
    test_list->next = malloc(sizeof(node_t));
    test_list->next->val = 2;
    test_list->next->next = malloc(sizeof(node_t));
    test_list->next->next->val = 3;
    test_list->next->next->next = malloc(sizeof(node_t));
    test_list->next->next->next->val = 4;
    test_list->next->next->next->next = NULL;

    push(test_list, 3);
    print_list(test_list);
    puts("Hello, world!");
    printf("hello its me");


	return 0;
}
