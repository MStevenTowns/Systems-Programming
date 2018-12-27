#include "Set_Variable.h"

//begins linked list and inserts first variable
Variable *New_Variable(Variable *var, char *name, char *value)
{
	Variable *last = NULL;
	Variable *link;
	for(link = var; link != NULL; link = link->link) //find last variable
	last = link;

	if(last == NULL) //insert first variable
		last = var = (Variable*)malloc(sizeof(Variable));
	else 
		last = last->link = (Variable*)malloc(sizeof(Variable));

	if(last != NULL) //insert new variable
	{
		last->name = malloc(strlen(name)+1);

		if(last->name != NULL)
			strcpy(last->name, name);

		last->value = malloc(strlen(value)+1);

		if(last->value != NULL)
			strcpy(last->value, value);

		last->link = NULL;
	}

	return var;
} 

//removes variable from the list
Variable *Delete_Variable(Variable *var, Variable *item)
{
	Variable *before = NULL;
	Variable *link = NULL;
	Variable *after = item->link;

	for(link = var; link != NULL && link->link != item; link = link->link);
	before = link;

	free(item->name);
	free(item->value);
	free(item);

	if(before == NULL) //delete first variable
		var = after;

	else //delete any other variable
		before->link = after;

	return var;
} 

//changes variable
void Update_Var(Variable *item, char *value)
{
	item->value = realloc(item->value, strlen(value)+1);
	strcpy(item->value, value);
} 

//retrieves the variable 
//used to print out variables
Variable *Get_Var(Variable *var, char *name)
{
	Variable *link = NULL; 
	for(link = var; link != NULL && strcmp(link->name, name) != 0; link = link->link);
	return link;
} 

//sets the variable to a given name
Variable * Set_Var(Variable *var, char *name, char *value)
{
	Variable *link = Get_Var(var, name);

	if(link != NULL) 
	{
		if((*value) == '\0') 
			var = Delete_Variable(var, link);
		else 
			Update_Var(link, value);
	}
	else if((*value) != '\0')
		var = New_Variable(var, name, value);

	return var;
} 
