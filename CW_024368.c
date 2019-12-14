#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100
/** Infix Postfix Prefix conversion and evaluation
Input by the user is once output of keyboard input saved in output.txt
Input read from file output and evaluation saved in same file

    NAME:   TARIQ ABOELYAZID
    ID:     024368
**/
    //declare structure stack operations
    struct stackNode{
        char opn[SIZE];
        float num;
        struct stackNode *nextOpPtr;
    };
    typedef struct stackNode StackNode;
    typedef StackNode *StackNodePtr;
    //declare functions
    void pushStack(StackNodePtr *sPtr,char *x);
    void pushNumStack(StackNodePtr *sPtr,float x);
    void printStack(StackNodePtr currentPtr);
    void menuKeyboard(char *x);
    void menuFile(char *x, char *outname);
    void saveFileoutputCon(char *x,int Exp,char *outname);
    void savekeyboardoutputCon(char *x,int Exp);
    void savekeyboardinput(char *x);
    void savekeyboardoutput(float ev);
    void saveFileoutputEx(float ev,char *outname);
    void clroutputCon();
    void IntiateToPostfixStack(StackNodePtr *sPtr);
    void IntiateToPrefixStack(StackNodePtr *sPtr);

    char* readFromFolder(char *outname);
    char* infixToPost(StackNodePtr *sPtr, char *infix);
    char* infixToPrefix(StackNodePtr *sPtr, char *infix);
    char* postfixToInfix(StackNodePtr *sPtr, char *postfix);
    char* postfixToprefix(StackNodePtr *sPtr, char *postfix);
    char* prefixToInfix(StackNodePtr *sPtr, char *prefix);
    char* prefixToPostfix(StackNodePtr *sPtr, char *prefix);
    char* popStack(StackNodePtr *topPtr);

    float popNumStack(StackNodePtr *topPtr);
    float Evaluate(StackNodePtr *sPtr, char *postfix);
    int ExpType(char *expression);
    int numStrStack(StackNodePtr currentPtr);
    int isInt(char *arr);
    int isOp(char *string);
    int isEmpty(StackNodePtr topPtr);
    int normEx(char *string);
    int imbal(char *string);
