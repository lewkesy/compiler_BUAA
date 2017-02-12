#ifndef OPTIMIZE_H_INCLUDED
#define OPTIMIZE_H_INCLUDED
#define NODESIZE 100
struct optimize{
    int num;
    char val[FELMSIZE];         //例如t0,a0,1,#1在节点里面的之类
    char node[NODESIZE][FTABLESIZE];    //例如a,b,@_1之类
    int fnode[NODESIZE];
    int lnode;
    int rnode;
    int nodeNum;
    int fnodeNum;
    int ignored;
    int finished;
} ;

struct counting{
    char elm[FELMSIZE];
    int times;
};

struct fTable oTBL[FTABLESIZE];
struct fTable tTBL[FTABLESIZE];             //寄存器最终翻译版本存储
struct fTable antiTBL[FTABLESIZE];          //用来保存逆序的oTBL
struct fTable DagAnalysis[FTABLESIZE];      //用来保存当前需要被分析的连续运算
struct optimize DagArray[200];       //用来保存DAG图的节点

int oTBL_length = -1;
int tTBL_length = -1;
int anti_length = -1;
int DagAnalysis_length = -1;
int DagArray_length = -1;
int init_reg;
int specialArrayNum = -1;                   //用来解决[@_2]a之类的数组

void return2OTBL();
void startDagAnalysis();
void deleteNode(char node[]);
void translate(int tTBL_length,char _reg[][FELMSIZE]);
void beginningOfTranslation();

void initialize(){


    DagAnalysis_length = -1;
    DagArray_length = -1;
    anti_length = -1;
    specialArrayNum = -1;
}
////////////////////////////////////??????????????????????????????????//
void addOTBL(int i){
    oTBL_length ++;
    strcpy(oTBL[oTBL_length].op,fTBL[i].op);
    strcpy(oTBL[oTBL_length].result,fTBL[i].result);
    strcpy(oTBL[oTBL_length].elm1,fTBL[i].elm1);
    strcpy(oTBL[oTBL_length].elm2,fTBL[i].elm2);
}

void origin(char node[]){
    int i;
    if(node[0] == '[' && !(node[1] >= '0' && node[1] <= '9')){
        for(i = strlen(node) - 1; i != -1 && node[i] != '$'; i--){
            ;
        }
        if(i != -1){
            node[i] = '\0';
        }
    }
}

void addOTBL1(char op[],char result[],char elm1[],char elm2[]){
    anti_length++;
    origin(result);
    origin(elm1);
    origin(elm2);
    strcpy(antiTBL[anti_length].op,op);
    strcpy(antiTBL[anti_length].result,result);
    strcpy(antiTBL[anti_length].elm1,elm1);
    strcpy(antiTBL[anti_length].elm2,elm2);
}

void addToTBL(){
    int i;
    for(i = anti_length; i != -1; i--){
        oTBL_length++;
        strcpy(oTBL[oTBL_length].op,antiTBL[i].op);
        strcpy(oTBL[oTBL_length].result ,antiTBL[i].result);
        strcpy(oTBL[oTBL_length].elm1,antiTBL[i].elm1);
        strcpy(oTBL[oTBL_length].elm2,antiTBL[i].elm2);
    }
}

int lookUpDag(char val[]){
    int i,j;
    if(val[0] == '[' && !(val[1] >= '0' && val[1] <= '9')){
        return -2;
    }

    for(i = 0; i <= DagArray_length; i++){      //遍历所有已经建立的节点
        for(j = 0; j < DagArray[i].nodeNum; j++){       //遍历每个节点的node内容
            if(!strcmp(DagArray[i].node[j],val)){
                return i;
            }
        }
    }
    return -1;
}

int lookUpMidDag(char op[],int left,int right){
    int i;
    for(i = 0; i <= DagArray_length; i++){      //遍历所有已经建立的节点
        if(!strcmp(op,DagArray[i].val)&& DagArray[i].lnode == left && DagArray[i].rnode == right){
            return i;        }
    }
    return -1;
}

