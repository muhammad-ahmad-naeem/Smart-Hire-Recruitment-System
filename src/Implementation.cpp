#include "header.h"
long cmpCount = 0;
static unsigned int seed = 12345;
int rnd(int n)
{
    seed = seed * 1103515245u + 12345u;
    return (int)((seed >> 8) % (unsigned int)n);
}
int slen(const char *a)
{
    int n = 0;
    while (a[n])
        n++;
    return n;
}
void scopy(char *d, const char *s)
{
    int i = 0;
    while (s[i])
    {
        d[i] = s[i];
        i++;
    }
    d[i] = 0;
}
bool seq(const char *a, const char *b)
{
    int i = 0;
    while (a[i] && b[i])
    {
        if (a[i] != b[i])
            return false;
        i++;
    }
    return a[i] == b[i];
}
void lowerStr(char *s)
{
    for (int i = 0; s[i]; i++)
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[i] += 32;
}
void readWord(char *d, int mx)
{
    char ch;
    cin.get(ch);
    while (!cin.fail() && (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r'))
        cin.get(ch);
    int i = 0;
    while (!cin.fail() && ch != ' ' && ch != '\n' && ch != '\t' && ch != '\r')
    {
        if (i < mx - 1)
            d[i++] = ch;
        cin.get(ch);
    }
    d[i] = 0;
}
int readInt(const char *p, int lo, int hi)
{
    int x;
    while (true)
    {
        cout << p;
        cin >> x;
        if (cin.eof())
            return lo;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input" << endl;
            continue;
        }
        if (x >= lo && x <= hi)
            return x;
        cout << "Enter a value between " << lo << " and " << hi << endl;
    }
}