int main()
{
        char *key = malloc(10000 * sizeof(char));
        char *x = malloc(10000 * sizeof(char));
        char *outname = malloc(100000 * sizeof(char));

    while(strcmp(key, "C")!=0){
        printf("A.Read Expression from specific file[Type location eg. C:\\Your file_name.txt]\n");
        printf("B.Default Input[Keyboard]\n");
        printf("C.EXIT\n");
        printf("Select input form:\n");
        gets(key);
        if(strcmp(key, "A")==0)
        {
          printf("Write File location as [Type location eg. C:\\Your file_name.txt]\n");
          gets(outname);
          x = readFromFolder(outname);
          printf("%s\n",x);
          if (normEx(x)==1){
                if(imbal(x)==1){
                        if(ExpType(x)>0){
                                menuFile(x,outname);
                        }else if(ExpType(x)== 0){
                            printf("This expression is not infix, postfix, prefix\n");
                        }
                }else if(imbal(x) ==0){
                    printf("%s unbalanced parenthesis\n",x);
                }
          }else if(normEx(x)==0){
            printf("%s is not expression or can not evaluate\n",x);
          }
        }else if( strcmp(key, "B")==0){
            printf("Your expression use spaces between operators and operands:\n");
            gets(x);
            if (normEx(x)==1){
                if(imbal(x)==1){
                        if(ExpType(x)>0){
                                savekeyboardinput(x);
                                clroutputCon();
                                menuKeyboard(x);
                        }else if(ExpType(x)== 0){
                            printf("This expression is not infix, postfix, prefix\n");
                        }
                }else if(imbal(x) ==0){
                    printf("%s unbalanced parenthesis\n",x);
                }

            }else if(normEx(x)==0){
                printf("%s is not expression can not evaluate\n",x);
            }
        }else if (strcmp(key, "C")==0){
                printf("GoodBye\n");
                exit(0);
        }
    }
    return 0;
}
//menu void function
void menuKeyboard(char *x){
    int menChoice,choice,exp;
    float Ev;
    StackNodePtr strtPtr = NULL;
    char* result = malloc(1000000 * sizeof(char));
     while(menChoice != 3){
        printf("1.Convert\n2.Evaluate\n3.Exit\n");
        printf("Your menu choice\n");
        scanf("%d",&menChoice);
        switch(menChoice){
            //convert menu is returned
            case 1:
                exp = ExpType( x );
                switch (exp){
                        //case expression type Infix
                        case 1:
                            printf("Infix Expression = %s\n",x);
                            printf("1.Convert infix to postfix\n2.Convert infix to prefix\n3.Both\n");
                            printf("Your choice:\n");
                            scanf("%d",&choice);
                            if(choice == 1){
                                result = infixToPost(&strtPtr, x);
                                savekeyboardoutputCon(result,3);
                                printf("Postfix Expression = ");
                                printf("%s\n", result );
                            }else if(choice == 2){
                                result=infixToPrefix(&strtPtr, x);
                                savekeyboardoutputCon(result,2);
                                printf("Prefix Expression = ");
                                printf("%s\n",result);
                            }else if(choice == 3){
                                result = infixToPost(&strtPtr, x);
                                savekeyboardoutputCon(result,3);
                                printf("Postfix Expression = ");
                                printf("%s\n",result);
                                result = infixToPrefix(&strtPtr, x);
                                savekeyboardoutputCon(result,2);
                                printf("Prefix Expression = ");
                                printf("%s\n",result);
                            }
                        break;
                        //case expression type Prefix
                        case 2:
                            printf("Prefix Expression = %s\n",x);
                            printf("1.Convert Prefix to Infix\n2.Convert Prefix to Postfix\n3.Both\n");
                            printf("Your choice:\n");
                            scanf("%d",&choice);
                            if(choice == 1){
                                result = prefixToInfix(&strtPtr, x);
                                savekeyboardoutputCon(result,1);
                                printf("Infix Expression = ");
                                printf("%s\n", result);
                            }else if(choice == 2){
                                result =prefixToPostfix(&strtPtr, x);
                                savekeyboardoutputCon(result,3);
                                printf("Postfix Expression = ");
                                printf("%s\n",result);
                            }else if(choice == 3){
                                result = prefixToInfix(&strtPtr, x);
                                savekeyboardoutputCon(result,1);
                                printf("Infix Expression = ");
                                printf("%s\n", result);
                                result =prefixToPostfix(&strtPtr, x);
                                savekeyboardoutputCon(result,3);
                                printf("Postfix Expression = ");
                                printf("%s\n",result);
                            }
                        break;
                        //case expression type Postfix
                        case 3:
                            printf("Postfix Expression = %s\n",x);
                            printf("1.Convert Postfix to Infix\n2.Convert Postfix to Prefix\n3.Both\n");
                            printf("Your choice:\n");
                            scanf("%d",&choice);
                            if(choice == 1){
                                result =postfixToInfix(&strtPtr, x);
                                savekeyboardoutputCon(result,1);
                                printf("Infix Expression = ");
                                printf("%s\n",result);
                            }else if(choice == 2){
                                result = postfixToprefix(&strtPtr, x);
                                savekeyboardoutputCon(result,2);
                                printf("Prefix Expression = ");
                                printf("%s\n",result);
                            }else if(choice == 3){
                                result = postfixToInfix(&strtPtr, x);
                                savekeyboardoutputCon(result,1);
                                printf("Infix Expression = ");
                                printf("%s\n",result);
                                result = postfixToprefix(&strtPtr, x);
                                savekeyboardoutputCon(result,2);
                                printf("Prefix Expression = ");
                                printf("%s\n",result);
                            }
                        break;
                    }
                break;
                /*Evaluates Expression*/
                case 2:
                    switch(ExpType(x)){
                        /*If expression Infix
                        expression converted to postfix then evaluated*/
                    case 1:
                        Ev = Evaluate(&strtPtr, infixToPost(&strtPtr, x));
                        printf("%s = %.2f\n",x, Ev );
                        break;
                        /*If expression prefix
                        expression converted to postfix then evaluated*/
                    case 2:
                        Ev = Evaluate(&strtPtr, prefixToPostfix(&strtPtr, x) );
                        printf("%s = %.2f\n",x, Ev );
                        break;
                        /*If expression postfix
                        expression then evaluated*/
                    case 3:
                        Ev = Evaluate(&strtPtr, x);
                        printf("%s = %.2f\n",x, Ev);
                        break;
                    }
                    savekeyboardoutput(Ev);
                    break;
                    /*If user selects 3 Exit menu closes*/
                case 3:
                    exit(0);
                    break;
        }
        }//end of while
     }//end of menu function
