#include <stdio.h>

typedef struct node {
  int value;
  struct node *next;
} node;

int has_cycle(node *head) {
	// Your code goes here:
  //2 Pointers at head
  node* head1 = head;
  node* head2 = head;

  //Iteration
  //If there is a length of 0 for the cycle
  if (head == NULL){
    return 0;
  } 
  //Checks if head1 next is not null and if head2 next is not null
  //Does third condition if head2 next next is not null since it does not
  //head next next in any condition would just skip the null part
  while(head1->next != NULL && head2->next != NULL && head2->next->next != NULL){
    //First pointer by one node and second pointer by two nodes
    head1 = head1->next;
    head2 = head2->next->next;
    //If 1st Pointer is the same as the first pointer
    if (head1 == head2){
      return 1;
    }
    //Next node of second pointer pointed to by first pointer
    if (head2->next == head1){
      return 1;
    }
  }
  //Returns no cycle if all fails
  return 0;
}

void test_has_cycle(void) {
  int i;
  node nodes[25]; //enough to run our tests
  for(i=0; i < sizeof(nodes)/sizeof(node); i++) {
    nodes[i].next = 0;
    nodes[i].value = 0;
  }
  nodes[0].next = &nodes[1];
  nodes[1].next = &nodes[2];
  nodes[2].next = &nodes[3];
  printf("Checking first list for cycles. There should be none, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[0])?"a":"no");
  
  nodes[4].next = &nodes[5];
  nodes[5].next = &nodes[6];
  nodes[6].next = &nodes[7];
  nodes[7].next = &nodes[8];
  nodes[8].next = &nodes[9];
  nodes[9].next = &nodes[10];
  nodes[10].next = &nodes[4];
  printf("Checking second list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[4])?"a":"no");
  
  nodes[11].next = &nodes[12];
  nodes[12].next = &nodes[13];
  nodes[13].next = &nodes[14];
  nodes[14].next = &nodes[15];
  nodes[15].next = &nodes[16];
  nodes[16].next = &nodes[17];
  nodes[17].next = &nodes[14];
  printf("Checking third list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[11])?"a":"no");
  
  nodes[18].next = &nodes[18];
  printf("Checking fourth list for cycles. There should be a cycle, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[18])?"a":"no");
  
  nodes[19].next = &nodes[20];
  nodes[20].next = &nodes[21];
  nodes[21].next = &nodes[22];
  nodes[22].next = &nodes[23];
  printf("Checking fifth list for cycles. There should be none, has_cycle says it has %s cycle\n",
    has_cycle(&nodes[19])?"a":"no");
  
  printf("Checking length-zero list for cycles. There should be none, has_cycle says it has %s cycle\n",
    has_cycle(NULL)?"a":"no");
}

int main(void) {
  test_has_cycle();
  return 0;
}
