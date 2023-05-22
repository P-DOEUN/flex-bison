/*
 * Declarations for a calculator fb3-1
 */
 /* interface to the lexer */

#define NHASH 9997


extern int yylineno; /* from lexer */


void yyerror(char* s, ...);


enum bifs { B_sqrt, B_exp, B_log, B_print }; ////////B_sqrt = 1,


/* nodes in the abstract syntax tree */
struct ast {
	int nodetype;
	struct ast* l;
	struct ast* r;
};
struct numval {
	int nodetype;   /* type K for constant */
	double number;
};






struct fncall {
	int nodetype;
	struct ast* l;
	int functype; ////enum bifs functype; 

};


struct symbol {
	char* name;
	//int value; ////double value;
	double value;
	struct ast* func;
	//struct ast *syms;  ////struct symlist *syms;
	struct symlist* syms;
};
////struct symbol symtab[NHASH]; 
////struct symbol *lookup(char*);


struct ufncall {
	int nodetype;
	struct ast* l;
	struct symbol* s;
};


struct symref {
	int nodetype;
	struct symbol* s;
};


struct symasgn {
	int nodetype;
	struct symbol* s;
	struct ast* v;
};


struct flow {
	int nodetype;
	struct ast* cond;
	struct ast* tl;
	struct ast* el;
};


struct symlist {
	struct symbol* sym;
	struct symlist* next;
};

static unsigned symhash(char*);

struct symbol* lookup(char* sym);




/* build an AST */
struct ast* newast(int nodetype, struct ast* l, struct ast* r);
struct ast* newnum(double d);





struct ast* newcmp(int cmptype, struct ast* l, struct ast* r);

struct ast* newfunc(int functype, struct ast* l);

struct ast* newcall(struct symbol* s, struct ast* l);

struct ast* newref(struct symbol* s);

struct ast* newasgn(struct symbol* s, struct ast* v);

struct ast* newflow(int nodetype, struct ast* cond, struct ast* tl, struct ast* el);////struct ast *tr);

struct symlist* newsymlist(struct symbol* sym, struct symlist* next);

void symlistfree(struct symlist* sl);

static double callbuiltin(struct fncall* f);

void dodef(struct symbol* name, struct symlist* syms, struct ast* func); ////struct ast *stmts);





/* evaluate an AST */
double eval(struct ast*);
/* delete and free an AST */
void treefree(struct ast*);