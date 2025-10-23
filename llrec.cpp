#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************

void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot){
  if (head == NULL){
    smaller = NULL;
    larger = NULL;
    return;
  }
  Node* temp = head;
  Node* rest = head ->next;
  temp->next = NULL; // detach

  llpivot(rest, smaller, larger, pivot);

  if (temp->val <= pivot){
    temp->next = smaller;
    smaller = temp;
  }
  if (head->val > pivot){
    temp->next = larger;
    larger = temp;
  }
  head = NULL;
}

