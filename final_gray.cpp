//NAME: Man Jin Hay
//ID: 20041763(jhman)
//EMAIL: sliv.phone@gmail.com
//Lab Section: LA3

#include <iostream>
#include <math.h>
#include <iomanip>
#include <cstring>
using namespace std;

enum Encoding {GRAY, BINARY};

const int BITSIZE = 8;
const int MAX_NUM = 255;
const int MIN_NUM = 0;

/* TO DO #1 */
void decimal_to_binary(int n, char binary[], int i)
{
    int point = (int)(n/pow(2,i));
    int rmd = n%(int)pow(2,i);
    binary[BITSIZE]= '\0';
    if(point == 1){
        binary[BITSIZE-1-i] = 49;
    }else{
        binary[BITSIZE-1-i] = 48;
    }
    if(i>=1){
        i--;
        decimal_to_binary(rmd,binary,i);
    }
}

/* TO DO #2 */
int binary_to_decimal(char binary[], int i)
{
    int sum = 0;
    if(i<0){
        return sum;
    }

    if(binary[i]==49){
        sum+= pow(2,BITSIZE-i-1);
    }
    i--;
    return sum+=binary_to_decimal(binary,i);
}

/* TO DO #3 */
void binary_to_gray(char binary[], char gray[], int i)
{   
    gray[0] = binary[0];
    gray[8] = '\0';
    i++;
    if(!(binary[i-1]==49) != !(binary[i]==49)){
        gray[i] = 49;
    }else{
        gray[i] = 48;
    }
    if(i<BITSIZE-1){
        binary_to_gray(binary,gray,i);
    }
}

/* TO DO #4 */
void gray_to_binary(char binary[], char gray[], int i)
{   
    binary[0] = gray[0];
    binary[8] = '\0';
    i++;
    if(!(gray[i]==49) != !(binary[i-1]==49)){
        binary[i] = 49;
    }else{
        binary[i] = 48;
    }
    if(i<BITSIZE-1){
        gray_to_binary(binary,gray,i);
    }
}

/* TO DO #5 */
void binary_reflection(char gray_array[][BITSIZE+1], int i)
{
    // Print all the i-bit Gray encodings
    
    cout << endl << i << "-bit Gray codes:" << endl;
    cout << setw(15) << "Decimal" << setw(15) << "Gray" << endl;
    
    int size = (int) pow(2,i);// YOUR CODE HERE: what is the value of 'size'?
    for(int j=0; j<size; j++)
        cout << setw(15) << j << setw(15) << gray_array[j] << endl;
    
    // Calculate a new array, which will hold all the (i+1)-bit Gray encodings
    // This array should be printed in the next recursive call

    // First calculate the new size for this new array
    const int NEW_SIZE = 2*size;// YOUR CODE HERE: what is the value of 'NEW_SIZE'?
    char new_gray_array[NEW_SIZE][BITSIZE+1];
        
    for (int j = 0; j < (NEW_SIZE/2); ++j)
    {
        for (int k = 0; k < i; ++k)
        {
            new_gray_array[j][k+1] = gray_array[j][k];
        }
        new_gray_array[j][0] = '0';
        new_gray_array[j][i+1] = '\0';
    }

    for (int j = NEW_SIZE/2; j < NEW_SIZE; ++j)
    {
        for (int k = 0; k < i; ++k)
        {
            new_gray_array[j][k+1] = gray_array[NEW_SIZE-1-j][k];
        }
        new_gray_array[j][0] = '1';
        new_gray_array[j][i+1] = '\0';
    }

    // Then calculate the contents of this new array, i.e., the (i+1)-bit Gray encodings
    /* YOUR CODE HERE */
    if(i<8){
        i++;
        binary_reflection(new_gray_array,i);
    }
}

void print(int n)
{
        cout << "The decimal position is " << n << endl;
}

void print(char number[], Encoding e = BINARY)
{
    
    if(e == GRAY)
        cout << "The gray code is ";
    else if(e == BINARY)
        cout << "The binary number is ";
    
    cout << number << endl;
}

char get_menu_choice(void)
{
    char c;
    
    cout << endl << "Menu:" << endl;
    cout << "1. Convert a decimal position to its Gray code" << endl;
    cout << "2. Convert a Gray code to its decimal position" << endl;
    cout << "3. Print Gray codes using binary-reflection" << endl;
    cout << "4. Exit" << endl;
    
    do{
        cout << "Enter your choice: ";
        cin >> c;
    } while((c!= '1') && (c!= '2') && (c!= '3') && (c!= '4'));
    
    return c;
}

void get_gray_code(char gray[])
{
    char c[1000];
    
    do
    {
        cout << "Enter an 8-bit Gray code: ";
        cin >> c;
    } while(strlen(c)!=BITSIZE);
    
    strcpy(gray, c);
}

int get_decimal_number(void)
{
    int n;
    
    do
    {
        cout << "Enter a decimal position in range [0,255]: ";
        cin >> n;
    } while(n<MIN_NUM || n>MAX_NUM);
    
    return n;
}

int main(void)
{
    char c;
    int n;
    char binary[BITSIZE+1];
    char gray[BITSIZE+1];
    char gray_array[2][BITSIZE+1] = {"0", "1"};
    
    do
    {
        c = get_menu_choice();
        
        switch(c)
        {
            case '1':
                n = get_decimal_number();
                decimal_to_binary(n, binary, BITSIZE-1);
                binary_to_gray(binary, gray, 0); 
                print(n);
                print(binary);
                print(gray,GRAY);
                break;
            case '2':
                get_gray_code(gray);
                gray_to_binary(binary, gray, 0);
                n = binary_to_decimal(binary, BITSIZE-1);
                print(gray, GRAY);
                print(binary);
                print(n);
                break;
            case '3':
                binary_reflection(gray_array, 1);
                break;
        }
    } while(c != '4');
    
    cout << "Good bye!" << endl;
    
    return 0;
}