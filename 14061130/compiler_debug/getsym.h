#ifndef GETSYM_H_INCLUDED
#define GETSYM_H_INCLUDED

#define TOKEN_SIZE 200
#define NUMBER_OF_WORD 14
#define NUMBER_OF_WSYM 26
#define pTBLLENGTH 1024
struct paraTable
{
    int type; // -1左小括号，-2左中括号，-3左大括号
} ;
const char word[NUMBER_OF_WORD][20] = { "const","int","char","void","main","if","else","while","switch","case","default","scanf","printf","return" };
//保留字
const char wword[NUMBER_OF_WORD][20] = { "CONSTSYM","INTSYM","CHARSYM","VOIDSYM","MAINSYM","IFSYM","ELSESYM","WHILESYM","SWITCHSYM","CASESYM","DEFAULTSYM","SCANFSYM","PRINTFSYM","RETURNSYM" };
//保留字助记符
const char wsym[NUMBER_OF_WSYM][20] = { "ident","num","unsigned_num","word","plus","minus","mul","div","lss","lsseql","gtr","gtreql","becomes","eql","neql","lparan","rparan","lbrack","rbrack","comma","colon","semicolon","lcbrack","rcbrack","quatation","sig_quatation" };
//单词符号编码

struct paraTable pTBL[pTBLLENGTH] = {{0}}; //括号栈;
int pTBL_link = 0;//括号栈指针

FILE *in, *out;
char token[TOKEN_SIZE] = { 0 };
char lastToken[TOKEN_SIZE] = {0};
char symbol[TOKEN_SIZE] = { 0 };

void nextlineRead();                //跳小语句，一行
void nextstatementRead();           //跳整个函数
int getsym();
void clearTOKEN();
int reserve(char token[]);
char getch();
void ungets(char ch[]);
int getsym();
void nextstatementRead();
void ungets(char ch[]);
char getch();
void nextlineRead();
void clearTOKEN();
int reserve(char token[]);


//括号栈栈顶是link-1
void quaOutStack()
{
    if(pTBL[pTBL_link - 1].type == -3)
    {
        pTBL_link--;
        return;
    }
    else
    {
        pTBL_link--;
        while(pTBL[pTBL_link - 1].type == -3)
        {
            pTBL_link --;
        }
    }
}

void brackOutStack()
{
    if(pTBL[pTBL_link - 1].type == -2)
    {
        pTBL_link--;
        return;
    }
    else
    {
        error(7);
    }
}

void paranOutStack()
{
    if(pTBL[pTBL_link - 1].type == -1)
    {
        pTBL_link--;
        return;
    }
    else
    {
        error(5);
    }
}

void quaInStack()
{
    pTBL[pTBL_link].type = -3;
    if(pTBL[pTBL_link - 1].type == -1)
        error(5);
    else if(pTBL[pTBL_link - 1].type == -2)
        error(7);
    pTBL_link++;
}

void brackInStack()
{
    pTBL[pTBL_link].type = -2;
    pTBL_link++;
}

void paranInStack()
{
    pTBL[pTBL_link].type = -1;
    pTBL_link++;
}
//getsym.h
void nextstatementRead(){
    do{
        getsym();
        if(token[0] == '(')
            paranInStack();
        else if(token[0] == ')')
            paranOutStack();
        else if(token[0] == '[')
            brackInStack();
        else if(token[0] == ']')
            brackOutStack();
        else if(token[0] == '{')
            quaInStack();
        else if(token[0] == '}')
            quaOutStack();
    }
    while(strcmp(token,"int") && strcmp(token,"char") && strcmp(token,"void") && strcmp(token,""));

    if(strcmp(token,"{"))
        ungets(token);
}

void ungets(char ch[]){     //这个函数查一下对不对
    int i;
    for(i = strlen(ch) - 1; i != -1 ; i--){
        ungetc(ch[i],in);
    }
}

char getch(){
    return fgetc(in);
}

