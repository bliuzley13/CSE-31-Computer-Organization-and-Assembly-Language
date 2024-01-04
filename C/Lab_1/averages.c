#include <stdio.h>
int main(){
    //Variables for the average of even and odd digits with n being an input 
    float avg_even = 0.0; //average of even numbers
    float avg_odd = 0.0; //average of odd numbers
    int n = 1; //counter for the "Enter the nth value:""
    int oDD = 0; // sums the number with odd count in digits
    int eVEN = 0; // sums the number with even count in digits
    int oddCount = 0; // Number of odd numbers in inputs
    int evenCount = 0; // Number of even numbers in inputs
    int nUM; //number that is inputted
    int sum; // sum of the digits
    int zeroCheck[1]; // checks if there is an average possible

    //First Integer input
    printf("Enter the 1st value: ");
    scanf("%d", &nUM);
    //Array of one element which exists to check if there is 0 in it
    zeroCheck[0] = nUM;
    //No existing average possible (0 terminates the data collection portion)
    if (zeroCheck[0] == 0){
        printf("There is no average to compute.");
    }
    //Works when the array does not have a zero in it
    else{
        for (int i = 1; i <= 123456789; i++){
            //The array has a value that should not be lost
            zeroCheck[0] = nUM;
            //Does work to sort the numbers that add up their digits to even or odd
            if (nUM != 0){
                //Takes in the number and rewords it
                int numBER = nUM;
                //sum is reset every time when getting the sum of digits
                sum = 0;
                //Finds the modulo remainder to discover the sum of digits & it does the addition aspect to have the sum of a digit input
                while (numBER != 0){
                    sum = sum + (numBER % 10);
                    numBER /= 10;
                }
                //Odd/Even Determinator with remainder
                int rEM = sum % 10;
                //checks if the remainder is a certain value in order for it to be odd
                if ((rEM==1)^(rEM==3)^(rEM==5)^(rEM==7)^(rEM==9)^(rEM==-1)^(rEM==-3)^(rEM==-5)^(rEM==-7)^(rEM==-9)){
                    oddCount++;
                    oDD = nUM + oDD;
                }
                //has remainders in which every other value is even
                else{
                    evenCount++;
                    eVEN = nUM + eVEN;
                }
            
            }
            //number which is intended to say "Enter the 4th value: ", "Enter the 5th value: ", and so forth
            n = n + 1;
            //All format
            printf("Enter the ");
            if (n == 2){
                printf("2nd ");
            }
            else if (n == 3)
            {
                printf("3rd ");
            }
            //Because everything after 3 ends with a "th"
            else {
                printf("%dth ", n);
            }
            printf("value: ");
            //Inputted Value for each input
            scanf("%d", &nUM);
            //Breaks loop if the input is 0
            if (nUM == 0){
                printf("\n");
                break;
            }
            
        }
        //Final Result Check
        avg_even = (double)eVEN / evenCount;
        avg_odd = (double)oDD / oddCount;
        //Printing the resulting code:
        //makes sure it is not printed if digits summing up to even are not in any of the inputs
        if (evenCount != 0){
            printf("Average of input values whose digits sum up to an even number: %.2f\n", avg_even);
        }
        //makes sure it is not printed if digits summing up to odd are not in any of the inputs
        if (oddCount != 0){
        printf("Average of input values whose digits sum up to an odd number: %.2f\n", avg_odd);
        }
    }
    
    return 0;
}