void createTempVTBL(int num){
    char nodeName[FELMSIZE];
    char number[5];
    init_reg++;
    dTBL_length++;
    itoa(init_reg,number,10);
    nodeName[0] = '@';
    nodeName[1] = '_';
    nodeName[2] = '\0';
    strcat(nodeName,number);

    strcpy(DagArray[num].node[0],nodeName);
    DagArray[num].nodeNum++;
    DagArray[num].ignored = 1;
    strcpy(dTBL[init_reg].name,nodeName);
    dTBL[init_reg].val = dTBL_length;
}

void addFNode(int node,int fNode){
    int fnodeNum;
    fnodeNum = DagArray[node].fnodeNum;
    DagArray[node].fnode[fnodeNum] = fNode;
    DagArray[node].fnodeNum++;
}

void addNode(int num,char node[]){
    int nodeNum;
    nodeNum = DagArray[num].nodeNum;
    deleteNode(node);
    strcpy(DagArray[num].node[nodeNum],node);
    DagArray[num].nodeNum++;
}

int ifArraySame(char tempNodeChar[],char tempChar[]){
    int i;
    for(i = 0; i < strlen(tempNodeChar) && tempNodeChar[i] != '$'; i++){
        if(tempNodeChar[i] != tempChar[i]){
            return -1;
        }
    }
    return 1;
}

void deleteNode(char node[]){
    int i,j,k;
    for(i = 0; i <= DagArray_length; i++){      //遍历所有已经建立的节点
        for(j = 0; j < DagArray[i].nodeNum; j++){       //遍历每个节点的node内容
            if(!strcmp(DagArray[i].node[j],node) ||
               (node[0] == '[' && DagArray[i].node[j][0] == '[' && ifArraySame(DagArray[i].node[j],node) == 1)){
                for(k = j;k < DagArray[i].nodeNum - 1; k++){//删除当前重复node
                    strcpy(DagArray[i].node[k],DagArray[i].node[k + 1]);
                }
                DagArray[i].nodeNum--;

                if(DagArray[i].nodeNum == 1){
                    DagArray[i].ignored = 1;
                }
                //新建备份节点
                if(DagArray[i].nodeNum == 0){
                    createTempVTBL(i);
                }
                continue;
            }
        }
    }
}

void deleteFNode(int fnode,int node){
    int i,j;
    for(i = 0; i < DagArray[node].fnodeNum; i++){
        if(DagArray[node].fnode[i] == fnode){
           for(j = i; j < DagArray[node].fnodeNum - 1;j++){
                DagArray[node].fnode[j] = DagArray[node].fnode[j+1];
           }
           DagArray[node].fnodeNum--;
           return;
        }
    }
}