/*Menu for file*/
void menuFile(char *x, char *outname)
{
    int menChoice,choice,exp;
    float Ev;
    StackNodePtr strtPtr = NULL;
    char* result = malloc(1000000 * sizeof(char));
     while(menChoice != 3){
        printf("1.Convert\n2.Evaluate\n3.Exit\n");
        printf("Your menu choice\n");
        scanf("%d",&menChoice);
        switch(menChoice){
            //convert menu is returned
            case 1:
                exp = ExpType( x );
                switch (exp){
                        //case expression type Infix
                        case 1:
                            printf("Infix Expression = %s\n",x);
                            printf("1.Convert infix to postfix\n2.Convert infix to prefix\n3.Both\n");
                            printf("Your choice:\n");
                            scanf("%d",&choice);
                            if(choice == 1){
                                result = infixToPost(&strtPtr, x);
                                saveFileoutputCon(result,3,outname);
                                printf("Postfix Expression = ");
                                printf("%s\n", result );
                            }else if(choice == 2){
                                result=infixToPrefix(&strtPtr, x);
                                saveFileoutputCon(result,2,outname);
                                printf("Prefix Expression = ");
                                printf("%s\n",result);
                            }else if(choice == 3){
                                result = infixToPost(&strtPtr, x);
                                saveFileoutputCon(result,3,outname);
                                printf("Postfix Expression = ");
                                printf("%s\n",result);
                                result = infixToPrefix(&strtPtr, x);
                                saveFileoutputCon(result,2,outname);
                                printf("Prefix Expression = ");
                                printf("%s\n",result);
                            }
                        break;
                        //case expression type Prefix
                        case 2:
                            printf("Prefix Expression = %s\n",x);
                            printf("1.Convert Prefix to Infix\n2.Convert Prefix to Postfix\n3.Both\n");
                            printf("Your choice:\n");
                            scanf("%d",&choice);
                            if(choice == 1){
                                result = prefixToInfix(&strtPtr, x);
                                saveFileoutputCon(result,1,outname);
                                printf("Infix Expression = ");
                                printf("%s\n", result);
                            }else if(choice == 2){
                                result =prefixToPostfix(&strtPtr, x);
                                saveFileoutputCon(result,3,outname);
                                printf("Postfix Expression = ");
                                printf("%s\n",result);
                            }else if(choice == 3){
                                result = prefixToInfix(&strtPtr, x);
                                saveFileoutputCon(result,1,outname);
                                printf("Infix Expression = ");
                                printf("%s\n", result);
                                result =prefixToPostfix(&strtPtr, x);
                                saveFileoutputCon(result,3,outname);
                                printf("Postfix Expression = ");
                                printf("%s\n",result);
                            }
                        break;
                        //case expression type Postfix
                        case 3:
                            printf("Postfix Expression = %s\n",x);
                            printf("1.Convert Postfix to Infix\n2.Convert Postfix to Prefix\n3.Both\n");
                            printf("Your choice:\n");
                            scanf("%d",&choice);
                            if(choice == 1){
                                result =postfixToInfix(&strtPtr, x);
                                saveFileoutputCon(result,1,outname);
                                printf("Infix Expression = ");
                                printf("%s\n",result);
                            }else if(choice == 2){
                                result = postfixToprefix(&strtPtr, x);
                                saveFileoutputCon(result,2,outname);
                                printf("Prefix Expression = ");
                                printf("%s\n",result);
                            }else if(choice == 3){
                                result = postfixToInfix(&strtPtr, x);
                                saveFileoutputCon(result,1,outname);
                                printf("Infix Expression = ");
                                printf("%s\n",result);
                                result = postfixToprefix(&strtPtr, x);
                                saveFileoutputCon(result,2,outname);
                                printf("Prefix Expression = ");
                                printf("%s\n",result);
                            }
                        break;
                    }
                break;
                /*Evaluates Expression*/
                case 2:
                    switch(ExpType(x)){
                        /*If expression Infix
                        expression converted to postfix then evaluated*/
                    case 1:
                        Ev = Evaluate(&strtPtr, infixToPost(&strtPtr, x));
                        printf("%s = %.2f\n",x, Ev );
                        break;
                        /*If expression prefix
                        expression converted to postfix then evaluated*/
                    case 2:
                        Ev = Evaluate(&strtPtr, prefixToPostfix(&strtPtr, x) );
                        printf("%s = %.2f\n",x, Ev );
                        break;
                        /*If expression postfix
                        expression then evaluated*/
                    case 3:
                        Ev = Evaluate(&strtPtr, x);
                        printf("%s = %.2f\n",x, Ev);
                        break;
                    }
                    saveFileoutputEx(Ev,outname);
                    break;
                    /*If user selects 3 Exit menu closes*/
                case 3:
                    exit(0);
                    break;
        }
        }//end of while
     }//end of menu function
