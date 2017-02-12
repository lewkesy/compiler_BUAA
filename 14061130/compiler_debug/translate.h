#ifndef TRANSLATE_H_INCLUDED
#define TRANSLATE_H_INCLUDED

struct fTable mStack[FTABLESIZE];                 //四元式表
int currentfinallevel;
char func[FELMSIZE];
char reg1[FELMSIZE];
char reg2[FELMSIZE];
char reg3[FELMSIZE];
char reg1text[FELMSIZE];
char reg2text[FELMSIZE];
char reg3text[FELMSIZE];

void setTable(char op[],char elm1[],char elm2[],char result[]){

    mStack_length++;
    strcpy(mStack[mStack_length].op,op);
    strcpy(mStack[mStack_length].elm1,elm1);
    strcpy(mStack[mStack_length].elm2,elm2);
    strcpy(mStack[mStack_length].result,result);
    //printf("%s\t%s\t%s\t%s\n",op,result,elm1,elm2);
}

void storeReg(char elm1[],char elm2[],char elm3[]){
    int lookUpResult;
    char raddr[FELMSIZE];
    lookUpResult = lookUp(elm1,currentfinallevel);
    if(lookUpResult != -1){
        itoa(vTBL[lookUpResult].raddr * 4,raddr,10);
        strcat(raddr,"($s3)");
        setTable("sw","$t7",raddr," ");
     }
     else if(lookUpGlobal(elm1,0) != -1){
        itoa(vTBL[lookUpGlobal(elm1,0)].raddr * 4,raddr,10);
        strcat(raddr,"($s2)");
        setTable("sw","$t7",raddr," ");
     }
     else if(lookUpDTBL(elm1) != -1){
        itoa(lookUpDTBL(elm1) * 4,raddr,10);
        strcat(raddr,"($s5)");
        setTable("sw","$t7",raddr," ");
     }

     lookUpResult = lookUp(elm2,currentfinallevel);
    if(lookUpResult != -1){
        itoa(vTBL[lookUpResult].raddr * 4,raddr,10);
        strcat(raddr,"($s3)");
        setTable("sw","$t8",raddr," ");
     }
     else if(lookUpGlobal(elm2,0) != -1){
        itoa(vTBL[lookUpGlobal(elm2,0)].raddr * 4,raddr,10);
        strcat(raddr,"($s2)");
        setTable("sw","$t8",raddr," ");
     }
     else if(lookUpDTBL(elm2) != -1){
        itoa(lookUpDTBL(elm2) * 4,raddr,10);
        strcat(raddr,"($s5)");
        setTable("sw","$t8",raddr," ");
     }

     lookUpResult = lookUp(elm3,currentfinallevel);
    if(lookUpResult != -1){
        itoa(vTBL[lookUpResult].raddr * 4,raddr,10);
        strcat(raddr,"($s3)");
        setTable("sw","$t9",raddr," ");
     }
     else if(lookUpGlobal(elm3,0) != -1){
        itoa(vTBL[lookUpGlobal(elm3,0)].raddr * 4,raddr,10);
        strcat(raddr,"($s2)");
        setTable("sw","$tp9",raddr," ");
     }
     else if(lookUpDTBL(elm3) != -1){
        itoa(lookUpDTBL(elm3) * 4,raddr,10);
        strcat(raddr,"($s5)");
        setTable("sw","$t9",raddr," ");
     }
}

void loadReg(char elm1[],char elm2[],char elm3[]){
    int lookUpResult;
    char raddr[FELMSIZE];
    lookUpResult = lookUp(elm1,currentfinallevel);
    if(lookUpResult != -1){
        itoa(vTBL[lookUpResult].raddr * 4,raddr,10);
        strcat(raddr,"($s3)");
        setTable("lw","$t7",raddr," ");
     }
     else if(lookUpGlobal(elm1,0) != -1){
        itoa(vTBL[lookUpGlobal(elm1,0)].raddr * 4,raddr,10);
        strcat(raddr,"($s2)");
        setTable("lw","$t7",raddr," ");
     }
     else if(lookUpDTBL(elm1) != -1){
        itoa(lookUpDTBL(elm1) * 4,raddr,10);
        strcat(raddr,"($s5)");
        setTable("lw","$t7",raddr," ");
     }

     lookUpResult = lookUp(elm2,currentfinallevel);
    if(lookUpResult != -1){
        itoa(vTBL[lookUpResult].raddr * 4,raddr,10);
        strcat(raddr,"($s3)");
        setTable("lw","$t8",raddr," ");
     }
     else if(lookUpGlobal(elm2,0) != -1){
        itoa(vTBL[lookUpGlobal(elm2,0)].raddr * 4,raddr,10);
        strcat(raddr,"($s2)");
        setTable("lw","$t8",raddr," ");
     }
     else if(lookUpDTBL(elm2) != -1){
        itoa(lookUpDTBL(elm2) * 4,raddr,10);
        strcat(raddr,"($s5)");
        setTable("lw","$t8",raddr," ");
     }

     lookUpResult = lookUp(elm3,currentfinallevel);
    if(lookUpResult != -1){
        itoa(vTBL[lookUpResult].raddr * 4,raddr,10);
        strcat(raddr,"($s3)");
        setTable("lw","$t9",raddr," ");
     }
     else if(lookUpGlobal(elm3,0) != -1){
        itoa(vTBL[lookUpGlobal(elm3,0)].raddr * 4,raddr,10);
        strcat(raddr,"($s2)");
        setTable("lw","$tp9",raddr," ");
     }
     else if(lookUpDTBL(elm3) != -1){
        itoa(lookUpDTBL(elm3) * 4,raddr,10);
        strcat(raddr,"($s5)");
        setTable("lw","$t9",raddr," ");
     }
}

