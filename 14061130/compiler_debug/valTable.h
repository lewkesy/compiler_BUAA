#ifndef VALTABLE_H_INCLUDED
#define VALTABLE_H_INCLUDED

#define NAMESIZE 200
#define RUNTIMESTACKSIZE 4096
#define VALTABLESIZE 4096
#define FTABLESIZE 4096
#define FUNCSTACKSIZE 4096
#define FELMSIZE 50
#define TITLENUM 50
#define TITLESIZE 200
struct valTable{
    char name[NAMESIZE];
    int type;                   //type  0:void  1:int  2:char
    int kind;                   //kind  0:var  1:const  2:array  3:function
    int level;                  //在最外层就是0，每次过一个函数层数++，函数声明全是level0
    //int daddr;                  //当前标识符在数据栈中的位置
    int amount;                 //特指函数所有的参数数量；
    int raddr;                  //当前运行栈中根据当前函数栈底的偏移
    int flevel;                 //如果是函数，指出该函数的变量在第几层
};

struct fTable{
	char op[FELMSIZE];          //操作符
	char elm1[FELMSIZE] ;       //操作数1
	char elm2[FELMSIZE];        //操作数2
	char result[FELMSIZE];      //运算结果
};

struct labelTable{
    char labelName[FELMSIZE];
    char funcName[FELMSIZE];
};

struct dataTable{
    char name[FELMSIZE];
    int val;
};
struct dataTable dTBL[RUNTIMESTACKSIZE];        //数据栈
struct valTable vTBL[VALTABLESIZE];             //符号表
struct fTable fTBL[FTABLESIZE];                 //四元式表
int conditionStack[RUNTIMESTACKSIZE] = {0};        //用来等返回条件返回的表
int unconditionStack[RUNTIMESTACKSIZE] = {0};        //用来等返回条件配套的返回的表
struct labelTable lTBL[RUNTIMESTACKSIZE];           //label在四元式中的位置

int currentlevel = 0;
char currentFunc[FELMSIZE];
int mStack_length = -1;
int vTBL_length = -1;                            //符号表当前长度
int fTBL_length = -1;                            //四元式表当前长度
int rStack_length = -1;                          //运行栈中变量相对偏移
int global_length = -1;                          //全局变量相抵偏移
int conditionStack_length = -1;                  //当前等待返回值表当前长度
int unconditionStack_length = -1;                //当前等待返回值配套的表当前长度
int labelNum = 0;                                //当前label位数
int lTBL_length = -1;                            //label表指针
int dTBL_length = -1;                            //数据表指针
int expressType = 1;

char title[TITLENUM][TITLESIZE];
int title_length = -1;
int msgNum = 0;
int ifReturn = 0;
int ifHasReturn = 0;

int isNum(char _elm[]){
    int i;
    char elmm[FELMSIZE];
    strcpy(elmm,_elm);
    if(!(elmm[0] == '-' || elmm[0] == '+') && !(elmm[0] >= '0' && elmm[0] <= '9')){
        return -1;
    }
    for(i = 1; i < strlen(elmm); i++){
        if(!(elmm[i] >= '0' && elmm[i] <= '9'))
            return -1;
    }
    if(strlen(elmm) == 1 && (elmm[0] == '-' || elmm[0] == '+'))
        return -1;

    return 1;
}

int addTitle(char _string[]){
    msgNum++;
    char string[TITLESIZE];
    char temp_num[4];
    strcpy(string,"msg");
    itoa(msgNum,temp_num,10);
    strcat(string,temp_num);
    strcat(string,":  .asciiz ");
    strcat(string,_string);
    strcpy(title[msgNum],string);
    return msgNum;
}

void li(char reg[],int num){
    fTBL_length++;
    strcpy(fTBL[fTBL_length].op,"li");
    strcpy(fTBL[fTBL_length].elm1,reg);
    strcpy(fTBL[fTBL_length].elm2," ");
    itoa(num,fTBL[fTBL_length].result,10);
}

