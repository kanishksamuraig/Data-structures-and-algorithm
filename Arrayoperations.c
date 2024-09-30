#include <stdio.h>
int main()
{
    int a[100], pos, i = 1, j, size = 0, op, x;
    while (i == 1)
    {
        printf("1)Insertion at the end\n2)insertion at the start\n3)insertion at the position\n");
        printf("4)deletion at the start\n5)deletion at the end\n6)deletion at a position\n7)traversal\n8)exit\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1: // inserting at the end
            printf("Enter the element you want to insert at the end: ");
            scanf("%d", &x);
            size++;
            a[size - 1] = x;
            break;
        case 2: // inserting at the start
            printf("Enter the element you want to insert at the first: ");
            scanf("%d", &x);
            for (j = size - 1; j >= 0; j--)
            {
                a[j + 1] = a[j];
            }
            a[0] = x;
            size++;
            break;
        case 3: // inserting at a position
            printf("Enter the element you want to insert: ");
            scanf("%d", &x);
            printf("Enter the position at which you want to insert: ");
            scanf("%d", &pos);
            for (j = size - 1; j >= pos - 1; j--)
            {
                a[j + 1] = a[j];
            }
            a[pos - 1] = x;
            size++;
            break;
        case 4: // deleting at the start
            if (size == 0)
            {
                printf("array is empty\n");
            }
            else
            {
                for (j = 0; j <= size - 1; j++)
                {
                    a[j] = a[j + 1];
                }
                size--;
            }
            break;
        case 5: // deleting at the end
            if (size == 0)
            {
                printf("array is empty\n");
            }
            else
            {
                a[size - 1] = a[size];
                size--;
            }
            break;
        case 6: // Deleting at a position
            if (size == 0)
            {
                printf("array is empty\n");
            }
            else
            {
                printf("Enter the position at which you want to perform delete:");
                scanf("%d", &pos);
                for (j = pos - 1; j <= size - 1; j++)
                {
                    a[j] = a[j + 1];
                }
                size--;
            }
            break;
        case 7: // traversal
            printf("{");
            for (j = 0; j <= size - 1; j++)
            {
                if (j == size - 1)
                {
                    printf("%d}\n", a[j]);
                    break;
                }
                printf("%d,", a[j]);
            }
            break;
        case 8: // quit
            printf("{");
            for (j = 0; j <= size - 1; j++)
            {
                if (j == size - 1)
                {
                    printf("%d}\n", a[j]);
                    break;
                }
                printf("%d,", a[j]);
            }
            printf("Exiting..\n");
            i = 0;
            break;
        default:
            printf("Enter the valid operation given above..\n");
            break;
        }
    }
    return 0;
}
