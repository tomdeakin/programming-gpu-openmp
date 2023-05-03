/*

Name:   linked_list_seq ....  figure 2.11

Description:  This program traverses a linked list carrying out
                     a compute-intensive computation for each element 
                     of the list.  The computations are independent and
                     don't matter at all for the purposes of this exercise.

History: Written by Tim Mattson, May 2023

*/

#include <stdio.h> 

// definition of a node in the list
struct node {
   int data;
   int result;
   struct node* next;
};

void processwork(struct node *p); // function not provided
struct node* fill_list(struct node *p); // function not provided

int main(int argc, char *argv[]) {
   struct node *p=NULL;
   struct node *head=NULL;
     

   p = fill_list(p);  // function (not shown) to fill the list
   head = p;

   // traverse the list process work for each node
   while (p != NULL) {
      processwork(p); // function not provided
      p = p->next;
   }

   return 0;
}

