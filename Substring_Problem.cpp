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
class node
{
public:
    unordered_map<char, node *> child;
    node *suffixLink = NULL;
    node *outputLink = NULL;
    ll patternIndex;

    node()
    {
        this->suffixLink = NULL;
        this->outputLink = NULL;
        this->patternIndex = -1;
    }
};

void buildTree(node *root, vs &patterns)
{
    loop(i, 0, patterns.size() - 1)
    {
        node *curr = root;
        loop(j, 0, patterns[i].size() - 1)
        {
            ll c = patterns[i][j];
            if (!curr->child.count(c))
            {
                curr->child[c] = new node();
            }

            curr = curr->child[c];
        }

        curr->patternIndex = i;
    }
}
void build_Suffix_and_output_links(node *root)
{
    root->suffixLink = root;
    queue<node *> q;
    for (auto &[c, val] : root->child)
    {
        q.push(val);
        val->suffixLink = root;
    }
    while (q.size())
    {
        node *currState = q.front();
        q.pop();
        for (auto &[c, val] : currState->child)
        {

            node *ccChild = val;
            node *temp = currState->suffixLink;
            while (temp != root and temp->child.find(c) == temp->child.end())
                temp = temp->suffixLink;

            if (temp->child.find(c) != temp->child.end())
                ccChild->suffixLink = temp->child[c];
            else
                ccChild->suffixLink = root;

            q.push(ccChild);
        }

        if (currState->suffixLink->patternIndex >= 0)
            currState->outputLink = currState->suffixLink;
        else
            currState->outputLink = currState->suffixLink->outputLink;
    }
}

void search(node *root, string s, vector<vi> &res)
{
    node *parent = root;
    loop(i, 0, s.size() - 1)
    {
        int c = s[i];
        if (parent->child.find(c) != parent->child.end())
        {
            parent = parent->child[c];
            if (parent->patternIndex > -1)
                res[parent->patternIndex].push_back(i);
            node *myOutputLink = parent->outputLink;
            while (myOutputLink)
            {
                res[myOutputLink->patternIndex].push_back(i);
                myOutputLink = myOutputLink->outputLink;
            }
        }
        else
        {
            while (parent != root and !parent->child.count(c))
            {
                parent = parent->suffixLink;
            }

            if (parent->child.count(c))
                i--;
        }
    }
}

int main(int argc, char const *argv[])
{
    file_i_o();
    string q;
    cin >> q;
    ll n;
    cin >> n;
    vector<string> patterns(n);
    for (int i = 0; i < n; i++)
        cin >> patterns[i];
    cout << endl;
    node *root = new node();
    buildTree(root, patterns);
    build_Suffix_and_output_links(root);
    vector<vi> ans(n);
    search(root, q, ans);
    loop(i, 0, n - 1)
    {
        cout << (ans[i].size() ? "Y" : "N") << endl;
    }

    return 0;
}