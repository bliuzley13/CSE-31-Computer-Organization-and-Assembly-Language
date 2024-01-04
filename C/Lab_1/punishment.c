#include <stdio.h>
int main(){
    //Variables for the program in repetition count and inserting the typo index
    int repCount;
    int typoIndex;
    //Input Phrases that are used once
    //Number of Repetitions of a phrase, prints new line after that
    printf("Enter the repetition count for the punishment phrase: ");
    scanf("%d", &repCount);
    
    //Doing the Re-Enter portion
    //For the repetition count being below 0
    while (repCount <= 0){
        printf("You entered an invalid value for the repetition count! Please re-enter: ");
        scanf("%d", &repCount);
        //When the repetition count issue is satisfied
        if (repCount >= 1){
            break;
        }
    }
    printf("\n");


    //Looks for the line where the typo is going to be placed
    printf("Enter the line where you want to insert the typo: ");
    scanf("%d", &typoIndex);
    
    //For the typo count being less than 0 or the typoIndex being higher than the repetitions
    while ((typoIndex < 1) || (repCount < typoIndex)){
        printf("You entered an invalid value for the typo placement! Please re-enter: ");
        scanf("%d", &typoIndex);
        //When the typo count issue is satisfied
        if ((typoIndex >= 1) && (repCount >= typoIndex)){
            break;
        }
    }
    printf("\n");

    //Typing out the for loop with the repetition
    for (int i = 1; i <= repCount; i++) {
        //Typo Code part at the intended line
        if (i == typoIndex){
            printf("Cading wiht is C avesone! \n");
        }
        //Prints correct phrase otherwise
        else {
            printf("Coding with C is awesome! \n");
        }
    }
    return 0;
}