int ifReg(char elm[]){
    if(!strcmp(elm,reg1)){
        return 1;
    }
    else if(!strcmp(elm,reg2)){
        return 2;
    }
    else if(!strcmp(elm,reg3)){
        return 3;
    }

    return -1;
}

int tempVaribleNum(char tempVarible[]){
    int i;
    char varible[FELMSIZE];
    strcpy(varible,tempVarible);
    for(i = 2; i < strlen(varible);i++){
        varible[i - 2] = tempVarible[i];
    }
    varible[i - 2] = '\0';
    return(atoi(varible));
}

int lookUpText(char text[]){
    if(!strcmp(text,reg1text))
        return 1;
    else if(!strcmp(text,reg2text))
        return 2;
    else if(!strcmp(text,reg3text))
        return 3;
    return -1;
}

int analysis(char _elm1[],char _elm2[]){
    //t3t4t5寄存器存翻译运算的过程变量
    int num1 = 0;
    int num2 = 0;//如果元素为数字则标为1
    char elm1[FELMSIZE];
    char elm2[FELMSIZE];
    int currentlevel;
    char raddr[FELMSIZE];
    char index[10];
    char ident[15];
    int temp_raddr;
    int i;
    int j;
    int lookUpTextResult;
    int countReg;
    strcpy(elm1,_elm1);
    strcpy(elm2,_elm2);

    currentlevel = lookUp(func,0);
    currentlevel = vTBL[currentlevel].flevel;
    if(isNum(elm1) == 1){
        num1 = 1;
    }
    else{
        countReg = ifReg(elm1);
        if(countReg != -1){
            if(countReg == 1){
                strcpy(_elm1,"$t7");
            }
            else if(countReg == 2){
                strcpy(_elm1,"$t8");
            }
            else{
                strcpy(_elm1,"$t9");
            }
            num1 = 0;
        }
        else{
            if(elm1[0] == '['){
                strcpy(index,"");
                strcpy(ident,"");
                i = 0;
                while(elm1[i + 1] != ']'){
                    index[i] = elm1[i + 1];//中括号里面的内容
                    i++;
                }
                index[i] = '\0';
                i += 2;
                j = 0;
                while(i != strlen(elm1)){
                    ident[j] = elm1[i];//数组名称
                    j++;
                    i++;
                }
                ident[j] = '\0';
                if(elm1[1] == '@'){//数据表

                    itoa(tempVaribleNum(index) * 4,raddr,10);
                    strcat(raddr,"($s5)");
                    lookUpTextResult = lookUpText(raddr);
                    if(lookUpTextResult == -1)
                        setTable("lw","$t0",raddr," ");
                    else{
                        switch(lookUpTextResult){
                            case 1:setTable("move","$t0","$t7"," ");break;
                            case 2:setTable("move","$t0","$t8"," ");break;
                            case 3:setTable("move","$t0","$t9"," ");break;
                        }
                    }
                    setTable("sll","$t0","$t0","2");
                    //number inside
                    temp_raddr = lookUp(ident,currentlevel);
                    if(temp_raddr != -1){
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);

                        //beginning of the array
                        setTable("li","$t1",raddr," ");
                        setTable("addu","$t1","$t1","$t0");
                        setTable("addu","$t1","$t1","$s3");
                        setTable("lw","$t0","0($t1)"," ");
                        //load array number into $t0
                        strcpy(_elm1,"$t0");
                    }

                    else{
                        temp_raddr = lookUpGlobal(ident,0);
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);

                        //beginning of the array
                        setTable("li","$t1",raddr," ");
                        setTable("addu","$t1","$t1","$t0");
                        setTable("addu","$t1","$t1","$s2");
                        setTable("lw","$t0","0($t1)"," ");
                        //load array number into $t0
                        strcpy(_elm1,"$t0");
                    }
                }
                else if(elm1[1] >= '0' && elm1[1] <= '9'){//数字
                    itoa(atoi(index) * 4,raddr,10);
                    setTable("li","$t0",raddr," ");
                    temp_raddr = lookUp(ident,currentlevel);
                    if(temp_raddr != -1){
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                        //beginning of the array
                        setTable("li","$t1",raddr," ");
                        setTable("addu","$t1","$t1","$t0");
                        setTable("addu","$t1","$t1","$s3");
                        setTable("lw","$t0","0($t1)"," ");
                        //load array number into $t0
                        strcpy(_elm1,"$t0");
                    }
                    else{
                        temp_raddr = lookUpGlobal(ident,0);
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);

                        setTable("li","$t1",raddr," ");
                        setTable("addu","$t1","$t1","$t0");
                        setTable("addu","$t1","$t1","$s2");
                        setTable("lw","$t0","0($t1)"," ");
                        strcpy(_elm1,"$t0");
                    }
                }
                else{//参数
                    if(lookUp(index,currentlevel) == -1){
                        itoa(vTBL[lookUpGlobal(index,0)].raddr * 4,raddr,10);
                        strcat(raddr,"($s2)");
                    }
                    else{
                        itoa(vTBL[lookUp(index,currentlevel)].raddr * 4,raddr,10);
                        strcat(raddr,"($s3)");
                    }
                    lookUpTextResult = lookUpText(raddr);
                    if(lookUpTextResult == -1)
                        setTable("lw","$t0",raddr," ");
                    else{
                        switch(lookUpTextResult){
                            case 1:setTable("move","$t0","$t7"," ");break;
                            case 2:setTable("move","$t0","$t8"," ");break;
                            case 3:setTable("move","$t0","$t9"," ");break;
                        }
                    }
                    setTable("sll","$t0","$t0","2");
                    temp_raddr = lookUp(ident,currentlevel);
                    if(temp_raddr != -1){
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                        setTable("li","$t1",raddr," ");
                        setTable("addu","$t1","$t1","$t0");
                        setTable("addu","$t1","$t1","$s3");
                        setTable("lw","$t0","0($t1)"," ");
                        strcpy(_elm1,"$t0");
                    }

                    else{
                        temp_raddr = lookUpGlobal(ident,0);
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                        setTable("li","$t1",raddr," ");
                        setTable("addu","$t1","$t1","$t0");
                        setTable("addu","$t1","$t1","$s2");
                        setTable("lw","$t0","0($t1)"," ");
                        strcpy(_elm1,"$t0");
                    }

                }
                num1 = 0;
            }
            else if(elm1[0] == '@'){
                itoa(tempVaribleNum(elm1) * 4,raddr,10);
                strcat(raddr,"($s5)");
                setTable("lw","$t0",raddr," ");
                strcpy(_elm1,"$t0");
                num1 = 0;
            }
            else if(elm1[0] != '$' && elm1[0] != ' '){
                currentlevel = lookUp(func,0);
                currentlevel = vTBL[currentlevel].flevel;
                currentlevel = lookUp(elm1,currentlevel);//只是用来暂时存地址的

                if(currentlevel != -1){
                    itoa(vTBL[currentlevel].raddr * 4,raddr,10);
                    strcat(raddr,"($s3)");
                    setTable("lw","$t0",raddr," ");
                    strcpy(_elm1,"$t0");
                    num1 = 0;
                }
                else{
                    itoa(vTBL[lookUpGlobal(elm1,0)].raddr * 4,raddr,10);
                    strcat(raddr,"($s2)");
                    setTable("lw","$t0",raddr," ");
                    strcpy(_elm1,"$t0");
                    num1 = 0;
                }

            }
        }

    }

    currentlevel = lookUp(func,0);
    currentlevel = vTBL[currentlevel].flevel;
    if(isNum(elm2) == 1){
        num2 = 1;
    }
    else{
        countReg = ifReg(elm2);
        if(countReg != -1){
            if(countReg == 1){
                strcpy(_elm2,"$t7");
            }
            else if(countReg == 2){
                strcpy(_elm2,"$t8");
            }
            else{
                strcpy(_elm2,"$t9");
            }
            num2 = 0;
        }
        else{
            if(elm2[0] == '['){
                strcpy(index,"");
                strcpy(ident,"");
                currentlevel = lookUp(func,0);
                currentlevel = vTBL[currentlevel].flevel;
                i = 0;
                while(elm2[i + 1] != ']'){
                    index[i] = elm2[i + 1];//中括号里面的内容
                    i++;
                }
                index[i] = '\0';
                i += 2;
                j = 0;
                while(i != strlen(elm2)){
                    ident[j] = elm2[i];//数组名称
                    j++;
                    i++;
                }
                ident[j] = '\0';
                if(elm2[1] == '@'){//数据表
                    itoa(tempVaribleNum(index) * 4,raddr,10);
                    strcat(raddr,"($s5)");
                    lookUpTextResult = lookUpText(raddr);
                    if(lookUpTextResult == -1)
                        setTable("lw","$t3",raddr," ");
                    else{
                        switch(lookUpTextResult){
                            case 1:setTable("move","$t3","$t7"," ");break;
                            case 2:setTable("move","$t3","$t8"," ");break;
                            case 3:setTable("move","$t3","$t9"," ");break;
                        }
                    }
                    setTable("sll","$t3","$t3","2");
                    //number inside
                    temp_raddr = lookUp(ident,currentlevel);
                    if(temp_raddr != -1){
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                        setTable("li","$t4",raddr," ");
                        setTable("addu","$t4","$t4","$t3");
                        setTable("addu","$t4","$t4","$s3");
                        setTable("lw","$t3","0($t4)"," ");
                        strcpy(_elm1,"$t3");
                    }
                    else{
                        temp_raddr = lookUpGlobal(ident,0);
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                        //beginning of the array
                        setTable("li","$t4",raddr," ");
                        setTable("addu","$t4","$t4","$t3");
                        setTable("addu","$t4","$t4","$s2");
                        setTable("lw","$t3","0($t4)"," ");
                        //load array number into $t0
                        strcpy(_elm2,"$t3");
                    }

                }
                else if(elm2[1] >= '0' && elm2[1] <= '9'){//数字
                    itoa(atoi(index) * 4,raddr,10);
                    setTable("li","$t3",raddr," ");
                    temp_raddr = lookUp(ident,currentlevel);
                    if(temp_raddr != -1){
                            //beginning of the array
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                        setTable("li","$t4",raddr," ");
                        setTable("addu","$t4","$t4","$t3");
                        setTable("addu","$t4","$t4","$s3");
                        setTable("lw","$t3","0($t4)"," ");
                        //load array number into $t0
                        strcpy(_elm2,"$t3");
                    }

                    else{
                        temp_raddr = lookUpGlobal(ident,0);
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                        setTable("li","$t4",raddr," ");
                        setTable("addu","$t4","$t4","$t3");
                        setTable("addu","$t4","$t4","$s2");
                        setTable("lw","$t3","0($t4)"," ");
                        strcpy(_elm2,"$t3");
                    }
                }
                else{//参数
                    if(lookUp(index,currentlevel) == -1){
                        itoa(vTBL[lookUpGlobal(index,0)].raddr * 4,raddr,10);
                        strcat(raddr,"($s2)");
                    }
                    else{
                        itoa(vTBL[lookUp(index,currentlevel)].raddr * 4,raddr,10);
                        strcat(raddr,"($s3)");
                    }
                    lookUpTextResult = lookUpText(raddr);
                    if(lookUpTextResult == -1)
                        setTable("lw","$t3",raddr," ");
                    else{
                        switch(lookUpTextResult){
                            case 1:setTable("move","$t3","$t7"," ");break;
                            case 2:setTable("move","$t3","$t8"," ");break;
                            case 3:setTable("move","$t3","$t9"," ");break;
                        }
                    }
                    setTable("sll","$t3","$t3","2");
                    temp_raddr = lookUp(ident,currentlevel);
                    if(temp_raddr != -1){
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                        setTable("li","$t4",raddr," ");
                        setTable("addu","$t4","$t4","$t3");
                        setTable("addu","$t4","$t4","$s3");
                        setTable("lw","$t3","0($t4)"," ");
                        strcpy(_elm2,"$t3");

                    }
                    else{
                        temp_raddr = lookUpGlobal(ident,0);
                        itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                        setTable("li","$t4",raddr," ");
                        setTable("addu","$t4","$t4","$t3");
                        setTable("addu","$t4","$t4","$s2");
                        setTable("lw","$t3","0($t4)"," ");
                        strcpy(_elm2,"$t3");

                    }
                }
                num2 = 0;
            }
            else if(elm2[0] == '@'){
                itoa(tempVaribleNum(elm2) * 4,raddr,10);
                strcat(raddr,"($s5)");
                setTable("lw","$t3",raddr," ");
                strcpy(_elm2,"$t3");
                num2 = 0;
            }
            else if(elm2[0] != '$' && elm2[0] != ' '){
                currentlevel = lookUp(func,0);
                currentlevel = vTBL[currentlevel].flevel;
                currentlevel = lookUp(elm2,currentlevel);//只是用来暂时存地址的
                if(currentlevel != -1){
                    itoa(vTBL[currentlevel].raddr * 4,raddr,10);
                    strcat(raddr,"($s3)");
                    setTable("lw","$t3",raddr," ");
                    strcpy(_elm2,"$t3");
                    num2 = 0;
                }
                else{
                    itoa(vTBL[lookUpGlobal(elm2,0)].raddr * 4,raddr,10);
                    strcat(raddr,"($s2)");
                    setTable("lw","$t3",raddr," ");
                    strcpy(_elm2,"$t3");
                    num2 = 0;
                }
            }
        }

    }

    if(num1 == 1 && num2 ==1){
        return 1;
    }

    else if((num2 == 1) && (num1 == 0)){
        return 2;
    }

    else if((num1 == 1) && (num2 == 0)){
        return 3;
    }
    return 4;
}

