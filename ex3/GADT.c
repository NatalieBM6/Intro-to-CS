
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "GADT.h"

typedef struct Element {
	ELM listElm;
	struct Element *next;
} Element_t;

typedef struct List {
	Element_t *head;
	ELM(*create_elm)();
	void(*cpy_elm)(ELM, ELM);
	int(*cmp_elm)(ELM, ELM);
	void(*free_elm)(ELM);
	void(*print_elm)(ELM);
	ELM(*add_elm_to_elm)(ELM, ELM);
} List_t;

/************************************************************************
*function name:SLCreate
*The Input: adresses of functions defined in another file, according to the
*generic struct.
*The Output: a pointer to the new linked list.
*The Function operation: The function recieves adresses of functions defined
*in another file and creates a head for a linked list according to the generic
*struct.
*************************************************************************/
HEAD SLCreate(ELM head_val, ELM(*create_elm)(), void(*cpy_elm)(ELM, ELM),
	int(*cmp_elm)(ELM, ELM), void(*free_elm)(ELM),
	void(*print_elm)(ELM), ELM(*add_elm_to_elm)(ELM, ELM)) {
	List_t *list;
	Element_t *newElement;
	list = (List_t*)calloc(1, sizeof(List_t));
	//if allocation succeded.
	if (list != NULL) {
		newElement = (Element_t*)calloc(1, sizeof(Element_t));
		//if allocation succeded.
		if (newElement != NULL) {
			newElement->listElm = (*create_elm)(); //create new element.
			//copy the head of the list's value to the new element.
			cpy_elm(head_val, newElement->listElm);
			newElement->next = NULL;
			list->head = newElement;
			list->create_elm = create_elm;
			list->cpy_elm = cpy_elm;
			list->cmp_elm = cmp_elm;
			list->free_elm = free_elm;
			list->print_elm = print_elm;
			list->add_elm_to_elm = add_elm_to_elm;
			return list;
		}
	}
	return NULL;
}

/************************************************************************
*function name:SLAddListElement
*The Input: a pointer to pointer to the head of the list and an element
*to add to the list.
*The Output: Success/Failure of the element addition.
*The Function operation: The function adds a new element to it's correct
*place in the sorted list.
*************************************************************************/
RESULT SLAddListElement(HEAD* head, ELM node) {
	Element_t *current;
	Element_t *previous;
	Element_t *temp;
	Element_t *newElm;
	List_t **list;
	list = (List_t**)head;
	current = (**list).head;
	newElm = (Element_t*)calloc(1, sizeof(Element_t));
	if (newElm != NULL) {
		newElm->listElm = (**list).create_elm();
		newElm->next = NULL;
		if ((newElm->listElm) != NULL) {
			(**list).cpy_elm(node, newElm->listElm);
			//if new element is smaller than the head, add it to the start of the list.
			if (((**list).cmp_elm((**list).head->listElm, newElm->listElm)) > 0) {
				temp = (**list).head;
				(**list).head = newElm;
				newElm->next = temp;
			}
			//else, add the element to it's correct place in the sorted list.
			else {
				while (current->next != NULL) {
					previous = current;
					current = current->next;
					if (((**list).cmp_elm(current->listElm, newElm->listElm) > 0) &&
						((**list).cmp_elm(previous->listElm, newElm->listElm) < 0)) {
						temp = previous->next;
						previous->next = newElm;
						newElm->next = temp;
						return success;
					}
				}
				current->next = newElm;
			}
			return success;
		}
	}
	return outOfMem;
} //end of function

  /************************************************************************
  *function name:SLAddToElement.
  *The Input: a pointer to pointer to the head of the list and two elements:
  * a given element to add to another element and the element to add the first
  *element to.
  *The Output: -.
  *The Function operation: The function finds where a given element is on
  *the list and adds to it another element.
  *************************************************************************/
void SLAddToElement(HEAD* head, ELM toEl, ELM addEl) {
	List_t **list;
	ELM temp = NULL;
	list = (List_t**)head;
	//The new element, created by adding an element to an element.
	temp = (**list).add_elm_to_elm(toEl, addEl);
	//if the element we add to is on the list.
	if (SLFindElement(*head, toEl) != NULL) {
		//If the list has more than one element.
		if ((**list).head->next != NULL) {
			//remove the element we add to from the list.
			SLRemoveElement(head, toEl);
			//add the new element, created by adding an element to an element.
			SLAddListElement(head, temp);
			(**list).free_elm(&temp);
		}
		//else, the element we want to add to is the only element on the list.
		else {
			(**list).free_elm(&(**list).head->listElm);
			(**list).head->listElm = temp;

		}
	}
	return;
}

  /************************************************************************
  *function name:SLDestroy
  *The Input: a pointer to the head of the list.
  *The Output: -
  *The Function operation: The function frees the allocated memory of each
  *element on the list.The function deletes the linked list.
  *************************************************************************/