void nextlineRead(){ //这个查一下错没错
    char ch;
    int count;
    count = 0;
    do{
        ch = getch();
        count++;
        if(ch == '(')
            paranInStack();
        else if(ch == ')')
            paranOutStack();
        else if(ch == '[')
            brackInStack();
        else if(ch == ']')
            brackOutStack();
        else if(ch == '{')
            quaInStack();
        else if(ch == '}')
            quaOutStack();
    }while(ch != '\n' && ch != ';' && ch != '{' && ch != '}');
    token[0] = ch;
    token[1] = '\0';
    if(ch == '\n'){
        ungetc(ch,in);
    }
    else{
       //ungetc(ch,in);
    }


}

void clearTOKEN() {
	int i = 0;
	for (i = 0; i < TOKEN_SIZE; i++) {
		token[i] = '\0';
	}
	return;
}
int reserve(char token[]) {
	int i;
	char temp[TOKEN_SIZE] = {0};
	for (i = 0; i < strlen(token); i++)
		temp[i] = tolower(token[i]);

	for (i = 0; i < NUMBER_OF_WORD; i++) {
		if (!strcmp(word[i], temp))
			return i;
	}
	return -1;
}

int getsym() {
	int tsize, resultValue;		//token大小,resultValue保留字编号;
	char ch;
    strcpy(lastToken,token);
	//init
	clearTOKEN();
	tsize = 0;

	//start
	ch = getch();

	//if null
	if (ch == EOF) {
		return -1;
	}

	//avoid space
	while (ch == ' ' || ch == '\t' || ch == '\n') {
        if(ch == '\n')
            ll++;
		ch = getch();

	}

	//if null
	if (ch == EOF) {
		return -1;
	}

	//isLetter
	else if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_') {
		while ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_' || (ch >= '0' && ch <= '9')) {
            if(ch >= 'A' && ch <= 'Z'){
                ch = ch - 'A' + 'a';
            }
			token[tsize++] = ch;
			ch = getch();
		}
		//测试

        ungetc(ch, in);

		resultValue = reserve(token);
		if (resultValue == -1) {
			strcpy(symbol, "IDENTSYM");
		}
		else {
			strcpy(symbol, wword[resultValue]);
		}
	}

	//isdigit
	else if (ch >= '0' && ch <= '9') {
		if (ch == '0') {
			token[tsize++] = ch;
			ch = getch();
		}
        else{
            token[tsize++] = ch;
			ch = getch();
            while (ch >= '0' && ch <= '9') {
                token[tsize++] = ch;
                ch = getch();
            }
        }
		ungetc(ch, in);
        strcpy(symbol, "NUM");
	}
	//isColon
	else if (ch == ':') {
		token[tsize++] = ch;
		strcpy(symbol, "COLONSYM");
	}
	//isSemicolon
	else if (ch == ';') {
		token[tsize++] = ch;
		strcpy(symbol, "SEMICOLONSYM");
	}
	//isComma
	else if (ch == ',') {
		token[tsize++] = ch;
		strcpy(symbol, "COMMASYM");
	}
	//isMul
	else if (ch == '*') {
		token[tsize++] = ch;
		strcpy(symbol, "MULSYM");
	}
	//isDiv
	else if (ch == '/') {
		token[tsize++] = ch;
		strcpy(symbol, "DIVSYM");
	}
	//isLss/isLsseql
	else if (ch == '<') {
		token[tsize++] = ch;
		ch = getch();
		if (ch == '=') {
			token[tsize++] = ch;
			strcpy(symbol, "LSSEQLSYM");
		}
		else{
            strcpy(symbol, "LSSSYM");
            ungetc(ch,in);
		}

	}
	//isGtr/isGtreql
	else if (ch == '>') {
		token[tsize++] = ch;
		ch = getch();
		if (ch == '=') {
			token[tsize++] = ch;
			strcpy(symbol, "GRTEQLSYM");
		}
		else{
            strcpy(symbol, "GRTSYM");
            ungetc(ch,in);
		}

	}
	//isEql/isBecomes
	else if (ch == '=') {
		token[tsize++] = ch;
		ch = getch();
		if (ch == '=') {
			token[tsize++] = ch;
			strcpy(symbol, "EQLSYM");
		}
		else{
            strcpy(symbol, "BECOMESSYM");
            ungetc(ch,in);
		}

	}
	//isNeq
	else if(ch == '!'){
        token[tsize++] = ch;
        ch = getch();
        if(ch == '='){
            token[tsize++] = ch;
            strcpy(symbol,"NEQSYM");
        }
        else{
            ungetc(ch,in);
            error(1);
        }
	}
	//isLparan
	else if (ch == '(') {
		token[tsize++] = ch;
		strcpy(symbol, "LPARANSYM");
	}
	//isRparan
	else if (ch == ')') {
		token[tsize++] = ch;
		strcpy(symbol, "RPARANSYM");
	}
	//isLbrack
	else if (ch == '[') {
		token[tsize++] = ch;
		strcpy(symbol, "LBRACKSYM");
	}
	//isRbrack
	else if (ch == ']') {
		token[tsize++] = ch;
		strcpy(symbol, "RBRACKSYM");
	}
	//isLcbrack
	else if (ch == '{') {
		token[tsize++] = ch;
		strcpy(symbol, "LCBRACKSYM");
	}
	//isRcbrack
	else if (ch == '}') {
		token[tsize++] = ch;
		strcpy(symbol, "RCBRACKSYM");
	}
	//isPlus
	else if (ch == '+') {
		token[tsize++] = ch;
		strcpy(symbol, "PLUS");
	}
	//isMinus
	else if (ch == '-') {
		token[tsize++] = ch;
		strcpy(symbol, "MINUS");
	}
	//isQuatation
	else if (ch == '"') {
		int temp = 0;
		int temp1 = 0;
		token[tsize++] = ch;
		ch = getch();
		/*
		if (ch == '"') {
			strcpy(symbol, "ERROR_QUATATION");
			temp1 = -1;
			return 1;
		}
        */

		while ((ch != '"') && (tsize != TOKEN_SIZE) && (ch != '\n')) {
			if ((ch < ' ') || (ch > '~') || (ch == '"')) {
				strcpy(symbol, "ERROR_UNKNOW_LETTER_STRING");
				temp = -1;
			}
			token[tsize++] = ch;
			ch = getch();
		}
        //token[tsize++] = ch;


		if(temp == -1){
            error(1);
            strcpy(symbol, "ERROR_UNEXPECTED_WORD");
            return 1;
		}

		if (ch == '\n') {
			strcpy(symbol, "ERROR_INCOMPLETE");
			ungetc(ch, in);
			error(2);//2号错误
			return 1;
		}

		token[tsize++] = ch;
		if (temp != -1 && temp1 != -1)
			strcpy(symbol, "STRING");

		if (tsize == TOKEN_SIZE){
			strcpy(symbol, "ERROR_OVERFLOW");
			error(3);
			return 1;
		}


	}
	else if (ch == 39) {
		int temp = 0; //单引号里面内容大于一个
		int temp1 = 0; //单引号里面的内容不正确
		token[tsize++] = ch;
		ch = getch();
		if(!(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '_' || (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))) {
			strcpy(symbol, "ERROR_SIG_QUATATION");
			temp1 = -1;
		}
		while (ch != 39 && ch != '\n') {
			token[tsize++] = ch;
			ch = getch();
			temp++;
		}

		if (ch == '\n') {
			strcpy(symbol, "ERROR_INCOMPLETE");
			ungetc(ch, in);
			error(2);
			return 1;
		}

		//后面的引号读进去
		token[tsize++] = ch;
		if (temp != 1 || temp1 == -1){
			strcpy(symbol, "ERROR_SIG_QUATATION");
            error(4);
            return 1;
		}

		else{
            strcpy(symbol, "SIG_QUATATION");
		}

	}
	else {
		token[0] = ' ';
		strcpy(symbol, "ERROR_UNEXPECTED");
	}
	//要不要把引号单独抽出来看，取决于下面的语法分析，到时可以再修改
	return 1;
}

#endif // GETSYM_H_INCLUDED
