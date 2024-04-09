#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

/* Given Functions */
void shuffle_cases(int cases[], int cases_size); 
void offer(int cases[], int cases_size, int initial_amount);
int remove_case_and_get_amount(int cases[], int cases_size, int index);

/* Your Functions */
int pick_case_index(int cases[], int cases_size); //done
bool get_decision(void); //done
int cases_average(int cases[], int cases_size, int initial_amount); //done
int cases_remaining(int cases[], int cases_size); //done
int get_last_remaining_case(int cases[], int cases_size); 
void eliminate_cases(int cases[], int cases_size, int eliminated); //done

//main function----------------------------------------------------
int main(void) {
  int cases[] = {
      0,     1,      5,      10,     25,     50,     75,     100,     200,
      300,   400,    500,    750,    1000,   5000,   10000,  25000,   50000,
      75000, 100000, 200000, 300000, 400000, 500000, 750000, 1000000,
  };
  int cases_size = ARRAY_SIZE(cases);

  shuffle_cases(cases, cases_size);

  printf("First, pick a case to keep.\n");
  int initial_index = pick_case_index(cases, cases_size); //打印整个列表 //得知所开的盒子是哪个 //生成指数
  int initial_amount =
      remove_case_and_get_amount(cases, cases_size, initial_index); //第一个盒子被拿走，所对应之改为-1--》【列表：就那个位置上是-1其他没变
  printf("You picked %d, looks like a keeper.\n", initial_index + 1); 

  eliminate_cases(cases, cases_size, 6); //有（第）n个盒子被拿走了 被拿走的数由eliminated保存 //重复前两个函数执行移除，同时他俩执行输入和打印 //打印移除盒子里的钱数--》【列表：那些被移除的位置的数值也变成了-1，其余一样
  offer(cases, cases_size, initial_amount); //第一轮

  eliminate_cases(cases, cases_size, 5);
  offer(cases, cases_size, initial_amount);

  eliminate_cases(cases, cases_size, 4);
  offer(cases, cases_size, initial_amount);

  eliminate_cases(cases, cases_size, 3);
  offer(cases, cases_size, initial_amount);

  eliminate_cases(cases, cases_size, 2);
  offer(cases, cases_size, initial_amount);

  while (cases_remaining(cases, cases_size) > 1) {
    eliminate_cases(cases, cases_size, 1);
    offer(cases, cases_size, initial_amount);
  }

  int last_case = get_last_remaining_case(cases, cases_size);
  int last_amount = cases[last_case];
  printf("\nDo you want to swap your case with case %d?\n", last_case + 1);
  bool decision = get_decision();
  if (decision) {
    printf("\nYour initial case had $%d.\n", initial_amount);
    printf("You won $%d.\n", last_amount);
  } else {
    printf("\nThe last case had $%d.\n", last_amount);
    printf("You won $%d.\n", initial_amount);
  }

  return 0;
}
//end of the main function-----------------------------------------------------------------

void shuffle_cases(int cases[], int cases_size) {
  srand(42);
  for (int shuffle = 0; shuffle < 100; ++shuffle) {
    for (int i = 0; i < cases_size; ++i) {
      int j = rand() % cases_size;
      int temp = cases[i];
      cases[i] = cases[j];
      cases[j] = temp;
    }
  }
}

int remove_case_and_get_amount(int cases[], int cases_size, int index) {
  int amount = cases[index];
  cases[index] = -1;
  return amount;
}

void offer(int cases[], int cases_size, int initial_amount) {
  int offer_amount = cases_average(cases, cases_size, initial_amount);
  printf("\nYour offer to quit now is $%d, deal or no deal?.\n", offer_amount);
  bool deal = get_decision();
  if (deal) {
    printf("\nYour case was worth: $%d\n", initial_amount);
    printf("You walked away with $%d.\n", offer_amount);
    exit(0);
  }
}

//individual functions
int pick_case_index(int cases[], int cases_size){
    printf("Eligible cases:");
    for(int a = 0; a < cases_size; a += 1){
        if(cases[a] != -1){
            printf(" ");
            int eligibleCases = a + 1;
            printf("%d", eligibleCases);
        }
    }
    printf("\n");
    int pickNum;
    do{
        printf("Pick a case: ");
        scanf("%d", &pickNum);
    }while(pickNum < 1 || pickNum > 26 || cases[pickNum - 1] == -1);
    int indexNum = pickNum - 1;
    return indexNum;
}

bool get_decision(void){
    int decisionNum;
    do{
        printf("Decide now (0 for no, 1 for yes): ");
        scanf("%d", &decisionNum);
    }while(decisionNum != 1 && decisionNum != 0);
    bool decisionBool;
    if(decisionNum == 1){
        decisionBool = true;
    }else{
        decisionBool = false;
    }
    return decisionBool;
}

int cases_average(int cases[], int cases_size, int initial_amount){
    int amount = initial_amount;
    int eligibleNum = 1; //original 1 is given to the initial case
    for(int i = 0; i < cases_size; i += 1){
        if(cases[i] != -1){
            amount += cases[i];
            eligibleNum += 1;
        }
    }
    int average = (int)(amount / eligibleNum);
    return average;
}

void eliminate_cases(int cases[], int cases_size, int eliminated){
    printf("\nOpen %d case(s) to eliminate\n", eliminated);
    for(int i = 1; i <= eliminated; i += 1){
        int indexSelected = pick_case_index(cases, cases_size);
        int caseAmount = remove_case_and_get_amount(cases, cases_size, indexSelected);
        printf("Case %d is worth $%d, it's gone now.\n", indexSelected + 1, caseAmount); //** Attention to the ' here
    }
}

int cases_remaining(int cases[], int cases_size){
    int remainingNum = 0;
    for(int i = 0; i < cases_size; i += 1){
        if(cases[i] != -1){
            remainingNum += 1;
        }
    }
    return remainingNum;
}

int get_last_remaining_case(int cases[], int cases_size){
    int lastNum;
    for(int i = 0; i < cases_size; i += 1){
        if(cases[i] != -1){
            lastNum = i;
        }
    }
    return lastNum;
}