void startDagAnalysis(){
    int leftNum;
    int rightNum;
    int lookUpResult;
    int i;
    int tempLength;
    char tempArraylength[5];
    for(i = 0; i <= DagAnalysis_length; i++){
        //左节点
        lookUpResult = lookUpDag(DagAnalysis[i].elm1);
        if(lookUpResult < 0){
            //向DagArray中插入新的元素,这里注意一下，明天加上对数组的判断，形如[2]a的数组通过，别的不可以通过
            DagArray_length++;
            DagArray[DagArray_length].nodeNum = 0;
            DagArray[DagArray_length].fnodeNum = 0;
            DagArray[DagArray_length].num = DagArray_length;
            DagArray[DagArray_length].ignored = 0;
            DagArray[DagArray_length].lnode = -1;
            DagArray[DagArray_length].rnode = -1;
            DagArray[DagArray_length].finished = 0;
            strcpy(DagArray[DagArray_length].val,DagAnalysis[i].elm1);
            if(lookUpResult == -2){
                tempLength = strlen(DagArray[i].val);
                DagArray[i].val[tempLength] = '$';
                DagArray[i].val[tempLength + 1] = '\0';
                itoa(++specialArrayNum,tempArraylength,10);
                strcat(DagArray[DagArray_length].val,tempArraylength);
            }
            addNode(DagArray_length,DagAnalysis[i].elm1);

            leftNum = DagArray_length;
        }
        else{
            leftNum = lookUpResult;
        }


        //中间节点，等号特殊规则
        if(DagAnalysis[i].op[0] == '='){
            //防止出现 a = a 这种没有意义的情况
            char result[FELMSIZE];
            strcpy(result,DagAnalysis[i].result);
            if(!strcmp(result,DagAnalysis[i].elm1)){
                continue;
            }
            else{
                lookUpResult = lookUpDag(result);
                if(lookUpResult == -2){
                    tempLength = strlen(result);
                    result[tempLength] = '$';
                    result[tempLength + 1] = '\0';
                    itoa(++specialArrayNum,tempArraylength,10);
                    strcat(result,tempArraylength);
                }
                //删除节点，这里需要删除所有情况所以不用result
                deleteNode(DagAnalysis[i].result);
                //这里添加节点用result因为防止数组问题
                addNode(leftNum,result);
            }
        }
        //右节点
        else{
            lookUpResult = lookUpDag(DagAnalysis[i].elm2);
            if(lookUpResult == -1){
                //向DagArray中插入新的元素
                DagArray_length++;
                DagArray[DagArray_length].nodeNum = 0;
                DagArray[DagArray_length].fnodeNum = 0;
                DagArray[DagArray_length].ignored = 0;
                DagArray[DagArray_length].lnode = -1;
                DagArray[DagArray_length].rnode = -1;
                DagArray[DagArray_length].finished = 0;
                DagArray[DagArray_length].num = DagArray_length;
                strcpy(DagArray[DagArray_length].val,DagAnalysis[i].elm2);
                if(lookUpResult == -2){
                    tempLength = strlen(DagArray[i].val);
                    DagArray[i].val[tempLength] = '$';
                    DagArray[i].val[tempLength + 1] = '\0';
                    itoa(++specialArrayNum,tempArraylength,10);
                    strcat(DagArray[DagArray_length].val,tempArraylength);
                }
                addNode(DagArray_length,DagAnalysis[i].elm2);
                rightNum = DagArray_length;
            }
            else{
                rightNum = lookUpResult;
            }

            lookUpResult = lookUpMidDag(DagAnalysis[i].op,leftNum,rightNum);
            if(lookUpResult != -1){
                addNode(lookUpResult,DagAnalysis[i].result);
            }
            else{
                //向DagArray中插入新的元素
                DagArray_length++;
                DagArray[DagArray_length].nodeNum = 0;
                DagArray[DagArray_length].fnodeNum = 0;
                DagArray[DagArray_length].ignored = 0;
                DagArray[DagArray_length].lnode = -1;
                DagArray[DagArray_length].rnode = -1;
                DagArray[DagArray_length].finished = 0;
                DagArray[DagArray_length].num = DagArray_length;
                strcpy(DagArray[DagArray_length].val,DagAnalysis[i].op);
                DagArray[DagArray_length].lnode = leftNum;
                DagArray[DagArray_length].rnode = rightNum;
                addFNode(leftNum,DagArray_length);
                addFNode(rightNum,DagArray_length);
                addNode(DagArray_length,DagAnalysis[i].result);
            }
        }
    }
    return;
}

int ifVal(char node[][FTABLESIZE],int nodeNum){
    int i;
    int sum = 0;
    if(node[0][0] == '@'){
        for(i = 1;i < nodeNum; i++){
            if(node[i][0] != '@'){
                sum ++;
            }
        }
    }
    if(sum != 0){
        return sum;
    }
    return -1;
}

void findLRNode(char leftNode[],char rightNode[],int lnode,int rnode){


    /*strcpy(leftNode,DagArray[lnode].node[0]);
    strcpy(rightNode,DagArray[rnode].node[0]);*/
    if(ifVal(DagArray[lnode].node,DagArray[lnode].nodeNum) == 1){
        strcpy(leftNode,DagArray[lnode].node[1]);
    }
    else{
        strcpy(leftNode,DagArray[lnode].node[0]);
    }

    if(ifVal(DagArray[rnode].node,DagArray[rnode].nodeNum) == 1){
        strcpy(rightNode,DagArray[rnode].node[1]);
    }
    else{
        strcpy(rightNode,DagArray[rnode].node[0]);
    }
}

