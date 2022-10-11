#include <bits/stdc++.h>
//#include<ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
using namespace std;
#define ll long long int
#define ld long double
#define mod 1000000007
#define inf 1e18
#define endl "\n"
#define pb emplace_back
#define vi vector<ll>
#define vs vector<string>
#define pii pair<ll, ll>
#define ump unordered_map
#define mp map
#define pq_max priority_queue<ll>
#define pq_min priority_queue<ll, vi, greater<ll>>
#define ff first
#define ss second
#define mid(l, r) (l + (r - l) / 2)
#define loop(i, a, b) for (int i = (a); i <= (b); i++)
#define looprev(i, a, b) for (int i = (a); i >= (b); i--)
#define logarr(arr, a, b)            \
    for (int z = (a); z <= (b); z++) \
        cout << (arr[z]) << " ";     \
    cout << endl;

// typedef tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update> pbds;
ll power(long long x, ll y, ll p)
{
    ll res = 1;
    x = x % p;
    if (x == 0)
        return 0;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

long long modInverse(unsigned long long n,
                     int p)
{
    return power(n, p - 2, p);
}

unsigned long long nCrModPFermat(unsigned long long n,
                                 int r, int p)
{
    if (n < r)
        return 0;
    if (r == 0)
        return 1;
    long long fac[n + 1];
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;
    return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}
void file_i_o()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

typedef unsigned char byte;

/*

 * SuffixNode Declaration

 */

class SuffixNode
{

public:
    ll depth, begin, end;

    SuffixNode **children;

    SuffixNode *parent, *suffixLink;

    SuffixNode(int begin, int end, int depth, SuffixNode *parent)

    {

        children = new SuffixNode *[38];

        this->begin = begin;

        this->end = end;

        this->parent = parent;

        this->depth = depth;
    }

    bool contains(int d)

    {

        return depth <= d && d < depth + (end - begin);
    }
};

string alphabet;

int alphabetSize;

int lcsLength;

int lcsBeginIndex;

/*

 * Class SuffixTree Declaration

 */

class SuffixTree

{

public:
    /*

     * Funtion to build suffix tree for given text

     */

    SuffixNode *buildSuffixTree(string s)
    {

        int n = s.length();

        int *a = new int[n];

        for (int i = 0; i < n; i++)

        {

            a[i] = alphabet.find(s.at(i));
        }

        SuffixNode *root = new SuffixNode(0, 0, 0, NULL);

        SuffixNode *cn = root;

        root->suffixLink = root;

        SuffixNode *needsSuffixLink = NULL;

        int lastRule = 0;

        int j = 0;

        for (int i = -1; i < n - 1; i++)

        {

            int cur = a[i + 1];

            for (; j <= i + 1; j++)

            {

                int curDepth = i + 1 - j;

                if (lastRule != 3)

                {

                    if (cn->suffixLink != NULL)

                        cn = cn->suffixLink;

                    else

                        cn = cn->parent->suffixLink;

                    int k = j + cn->depth;

                    while (curDepth > 0 && !cn->contains(curDepth - 1))

                    {

                        k += cn->end - cn->begin;

                        cn = cn->children[a[k]];
                    }
                }

                if (!cn->contains(curDepth))

                {

                    if (needsSuffixLink != NULL)

                    {

                        needsSuffixLink->suffixLink = cn;

                        needsSuffixLink = NULL;
                    }

                    if (cn->children[cur] == NULL)

                    {

                        cn->children[cur] = new SuffixNode(i + 1, n, curDepth, cn);

                        lastRule = 2;
                    }

                    else

                    {

                        cn = cn->children[cur];

                        lastRule = 3;

                        break;
                    }
                }

                else

                {

                    int end = cn->begin + curDepth - cn->depth;

                    if (a[end] != cur)

                    {

                        SuffixNode *newn = new SuffixNode(cn->begin, end, cn->depth, cn->parent);

                        newn->children[cur] = new SuffixNode(i + 1, n, curDepth, newn);

                        newn->children[a[end]] = cn;

                        cn->parent->children[a[cn->begin]] = newn;

                        if (needsSuffixLink != NULL)

                            needsSuffixLink->suffixLink = newn;

                        cn->begin = end;

                        cn->depth = curDepth;

                        cn->parent = newn;

                        cn = needsSuffixLink = newn;

                        lastRule = 2;
                    }

                    else if (cn->end != n || (cn->begin - cn->depth) < j)

                    {

                        lastRule = 3;

                        break;
                    }

                    else

                        lastRule = 1;
                }
            }
        }

        root->suffixLink = NULL;

        return root;
    }

    /*

     * Funtion to find longest common substring

     */

    int findLCS(SuffixNode *node, int i1, int i2)

    {

        if (node->begin <= i1 && i1 < node->end)

            return 1;

        if (node->begin <= i2 && i2 < node->end)

            return 2;

        int mask = 0;

        for (int f = 0; f < alphabetSize; f++)

        {

            if (node->children[f] != NULL)

            {

                mask |= findLCS(node->children[f], i1, i2);
            }
        }

        if (mask == 3)

        {

            int curLength = node->depth + node->end - node->begin;

            if (lcsLength < curLength)

            {

                lcsLength = curLength;

                lcsBeginIndex = node->begin;
            }
        }

        return mask;
    }

    /*

     * Funtion to find longest common substring

     */

    void findLCS(string s1, string s2)

    {

        string x = "-";

        string y = "#";

        string ns1 = s1;

        string ns2 = s2;

        string s = s1.append(x.append(s2.append(y)));

        SuffixNode *root = buildSuffixTree(s);

        lcsLength = 0;

        lcsBeginIndex = 0;

        findLCS(root, ns1.length(), ns1.length() + ns2.length() + 1);

        bool chk = lcsLength > 0;

        if (chk)

        {

            cout << "\nLongest substring is " << s.substr(lcsBeginIndex, lcsLength);

            cout << endl;
        }

        else

        {

            cout << "No substring found" << endl;
        }
    }
};

int main()

{
    file_i_o();

    alphabet = "abcdefghijklmnopqrstuvwxyz1234567890-#";

    alphabetSize = alphabet.length();

    string s1, s2;

    cout << "Finding longest common substring using suffix trees\n";

    cout << "Enter 1st String: ";

    cin >> s1;

    cout << "Enter 2nd String: ";

    cin >> s2;

    SuffixTree st;

    st.findLCS(s1, s2);

    return 0;
}