void SLDestroy(HEAD head) {
	List_t **list;
	Element_t *temp;
	Element_t *current;
	list = (List_t**)head;
	current = (**list).head;
	//if the list is not empty.
	if ((**list).head->next != NULL) {
		while (current != NULL) {
			temp = current->next;
			//free to the current's element.
			(**list).free_elm(&current->listElm);
			free(current);
			current = temp;
		}
		free((*list));
		*list = NULL;
	}
	//When there is only one element in the list.
	else {
		//free to the only element.
		(**list).free_elm(&(**list).head->listElm);
		free((**list).head);
		free((*list));
		*list = NULL;
	}
	return;
}

/************************************************************************
*function name:SLRemoveElement.
*The Input: a pointer to pointer to the head of the list and an element
*to remove from the list.
*The Output: Success/Failure of the function.
*The Function operation: The function removes an element from the list.
*************************************************************************/
RESULT SLRemoveElement(HEAD* head, ELM node) {
	List_t **list = (List_t**)head;
	Element_t *current = (**list).head;
	Element_t *previous;
	Element_t *temp;
	//if the element we want to remove is the head of the list.
	if ((**list).cmp_elm((**list).head->listElm, node) == 0) {
		//if there is only one element on the list.
		if (!((**list).head->next)) {
			SLDestroy(head);
		}
		//When the head is not the only element on the list.
		else {
			temp = (**list).head->next;
			(**list).free_elm(&(**list).head->listElm);
			free((**list).head);
			(**list).head = temp;
		}
		return success;
	}
	//When the head of the list is not the element we want to remove.
	else {
		previous = (**list).head;
		current = (**list).head->next;
		//search for the element we want to remove in the list.
		while (current != NULL) {
			//When the element we want to remove exists in the list.
			if ((**list).cmp_elm(current->listElm, node) == 0) {
				temp = current->next;
				(**list).free_elm(&current->listElm);
				free(current);
				previous->next = temp;
				return success;
			}
			previous = current;
			current = current->next;
		}
		//When the element we want to remove doesn't exist in the list.
		printf("FALSE\n");
		return badArgs;
	}
	return badArgs;
} //end of function

  /************************************************************************
  *function name:SLFindElement.
  *The Input: a pointer to the head of the list and an element remove from
  *the list.
  *The Output: current or NULL.
  *The Function operation: The function finds out if a given element is on
  *the list.
  *************************************************************************/
ELM SLFindElement(HEAD head, ELM node) {
	List_t *list;
	Element_t *current;
	list = (List_t*)head;
	current = list->head;
	//If the list is not empty.
	if (current != NULL) {
		//while the list does not end search for the element.
		while (current != NULL) {
			//If the element we search for exists in the list.
			if (list->cmp_elm(current->listElm, node) == 0)
				return current;
			current = current->next;
		}
	}
	//When the list is empty or element is not in the list.
	else
		return NULL;
	return NULL;
}

/************************************************************************
*function name:SLPrintList.
*The Input: a pointer to the head of the list.
*The Output: -.
*The Function operation: The function prints all the elements on the list.
*************************************************************************/
void SLPrintList(HEAD head) {
	int tabs = 0, counter = 0;
	List_t *list;
	Element_t *current;
	list = (List_t*)head;
	current = list->head;
	//While the list continues.
	while (current != NULL) {
		//Print tabs according to the place of the element on the list.
		while (tabs < counter) {
			tabs++;
			printf("\t");
		}
		list->print_elm(current->listElm);
		current = current->next;
		counter++;
	}
	return;
}

/************************************************************************
*function name:SLPrintSize.
*The Input: a pointer to the head of the list.
*The Output: -.
*The Function operation: The function counts the amount of elements on the
*list and by that finds the length of the list.
*************************************************************************/
void SLPrintSize(HEAD head) {
	int counter = 0;
	List_t *list;
	Element_t *current;
	list = (List_t*)head;
	current = list->head;
	//While the list does not end increase the counter.
	while (current != NULL) {
		current = current->next;
		counter++;
	}
	printf("%d\n", counter);
	return;
}