void return2OTBL(){
    int i;
    int j;
    int k;
    char leftNode[FELMSIZE];
    char rightNode[FELMSIZE];
    int restNode;
    int searchStart;                //找当前节点需要赋值的节点名称

    restNode = DagArray_length;
    i = -1;
    while(restNode > -1){

        if(i == -1){
            for(k = DagArray_length; k != -1; k--){
                //如果找到需要进OTBL的点
                if(DagArray[k].finished != 1 && DagArray[k].fnodeNum == 0){
                    i = k;
                    break;
                }
            }
        }
        else{
            //如果val是算符，也就是说是中间节点
                if((isNum(DagArray[i].val) != 1) &&
                   (DagArray[i].val[0] == '+' ||
                    DagArray[i].val[0] == '-' ||
                    DagArray[i].val[0] == '*' ||
                    DagArray[i].val[0] == '/')){
                    //如果临时变量后面没有非临时变量
                    findLRNode(leftNode,rightNode,DagArray[i].lnode,DagArray[i].rnode);
                    //没有非临时变量
                    if(ifVal(DagArray[i].node,DagArray[i].nodeNum) == -1){
                        addOTBL1(DagArray[i].val,DagArray[i].node[0],leftNode,rightNode);
                    }
                    else{
                        for(j = 0; j < DagArray[i].nodeNum; j++){
                            if(DagArray[i].node[j][0] != '@')
                                addOTBL1(DagArray[i].val,DagArray[i].node[j],leftNode,rightNode);
                        }
                    }
                    restNode--;
                    //删除子节点的父节点信息
                    deleteFNode(DagArray[i].num,DagArray[i].lnode);
                    deleteFNode(DagArray[i].num,DagArray[i].rnode);

                    DagArray[i].finished = 1;
                    if(DagArray[DagArray[i].lnode].fnodeNum == 0)
                        i = DagArray[i].lnode;
                    else{
                        i = -1;
                    }
                }
                else if(DagArray[i].fnodeNum == 0){
                    //子节点
                    if(DagArray[i].nodeNum == 1 && strcmp(DagArray[i].val,DagArray[i].node[0])){
                        addOTBL1("=",DagArray[i].node[0],DagArray[i].val," ");
                    }
                    else if(DagArray[i].nodeNum != 1){
                        for(j = 1 ; j < DagArray[i].nodeNum; j++){
                            addOTBL1("=",DagArray[i].node[j],DagArray[i].val," ");
                        }
                    }
                    DagArray[i].finished = 1;
                    i = DagArray[i].lnode;
                    restNode--;
                }
                else{
                    i = -1;
                }
        }
    }
    if(restNode != -1){
            printf("error\n");
        }
    addToTBL();
}