void resultTrouble(char result[]){//用t3t4
    char index[FELMSIZE];
    char ident[FELMSIZE];
    char raddr[FELMSIZE];
    int i;
    int j;
    int temp_raddr;
    int currentlevel;
    int countReg;
    int lookUpTextResult;

    currentlevel = lookUp(func,0);
    currentlevel = vTBL[currentlevel].flevel;
    countReg = ifReg(result);
    if(countReg != -1){
        if(countReg == 1){
            strcpy(result,"$t7");
        }
        else if(countReg == 2){
            strcpy(result,"$t8");
        }
        else{
            strcpy(result,"$t9");
        }
    }
    else{
        if(result[0] == '['){
            strcpy(index,"");
            strcpy(ident,"");
            currentlevel = lookUp(func,0);
            currentlevel = vTBL[currentlevel].flevel;
            i = 0;
            while(result[i + 1] != ']'){
                index[i] = result[i + 1];//中括号里面的内容
                i++;
            }
            index[i] = '\0';
            i += 2;
            j = 0;
            while(i != strlen(result)){
                ident[j] = result[i];//数组名称
                j++;
                i++;
            }
            ident[j] = '\0';
            if(result[1] == '@'){//数据表
                itoa(tempVaribleNum(index) * 4,raddr,10);
                strcat(raddr,"($s5)");
                lookUpTextResult = lookUpText(raddr);
                    if(lookUpTextResult == -1){
                        setTable("lw","$t3",raddr," ");
                    }
                    else{
                        switch(lookUpTextResult){
                            case 1:setTable("move","$t3","$t7"," ");break;
                            case 2:setTable("move","$t3","$t8"," ");break;
                            case 3:setTable("move","$t3","$t9"," ");break;
                        }
                    }
                setTable("sll","$t3","$t3","2");
                //number inside
                temp_raddr = lookUp(ident,currentlevel);
                if(temp_raddr != -1){
                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);

                    //beginning of the array
                    setTable("li","$t4",raddr," ");
                    setTable("addu","$t4","$t4","$t3");
                    setTable("addu","$t4","$t4","$s3");
                    //load array number into $t0
                        strcpy(result,"0($t4)");

                }

                else{
                    temp_raddr = lookUpGlobal(ident,0);
                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);

                    //beginning of the array
                    setTable("li","$t4",raddr," ");
                    setTable("addu","$t4","$t4","$t3");
                    setTable("addu","$t4","$t4","$s2");
                    //load array number into $t0
                        strcpy(result,"0($t4)");
                }
            }
            else if(result[1] >= '0' && result[1] <= '9'){//数字
                itoa(atoi(index) * 4,raddr,10);
                setTable("li","$t3",raddr," ");
                temp_raddr = lookUp(ident,currentlevel);
                if(temp_raddr != -1){
                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                    setTable("li","$t4",raddr," ");
                    setTable("addu","$t4","$t4","$t3");
                    setTable("addu","$t4","$t4","$s3");
                    strcpy(result,"0($t4)");
                }

                else{
                    temp_raddr = lookUpGlobal(ident,0);
                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                    setTable("li","$t4",raddr," ");
                    setTable("addu","$t4","$t4","$t3");
                    setTable("addu","$t4","$t4","$s2");
                    strcpy(result,"0($t4)");
                }

            }
            else{//参数
                if(lookUp(index,currentlevel) == -1){
                    itoa(vTBL[lookUpGlobal(index,0)].raddr * 4,raddr,10);
                    strcat(raddr,"($s2)");
                }
                else{
                    itoa(vTBL[lookUp(index,currentlevel)].raddr * 4,raddr,10);
                    strcat(raddr,"($s3)");
                }
                lookUpTextResult = lookUpText(raddr);
                    if(lookUpTextResult == -1){
                        setTable("lw","$t3",raddr," ");
                    }
                    else{
                        switch(lookUpTextResult){
                            case 1:setTable("move","$t3","$t7"," ");break;
                            case 2:setTable("move","$t3","$t8"," ");break;
                            case 3:setTable("move","$t3","$t9"," ");break;
                        }
                    }
                setTable("sll","$t3","$t3","2");
                temp_raddr = lookUp(ident,currentlevel);
                if(temp_raddr != -1){
                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                    setTable("li","$t4",raddr," ");
                    setTable("addu","$t4","$t4","$t3");
                    setTable("addu","$t4","$t4","$s3");
                        strcpy(result,"0($t4)");

                }
                else{
                    temp_raddr = lookUpGlobal(ident,0);
                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                    setTable("li","$t4",raddr," ");
                    setTable("addu","$t4","$t4","$t3");
                    setTable("addu","$t4","$t4","$s2");
                        strcpy(result,"0($t4)");
                }

            }
        }
        else if(result[0] == '@'){
            itoa(tempVaribleNum(result) * 4,raddr,10);
            strcat(raddr,"($s5)");
            strcpy(result,raddr);
        }
        else if(result[0] != '$' && result[0] != ' '){
            currentlevel = lookUp(func,0);
            currentlevel = vTBL[currentlevel].flevel;
            currentlevel = lookUp(result,currentlevel);//只是用来暂时存地址的
            if(currentlevel != -1){

                itoa(vTBL[currentlevel].raddr * 4,raddr,10);
                strcat(raddr,"($s3)");
                strcpy(result,raddr);
            }
            else{
                itoa(vTBL[lookUpGlobal(result,0)].raddr * 4,raddr,10);
                strcat(raddr,"($s2)");
                strcpy(result,raddr);
            }
        }
        else{
            ;
        }
    }

}

