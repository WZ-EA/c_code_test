#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
// scanf
// Implement these functions
void handleInsert(LinkedList*); // done
void handleRemove(LinkedList*); // done
void handleCurrentCal(LinkedList*, int); // done
void handleVoltage(LinkedList*, int); // done
void handlePrint(LinkedList*); // done
void handleQuit(LinkedList*);  // done 

Node* createNewNode(int resistance, char labelName[STRING_MAX]);
void findAndInsert(LinkedList* circuit, int resistance, char labelName[STRING_MAX]);
void frontInsert(LinkedList* circuit, int resistance, char labelName[STRING_MAX]);
bool alreadyInList(LinkedList* circuit, char labelName[STRING_MAX]); 
int countTotalResistance(LinkedList* circuit);
float countTotalCurrent(int voltage, LinkedList* circuit);
int findCorrespondingResistance(LinkedList* circuit, char labelName[STRING_MAX]);

int main(void) {
  LinkedList circuit;
  initList(&circuit);
  char command = '\0';
  printf("Welcome to our circuit simulator\n");
  // Enter the source voltage!
  printf("What is the source of the voltage?\n");
  int voltage;
  readInputNumber(&voltage);

  while (command != 'Q') {
    command = getCommand();

    switch (command) {
      case 'I':
        handleInsert(&circuit);
        break;
      case 'R':
        handleRemove(&circuit);
        break;
      case 'C':
        handleCurrentCal(&circuit, voltage);
        break;
      case 'V':
        handleVoltage(&circuit, voltage);
        break;
      case 'P':
        handlePrint(&circuit);
        break;
      case 'Q':
        handleQuit(&circuit);
        break;
    }
  }
  return 0;
}

void handleInsert(LinkedList* circuit) {
  int resistance = 0;
  printf("What's the value of the resistor: ");
  readInputNumber(&resistance);
  printf("What's the label of the resistor: ");
  char labelName[STRING_MAX];
  readInputString(labelName, STRING_MAX);

  // TODO: Implement the insert into ordered list function

  if(alreadyInList(circuit, labelName) == false){
    findAndInsert(circuit, resistance, labelName);
  }else{
    printf("A resistor with %s label already exists.\n", labelName);
  }
}
void handleRemove(LinkedList* circuit) {  //  - - - - - - - - - - - - - - - - R - - - - - - - - - - - - - - - - - 
  // TODO: Implement the remove function
  char labelName[STRING_MAX];
  bool deleted = false;

  printf("What's the label of the resistor you want to remove: "); //What's the label of the resistor you want to remove: 
  //scanf("%s", labelName);
  readInputString(labelName, STRING_MAX);

  if(circuit->head == NULL){
    printf("The resistor with %s label does not exist.\n", labelName); //"The resistor with %s label does not exist.\n"
    return;
  }else if(strcmp(circuit->head->name, labelName) == 0){
    Node* newHead = circuit->head->next;
    free (circuit->head);
    circuit->head = newHead;
    return;
  }

  Node* current = circuit->head;
  while((current->next != NULL) && (strcmp(current->next->name, labelName) != 0)){
    current = current->next;
  }

  if(current->next != NULL){
    Node* temp = current->next;
    current->next = temp->next;
    free(temp);
    deleted = true;
  }

  if(deleted == false){
    printf("The resistor with %s label does not exist.\n", labelName);  //"The resistor with %s label does not exist.\n"
  }

}

void handleCurrentCal(LinkedList* circuit, int voltage) {
  // TODO: Implement the function that prints the value of current in the
  // circuit
  float current = countTotalCurrent(voltage, circuit);
  printf("The current in the circuit is %.6fA\n", current);
}