//vatTable
void storeData(char raddr[],char num[]){
    if(isNum(num) == 1){
        li("$t3",atoi(num));
        fTBL_length++;
        strcpy(fTBL[fTBL_length].op,"sw");
        strcpy(fTBL[fTBL_length].result,raddr);
        strcpy(fTBL[fTBL_length].elm1,"$t3");
        strcpy(fTBL[fTBL_length].elm2," ");
    }
    else{
        fTBL_length++;
        strcpy(fTBL[fTBL_length].op,"sw");
        strcpy(fTBL[fTBL_length].result,raddr);
        strcpy(fTBL[fTBL_length].elm1,num);
        strcpy(fTBL[fTBL_length].elm2," ");
    }
}

void loadData(char raddr[],char reg[]){
    fTBL_length++;
    strcpy(fTBL[fTBL_length].op,"lw");
    strcpy(fTBL[fTBL_length].result,raddr);
    strcpy(fTBL[fTBL_length].elm1,reg);
    strcpy(fTBL[fTBL_length].elm2," ");
}



void _move(char reset[],char origin[]){
    fTBL_length++;
    strcpy(fTBL[fTBL_length].op,"move");
    strcpy(fTBL[fTBL_length].elm1,reset);
    strcpy(fTBL[fTBL_length].elm2," ");
    strcpy(fTBL[fTBL_length].result,origin);
}

//对于数组，符号表中存的直接就是a[0],a[1]这种格式，不需要开头
int lookUp(char val[],int level){
    int i;
    for(i = 0; i <= vTBL_length; i++){
        if(!strcmp(val,vTBL[i].name) && level == vTBL[i].level)
            return i;
    }
    return -1;
}

int lookUpGlobal(char val[],int level){
    int i;
    for(i = 0; i <= vTBL_length; i++){
        if(!strcmp(val,vTBL[i].name) && 0 == vTBL[i].level)
            return i;
    }
    return -1;
}

int lookUpDTBL(char val[]){
    int i;
    for(i = 0; i <= dTBL_length; i++){
        if(!strcmp(dTBL[i].name,val)){
            return i;
        }
    }
    return -1;
}

int lookUpFunc(char val[]){
    int i;
    for(i = 0; i <= lTBL_length; i++){
        if(!strcmp(lTBL[i].funcName,val)){
            return 1;
        }
    }
    return -1;
}

void genlabel(){
    char num[6];

    fTBL_length++;
    strcpy(fTBL[fTBL_length].op,"label");
    itoa(labelNum,num,10);
    strcat(fTBL[fTBL_length].op,num);
    strcat(fTBL[fTBL_length].op,":");
    strcpy(fTBL[fTBL_length].elm1," ");
    strcpy(fTBL[fTBL_length].elm2," ");
    strcpy(fTBL[fTBL_length].result," ");

    labelNum++;
}

void genFuncLabel(char funcname[]){
    fTBL_length++;
    strcpy(fTBL[fTBL_length].op,funcname);
    strcat(fTBL[fTBL_length].op,":");
    strcpy(fTBL[fTBL_length].elm1," ");
    strcpy(fTBL[fTBL_length].elm2," ");
    strcpy(fTBL[fTBL_length].result," ");

    lTBL_length++;
    strcpy(lTBL[lTBL_length].funcName,funcname);
    strcpy(lTBL[lTBL_length].labelName,funcname);
}

void findLabel(char _funcName[],char label[]){
    int i;
    for(i = 0; i <= lTBL_length; i++){
        if(strcmp(_funcName,lTBL[i].funcName) == 0){
            strcpy(label,lTBL[i].labelName);
            break;
        }
    }
}

