/*
 * tokenizer.c
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

int currentIndex;
char state;
char * input;

struct TokenizerT_ {
    
    char * tokenChars;
    
};

typedef struct TokenizerT_ TokenizerT;

char * sortForToken(char *p){
    
    int a;
    char *token;
    
    for(a=currentIndex;a<strlen(p);a++){
        
        //printf("Loop attempt: %c \n",p[a]);
        
        //If it is a space, simply ignore it as white space
        if (p[a]==' '){
            
        }
        
        //If there is a character set that has a backslash, if it is \t \n \v \f \r then it is ignored as a white space characters, otherwise it gives an error on the slash
        else if (p[a]=='\\'){
            
            if (a<strlen(p)){
                
                // if it is a white space character then increment and ignore
                if ( p[a+1]=='t' || p[a+1]=='n' || p[a+1]=='v' || p[a+1]=='f' || p[a+1]=='r'){
                    a++;
                }
                
                //prints backslash as error in hex if it is not part of a white space character
                else {
                    printf("ERROR, Not A Token: [0x%02X]\n", p[a]);
                }
            }
        }
        
        //Converts the escape characters to hex and prints it as an error message
        else if  (!isdigit(p[a])){
            printf("ERROR, Not A Token: [0x%02X]\n",p[a]);
            if (a==strlen(p)){
                a++;
                currentIndex=a;
                return NULL;
            }
        }
        
        //Can either be an octal, hexadecimal, or floating-point if it starts with a 0
        else if (p[a]=='0'){
            
            //if 0 is the last item, then it is the only item and is returned as a token
            if (a+1==strlen(p)){
                
                
                token=(char*)(malloc(sizeof(char)));
                
                int count;
                //delimit with 0s
                if(1<sizeof(token)){
                    count=(int)sizeof(token);
                    count--;
                    while(count>=1){
                        token[count]=0;
                        count--;
                    }
                    
                }
                token[0]=p[a];
                a++;
                currentIndex=a;
                
                //This is a 0 number
                state='z';
                return token;
            }
            //If the zero is followed by a zero then the current 0 is a token and the index is incremented
            else if (p[a+1]=='0'){
                token=(char*)(malloc(sizeof(char)));
                
                int count;
                //delimit with 0s
                if(1<sizeof(token)){
                    count=(int)sizeof(token);
                    count--;
                    while(count>=1){
                        token[count]=0;
                        count--;
                    }
                    
                }
                
                token[0]=p[a];
                a++;
                currentIndex=a;
                state='z';
                return token;

            }
            
            //If 0 is the current item and the item after 0 is not a valid digit or a decimal point (possible float) or a hex beginning
            else if (!isdigit(p[a+1]) && p[a+1]!='.' && p[a+1]!='x' && p[a+1]!='X'){
                
                //return 0
                token=(char*)(malloc(sizeof(char)));
                
                int count;
                //delimit with 0s
                
                if(1<sizeof(token)){
                    count=(int)sizeof(token);
                    count--;
                    while(count>=1){
                        token[count]=0;
                        count--;
                    }
                    
                }
                token[0]=p[a];
                a++;
                currentIndex=a;
                state='z';
                return token;
            }
            
            //checks if a hexadecimal number beginning
            else if (a<strlen(p) && (p[a+1]=='x' || p[a+1]=='X')){
                
                //If the x is at the end of the input then this will not be a hexidecimal
                if (a+2==strlen(p)){
                    
                    //Save and return 0
                    token=(char*)(malloc(sizeof(char)));
                    
                    int count;
                    //delimit with 0s
                    if(1<sizeof(token)){
                        count=(int)sizeof(token);
                        count--;
                        while(count>=1){
                            token[count]=0;
                            count--;
                        }
                        
                    }

                    token[0]=p[a];
                    
                    a++;
                    currentIndex=a;
                    state='z';
                    return token;
                }
                
                //If the number after 0x is not a number in hexidecimal form (0-9, a-f, A-F), then it is not a hexidecimal number
                else if (!((p[a+2]>='0' && p[a+2]<='9') || (p[a+2]>='a'&& p[a+2]<='f') || (p[a+2]>='A' && p[a+2]<='F') )){
                    
                    //return 0
                    token=(char*)(malloc(sizeof(char)));
                    
                    int count;
                    //delimit with 0s
                    if(1<sizeof(token)){
                        count=(int)sizeof(token);
                        count--;
                        while(count>=1){
                            token[count]=0;
                            count--;
                        }
                        
                    }

                    token[0]=p[a];
                    a++;
                    currentIndex=a;
                    state='z';
                    return token;
                    
                }
                
                //We now know that it is a hex number for sure
                else{
                    int b=a+2;
                    int arraysize=2;
                    
                    //checks how many valid items are a part of the number after 0x
                    while (b<strlen(p)){
                        if ((p[b]>='0' && p[b]<='9') || (p[b]>='a'&& p[b]<='f') || (p[b]>='A' && p[b]<='F') ){
                            arraysize++;
                        }
                        b++;
                    }
                    
                    
                    
                    
                    //Create an array with memory allocated exactly to that size and add the 0 and x as the first two char array items in the token
                    token = (char*)(malloc(4*arraysize+1));
                    b=a;
                    int index=2;
                    token[0]=p[b];
                    token[1]=p[b+1];
                    b+=2;
                    
                    
                    
                    int count;
                    //delimit with 0s
                    if(arraysize<sizeof(token)){
                        count=(int)sizeof(token);
                        count--;
                        while(count>=arraysize){
                            token[count]=0;
                            count--;
                        }
                    }
                    
                    
                    while (b<strlen(p)){
                        if (( (p[b]>='0' && p[b]<='9') || (p[b]>='a' && p[b]<='f') || (p[b]>='A' && p[b]<='F') ) ){
                            token[index]=p[b];
                            index++;
                            b++;
                        }
                        
                        else{
                            break;
                        }
                        
                        
                    }
                    currentIndex=b;
                    
                    //set as hex
                    state='h';
                    return token;
                }
            }
            
            //If it has a value 1-7 after 0, then it is a possible octal number beginning
            else if ((a<strlen(p)) && (p[a+1]>='1' && p[a+1]<='7')){
                
                int b=a;
                int arraysize=2;
                
                //check number of elements in the octal number that meet criteria
                while (b<strlen(p)){
                    if (p[b]>='0' && p[b]<='7'){
                        arraysize++;
                    }
                    b++;
                }
                
                //Allocate memory according to elements
                token=(char*)(malloc(4*arraysize+1));
                int index=2;
                token[0]=p[a];
                token[1]=p[a+1];
                b=a+2;
                
                while (b<strlen(p)){
                    if (p[b]>='0' && p[b]<='9'){
                        token[index]=p[b];
                        index++;
                    }
                    else {
                        break;
                    }
                    b++;
                }
                currentIndex=b;
                
                //set as an octal
                state='o';
                return token;
            }
            
            //If it has a decimal point after 0 it is a possible floating-point number
            else if (a<strlen(p) && p[a+1]=='.'){
                
                //If there is no value after the decimal point than 0 is the token
                if (a+2==strlen(p)){
                    
                    
                    token=(char*)(malloc(4));
                    
                    int count;
                    //delimit with 0s
                    if(1<sizeof(token)){
                        count=(int)sizeof(token);
                        count--;
                        while(count>=1){
                            token[count]=0;
                            count--;
                        }
                        
                    }
                    
                    token[0]=p[a];
                    a++;
                    currentIndex=a;
                    state='d';
                    return token;
                    
                }
                
                //if the number after the decimal point is not a digit 0 is the token
                else if(!isdigit(p[a+2])){
                    token=(char*)(malloc(sizeof(char)));
                    
                    int count;
                    //delimit with 0s
                    if(1<sizeof(token)){
                        count=(int)sizeof(token);
                        count--;
                        while(count>=1){
                            token[count]=0;
                            count--;
                        }
                        
                    }

                    token[0]=p[a];
                    a++;
                    currentIndex=a;
                    state='d';
                    return token;
                }
                
                //If the value after the decimal point is valid, then store as a floating-point token
                else if (p[a+2]>='0'&& p[a+2]<='9'){
                    
                    int notation=0;
                    int negative=0;
                    
                    int arraysize=3;
                    
                    //point to the element after the decimal point
                    int b=a+2;
                    
                    
                    //check how many valid chars after '0','.' and the subsequent valid char
                    while (b<strlen(p)){
                        if (p[b]>='0' && p[b]<='9'){
                            arraysize++;
                        }
                        
                        //If there is an e with a valid number after
                        else if((p[b]=='e'||p[b]=='E') && (isdigit(p[b+1]) && p[b+1]!='0')){
                            
                            notation=1;
                            arraysize++;
                            break;
                        }
                        //If there is a minus sign with an e and a valid number after
                        else if(p[b+1]=='-' && (p[b]=='E' || p[b]=='e') && (isdigit(p[b+2]) && p[b+2]!='0')){
                           
                            notation=1;
                            negative=1;
                            arraysize++;
                            break;
                        }
                        else{
                            break;
                        }
                        
                        b++;
                    }
                    
                    //if it is in floating-point form (for example: 0.3e1)
                    if(notation==1 && (p[b]=='e' || p[b]=='E')){
                        
                        
                        b++;
                        
                        //c is now the index of the 1st valid number after e
                        int c=b;
                        
                        //increment past the negative
                        if (negative==1){
                            c++;
                        }
                        
                        
                        
                            //count the number of valid numbers after the first valid number
                            while (c<strlen(p)){
                                if (isdigit(p[a])){
                                    arraysize++;
                                }
                                else {
                                    break;
                                }
                                    c++;
                            }
                        
                        //Allocate memory accordingly
                        token = (char*)(malloc(4*arraysize));
                        
                        
                        int count;
                        
                        //delimit with 0s
                        
                        if(arraysize-1<(int)sizeof(token)){
                            count=(int)sizeof(token);
                            
                            count--;
                            while(count>=arraysize-1){
                                token[count]=0;
                                
                                count--;
                            }
                            
                        }
                        
                        //The minimum number of possible indexes
                        token[0]=p[a];
                        token[1]=p[a+1];
                        token[2]=p[a+2];
                        token[3]=p[a+3];
                        c=a+4;
                        
                        int index=4;
                        int hasE=0;
                        
                        if (token[2]=='e' ||token[2]=='E' || token[3]=='e' || token[3]=='E'){
                            hasE=1;
                        }
                        
                        //record other valid items to token
                        while (c<strlen(p)){
                            if (isdigit(p[c])){
                                token[index]=p[c];
                                index++;
                            }
                            //If a negative is found before the e, add it in
                            else if(hasE==0 && (p[c]=='e' || p[c]=='E')){
                                token[index]=p[c];
                                index++;
                                hasE=1;
                            }
                            else if (hasE==1 && p[c]=='-'){
                                token[index]=p[c];
                                index++;
                            }
                            else {
                                break;
                            }
                            c++;
                        }
                        currentIndex=c;
                        
                        //set as float
                        state='f';
                        return token;
                    }
                    else{
                        //Allocate memory accordingly
                        token = (char*)(malloc(4*arraysize));
                        
                        int count;
                        
                        //delimit with 0s
                        
                        if(arraysize<(int)sizeof(token)){
                            count=(int)sizeof(token);
                            
                            while(count>=arraysize-1){
                                token[count]=0;
                                
                                count--;
                            }

                        }
                        
                        
                    
                        //Set up token
                        b=a+3;
                        token[0]=p[a];
                        token[1]=p[a+1];
                        token[2]=p[a+2];
                        int index=3;
                        
                        
                        while (b<strlen(p)){
                            if (p[b]>='0' && p[b]<='9'){
                                token[index]=p[b];
                                
                                index++;
                                b++;
                            }
                            else{
                                break;
                            }
                        }
                        currentIndex=b;
                    
                        //set as float
                        state='f';
                        return token;
                    }
                    
                }
            }
            
            //if the number after the 0 is not a decimal point, octal num, or digit then 0 is the token
            else if(!isdigit(p[a+1])){
                
                token=(char*)(malloc(sizeof(char)));
                token[0]=p[a];
                a++;
                currentIndex=a;
                state='z';
                return token;
            }
            
            //If it is 0 and then an integer that is non-octal, then 0 is a token
            else if (p[a+1]=='8'||p[a+1]=='9'){
                token=(char*)(malloc(sizeof(int)));
                
                int count;
                //delimit with 0s
                if(1<sizeof(token)){
                    count=(int)sizeof(token);
                    
                    count--;
                    while(count>=1){
                        token[count]=0;
                        
                        count--;
                    }
                    
                }

                token[0]=p[a];
                a++;
                currentIndex=a;
                
                //set as 0
                state='z';
                return token;
            }
        }
        
        //Otherwise, if not 0, it is either a floating-point number or a decimal number (starting with 1-9)
        else if (p[a]>='1' && p[a]<='9'){
            
            
            int arraysize=1;
            int b=a+1;
            int isfloat=0;
            
            
            //if it is a possible floating point number in form beginning with a number, decimal point, and another number
            if (p[b]=='.' && (isdigit(p[b+1])) && !isdigit(p[b+2])){
                
                //set to first value after the decimal point
                int c=b+1;
                
                
                //If the decimal is a (0.0) type of float, and has an e after it, and a valid number after that then it is a float token
                if ((p[c+1]=='e' || p[c+1]=='E') && (isdigit(p[c+2]) || ((p[c+2]=='-') && isdigit(p[c+3]) ) ) ){
                    
                    //set to index of the first number after e
                    c+=2;
                    
                    int afterE=c;
                    int arraysize=5;
                    int minus=0;
                    
                    //add an additional index for the negative symbol
                    if ((p[c])=='-'){
                        arraysize=6;
                        
                        //increment to index of first number after "e-"
                        c++;
                        afterE=c;
                        minus=1;
                    }
                    
                    
                    while (c<strlen(p)){
                        if (isdigit(p[c])){
                            arraysize++;
                            c++;
                        }
                        else{
                            break;
                        }
                    }
                    
                    token =(char*)(malloc(sizeof(char)*arraysize));
                    
                    int count;
                    //delimit with 0s
                    if(1<sizeof(token)){
                        count=(int)sizeof(token);
                        
                        count--;
                        while(count>=arraysize-1){
                            token[count]=0;
                            
                            count--;
                        }
                    }
                    
                    token[0]=p[a];
                    token[1]=p[a+1];
                    token[2]=p[a+2];
                    token[3]=p[a+3];
                    token[4]=p[a+4];
                    int index=5;
                    
                    if (minus==0){
                        afterE++;
                    }
                    while (afterE<strlen(p)){
                        if (isdigit(p[afterE])){
                            token[index] = p[afterE];
                            index++;
                        }
                        else{
                            break;
                        }
                        afterE++;
                    }
                    
                    currentIndex=afterE;
                    state='f';
                    return token;
                    
                }
                
                
            }
            
            //check for the number if 0-9 digits after
            while (b<strlen(p)){
                
                if (p[b]>='0' && p[b]<='9'){
                    arraysize++;
                }
                
                //If a decimal point is found, break and evaluate
                else if (p[b]=='.'){
                    isfloat=1;
                    
                    break;
                }
                
                else{
                    break;
                }
                b++;
            }
            
            //If a decimal point was encountered, making it a possible floating-point token
            if (isfloat==1){
                
                
                //if the decimal is the last char in the string or the value after the decimal is not a number
                //then the number(s) before it is/are a decimal token
                if (b+1==strlen(p)){
                    
                    token=(char*)(malloc(4*arraysize));
                    
                    int count;
                    
                    //delimit with 0s
                    if(arraysize<sizeof(token)){
                        count=(int)sizeof(token);
                        
                        count--;
                        while(count>=arraysize-1){
                            token[count]=0;
                            
                            count--;
                        }
                        
                    }
                    
                    currentIndex=b;
                    
                    //c holds the index of the first valid number
                    int c=a;
                    
                    int index=0;
                    
                    //Save the valid numbers up to the decimal point
                    while (c<b) {
                        token[index]=p[c];
                        index++;
                        c++;
                    }
                    currentIndex=c;
                    
                    //set as a decimal number
                    state='d';
                    return token;
                }
                
                //if it has a character after the decimal that is a number, then this is a float. Add all proper numbers into the token and return them
                else if(isdigit(p[b+1])){
                    
                    int index=0;
                    
                    //set d to the index of decimal point
                    int d=b;
                    
                    //set to the index of the first valid number (1-9)
                    int c=a;
                    
                    //set b to the index of the first number after the decimal point
                    b++;
                    
                    //see how many valid items after the decimal point
                    while (b<strlen(p) && isdigit(p[b])){
                        arraysize++;
                        b++;
                    }
                    
                    //allocate memory accordingly
                    token=(char*)(malloc(4*arraysize));
                    
                    int count;
                    //delimit with 0s
                    if(arraysize<sizeof(token)){
                        count=(int)sizeof(token);
                        count--;
                        while(count>=arraysize-1){
                            token[count]=0;
                            
                            count--;
                        }
                    }

                    
                    
                    //now save the numbers before the decimal point
                    while (c<d){
                        token[index]=p[c];
                        c++;
                        index++;
                    }
                    
                    //when the decimal point is reached, save it into the token
                    token[index]=p[d];
                    index++;
                    c=d+1;
                    
                    //Now save the numbers after the decimal point
                    while(c<strlen(p) && isdigit(p[c])){
                        token[index]=p[c];
                        index++;
                        c++;
                    }
                    
                    currentIndex=c;
                    
                    //set as
                    state='f';
                    return token;
                }
                
                //The character after the decimal is a non-number, so we only save the current decimal token and leave the pointer at the decimal
                else{
                    
                    //allocate memory
                    token=(char*)(malloc(4*arraysize));
                    
                    int count;
                    
                    //delimit with 0s
                    if(arraysize<sizeof(token)){
                        count=(int)sizeof(token);
                        
                        count--;
                        while(count>=arraysize){
                            token[count]=0;
                            
                            count--;
                        }
                        
                    }
                    
                    int c=a;
                    int index=0;
                    
                    while (c<b){
                        token[index]=p[c];
                        c++;
                        index++;
                    }
                    
                    currentIndex=b;
                    state='d';
                    return token;
                    
                }
                
            }
            
            //otherwise we have a decimal number with no decimal point after it
            else{
                
                int index=0;
                
                //allocate memory for the decimal numbers
                token=(malloc(sizeof(char)*arraysize));
                int count=0;
                
                //delimit with 0s
                if(arraysize<sizeof(token)){
                    count=(int)sizeof(token);
                    count--;
                    while(count>=arraysize-1){
                        token[count]=0;
                        count--;
                    }
                    
                }
                

                //c is the index of the first valid number
                int c=a;
                
                //save the decimal numbers before the decimal point
                
                while (isdigit(p[c]) && c<strlen(p)){
                    
                    token[index]=p[c];
                    c++;
                    index++;
                }
                state='d';
                currentIndex=c;
                return token;
            }
        }
    }
    
    return NULL;
}


/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 *
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

TokenizerT *TKCreate( char * ts ) {
    
    
    
    
    if (ts!=NULL){
        
        //Create the token
        TokenizerT *t=malloc(sizeof(struct TokenizerT_));
    
        //Copy and allocate memory to hold the array with the token inside of it
        t->tokenChars=strdup(ts);
        
        
        return t;
        
    }
    
    return NULL;
}

/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
    
    free(tk->tokenChars);
    free(tk);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {
    if (tk==NULL){
        return NULL;
    }
    if (currentIndex<=strlen(input)){
        char *t;
        
        //space is dynamically allocated in sortForToken
        t=sortForToken(input);
        return t;
    }
    
    return NULL;
}


/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */


