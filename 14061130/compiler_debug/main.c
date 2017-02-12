#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "error.h"
#include "getsym.h"
#include "valTable.h"
#include "statement.h"
#include "optimize.h"
#include "translate.h"

//$s0 == $rr
//$amount == $s1
//复制当前栈底指针$s2
//$sp复制$s3
//函数返回值寄存$s4
//临时数据表地址$s5

int main() {
    int i;
    char inputFile[1024];
    printf("Input the direction of the test code:\n");
    //gets(inputFile);
	in = fopen("1.txt", "r");

    FILE *vTBLFile,*fTBLFile,*oTBLFile,*mStackFile;

    vTBLFile = fopen("vTBL.txt","w");
    fTBLFile = fopen("fTBL.txt","w");
    oTBLFile = fopen("oTBL.txt","w");
    mStackFile = fopen("mips.txt","w");
    i = getsym();
    while(i != -1){
        statement();
        if(!strcmp(token,"}")){
            if(currentType == 0 && returnNeed != 0)
                returnAction();
            else if(currentType != 0 && returnNeed != 0){
                error(30);
            }
        }
        i = getsym();
    }



    for(i = 0;i < fTBL_length + 1; i++){
        fprintf(fTBLFile,"%s",fTBL[i].op);
        fprintf(fTBLFile,"\t");
        fprintf(fTBLFile,"%s",fTBL[i].result);
        fprintf(fTBLFile,"\t");
        fprintf(fTBLFile,"%s",fTBL[i].elm1);
        fprintf(fTBLFile,"\t");
        fprintf(fTBLFile,"%s",fTBL[i].elm2);
        fprintf(fTBLFile,"\n");
    }

    startOptimize();
    for(i = 0;i < oTBL_length + 1; i++){
        fprintf(oTBLFile,"%s",oTBL[i].op);
        fprintf(oTBLFile,"\t");
        fprintf(oTBLFile,"%s",oTBL[i].result);
        fprintf(oTBLFile,"\t");
        fprintf(oTBLFile,"%s",oTBL[i].elm1);
        fprintf(oTBLFile,"\t");
        fprintf(oTBLFile,"%s",oTBL[i].elm2);
        fprintf(oTBLFile,"\n");
    }

    //translate();
    for(i = 0; i <= title_length + 1; i++){
        fprintf(mStackFile,"%s",title[i]);
        fprintf(mStackFile,"\n");
    }
    fprintf(mStackFile,".text\n");
    for(i = 0;i < mStack_length + 1; i++){
        fprintf(mStackFile,"%s ",mStack[i].op);
        fprintf(mStackFile,"%s",mStack[i].elm1);
        if(mStack[i].elm1[0] != ' ' && mStack[i].elm2[0] != ' ')
            fprintf(mStackFile,",");
        fprintf(mStackFile,"%s",mStack[i].elm2);
        if(mStack[i].result[0] != ' ')
            fprintf(mStackFile,",");
        fprintf(mStackFile,"%s",mStack[i].result);
        fprintf(mStackFile,"\n");
    }


	return 0;
}