void emit(char op[],char result[],char elm1[],char elm2[]){

    fTBL_length++;

    /*把读进来的两个数字存进去*/
    strcpy(fTBL[fTBL_length].elm1,elm1);
    strcpy(fTBL[fTBL_length].elm2,elm2);
    strcpy(fTBL[fTBL_length].result,result);

        /*四则运算*/
    if(!strcmp(op,"+")){
        strcpy(fTBL[fTBL_length].op,"+");
    }
    else if(!strcmp(op,"-")){
        strcpy(fTBL[fTBL_length].op,"-");
    }
    else if(!strcmp(op,"*")){
        strcpy(fTBL[fTBL_length].op,"*");
    }
    else if(!strcmp(op,"/")){
        strcpy(fTBL[fTBL_length].op,"/");
    }
    else if(!strcmp(op,"=")){
        strcpy(fTBL[fTBL_length].op,"=");
    }


    //比较大小
    else if(!strcmp(op,"")){
        strcpy(fTBL[fTBL_length].op,"BEQ");
        strcpy(fTBL[fTBL_length].elm2,"0");
    }
    else if(!strcmp(op,"=")){

    }
    else{
        if(!strcmp(op,"==")){
            strcpy(fTBL[fTBL_length].op,"BNE");
        }
        else if(!strcmp(op,"!=")){
            strcpy(fTBL[fTBL_length].op,"BEQ");
        }
        else if(!strcmp(op,">")){
            strcpy(fTBL[fTBL_length].op,"BLEZ");
        }
        else if(!strcmp(op,">=")){
            strcpy(fTBL[fTBL_length].op,"BLTZ");
        }
        else if(!strcmp(op,"<")){
            strcpy(fTBL[fTBL_length].op,"BGEZ");
        }
        else if(!strcmp(op,"<=")){
            strcpy(fTBL[fTBL_length].op,"BGTZ");
        }
    }
}

void sll(char op[],char result[],char elm1[],char elm2[]){
    fTBL_length++;
    strcpy(fTBL[fTBL_length].op,op);
    strcpy(fTBL[fTBL_length].elm1,result);
    strcpy(fTBL[fTBL_length].elm2,elm1);
    strcpy(fTBL[fTBL_length].result,elm2);
}

void jump(char op[],char elm1[]){
    fTBL_length++;
    strcpy(fTBL[fTBL_length].op,op);
    strcpy(fTBL[fTBL_length].result," ");
    strcpy(fTBL[fTBL_length].elm2," ");
    strcpy(fTBL[fTBL_length].elm1,elm1);
}


void acceptCall(){
    storeData("4($sp)" , "$s0");
    emit("+","$sp","$sp","4");//sp++
    _move("$s0","$sp");
    storeData("4($sp)","$ra");
    emit("+","$sp","$sp","4");//sp++
    storeData("4($sp)","$s3");//$rp
    emit("+","$sp","$sp","8");//sp++
    _move("$s3","$sp");
    emit("-","$t0","$s1","4");
    emit("+","$sp","$t0","$sp");//sp到目前栈顶
}

void returnAction(){
    if(strcmp(currentFunc,"main")){
        _move("$sp","$s0");
        loadData("0($sp)","$t0");
        _move("$s0","$t0");
        loadData("4($sp)","$t0");
        _move("$ra","$t0");
        loadData("8($sp)","$t0");
        _move("$s3","$t0");
        emit("-","$sp","$sp","4");
        jump("jr","$ra");
    }
}



void scanfAction(char read[]){
    int addr;
    char swAddr[FELMSIZE];
    int tempType = 0;
    addr = lookUp(token,currentlevel);
    if(addr == -1){
        addr = lookUpGlobal(token,0);
        if(addr == -1){
            error(29);
            nextlineRead();
            return;
        }
        itoa(vTBL[addr].raddr * 4,swAddr,10);
        strcat(swAddr,"($s2)");
    }
    else{
        itoa(vTBL[addr].raddr * 4,swAddr,10);
        strcat(swAddr,"($s3)");
    }
    tempType = vTBL[addr].type;
    fTBL_length++;
    strcpy(fTBL[fTBL_length].op,"li");
    if(tempType == 1)
        strcpy(fTBL[fTBL_length].result,"5");
    else if(tempType == 2)
        strcpy(fTBL[fTBL_length].result,"12");
    strcpy(fTBL[fTBL_length].elm2," ");
    strcpy(fTBL[fTBL_length].elm1,"$v0");
    fTBL_length++;
    strcpy(fTBL[fTBL_length].op,"syscall");
    strcpy(fTBL[fTBL_length].result," ");
    strcpy(fTBL[fTBL_length].elm1," ");
    strcpy(fTBL[fTBL_length].elm2," ");
    fTBL_length++;
    strcpy(fTBL[fTBL_length].op,"sw");
    strcpy(fTBL[fTBL_length].result,swAddr);
    strcpy(fTBL[fTBL_length].elm2," ");
    strcpy(fTBL[fTBL_length].elm1,"$v0");
}

