#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED


void error(int i);
int ll = 0;     //目前读到第几行代码了

//error.h
void error(int i)
{
    switch (i)
    {
    case 1:
        printf("line %d error %d : unknown letter exist\n",ll,i);
        break;
    case 2:
        printf("line %d error %d : incomplete input\n",ll,i);
        break;
    case 3:
        printf("line %d error %d : overflow\n",ll,i);
        break;
    case 4:
        printf("line %d error %d : unexpected letter in quatation\n",ll,i);
        break;
    case 5:
        printf("line %d error %d : expected '(' \n",ll,i);
        break;
    case 6:
        printf("line %d error %d : expected ')' \n",ll,i);
        break;
    case 7:
        printf("line %d error %d : expected '[' \n",ll,i);
        break;
    case 8:
        printf("line %d error %d : expected ']'\n",ll,i);
        break;
    case 9:
        printf("line %d error %d : expected '{'\n",ll,i);
        break;
    case 10:
        printf("line %d error %d : expected '}'\n",ll,i);
        break;
    case 11:
        printf("line %d error %d : expected ';'\n",ll,i);
        break;
    case 12:
        printf("line %d error %d : type expected \n",ll,i);
        break;
    case 13:
        printf("line %d error %d : identity expected after type \n",ll,i);
        break;
    case 14:
        printf("line %d error %d : '=' expected \n",ll,i);
        break;
    case 15:
        printf("line %d error %d : number expected  \n",ll,i);
        break;
    case 16:
        printf("line %d error %d : character expected  \n",ll,i);
        break;
    case 17:
        printf("line %d error %d : plus/minus before 0  \n",ll,i);
        break;
    case 18:
        printf("line %d error %d : wrong word after identity  \n",ll,i);
        break;
    case 19:
        printf("line %d error %d : case expected \n",ll,i);
        break;
    case 20:
        printf("line %d error %d : sig_quatation expected \n",ll,i);
        break;
    case 21:
        printf("line %d error %d : ':' expected \n",ll,i);
        break;
    case 22:
        printf("line %d error %d : unexpected declaration \n",ll,i);
        break;
    case 23:
        printf("line %d error %d : unexpected statement \n",ll,i);
        break;
    case 24:
        printf("line %d error %d : expected '('&')' between 'return' \n",ll,i);
        break;
    case 25:
        printf("line %d error %d : no index in the declaration of function \n",ll,i);
        break;
    case 26:
        printf("line %d error %d : sentence should be in the function \n",ll,i);
        break;
    case 27:
        printf("line %d error %d : no simple sentence in sentence list \n",ll,i);
        break;
    case 28:
        printf("line %d error %d : illegal variation declaration \n",ll,i);
        break;
    case 29:
        printf("line %d error %d : identity undeclared \n",ll,i);
        break;
    case 30:
        printf("line %d warning %d : function without return \n",ll,i);
        break;
    case 31:
        printf("line %d error %d : numbers in array declaration should be greater than -1 \n",ll,i);
        break;
    case 32:
        printf("line %d error %d : identity has been declared \n",ll,i);
        break;
    case 33:
        printf("line %d error %d : return parameter from void function \n",ll,i);
        break;
    case 34:
        printf("line %d error %d : no return parameter from function \n",ll,i);
        break;
    case 35:
        printf("line %d error %d : number of parameter is incorrect \n",ll,i);
        break;
    case 36:
        printf("line %d error %d : unable to fine parameter \n",ll,i);
        break;
    case 37:
        printf("line %d error %d : need identities when scanning \n",ll,i);
        break;
    case 38:
        printf("line %d error %d : variable required \n",ll,i);
        break;
    case 39:
        printf("line %d error %d : only print one parameter \n",ll,i);
        break;
    case 40:
        printf("line %d error %d : expected ',' \n",ll,i);
        break;
    }
}
#endif // ERROR_H_INCLUDED