void handleVoltage(LinkedList* circuit, int voltage) {  //  - - - - - - - - - - - - - - - - V - - - - - - - - - - - - - - - - - 
  // TODO: Implement the function that prints the potential difference across a
  // resistor
  char labelName[STRING_MAX];

  printf("What's the label of the resistor you want to find the voltage across: ");  //"What's the label of the resistor you want to find the voltage across: "
  //scanf("%s", labelName);
  readInputString(labelName, STRING_MAX);

  int correspondingResistance = findCorrespondingResistance(circuit, labelName);

  if(correspondingResistance == -1){
    printf("The resistor with %s label does not exist.\n", labelName); // "The resistor with %s label does not exist.\n"
  }else{
    float correspondCurrent = countTotalCurrent(voltage, circuit);
    float correspondVoltage = ((float)correspondingResistance) * correspondCurrent;
    printf("Voltage across resistor is %.6fV", correspondVoltage); // "Voltage across resistor is %.6fV" // whether to add the line space?
  }
}
void handlePrint(LinkedList* circuit) {
  // TODO: they can implement the print function
  Node* current = circuit->head; 

  if(current != NULL){
    printf("%s %d Ohms\n", current->name, current->value);

    while(current->next != NULL){
      current = current->next;
      printf("%s %d Ohms\n", current->name, current->value);
    }
  }
}

void handleQuit(LinkedList* circuit) {
  // TODO: Implement the quit function
  printf("Removing all resistors in the circuit ...\n");

  while(circuit->head != NULL){
    printf("%s %d Ohms\n", circuit->head->name, circuit->head->value);
    Node* temp = circuit->head;
    circuit->head = temp->next;
    free(temp);
  }

  /*
  Node* newHead = circuit->head->next;
    free (circuit->head);
    circuit->head = newHead;
    return;
  */
}



// Added Functions:
Node* createNewNode(int resistance, char labelName[STRING_MAX]){

  Node *newNode = (Node *)malloc(sizeof(Node));

  newNode->value = resistance; // AAA
  strcpy(newNode->name, labelName);
  newNode->next = NULL;

  return newNode;
}

void findAndInsert(LinkedList* circuit, int resistance, char labelName[STRING_MAX]){
  Node* current = circuit->head;

  if(current == NULL){
    frontInsert(circuit, resistance, labelName);
    return;
    
  }else if(strcmp(current->name, labelName) > 0){
    frontInsert(circuit, resistance, labelName);
    return;
  }

  while((current->next != NULL) && (strcmp(labelName, current->next->name) > 0)){
    current = current->next;
  }
  
  Node* newNode = createNewNode(resistance, labelName);

  newNode->next = current->next;
  current->next = newNode;
}

void frontInsert(LinkedList* circuit, int resistance, char labelName[STRING_MAX]){

  Node* temp = createNewNode(resistance, labelName);
  
  temp->next = circuit->head; //AAA
  circuit->head = temp;
}

bool alreadyInList(LinkedList* circuit, char labelName[STRING_MAX]){

  bool alreadyIn = false;
  Node* current = circuit->head;

  while((current != NULL)){
    if(strcmp(current->name, labelName) == 0){
      alreadyIn = true;
      return alreadyIn;
    }

    current = current->next;
  }

  return alreadyIn;

  /* Error example: you know why?
  bool alreadyIn = false;
  Node* current = circuit->head;

  if(current == NULL){
    return alreadyIn;
  }
  if(strcmp(current->name, labelName) == 0){
    alreadyIn = true;
    return alreadyIn;
  }

  while(current->next != NULL){
    if(strcmp(current->name, labelName) == 0){
      alreadyIn = true;
      return alreadyIn;
    }
    current = current->next;
  }

  return alreadyIn;
  */
}


int countTotalResistance(LinkedList* circuit){
  Node* current = circuit->head;
  int totalResistance = 0;

  while(current != NULL){
    totalResistance += current->value;
    current = current->next;
  }
  return totalResistance;
}

float countTotalCurrent(int voltage, LinkedList* circuit){

  int totalResistance = countTotalResistance(circuit);

  float totalCurrent = ((float)voltage) / ((float)totalResistance);
  return totalCurrent;
}

int findCorrespondingResistance(LinkedList* circuit, char labelName[STRING_MAX]){
  Node* current = circuit->head;
  int correspondingResistance = -1;

  while(current != NULL){
    if(strcmp(current->name, labelName) == 0){
      correspondingResistance = current->value;
    }

    current = current->next;
  }

  return correspondingResistance;

}
/* A test case example:

10
I
500
R1
I
500
R2
I
500
R2
R
R3
C
V
R1
P
R
R1
P
V
R1
V
R2
Q

*/