//push string on top of stack
void pushStack(StackNodePtr *sPtr,char *x){
    StackNodePtr newPtr;
    newPtr = malloc(sizeof(StackNode));
    if(newPtr != NULL){
        strcpy(newPtr->opn , x);
        newPtr->nextOpPtr = *sPtr;
        *sPtr = newPtr;
    }
}
/*Save expression typed by user using keyboard to input.txt*/
void savekeyboardinput(char *x)
{
        FILE *outfile;
        char *outname = malloc(100000 * sizeof(char));
        outname = "input.txt";
        outfile = fopen(outname, "w");
        if (!outfile) {
            printf("Can't open file <%s> for reading.\n", outname);
        }
        fprintf(outfile, x , outname);
        fclose(outfile);
}
/*clear output file*/
void clroutputCon()
{
        FILE *outfile;
        char *outname = malloc(100000 * sizeof(char));
        outname = "output.txt";
        outfile = fopen(outname, "w");
        if (!outfile) {
            printf("Can't open file <%s> for reading.\n", outname);
        }
        fclose(outfile);
}
/*save file output conversions*/
void saveFileoutputCon(char *x,int Exp,char *outname)
{
        FILE *outfile;
        outfile = fopen(outname, "a");
        if (!outfile) {
            printf("Can't open file <%s> for reading.\n", outname);
        }
        if(Exp == 1){
           fprintf(outfile, "\nInfix\n %s\n", x );
        }
        if(Exp == 2){
           fprintf(outfile, "\nPrefix\n %s\n", x );
        }
        if(Exp == 3){
           fprintf(outfile, "\nPostfix\n %s\n", x );
        }
        fclose(outfile);
}
/*Save keyboard output Conversion*/
void savekeyboardoutputCon(char *x,int Exp)
{
        FILE *outfile;
        char *outname = malloc(100000 * sizeof(char));
        outname = "output.txt";
        outfile = fopen(outname, "a");
        if (!outfile) {
            printf("Can't open file <%s> for reading.\n", outname);
        }
        if(Exp == 1){
           fprintf(outfile, "Infix\n %s\n", x );
        }
        if(Exp == 2){
           fprintf(outfile, "Prefix\n %s\n", x );
        }
        if(Exp == 3){
           fprintf(outfile, "Postfix\n %s\n", x );
        }
        fclose(outfile);
}
/*save keyboard output evaluation*/
void savekeyboardoutput(float ev)
{
        FILE *outfile;
        char *outname = malloc(100000 * sizeof(char));
        outname = "output.txt";
        outfile = fopen(outname, "a");
        if (!outfile) {
            printf("Can't open file <%s> for reading.\n", outname);
        }
           fprintf(outfile, "Evaluation\n%.2f\n ", ev );
        fclose(outfile);
}
/*Save File evaluation expression*/
void saveFileoutputEx(float ev,char *outname)
{
        FILE *outfile;
        outfile = fopen(outname, "a");
        if (!outfile) {
            printf("Can't open file <%s> for reading.\n", outname);
        }
           fprintf(outfile, "Evaluation\n%.2f\n ", ev );
        fclose(outfile);
}
/*Reads from file the first line only and
returns expression in buff*/
char* readFromFolder(char *outname)
{
        FILE *outfile;
        char* buff = malloc(100000 * sizeof(char));
        outfile = fopen(outname, "r");
        if (!outfile) {
            printf("Can't open file <%s> for reading.\n", outname);
        }
        fgets(buff, 255, outfile);
        fclose(outfile);
        return buff;
}
//push integer on top of stack
void pushNumStack(StackNodePtr *sPtr,float x){
    StackNodePtr newPtr;
    newPtr = malloc(sizeof(StackNode));
    if(newPtr != NULL){
        newPtr->num = x;
        newPtr->nextOpPtr = *sPtr;
        *sPtr = newPtr;
    }
}
//print all values in stack
void printStack(StackNodePtr currentPtr){
    if(currentPtr == NULL){
        printf("The Stack is empty\n");
    }else{
        printf("The Stack is: \n");
        while(currentPtr != NULL){
            printf("%s -> ",currentPtr->opn);
            (currentPtr) = (currentPtr)->nextOpPtr;
        }
    printf("NULL\n");
    }
}
//pop the top string in the stack
char* popStack(StackNodePtr *topPtr){
    StackNodePtr tempPtr;
    char* popStr =  malloc(100000 * sizeof(char));
    tempPtr = *topPtr;
    strcpy(popStr,(*topPtr)->opn); ;
    *topPtr = (*topPtr)->nextOpPtr;
    free(tempPtr);
    return popStr;
}
/*pops the top integer in the stack*/
float popNumStack(StackNodePtr *topPtr){
    StackNodePtr tempPtr;
   float popnum;
    tempPtr = *topPtr;
    popnum =(*topPtr)->num;
    *topPtr = (*topPtr)->nextOpPtr;
    free(tempPtr);
    return popnum;
}
//number of string in array
int numStrStack(StackNodePtr currentPtr){
    int count = 0;
        while(currentPtr != NULL){
            count++;
            (currentPtr) = (currentPtr)->nextOpPtr;
    }
return count;
}
//initiate stack to convert postfix
void IntiateToPostfixStack(StackNodePtr *sPtr)
{
    StackNodePtr newPtr;
    newPtr = malloc(sizeof(StackNode));
    if(newPtr != NULL){
        strcpy(newPtr->opn , "(");
        newPtr->nextOpPtr = *sPtr;
        *sPtr = newPtr;
    }
}
//initiate stack to convert prefix
void IntiateToPrefixStack(StackNodePtr *sPtr)
{
    StackNodePtr newPtr;
    newPtr = malloc(sizeof(StackNode));
    if(newPtr != NULL){
        strcpy(newPtr->opn , ")");
        newPtr->nextOpPtr = *sPtr;
        *sPtr = newPtr;
    }
}
//Check if string is number return 1 if string is number
int isInt(char *string)
{
int i;
   for(i = 0; i < strlen( string ); i ++)
   {
      //ASCII value of 0 = 48, 9 = 57. So if value is outside of numeric range then fail
      //Checking for negative sign "-" could be added: ASCII value 45.
      if ((string[i] < 48 || string[i] > 57) && string[i] != 45)
         return 0;
   }
            if(atoi(string)>99 || atoi(string)<-99){
                    return 0;
                }
   return 1;

}
//check if selected string is operator or not
int isOp(char *string)
{

    if(strcmp(string , "+" )== 0 || strcmp(string , "-" )== 0||
        strcmp(string  , "*" )== 0 || strcmp(string , "/" )== 0 ||
        strcmp(string  , "^" )== 0 || strcmp(string  , "(" )== 0 ||
        strcmp(string  , ")" )== 0 || isInt(string) == 1){
            return 1;
        }
return 0;
}
//convert infix to postfix
char* infixToPost(StackNodePtr *sPtr, char *infix)
{
        char* tempinfix = malloc(100000 * sizeof(char));
        char* postfix = malloc(100000 * sizeof(char));
        IntiateToPostfixStack(sPtr);
        strcpy(tempinfix, infix);
        strcat(tempinfix, " )");
        strcpy(postfix,"");
        char *array[strlen(tempinfix) + 1];
        int i=0,j;
        array[i] = strtok(tempinfix," ");
        while(array[i]!=NULL)
        {
           array[++i] = strtok(NULL," ");
        }
        for(j=0; j<i; j++)
        {
            if(isOp(array[j])==0 && isInt(array[j])==0)
                {
                    return "Error cannot convert or evaluate\n";
                }
            if(isOp(array[j])==1 && isInt(array[j])==0){
                    if(strcmp((*sPtr)->opn , "(")==0)
                    {
                        if(strcmp(array[j] , "+" )== 0 || strcmp(array[j] , "-" )== 0||
                           strcmp(array[j] , "*" )== 0 || strcmp(array[j] , "/" )== 0 ||
                           strcmp(array[j] , "^" )== 0 || strcmp(array[j] , "(" )== 0)
                           {
                                pushStack(sPtr,array[j]);
                           }
                    }else if(strcmp((*sPtr)->opn , "+" )==0|| strcmp((*sPtr)->opn ,"-")==0)
                    {
                        if(strcmp(array[j] , "+" )==0 || strcmp(array[j] , "-" )==0 ||
                           strcmp(array[j] , "*" )==0 || strcmp(array[j] , "/" )==0 ||
                           strcmp(array[j] , "^" )==0 || strcmp(array[j] , "(" )==0)
                           {
                                pushStack(sPtr,array[j]);
                           }
                    }else if(strcmp((*sPtr)->opn , "*")== 0|| strcmp((*sPtr)->opn , "/") ==0||
                             strcmp((*sPtr)->opn , "^")== 0)
                    {
                        if(strcmp(array[j] , "*" )== 0 || strcmp(array[j] , "/" )==0||
                           strcmp(array[j] , "^" )== 0 )
                           {
                                strcat(postfix,popStack(sPtr));
                                strcat(postfix ," ");
                                pushStack(sPtr,array[j]);
                           }
                            else if(strcmp(array[j] , "+" )== 0 || strcmp(array[j] , "-" )== 0){
                                strcat(postfix,popStack(sPtr));
                                strcat(postfix ," ");
                                pushStack(sPtr,array[j]);
                            }else if(strcmp(array[j] , "(" )==0){
                                pushStack(sPtr,array[j]);
                            }
                    }
                }
            if(strcmp(array[j] , ")" ) == 0)
            {
                while(strcmp((*sPtr)->opn , "(" ) != 0){
                        strcat(postfix,popStack(sPtr));
                        strcat(postfix ," ");
                      }
                if(strcmp((*sPtr)->opn , "(" ) == 0 )
                      {
                          popStack(sPtr);
                      }
            }if(isInt(array[j])== 1 ){
                strcat(postfix, array[j]);
                strcat(postfix ," ");
            }
        }
return postfix;
}
//Convert infix to prefix
char* infixToPrefix(StackNodePtr *sPtr, char *infix)
{
        char* tempinfix = malloc(100000 * sizeof(char));
        strcpy(tempinfix,infix);
        strrev(tempinfix);
        strcat(tempinfix, " (");
        IntiateToPrefixStack(sPtr);
        char* prefix = malloc(100000 * sizeof(char));
        strcpy(prefix," ");
        char *array[strlen(tempinfix) + 1];
        int i=0,j;
        array[i] = strtok(tempinfix," ");
        while(array[i]!=NULL)
        {
           array[++i] = strtok(NULL," ");
        }
        for(j=0; j<i; j++)
        {
            if(isOp(array[j])==0 && isInt(array[j])== 0)
                {
                    return "Error cannot convert or evaluate\n";
                }
            if(isOp(array[j])==1 && isInt(array[j])== 0){
                if(strcmp((*sPtr)->opn , ")")==0){
                    if(strcmp(array[j] , "+" )== 0 || strcmp(array[j] , "-" )== 0||
                       strcmp(array[j] , "*" )== 0 || strcmp(array[j] , "/" )== 0 ||
                       strcmp(array[j] , "^" )== 0 || strcmp(array[j] , ")" )== 0)
                       {
                            pushStack(sPtr,array[j]);
                       }
                }else if(strcmp((*sPtr)->opn , "+" )==0|| strcmp((*sPtr)->opn ,"-")==0){
                    if(strcmp(array[j] , "+" )==0 || strcmp(array[j] , "-" )==0 ||
                       strcmp(array[j] , "*" )==0 || strcmp(array[j] , "/" )==0 ||
                       strcmp(array[j] , "^" )==0 || strcmp(array[j] , ")" )==0)
                       {
                            pushStack(sPtr,array[j]);
                       }
                }else if(strcmp((*sPtr)->opn , "*")== 0|| strcmp((*sPtr)->opn , "/") ==0||
                         strcmp((*sPtr)->opn , "^")== 0)
                {
                if(strcmp(array[j] , "*" )== 0 || strcmp(array[j] , "/" )==0||
                   strcmp(array[j] , "^" )== 0 )
                   {
                        pushStack(sPtr,array[j]);
                   }
                    else if(strcmp(array[j] , "+" )== 0 || strcmp(array[j] , "-" )== 0){
                        strcat(prefix,popStack(sPtr));
                        strcat(prefix ," ");
                        pushStack(sPtr,array[j]);
                    }else if( strcmp(array[j] , ")" )==0){
                        pushStack(sPtr,array[j]);
                    }
            }
            }if(strcmp(array[j] , "(" ) == 0)
            {
                while(strcmp((*sPtr)->opn , ")" ) != 0){
                        strcat(prefix ," ");
                        strcat(prefix,popStack(sPtr));
                      }
                if(strcmp((*sPtr)->opn , ")" ) == 0 )
                      {
                          popStack(sPtr);
                      }
            }else
            if(isInt( strrev(array[j]) )== 1){
                strcat(prefix ," ");
                strcat(prefix, strrev(array[j]));
            }
        }
return strrev(prefix);
}
// convert postfix to infix
char* postfixToInfix(StackNodePtr *sPtr, char *postfix)
{
    char opr_temp[SIZE];
    char ope_temp[SIZE];
    char opr2[SIZE];
    char opr1[SIZE];
    char* infix = malloc(100000 * sizeof(char));
    char* temppostfix = malloc(100000 * sizeof(char));
    strcpy(temppostfix,postfix);
    char *array[strlen(temppostfix) + 1];
        int i=0,j;
        array[i] = strtok(temppostfix," ");
        while(array[i]!=NULL)
        {
           array[++i] = strtok(NULL," ");
        }
        for(j=0; j<i; j++)
        {
                strcpy(opr_temp,"");
                strcpy(infix,"");
                strcpy(opr2,"");
                strcpy(opr1,"");
                strcpy(ope_temp,"");
                    if(isOp(array[j])==0 && isInt(array[j])== 0){
                        return "Error cannot convert or evaluate\n";
                    }else if(strcmp(array[j] , "+" )==0 || strcmp(array[j] , "-" )==0 ||
                             strcmp(array[j] , "*" )==0 || strcmp(array[j] , "/" )==0 ||
                             strcmp(array[j] , "^" )==0 )
                    {
                    if(numStrStack(*sPtr)<2){
                        return "Invalid Input to many operators\n";

                }else if(numStrStack(*sPtr)>1){
                        strcpy(opr2,popStack(sPtr));
                        strcpy(ope_temp,array[j]);
                        strcpy(opr1,popStack(sPtr));
                        strcat(infix,"(");
                        strcat(infix," ");
                        strcat(infix,opr1);
                        strcat(infix," ");
                        strcat(infix,ope_temp);
                        strcat(infix," ");
                        strcat(infix,opr2);
                        strcat(infix," ");
                        strcat(infix,")");
                        pushStack(sPtr,infix);
            }
        }else if(isInt(array[j])){
                pushStack(sPtr, array[j]);
            }
    }
        strcpy(infix,popStack(sPtr));
        if ((*sPtr)== NULL ){
            return infix;
        }else if((*sPtr) != NULL ){
            return "The user input has too many value\n";
        }
}
//convert postfix to prefix
char* postfixToprefix(StackNodePtr *sPtr, char *postfix)
{
    char opr_temp[SIZE];
    char ope_temp[SIZE];
    char opr2[SIZE];
    char opr1[SIZE];
    char* prefix = malloc(100000 * sizeof(char));
    char* temppostfix = malloc(100000 * sizeof(char));
    strcpy(temppostfix,postfix);
    char *array[strlen(temppostfix) + 1];
        int i=0,j;
        array[i] = strtok(temppostfix," ");
        while(array[i]!=NULL)
        {
           array[++i] = strtok(NULL," ");
        }
        for(j=0; j<i; j++)
        {
                strcpy(opr_temp,"");
                strcpy(prefix,"");
                strcpy(opr2,"");
                strcpy(opr1,"");
                strcpy(ope_temp,"");
                    if(isOp(array[j])==0 && isInt(array[j])== 0){
                        return "Error can not convert or evaluate\n";
                    }else if(strcmp(array[j] , "+" )==0 || strcmp(array[j] , "-" )==0 ||
                             strcmp(array[j] , "*" )==0 || strcmp(array[j] , "/" )==0 ||
                             strcmp(array[j] , "^" )==0 )
                    {
                    strcpy(opr2,popStack(sPtr));
                    strcpy(ope_temp,array[j]);
                    strcpy(opr1,popStack(sPtr));
                    strcat(prefix,ope_temp);
                    strcat(prefix," ");
                    strcat(prefix,opr1);
                    strcat(prefix," ");
                    strcat(prefix,opr2);
                    strcat(prefix," ");
                    pushStack(sPtr,prefix);
					}else if(isInt(array[j])){
                        pushStack(sPtr, array[j]);
                    }
        }
return prefix;
}
//convert to infix
char* prefixToInfix(StackNodePtr *sPtr, char *prefix)
{
    char opr_temp[SIZE];
    char ope_temp[SIZE];
    char opr2[SIZE];
    char opr1[SIZE];
    char* infix = malloc(100000 * sizeof(char));
    char* tempprefix = malloc(100000 * sizeof(char));
    strcpy(tempprefix,prefix);
    strrev(tempprefix);
    char *array[strlen(tempprefix) + 1];
        int i=0,j;
        array[i] = strtok(tempprefix," ");
        while(array[i]!=NULL)
        {
           array[++i] = strtok(NULL," ");
        }
        for(j=0; j<i; j++)
        {
                strcpy(opr_temp,"");
                strcpy(infix,"");
                strcpy(opr2,"");
                strcpy(opr1,"");
                strcpy(ope_temp,"");
                    if(isOp(array[j])==0 && isInt(array[j])== 0){
                        return "Error cannot evaluate or convert\n";
                    }else if(strcmp(array[j] , "+" )==0 || strcmp(array[j] , "-" )==0 ||
                             strcmp(array[j] , "*" )==0 || strcmp(array[j] , "/" )==0 ||
                             strcmp(array[j] , "^" )==0)
                    {
                   if(numStrStack(*sPtr)<2){
                        return "Invalid Input to many operators\n";
                    }else if(numStrStack(*sPtr)>1){
                        strcpy(opr2,popStack(sPtr));
                        strcpy(ope_temp,array[j]);
                        strcpy(opr1,popStack(sPtr));
                        strcat(infix,")");
                        strcat(infix," ");
                        strcat(infix,opr1);
                        strcat(infix," ");
                        strcat(infix,ope_temp);
                        strcat(infix," ");
                        strcat(infix,opr2);
                        strcat(infix," ");
                        strcat(infix,"(");
                        pushStack(sPtr,infix);
                    }
                }else if(isInt(array[j])){
                        pushStack(sPtr, array[j]);
                    }
    }
        strcpy(infix,popStack(sPtr));
        if ((*sPtr) == NULL ){
            return strrev(infix);
        }else if((*sPtr) != NULL ){
            return "The user input has too many value\n";
        }
}
//prefix to postfix
char* prefixToPostfix(StackNodePtr *sPtr, char *prefix)
{
    char opr_temp[SIZE];
    char ope_temp[SIZE];
    char opr2[SIZE];
    char opr1[SIZE];
    char* tempprefix = malloc(100000 * sizeof(char));
    strcpy(tempprefix,prefix);
    strrev(tempprefix);
    char* postfix = malloc(100000 * sizeof(char));
        char *array[strlen(tempprefix) + 1];
        int i=0,j;
        array[i] = strtok(tempprefix," ");
        while(array[i]!=NULL)
        {
           array[++i] = strtok(NULL," ");
        }
        for(j=0; j<i; j++)
        {
                strcpy(opr_temp,"");
                strcpy(postfix,"");
                strcpy(opr2,"");
                strcpy(opr1,"");
                strcpy(ope_temp,"");
                    if(isOp(array[j])==0 && isInt(array[j])== 0){
                        return "Error cannot evaluate or convert\n";
                    }else if(strcmp(array[j] , "+" )==0 || strcmp(array[j] , "-" )==0 ||
                             strcmp(array[j] , "*" )==0 || strcmp(array[j] , "/" )==0 ||
                             strcmp(array[j] , "^" )==0)
                    {
           if(numStrStack(*sPtr)<2){
                return "Invalid Input to many operators\n";
            }else if(numStrStack(*sPtr)>1){
                strcpy(opr1,popStack(sPtr));
                strcpy(ope_temp,array[j]);
                strcpy(opr2,popStack(sPtr));
                strcat(postfix,opr1);
                strcat(postfix," ");
                strcat(postfix,opr2);
                strcat(postfix," ");
                strcat(postfix,ope_temp);
                pushStack(sPtr,postfix);
            }
        }else if(isInt(array[j])==1){
                        pushStack(sPtr, strrev(array[j]));
                    }
    }
        strcpy(postfix,popStack(sPtr));
        if ((*sPtr) == NULL ){
            return postfix;
        }else if((*sPtr) != NULL ){
            return "The user input has too many value\n";
        }
}
/*if expression infix return 1
 else if expression prefix return 2
 else if expression postfix return 3
 otherwise return 0*/