void DagOptimize(){
    int i = -1;
    int temp;
    init_reg = tempRegNum;
    temp = 0;
    while(i != fTBL_length + 1){
        i++;
        //find the first section
        if(fTBL[i].op[strlen(fTBL[i].op) - 1] != ':'){
            if(i == fTBL_length + 1)
                break;

            addOTBL(i);
            continue;
        }
        else{

            addOTBL(i);//把label存到oTBL里面，下面是一个块里面的内容
            i++;
            while(!(!strcmp(fTBL[i].op,"j") || !strcmp(fTBL[i].op,"jal") || !strcmp(fTBL[i].op,"jr"))) {
                if(i == fTBL_length + 1)
                    break;
                //如果不是四则运算，直接放进oTBL
                if( fTBL[i].op[0] != '=' &&
                    fTBL[i].op[0] != '+' &&
                    fTBL[i].op[0] != '-' &&
                    fTBL[i].op[0] != '*' &&
                    fTBL[i].op[0] != '/'){
                    addOTBL(i);
                    i++;
                }
                else if(fTBL[i].elm1[0] == '$'||
                        fTBL[i].elm2[0] == '$'||
                        fTBL[i].result[0] == '$'){
                    addOTBL(i);
                    i++;
                }
                else{
                    //如果读进来了一个四则运算，则开始进入DAG图分析过程
                    while(  fTBL[i].op[0] == '=' ||
                            fTBL[i].op[0] == '+' ||
                            fTBL[i].op[0] == '-' ||
                            fTBL[i].op[0] == '*' ||
                            fTBL[i].op[0] == '/'){
                        //这里判断是不是带参数的数组
                        if( (fTBL[i].op[0] == '[' && (fTBL[i].op[1] < '0' || fTBL[i].op[1] > '9')) ||
                            (fTBL[i].result[0] == '[' && (fTBL[i].result[1] < '0' || fTBL[i].result[1] > '9')) ||
                            (fTBL[i].elm1[0] == '[' && (fTBL[i].elm1[1] < '0' || fTBL[i].elm1[1] > '9')) ||
                            (fTBL[i].elm2[0] == '[' && (fTBL[i].elm2[1] < '0' || fTBL[i].elm2[1] > '9'))){
                                temp = 1;
                                break;
                            }

                        DagAnalysis_length++;
                        strcpy(DagAnalysis[DagAnalysis_length].op,fTBL[i].op);
                        strcpy(DagAnalysis[DagAnalysis_length].elm1,fTBL[i].elm1);
                        strcpy(DagAnalysis[DagAnalysis_length].elm2,fTBL[i].elm2);
                        strcpy(DagAnalysis[DagAnalysis_length].result,fTBL[i].result);
                        i++;

                        if( fTBL[i].elm1[0] == '$'||
                            fTBL[i].elm2[0] == '$'||
                            fTBL[i].result[0] == '$'){
                            break;
                        }
                    }
                        startDagAnalysis();
                        return2OTBL();
                        initialize();

                    if(temp == 1){
                        addOTBL(i);
                        i++;
                        temp = 0;
                    }

                    //need clearFunc
                }
            }
            if(!strcmp(fTBL[i].op,"j") || !strcmp(fTBL[i].op,"jal") || !strcmp(fTBL[i].op,"jr")){
                addOTBL(i);
                //i++;
            }
        }
    }

}

void peephole(){
    int i,j,num,sum;
    sum = 0;
    for(i = 0; i <= oTBL_length; i++){
        if(!strcmp(oTBL[i].op,"+") && !strcmp(oTBL[i].elm1,"$sp") && !strcmp(oTBL[i].result,"$sp")){
            j = i;
            num = 0;
            while(!strcmp(oTBL[j].elm1,"$sp") && !strcmp(oTBL[j].result,"$sp")){
                num += atoi(oTBL[j].elm2);
                j++;
            }
            strcpy(oTBL[sum].op,"+");
            strcpy(oTBL[sum].result,"$sp");
            strcpy(oTBL[sum].elm1,"$sp");
            itoa(num,oTBL[sum].elm2,10);
            i = j - 1;
            sum++;
        }
        else{
            strcpy(oTBL[sum].op,oTBL[i].op);
            strcpy(oTBL[sum].result,oTBL[i].result);
            strcpy(oTBL[sum].elm1,oTBL[i].elm1);
            strcpy(oTBL[sum].elm2,oTBL[i].elm2);
            sum++;
        }
    }
    oTBL_length = sum - 1;
}

