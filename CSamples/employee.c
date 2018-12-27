#include <stdio.h>

/* User defined types */

enum deptcode {sales,personnel,packing,engineering};

typedef enum deptcode DEPT;

struct person {
  int age, salary;
  DEPT department;
  char name[12];
  char address[6][20];
};

typedef struct person EMPLOYEE;

void read_line(char Str[]) {
  int i = 0;   char next;
  while ((next=getchar())!='\n') {
    Str[i] = next;
    i++;
  }
  Str[i] = 0;    /* Set the null char at the end */
}

void print_employee(EMPLOYEE Emp) {
  int i;
  printf(" %d %d %d\n",Emp.age,Emp.salary,Emp.department);
  printf("%s\n",Emp.name);
  for (i=0;i<=5;i++) printf("%s\n",Emp.address[i]);
}

int main () {
  EMPLOYEE This_Employee;
  int i;
  printf("enter age\n");
  scanf("%d",&This_Employee.age);
  printf("enter salary\n");
  scanf("%d",&This_Employee.salary);
  printf("enter dept name\n");
  scanf("%d\n",&This_Employee.department);
  printf("enter employee name\n");
  read_line(This_Employee.name);
  printf("enter employee address\n");
  for (i=0; i<=5; i++) read_line(This_Employee.address[i]);
  print_employee(This_Employee);
}