int main(int argc, char **argv) {
    
    
    if (argc<=1)
    {
        printf("No input\n");
    }
    
    //doesn't use the input argv[1] unless it is not null, avoids running into segmentation fault
    if (argc>1){
        
        //Set main index of array to 0;
        currentIndex=0;
        
        input=argv[1];
        
        //int a;
    
        //for (a=0;a<strlen(input);a++){
        //    printf("%c\n",input[a]);            //prints out the entered input, letter by letter in the char array
        //}
        
        TokenizerT *t;
        char *tokenArr;
        
        tokenArr=sortForToken(input);
        if (tokenArr!=NULL){
            t=TKCreate(tokenArr);
            
            if (tokenArr!=NULL){
                
                t=TKCreate(tokenArr);
                
                if (state=='h'){
                    printf("hex: ");
                }
                else if (state=='o'){
                    printf("octal: ");
                }
                else if (state=='z'){
                    printf("zero: ");
                }
                else if (state=='d'){
                    printf("decimal: ");
                }
                else if (state=='f'){
                    printf("float: ");
                }
                
                printf("%s\n",t->tokenChars);
                
            }
            TKDestroy(t);
            while(currentIndex<strlen(input)&& tokenArr!=NULL){
                
                tokenArr=TKGetNextToken(t);
                if (tokenArr!=NULL){
                    t=TKCreate(tokenArr);

                    if (state=='h'){
                        printf("hex: ");
                    }
                    else if (state=='o'){
                        printf("octal: ");
                    }
                    else if (state=='z'){
                        printf("zero: ");
                    }
                    else if (state=='d'){
                        printf("decimal: ");
                    }
                    else if (state=='f'){
                        printf("float: ");
                    }
                
                
                    printf("%s\n",t->tokenChars);
                    TKDestroy(t);
                }
                
            }
        
            
        }
        

        
    }
    return 0;
}

