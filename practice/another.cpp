#include <iostream>
using namespace std;
void swapv(int, int);
void swapr(int &, int &);
void swapa(int *, int *);
int main()
{
    int a = 10, b = 20;
    swapa(&a, &b);
    cout << "The value of a and b before swapping is:" << a << " " << b;
}
void swapv(int i, int j)
{
    int temp = i;
    i = j;
    j = temp;
}
void swapr(int &i, int &j)
{
    int temp = i;
    i = j;
    j = temp;
}
void swapa(int *i, int *j)
{
    int temp = *i;
    *i = *j;
    *j = temp;
}