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
        printf("\tpush\t%d\n", p->con.value);
        break;
    case typeId:
        printf("\tlea\tr9, [rip+%c]\n", p->id.i + 'a');
        printf("\tpush\t[r9]\n");
        break;
    case typeOpr:
        switch (p->opr.oper)
        {
        case WHILE:
            printf("L%03d:\n", lbl1 = lbl++);
            ex(p->opr.op[0]);

            printf("\tjnz\tL%03d\n", lbl2 = lbl++);
            ex(p->opr.op[1]);
            printf("\tjmp\tL%03d\n", lbl1);
            printf("L%03d:\n", lbl2);
            break;
        case IF:
            ex(p->opr.op[0]);
            if (p->opr.nops > 2)
            {
                /* if else */
                printf("\tjnz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("\tjmp\tL%03d\n", lbl2 = lbl++);
                printf("L%03d:\n", lbl1);
                ex(p->opr.op[2]);
                printf("L%03d:\n", lbl2);
            }
            else
            {
                /* if */
                printf("\tjnz\tL%03d\n", lbl1 = lbl++);
                ex(p->opr.op[1]);
                printf("L%03d:\n", lbl1);
            }
            break;
        case PRINT:
            ex(p->opr.op[0]);
            printf("\tlea rdi, [rip+fmt_str]\n");
            printf("\tpop rsi\n");
            printf("\txor rax, rax\n");
            printf("\tpush rbp\n");
            printf("\tcall printf\n");
            printf("\tpop rbp\n");
            break;
        case '=':
            ex(p->opr.op[1]);
            index[0] = p->opr.op[0]->id.i;
            printf("\tlea\tr9, [rip+%c]\n", index[0] + 'a');
            printf("\tpop\t[r9]\n");
            break;
        case UMINUS:
            ex(p->opr.op[0]);
            index[0] = p->opr.op[0]->id.i;
            printf("\tpop\trdi\n");
            printf("\tneg\trdi\n");
            printf("\tpush\trdi\n");
            break;
        case FACT:
            ex(p->opr.op[0]);
            printf("\tpop\trdi\n");
            printf("\txor\trax, rax\n");
            printf("\tcall\tfactorial\n");
            printf("\tpush\trax\n");
            break;
        case LNTWO:
            ex(p->opr.op[0]);
            printf("\tpop\trdi\n");
            printf("\txor\trax, rax\n");
            printf("\tcall\tlntwo\n");
            printf("\tpush\trax\n");
            break;
        default:
            ex(p->opr.op[0]);
            ex(p->opr.op[1]);
            index[0] = p->opr.op[0]->id.i;
            index[1] = p->opr.op[1]->id.i;
            switch (p->opr.oper)
            {
            case GCD:
                if (p->opr.op[0]->type == typeCon)
                {
                    printf("\tpop rdi\n");
                }
                else
                {
                    index[0] = p->opr.op[0]->id.i;
                    printf("\tlea r8, [rip+ARRAY]\n");
                    if (index[0] != 0)
                    {
                        printf("\tadd r8, 8*%d\n", index[0]);
                    }
                    printf("\tmov rdi, [r8]\n");
                }
                if (p->opr.op[1]->type == typeCon)
                {
                    printf("\tpop rsi\n");
                }
                else
                {
                    index[1] = p->opr.op[1]->id.i;
                    printf("\tlea r8, [rip+ARRAY]\n");
                    if (index[1] != 0)
                    {
                        printf("\tadd r8, 8*%d\n", index[1]);
                    }
                    printf("\tmov rsi, [r8]\n");
                }
                printf("\txor rax, rax\n");
                printf("\tcall gcd\n");
                printf("\tpush rax\n");
                break;
            case '+':
                printf("\tpop\trdi\n");
                printf("\tpop\trsi\n");
                printf("\tadd rdi, rsi\n");
                printf("\tpush rdi\n");
                break;
            case '-':
                printf("\tpop\trdi\n");
                printf("\tpop\trsi\n");
                printf("\tsub rsi, rdi\n");
                printf("\tpush rsi\n");
                break;
            case '*':
                printf("\tpop\trdi\n");
                printf("\tpop\trax\n");
                printf("\txor\trdx, rdx\n");
                printf("\timul rdi\n");
                printf("\tpush rax\n");
                break;
            case '/':
                printf("\tpop\trdi\n");
                printf("\tpop\trax\n");
                printf("\txor rdx, rdx\n");
                printf("\tidiv rdi\n");
                printf("\tpush rax\n");
                break;
            case '<':
                if (p->opr.op[0]->type == typeCon)
                {
                    printf("\tpop rdi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[0] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[0]);
                    }
                    printf("\tmov rdi, [r9]\n");
                }
                if (p->opr.op[1]->type == typeCon)
                {
                    printf("\tpop rsi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[1] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[1]);
                    }
                    printf("\tmov rsi, [r9]\n");
                }

                printf("\tmov r8, 0\n");
                printf("\tmov r9, 1\n");
                printf("\tcmp rdi, rsi\n");
                printf("\tcmovl r9, r8\n");
                printf("\txor r8, r9\n");

                break;
            case '>':
                if (p->opr.op[0]->type == typeCon)
                {
                    printf("\tpop rdi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[0] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[0]);
                    }
                    printf("\tmov rdi, [r9]\n");
                }
                if (p->opr.op[1]->type == typeCon)
                {
                    printf("\tpop rsi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[1] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[1]);
                    }
                    printf("\tmov rsi, [r9]\n");
                }

                printf("\tmov r8, 0\n");
                printf("\tmov r9, 1\n");
                printf("\tcmp rdi, rsi\n");
                printf("\tcmovg r9, r8\n");
                printf("\txor r8, r9\n");

                break;
            case GE:
                if (p->opr.op[0]->type == typeCon)
                {
                    printf("\tpop rdi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[0] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[0]);
                    }
                    printf("\tmov rdi, [r9]\n");
                }
                if (p->opr.op[1]->type == typeCon)
                {
                    printf("\tpop rsi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[1] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[1]);
                    }
                    printf("\tmov rsi, [r9]\n");
                }

                printf("\tmov r8, 0\n");
                printf("\tmov r9, 1\n");
                printf("\tcmp rdi, rsi\n");
                printf("\tcmovge r9, r8\n");
                printf("\txor r8, r9\n");
                break;
            case LE:
                if (p->opr.op[0]->type == typeCon)
                {
                    printf("\tpop rdi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[0] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[0]);
                    }
                    printf("\tmov rdi, [r9]\n");
                }
                if (p->opr.op[1]->type == typeCon)
                {
                    printf("\tpop rsi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[1] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[1]);
                    }
                    printf("\tmov rsi, [r9]\n");
                }

                printf("\tmov r8, 0\n");
                printf("\tmov r9, 1\n");
                printf("\tcmovle r9, r8\n");
                printf("\txor r8, r9\n");
                break;
            case NE:
                if (p->opr.op[0]->type == typeCon)
                {
                    printf("\tpop rdi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[0] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[0]);
                    }
                    printf("\tmov rdi, [r9]\n");
                }
                if (p->opr.op[1]->type == typeCon)
                {
                    printf("\tpop rsi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[1] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[1]);
                    }
                    printf("\tmov rsi, [r9]\n");
                }

                printf("\tmov r8, 0\n");
                printf("\tmov r9, 1\n");
                printf("\tcmp rdi, rsi\n");
                printf("\tcmovne r8, r9\n");
                printf("\txor r9, r8\n");

                break;
            case EQ:
                if (p->opr.op[0]->type == typeCon)
                {
                    printf("\tpop rdi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[0] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[0]);
                    }
                    printf("\tmov rdi, [r9]\n");
                }
                if (p->opr.op[1]->type == typeCon)
                {
                    printf("\tpop rsi\n");
                }
                else
                {
                    printf("\tlea r9, [rip+ARRAY]\n");
                    if (index[1] != 0)
                    {
                        printf("\tadd r9, 8*%d\n", index[1]);
                    }
                    printf("\tmov rsi, [r9]\n");
                }

                printf("\tcmp rdi, rsi\n");
                break;
            }
        }
    }
    return 0;
}