void countingAnalysis(){
    struct counting counting[100];
    int counting_length = -1;
    char reg[3][FELMSIZE];
    int i;
    int j;
    int temp;
    int max;
    char tempChar[FELMSIZE];
    //initial
    temp = 0;
    for(i = 0; i < 10; i++){
        counting[i].times = 0;
    }

    for(i = 0; i <= tTBL_length; i++){
        //elm1
        if(tTBL[i].elm1[0] != '$' && tTBL[i].elm1[0] != ' ' && tTBL[i].elm1[0] != '\t' &&
           (tTBL[i].op[0] == '+' || tTBL[i].op[0] == '-' || tTBL[i].op[0] == '*' || tTBL[i].op[0] == '/' || tTBL[i].op[0] == '=')&&
           (tTBL[i].elm1[0] < '0' || tTBL[i].elm1[0] > '9') &&
           (tTBL[i].elm1[0] != '+' && tTBL[i].elm1[0] != '-') &&
            tTBL[i].elm1[0] != '#'){
            for(j = 0; j <= counting_length ;j++){
                if(!strcmp(counting[j].elm,tTBL[i].elm1)){
                    counting[j].times ++;
                    temp = 1;
                    break;
                }
            }
            if(temp != 1){
                ++counting_length;
                counting[counting_length].times = 1;
                strcpy(counting[counting_length].elm,tTBL[i].elm1);
            }
        }
        temp = 0;

        //elm2
        if(tTBL[i].elm2[0] != '$' && tTBL[i].elm2[0] != ' ' && tTBL[i].elm2[0] != '\t' &&
            (tTBL[i].op[0] == '+' || tTBL[i].op[0] == '-' || tTBL[i].op[0] == '*' || tTBL[i].op[0] == '/' || tTBL[i].op[0] == '=')&&
            (tTBL[i].elm2[0] < '0' || tTBL[i].elm2[0] > '9') &&
            (tTBL[i].elm2[0] != '+' && tTBL[i].elm2[0] != '-') &&
             tTBL[i].elm2[0] != '#'){
            for(j = 0; j <= counting_length ;j++){
                if(!strcmp(counting[j].elm,tTBL[i].elm2)){
                    counting[j].times ++;
                    temp = 1;
                    break;
                }
            }
            if(temp != 1){
                ++counting_length;
                counting[counting_length].times = 1;
                strcpy(counting[counting_length].elm,tTBL[i].elm2);
            }
        }
        temp = 0;
    }

    temp = -1;
    max = 0;
    for(j = 0;j < 3; j++){
        strcpy(tempChar,"null");
        for(i = 0; i <= counting_length;i++){
            if(counting[i].times > max){
                max = counting[i].times;
                strcpy(tempChar,counting[i].elm);
                temp = i;
            }
        }
        strcpy(reg[j],tempChar);
        counting[temp].times = -1;
        max = 0;
    }
    translate(tTBL_length,reg);
}

void countingReg(){
    int i;            //i用来计数当前遍历oTBL读到的位置，j为当前oTBL的位置
    int temp;
    i = 0;
    temp = 0;
    while(i != oTBL_length + 1){

        if(oTBL[i].op[strlen(oTBL[i].op) - 1] != ':'){
            tTBL_length++;
            strcpy(tTBL[tTBL_length].op,oTBL[i].op);
            strcpy(tTBL[tTBL_length].result,oTBL[i].result);
            strcpy(tTBL[tTBL_length].elm1,oTBL[i].elm1);
            strcpy(tTBL[tTBL_length].elm2,oTBL[i].elm2);
            i++;
            continue;
        }
        else{
            //do not need to deal with label
            if(temp == 0){
                countingAnalysis();
                temp++;
            }


            tTBL_length = -1;//initial
            do{

                tTBL_length++;
                strcpy(tTBL[tTBL_length].op,oTBL[i].op);
                strcpy(tTBL[tTBL_length].result,oTBL[i].result);
                strcpy(tTBL[tTBL_length].elm1,oTBL[i].elm1);
                strcpy(tTBL[tTBL_length].elm2,oTBL[i].elm2);
                i++;
            }while(i != oTBL_length + 1 && (
                      (oTBL[i].op[0] == 'l' &&
                       oTBL[i].op[1] == 'a' &&
                       oTBL[i].op[2] == 'b' &&
                       oTBL[i].op[3] == 'e' &&
                       oTBL[i].op[4] == 'l') || !(oTBL[i].op[strlen(oTBL[i].op) - 1] == ':')));

            countingAnalysis();
            tTBL_length = -1;
        }
    }
}


void startOptimize(){
    DagOptimize();
    peephole();
    beginningOfTranslation();
    countingReg();
}
#endif // OPTIMIZE_H_INCLUDED