void translate(int tTBL_length,char _reg[][FELMSIZE]){
    int i;
    int j;
    int k;
    int kind;
    int temp_raddr;
    int countReg;
    int currentlevel;
    int lookUpResult;
    int lookUpTextResult;
    char op[FELMSIZE];
    char elm1[FELMSIZE];
    char elm2[FELMSIZE];
    char result[FELMSIZE];
    char index[FELMSIZE];
    char ident[FELMSIZE];
    char raddr[FELMSIZE];
    char tempChar[FELMSIZE];

    for(i = 0; i <= tTBL_length; i++){
        strcpy(op,tTBL[i].op);
        strcpy(elm1,tTBL[i].elm1);
        strcpy(elm2,tTBL[i].elm2);
        strcpy(result,tTBL[i].result);

        if(op[strlen(op) - 1] == ':'){
            op[strlen(op) - 1] = '\0';
            strcpy(tempChar,op);
            if(lookUpFunc(tempChar) == 1){
                strcpy(func,op);
                func[strlen(op)] = '\0';
            }

            currentfinallevel = lookUp(func,0);
            currentfinallevel = vTBL[currentfinallevel].flevel;
        }

        //reg1
        lookUpResult = lookUp(_reg[0],currentfinallevel);
        if(lookUpResult != -1){
            itoa(vTBL[lookUpResult].raddr * 4,reg1text,10);
            strcat(reg1text,"($s3)");
        }
        else{
            lookUpResult = lookUpGlobal(_reg[0],0);
            if(lookUpResult != -1){
                itoa(vTBL[lookUpResult].raddr * 4,reg1text,10);
                strcat(reg1text,"($s2)");
            }
            else{
                lookUpResult = lookUpDTBL(_reg[0]);
                itoa(lookUpResult * 4,reg1text,10);
                strcat(reg1text,"($s5)");
            }
        }


        //reg2
        lookUpResult = lookUp(_reg[1],currentfinallevel);
        if(lookUpResult != -1){
            itoa(vTBL[lookUpResult].raddr * 4,reg2text,10);
            strcat(reg2text,"($s3)");
        }
        else{
            lookUpResult = lookUpGlobal(_reg[1],0);
            if(lookUpResult != -1){
                itoa(vTBL[lookUpResult].raddr * 4,reg2text,10);
                strcat(reg2text,"($s2)");
            }

            else{
                lookUpResult = lookUpDTBL(_reg[1]);
                itoa(lookUpResult * 4,reg2text,10);
                strcat(reg2text,"($s5)");
            }
        }

        //reg3
        lookUpResult = lookUp(_reg[2],currentfinallevel);
        if(lookUpResult != -1){
            itoa(vTBL[lookUpResult].raddr * 4,reg3text,10);
            strcat(reg3text,"($s3)");
        }
        else{
            lookUpResult = lookUpGlobal(_reg[2],0);
            if(lookUpResult != -1){
                itoa(vTBL[lookUpResult].raddr * 4,reg3text,10);
                strcat(reg3text,"($s2)");
            }
            else{
                lookUpResult = lookUpDTBL(_reg[2]);
                itoa(lookUpResult * 4,reg3text,10);
                strcat(reg3text,"($s5)");
            }
        }


        //写出记录当前被替换掉的临时变量的内容，想一下什么时候不再去替换
        strcpy(reg1,_reg[0]);
        strcpy(reg2,_reg[1]);
        strcpy(reg3,_reg[2]);

        if(tTBL[i].op[0] == '+' || tTBL[i].op[0] == '-' || tTBL[i].op[0] == '*' || tTBL[i].op[0] == '/' || tTBL[i].op[0] == '='){

            kind = analysis(elm1,elm2);
            switch(tTBL[i].op[0]){
                case '+':
                    resultTrouble(result);
                    if(kind == 1){
                        setTable("li","$t0",elm1," ");
                        setTable("li","$t1",elm2," ");
                        if(result[0] == '$' && result[1] == 's')
                            setTable("addu",result,elm1,elm2);
                        else if(result[0] == '$')
                            setTable("addu",result,"$t0","$t1");
                        else{
                            setTable("addu","$t0","$t0","$t1");
                            setTable("sw","$t0",result," ");
                        }

                    }
                    else if(kind == 4){
                        if(result[0] == '$')
                            setTable("addu",result,elm1,elm2);
                        else{

                            setTable("addu","$t0",elm1,elm2);
                            setTable("sw","$t0",result," ");
                        }

                    }
                    else{
                        if(kind == 2){
                            if(result[0] == '$')
                                setTable("addi",result,elm1,elm2);
                            else{
                                setTable("addi","$t0",elm1,elm2);
                                setTable("sw","$t0",result," ");
                            }
                        }
                    else{
                        if(result[0] == '$')
                            setTable("addi",result,elm2,elm1);
                        else{
                            setTable("addi","$t0",elm2,elm1);
                            setTable("sw","$t0",result," ");
                        }
                    }
                }
                break;
                case '-':
                    resultTrouble(result);
                    if(kind == 1){
                        setTable("li","$t0",elm1," ");
                        setTable("li","$t1",elm2," ");
                        if(result[0] == '$' && result[1] == 's')
                            setTable("subu",result,elm1,elm2);
                        else if(result[0] == '$')
                            setTable("subu",result,"$t0","$t1");
                        else{
                            setTable("subu","$t0","$t0","$t1");
                            setTable("sw","$t0",result," ");
                        }
                    }
                    else if(kind == 4){
                        if(result[0] == '$')
                            setTable("subu",result,elm1,elm2);
                        else{
                            setTable("subu","$t0",elm1,elm2);
                            setTable("sw","$t0",result," ");
                        }

                    }
                    else{
                        if(kind == 2){
                            setTable("li","$t3",elm2," ");
                            if(result[0] == '$')
                                setTable("subu",result,elm1,"$t3");
                            else{
                                setTable("subu","$t0",elm1,"$t3");
                                setTable("sw","$t0",result," ");
                            }
                        }
                        else{
                            setTable("li","$t0",elm1," ");
                            if(result[0] == '$')
                                setTable("subu",result,"$t0",elm2);
                            else{
                                setTable("subu","$t0","$t0",elm2);
                                setTable("sw","$t0",result," ");
                            }
                        }
                    }
                    break;
                case '*':
                    resultTrouble(result);
                    if(kind == 1){
                        setTable("li","$t0",elm1," ");
                        setTable("li","$t1",elm2," ");
                        setTable("mult"," ","$t0","$t1");
                    }
                    else if(kind == 4){
                        setTable("mult"," ",elm1,elm2);
                    }
                    else{
                        if(kind == 2){
                            setTable("li","$t1",elm2," ");
                            setTable("mult"," ",elm1,"$t1");
                        }
                        else{
                            setTable("li","$t0",elm1," ");
                            setTable("mult"," ",elm2,"$t0");
                        }
                    }

                    setTable("li","$t0","0"," ");
                    setTable("mflo","$t1"," "," ");
                    setTable("addu","$t0","$t0","$t1");
                    if(result[0] == '$')
                        setTable("move",result,"$t0"," ");
                    else
                        setTable("sw","$t0",result," ");
                    break;
                case '/':
                    resultTrouble(result);
                    if(kind == 1){
                        setTable("li","$t0",elm1," ");
                        setTable("li","$t1",elm2," ");
                        setTable("div"," ","$t0","$t1");
                    }
                    else if(kind == 4){
                        setTable("div"," ",elm1,elm2);
                    }
                    else{
                        if(kind == 2){
                            setTable("li","$t1",elm2," ");
                            setTable("div"," ",elm1,"$t1");
                        }
                        else{
                            setTable("li","$t0",elm1," ");
                            setTable("div"," ","$t0",elm2);
                        }
                    }
                    setTable("mflo","$t0"," "," ");
                    if(result[0] == '$')
                        setTable("move",result,"$t0"," ");
                    else
                        setTable("sw","$t0",result," ");
                    break;
                case '=':
                    strcpy(index,"");
                    strcpy(ident,"");

                    currentlevel = lookUp(func,0);
                    currentlevel = vTBL[currentlevel].flevel;
                    countReg = ifReg(result);
                    if(countReg != -1){
                        if(countReg == 1){
                            strcpy(result,"$t7");
                        }
                        else if(countReg == 2){
                            strcpy(result,"$t8");
                        }
                        else{
                            strcpy(result,"$t9");
                        }
                    }
                    else{
                        if(result[0] == '['){
                            currentlevel = lookUp(func,0);
                            currentlevel = vTBL[currentlevel].flevel;
                            k = 0;
                            while(result[k + 1] != ']'){
                                index[k] = result[k + 1];//中括号里面的内容
                                k++;
                            }
                            index[k] = '\0';
                            k += 2;
                            j = 0;
                            while(k != strlen(result)){
                                ident[j] = result[k];//数组名称
                                j++;
                                k++;
                            }
                            ident[j] = '\0';
                            if(result[1] == '@'){//数据表
                                itoa(tempVaribleNum(index) * 4,raddr,10);
                                strcat(raddr,"($s5)");
                                lookUpTextResult = lookUpText(raddr);
                                if(lookUpTextResult == -1)
                                    setTable("lw","$t3",raddr," ");
                                else{
                                    switch(lookUpTextResult){
                                        case 1:setTable("move","$t3","$t7"," ");break;
                                        case 2:setTable("move","$t3","$t8"," ");break;
                                        case 3:setTable("move","$t3","$t9"," ");break;
                                    }
                                }
                                setTable("sll","$t3","$t3","2");
                                //number inside
                                temp_raddr = lookUp(ident,currentlevel);
                                if(temp_raddr != -1){
                                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                                    //beginning of the array
                                    setTable("li","$t4",raddr," ");
                                    setTable("addu","$t4","$t4","$t3");
                                    setTable("addu","$t4","$t4","$s3");
                                    //load array number into $t0
                                    strcpy(result,"0($t4)");
                                }
                                else{
                                    temp_raddr = lookUpGlobal(ident,0);
                                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                                    //beginning of the array
                                    setTable("li","$t4",raddr," ");
                                    setTable("addu","$t4","$t4","$t3");
                                    setTable("addu","$t4","$t4","$s2");
                                    //load array number into $t0
                                    strcpy(result,"0($t4)");
                                }

                            }
                            else if(result[1] >= '0' && result[1] <= '9'){//数字
                                itoa(atoi(index) * 4,raddr,10);
                                setTable("li","$t3",raddr," ");
                                temp_raddr = lookUp(ident,currentlevel);
                                if(temp_raddr != -1){

                                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                                    setTable("li","$t4",raddr," ");
                                    setTable("addu","$t4","$t4","$t3");
                                    setTable("addu","$t4","$t4","$s3");
                                    strcpy(result,"0($t4)");
                                }
                                else{
                                    temp_raddr = lookUpGlobal(ident,0);
                                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                                    setTable("li","$t4",raddr," ");
                                    setTable("addu","$t4","$t4","$t3");
                                    setTable("addu","$t4","$t4","$s2");
                                    strcpy(result,"0($t4)");
                                }
                            }
                            else{//参数
                                if(lookUp(index,currentlevel) == -1){
                                    itoa(vTBL[lookUpGlobal(index,0)].raddr * 4,raddr,10);
                                    strcat(raddr,"($s2)");
                                }
                                else{
                                    itoa(vTBL[lookUp(index,currentlevel)].raddr * 4,raddr,10);
                                    strcat(raddr,"($s3)");
                                }
                                lookUpTextResult = lookUpText(raddr);
                                if(lookUpTextResult == -1)
                                    setTable("lw","$t3",raddr," ");
                                else{
                                    switch(lookUpTextResult){
                                        case 1:setTable("move","$t3","$t7"," ");break;
                                        case 2:setTable("move","$t3","$t8"," ");break;
                                        case 3:setTable("move","$t3","$t9"," ");break;
                                    }
                                }
                                setTable("sll","$t3","$t3","2");
                                temp_raddr = lookUp(ident,currentlevel);
                                if(temp_raddr != -1){
                                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                                    setTable("li","$t4",raddr," ");
                                    setTable("addu","$t4","$t4","$t3");
                                    setTable("addu","$t4","$t4","$s3");
                                    strcpy(result,"0($t4)");
                                }


                                else{
                                    temp_raddr = lookUpGlobal(ident,0);
                                    itoa(vTBL[temp_raddr].raddr * 4,raddr,10);
                                    setTable("li","$t4",raddr," ");
                                    setTable("addu","$t4","$t4","$t3");
                                    setTable("addu","$t4","$t4","$s2");
                                    strcpy(result,"0($t4)");
                                }
                            }
                        }
                        else if(result[0] == '@'){
                            itoa(tempVaribleNum(result) * 4,raddr,10);
                            strcat(raddr,"($s5)");
                            strcpy(result,raddr);
                        }
                        else if(result[0] != '$' && result[0] != ' '){
                            currentlevel = lookUp(func,0);
                            currentlevel = vTBL[currentlevel].flevel;
                            currentlevel = lookUp(result,currentlevel);//只是用来暂时存地址的
                            if(currentlevel != -1){

                                itoa(vTBL[currentlevel].raddr * 4,raddr,10);
                                strcat(raddr,"($s3)");
                                strcpy(result,raddr);
                            }
                            else{
                                itoa(vTBL[lookUpGlobal(result,0)].raddr * 4,raddr,10);
                                strcat(raddr,"($s2)");
                                strcpy(result,raddr);
                            }
                        }

                    }
                    if(isNum(elm1) == 1){
                        setTable("li","$t0",elm1," ");
                        if(result[0] == '$'){
                            setTable("move",result,"$t0"," ");
                        }
                        else{
                            setTable("sw","$t0",result," ");
                        }
                    }
                    else{
                        if(result[0] == '$'){
                            setTable("move",result,elm1," ");
                        }
                        else{
                            setTable("sw",elm1,result," ");
                        }
                    }

                    //setTable("sw","$t0",result," ");

                    break;
            }
        }
        else{
            if(!strcmp(op,"BEQ")
               || !strcmp(op,"BNE")
               || !strcmp(op,"BGEZ")
               || !strcmp(op,"BGTZ")
               || !strcmp(op,"BLTZ")
               || !strcmp(op,"BLEZ")){
                kind = analysis(elm1,elm2);
                if(!strcmp(op,"BEQ") || !strcmp(op,"BNE")){
                    if(kind == 1){
                        //这里处理掉beq/bgez之类的内容
                        setTable("li","$t0",elm1," ");
                        setTable("li","$t3",elm2," ");
                        setTable(tTBL[i].op,"$t0","$t3",tTBL[i].result);
                    }
                    else if(kind == 4){
                        setTable(tTBL[i].op,elm1,elm2,result);
                    }
                    else if(kind == 2){
                        setTable("li","$t3",elm2," ");
                        setTable(tTBL[i].op,elm1,"$t3",result);
                    }
                    else{
                        setTable("li","$t0",elm1," ");
                        setTable(tTBL[i].op,"$t0",elm2,result);
                    }
                }
                else if(!strcmp(op,"BGEZ")
                        || !strcmp(op,"BGTZ")
                        || !strcmp(op,"BLTZ")
                        || !strcmp(op,"BLEZ")){
                    if(kind == 1){
                        //这里处理掉beq/bgez之类的内容
                        setTable("li","$t0",elm1," ");
                        setTable("li","$t3",elm2," ");
                        setTable("subu","$t0","$t0","$t3");
                        setTable(tTBL[i].op,"$t0"," ",tTBL[i].result);
                    }
                    else if(kind == 4){
                        setTable("subu","$t0",elm1,elm2);
                        setTable(tTBL[i].op,"$t0"," ",result);
                    }
                    else if(kind == 2){
                        setTable("li","$t3",elm2," ");
                        setTable("subu","$t0",elm1,"$t3");
                        setTable(tTBL[i].op,"$t0"," ",result);
                    }
                    else{
                        setTable("li","$t0",elm1," ");
                        setTable("subu","$t0","$t0",elm2);
                        setTable(tTBL[i].op,"$t0"," ",result);
                    }
                }
            }
            else if(!strcmp(tTBL[i].op,"lw")){
                analysis(elm1,"0");
                if(!strcmp(tTBL[i].result,reg1text)){
                    setTable("move",tTBL[i].elm1,"$t7"," ");
                }
                else if(!strcmp(tTBL[i].result,reg2text)){
                    setTable("move",tTBL[i].elm1,"$t8"," ");
                }
                else if(!strcmp(tTBL[i].result,reg3text)){
                    setTable("move",tTBL[i].elm1,"$t9"," ");
                }
                else{
                    setTable(tTBL[i].op,elm1,elm2,tTBL[i].result);
                }
            }
            else if(!strcmp(tTBL[i].op,"sw")){

                if(!strcmp(tTBL[i].result,reg1text)){
                    setTable("move","$t7",elm1," ");
                }
                else if(!strcmp(tTBL[i].result,reg2text)){
                    setTable("move","$t8",elm1," ");
                }
                else if(!strcmp(tTBL[i].result,reg3text)){
                    setTable("move","$t9",elm1," ");
                }
                else{
                    setTable(tTBL[i].op,elm1,elm2,tTBL[i].result);
                }
            }
            else if(!strcmp(tTBL[i].op,"jal")){

                storeReg(reg1,reg2,reg3);
                setTable(tTBL[i].op,elm1,elm2,tTBL[i].result);
                loadReg(reg1,reg2,reg3);
            }
            else{

                setTable(tTBL[i].op,elm1,elm2,tTBL[i].result);
                if(!strcmp(tTBL[i].op,"move") && !strcmp(elm1,"$s3") && !strcmp(result,"$sp")){
                    if(reg1text[0] != '-')
                        setTable("lw","$t7",reg1text," ");
                    if(reg2text[0] != '-')
                        setTable("lw","$t8",reg2text," ");
                    if(reg3text[0] != '-')
                        setTable("lw","$t9",reg3text," ");
                }
            }
        }
    }

    puts(func);
    puts(reg1);
    puts(reg1text);
    puts(reg2);
    puts(reg2text);
    puts(reg3);
    puts(reg3text);
    printf("\n");

}

void beginningOfTranslation(){
    char elm1[FELMSIZE];
    setTable("li","$sp","0x10040000"," ");
    setTable("li","$s5","0x10000000"," ");
    setTable("move","$s2","$sp"," ");
    itoa(global_length * 4,elm1,10);
    setTable("addi","$sp","$sp",elm1);
    setTable(" "," "," "," ");

}
#endif // TRANSLATE_H_INCLUDED
