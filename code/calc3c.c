#include <stdio.h>
#include <stdbool.h>
#include "calc3.h"
#include "y.tab.h"

#include "extras/factorial.h"
#include "extras/gcd.h"
#include "extras/lntwo.h"

static int lbl;

int ex(nodeType *p)
{
    int lbl1, lbl2;
    int index[2] = {0};

    if (!p)
        return 0;
    switch (p->type)
    {
    case typeCon:
        printf("\tstack_push(stack, %d);\n", p->con.value);
        break;
    case typeId:
        printf("\tstack_push(stack, %c);\n", p->id.i + 'a');
        break;
    case typeOpr:
        switch (p->opr.oper)
        {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);
            printf("\tif (!stack_pop(stack)) { goto L%03d; }\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tgoto L%03d;\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2)
            {
                /* if else */
                printf("\tif (!stack_pop(stack)) { goto L%03d; }\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tgoto L%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            }
            else
            {
                /* if */
                printf("\tif (!stack_pop(stack)) { goto L%03d; }\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:
            ex(p->opr.op[0]);
            printf("\tr0 = stack_pop(stack);\n");
            printf("\tprint(r0);\n");
            break;
        case '=':
            ex(p->opr.op[1]);
            printf("\t%c = stack_pop(stack);\n", p->opr.op[0]->id.i + 'a');
            break;
        case UMINUS:
            ex(p->opr.op[0]);
            printf("\tr0 = stack_pop(stack);\n");
            printf("\tr1 = -r0;\n");
            printf("\tstack_push(stack,r1);\n");
            break;
        case FACT:
            ex(p->opr.op[0]);
            printf("\tr0 = stack_pop(stack);\n");
            printf("\tr1 = factorial(r0);\n");
            printf("\tstack_push(stack,r1);\n");
            break;
        case LNTWO:
            printf("\tr0 = stack_pop(stack);\n");
            printf("\tr1 = lntwo(r0);\n");
            printf("\tstack_push(stack,r1);\n");
            break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            switch (p->opr.oper)
            {
            case GCD:
                printf("\tr1 = stack_pop(stack);\n");
                printf("\tr0 = stack_pop(stack);\n");
                printf("\tr0 = gcd(r0, r1);\n");
                printf("\tstack_push(stack, r0);\n");
                break;
            case '+':
                printf("\tr1 = stack_pop(stack);\n");
                printf("\tr0 = stack_pop(stack);\n");
                printf("\tr0 = r0 + r1;\n");
                printf("\tstack_push(stack,r0);\n");
                break;
            case '-':
                printf("\tr1 = stack_pop(stack);\n");
                printf("\tr0 = stack_pop(stack);\n");
                printf("\tr0 = r0 - r1;\n");
                printf("\tstack_push(stack, r0);\n");
                break;
            case '*':
                printf("\tr1 = stack_pop(stack);\n");
                printf("\tr0 = stack_pop(stack);\n");
                printf("\tr0 = r0 * r1;\n");
                printf("\tstack_push(stack, r0);\n");
                break;
            case '/':
                printf("\tr1 = stack_pop(stack);\n");
                printf("\tr0 = stack_pop(stack);\n");
                printf("\tr0 = r0 / r1;\n");
                printf("\tstack_push(stack, r0);\n");
                break;
            case '<':
                printf("\tr1 = stack_pop(stack);\n");
                printf("\tr0 = stack_pop(stack);\n");
                printf("\tstack_push(stack, r0 < r1);\n");
                break;
            case '>':
                printf("\tr1 = stack_pop(stack);\n");
                printf("\tr0 = stack_pop(stack);\n");
                printf("\tstack_push(stack, r0 > r1);\n");
                break;
            case GE:
                printf("\tr1 = stack_pop(stack);\n");
                printf("\tr0 = stack_pop(stack);\n");
                printf("\tstack_push(stack, r0 >= r1);\n");
                break;
            case LE:
                printf("\tr1 = stack_pop(stack);\n");
                printf("\tr0 = stack_pop(stack);\n");
                printf("\tstack_push(stack, r0 <= r1);\n");
                break;
            case NE:
                printf("\tr1 = stack_pop(stack);\n");
                printf("\tr0 = stack_pop(stack);\n");
                printf("\tstack_push(stack, r0 != r1);\n");
                break;
            case EQ:
                printf("\tr1 = stack_pop(stack);\n");
                printf("\tr0 = stack_pop(stack);\n");
                printf("\tstack_push(stack, r0 == r1);\n");
                break;
            }
        }
    }
    return 0;
}