int ExpType(char *expression)
{
        char* tempstr = malloc(100000 * sizeof(char));
        strcpy(tempstr,expression);
        char *array[strlen(tempstr) + 1];
        int i=0;
        array[i] = strtok(tempstr," ");
        while(array[i]!=NULL)
        {
           array[++i] = strtok(NULL," ");
        }
        if( strcmp(array[0], "(" )==0 && strcmp(array[i-1], ")")==0){
            if(isInt(array[1])==1 && isInt(array[i-2])==1){
                return 1;
            }else{
                return 0;
            }

        }else if(isInt(array[0])==1 && isInt(array[i-1])==1){
            return 1;
        }else if(isInt(array[0])==1 && strcmp(array[i-1], ")")==0){
            if(isInt(array[i-2])==1){
                return 1;
            }else{
                return 0;
            }
        }else if(isInt(array[i-1])==1 && strcmp(array[0], "(")==0){
            if(isInt(array[1])==1){
                return 1;
            }else{
                return 0;
            }
        }else if(isInt(array[0]) == 0 && isOp(array[0]) == 1){
            if(isInt(array[i-1]) == 1){
                return 2;
            }else{
                return 0;
            }
        }else if(isInt(array[i-1]) == 0 && isOp(array[i-1]) == 1){
            if(isInt(array[0]) == 1){
                return 3;
            }else{
                return 0;
            }
        }
}
//evaluates the postfix expression
float Evaluate(StackNodePtr *sPtr, char *postfix)
{
    float val;
    char* temppostfix = malloc(100000 * sizeof(char));
    strcpy(temppostfix,postfix);
    strcat(temppostfix," )");
    int tempnum;
    char *array[strlen(temppostfix) + 1];
        int i=0,j;
        array[i] = strtok(temppostfix," ");
        while(array[i]!=NULL)
        {
           array[++i] = strtok(NULL," ");
        }
        for(j=0; j<i; j++)
        {
            if(isInt( array[j] ) == 1 ){
                tempnum = atoi(array[j]);
                pushNumStack(sPtr, tempnum);
            }
            if(strcmp(array[j] , "+" )==0 || strcmp(array[j] , "-" )==0 ||
               strcmp(array[j] , "*" )==0 || strcmp(array[j] , "/" )==0 ||
               strcmp(array[j] , "^" )==0){
                float a = popNumStack(sPtr);
                float b = popNumStack(sPtr);
                switch(array[j][0]){
                    case '+':
                    val = b + a;
                    break;
                    case '-':
                    val = b - a;
                    break;
                    case '*':
                    val = b * a;
                    break;
                    case '/':
                    val = b / a;
                    break;
                    case '^':
                    val = pow(b,a);
                    break;
                }
                pushNumStack(sPtr,val);
            }
            if( strcmp(array[j] , ")" )==0){
                break;
            }
        }
        val = popNumStack(sPtr);
   return val;
}
// return 1 if the stack is empty, 0 otherwise
int isEmpty(StackNodePtr topPtr)
{
    return topPtr== NULL;
}
/** check if input expression free from alphabets
and other operators**/
int normEx(char *string)
{
        char *tempstr = malloc(100000 * sizeof(char));
        strcpy(tempstr,string);
        char *array[strlen(tempstr) + 1];
        int i=0,j;
        array[i] = strtok(tempstr," ");
        while(array[i]!=NULL)
        {
           array[++i] = strtok(NULL," ");
        }
        for(j=0;j<i;j++)
        {
            if(isInt(array[j])==0 && isOp(array[j])==0 )
            {
                return 0;
            }
        }
        return 1;
}
/*check if there is imbalance parenthesis*/
int imbal(char *string){
        int count =0;
        StackNodePtr sPtr = NULL;
        char* tempstr = malloc(100000 * sizeof(char));
        strcpy(tempstr,string);
        char *array[strlen(tempstr) + 1];
        int i=0,j;
        array[i] = strtok(tempstr," ");
        while(array[i]!=NULL)
        {
           array[++i] = strtok(NULL," ");
        }
        for(j=0;j<i;j++)
        {
            if(strcmp(array[j], "(") == 0 ){
                pushStack(&sPtr,array[j]);
                count++;
            }else if(strcmp(array[j], ")") == 0){

                 if(isEmpty(sPtr)){
                     return 0;
                 }else if(!isEmpty(sPtr)){
                     popStack(&sPtr);
                     count--;
                 }
            }
        }
        if(count==0){
           return 1;
        }else if(count!=0){
            return 0;
        }

}