void printfAction(char write[],int signal){
    //title
    int stringNum;

    strcpy(title[0]," .data");
    char temp_num[10];
    if(signal == 0){
        title_length++;
        stringNum = addTitle(write);

        fTBL_length++;
        strcpy(fTBL[fTBL_length].op,"la");

        itoa(msgNum,temp_num,10);
        strcpy(fTBL[fTBL_length].result,"msg");
        strcat(fTBL[fTBL_length].result,temp_num);
        strcpy(fTBL[fTBL_length].elm1,"$a0");
        strcpy(fTBL[fTBL_length].elm2," ");
        fTBL_length++;
        strcpy(fTBL[fTBL_length].op,"li");
        strcpy(fTBL[fTBL_length].result,"4");
        strcpy(fTBL[fTBL_length].elm1,"$v0");
        strcpy(fTBL[fTBL_length].elm2," ");
        fTBL_length++;
        strcpy(fTBL[fTBL_length].op,"syscall");
        strcpy(fTBL[fTBL_length].result," ");
        strcpy(fTBL[fTBL_length].elm1," ");
        strcpy(fTBL[fTBL_length].elm2," ");
    }
    else{
        int tempType = 0;
        fTBL_length++;
        stringNum = lookUp(write,currentlevel);
        if(stringNum == -1){
            stringNum = lookUpGlobal(write,0);
            if(stringNum == -1){
                ;
            }
            else{
                itoa(vTBL[stringNum].raddr * 4,fTBL[fTBL_length].result,10);
                strcat(fTBL[fTBL_length].result,"($s2)");
                tempType = vTBL[stringNum].type;
            }
        }
        else{
            itoa(vTBL[stringNum].raddr * 4,fTBL[fTBL_length].result,10);
            strcat(fTBL[fTBL_length].result,"($s3)");
            tempType = vTBL[stringNum].type;
        }
        if(stringNum == -1){
            if(isNum(write) == 1)
                ;
            else{
                itoa(lookUpDTBL(write) * 4,fTBL[fTBL_length].result,10);
                strcat(fTBL[fTBL_length].result,"($s5)");
                tempType = expressType;
            }

        }

        if(isNum(write) == 1){
            tempType = 1;
            strcpy(fTBL[fTBL_length].op,"li");
            strcpy(fTBL[fTBL_length].elm1,"$a0");
            strcpy(fTBL[fTBL_length].elm2," ");
            strcpy(fTBL[fTBL_length].result,write);
        }
        else{
            strcpy(fTBL[fTBL_length].op,"lw");
            strcpy(fTBL[fTBL_length].elm1,"$a0");
            strcpy(fTBL[fTBL_length].elm2," ");
        }

        fTBL_length++;
        strcpy(fTBL[fTBL_length].op,"li");
        if(tempType == 1)
            strcpy(fTBL[fTBL_length].result,"1");
        else if(tempType == 2)
            strcpy(fTBL[fTBL_length].result,"11");
        strcpy(fTBL[fTBL_length].elm1,"$v0");
        strcpy(fTBL[fTBL_length].elm2," ");
        fTBL_length++;
        strcpy(fTBL[fTBL_length].op,"syscall");
        strcpy(fTBL[fTBL_length].result," ");
        strcpy(fTBL[fTBL_length].elm1," ");
        strcpy(fTBL[fTBL_length].elm2," ");
    }
}



void expressionTranslate(char elm[],char result[]){
    int vTBL_addr;
    int i;
    if(elm[0] == '@'){
        for(i = 0; i <= dTBL_length; i++){
            if(!strcmp(dTBL[i].name,elm)){
                itoa(i * 4,result,10);
                strcat(result,"($s5)");
                return;
            }
        }
    }
    else if(isNum(elm) == 1){
        strcpy(result,elm);
        return;
    }
    else{
        vTBL_addr = lookUp(elm,currentlevel);
        if(vTBL_addr == -1){
            vTBL_addr = lookUpGlobal(elm,0);
            if(vTBL_addr == -1){
                error(36);
                nextlineRead();
                strcpy(result,"error");
            }
            else{
                itoa(vTBL[vTBL_addr].raddr * 4,result,10);
                strcat(result,"($s2)");//返回全局变量
                return;
            }
        }
        else{
            itoa(vTBL[vTBL_addr].raddr * 4,result,10);
            strcat(result,"($s3)");
            return;
        }
    }
}
#endif // VALTABLE_H_INCLUDED














