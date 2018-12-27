#ifndef VARIABLE_TS_H
#define VARIABLE_TS_H
#include <stdlib.h>
#include <string.h>

//creates linked list for variables
struct variable
{
	char *name;
	char *value;
	struct variable *link;
};
typedef struct variable Variable;

Variable *New_Variable(Variable *var, char *name, char *value);
Variable *Delete_Variable(Variable *var, Variable *item);
void Update_Var(Variable *item, char *value);
Variable *Set_Var(Variable *var, char *name, char *value);
Variable *Get_Var(Variable *var, char *name);

#endif 
