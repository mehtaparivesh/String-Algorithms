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
class SuffixArray
{
#define MAX_N 100010;

public:
    ll n = -1;
    string s;
    ll RA[100010];
    ll SA[100010];
    ll tempRA[100010];
    ll tempSA[100010];
    vi lcp;

    void countingSort(int k)
    {                                // O(n)
        int i, maxi = max(300ll, n); // up to 255 ASCII chars or length of n
        int sum = 0;
        vi c(100010);
        // memset(c, 0, sizeof(c));         // clear frequency table
        for (i = 0; i < n; i++)
            c[i + k < n ? RA[i + k] : 0]++; // count the frequency of each integer rank

        for (i = 0; i < maxi; i++)
        {
            int t = c[i];
            c[i] = sum;
            sum += t;
        }

        for (i = 0; i < n; i++) // shuffle the suffix array if necessary
            tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];

        for (i = 0; i < n; i++) // update the suffix array SA
            this->SA[i] = tempSA[i];
    }

    SuffixArray(string x)
    {
        this->s = x;
        this->s += "$";
        this->n = s.length();
        for (int i = 0; i < n; i++)
            this->RA[i] = s[i];
        for (int i = 0; i < n; i++)
            SA[i] = i;

        for (int k = 1; k < n; k *= 2)
        {
            countingSort(k);
            countingSort(0);

            int r = 0;
            tempRA[this->SA[0]] = r;    // re-ranking; start from rank r = 0
            for (int i = 1; i < n; i++) // compare adjacent suffixes if same pair => same rank r; otherwise, increase r
            {
                tempRA[this->SA[i]] = (RA[this->SA[i]] == RA[this->SA[i - 1]] && RA[this->SA[i] + k] == RA[this->SA[i - 1] + k]) ? r : ++r;
            }

            for (int i = 0; i < n; i++)
            {
                RA[i] = tempRA[i]; // update the rank array RA
            }

            if (RA[this->SA[n - 1]] == n - 1)
                break; // nice optimization trick
        }
        kasai(); // use it to make lcp array in O(N) time

        logarr(lcp, 0, lcp.size() - 1);
        logarr(SA, 0, n - 1);
    }

    void kasai()
    {
        int k = 0;
        lcp = {};
        lcp.resize(n);
        vi rank(n);

        for (int i = 0; i < n; i++)
            rank[this->SA[i]] = i;

        for (int i = 0; i < n; i++, k = max(k - 1, 0))
        {
            if (rank[i] == n - 1)
            {
                k = 0;
                continue;
            }
            int j = this->SA[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            this->lcp[rank[i]] = k;
        }
    }
};

int main(int argc, char const *argv[])
{
    file_i_o();
    string s;
    cin >> s;
    string t = s + s;
    SuffixArray *sa = new SuffixArray(t);
    string ans = "";
    for (int i = 0; i < t.size(); i++)
    {
        ll len = t.size() - sa->SA[i];
        if (len >= s.size())
        {
            ans = t.substr(sa->SA[i], s.size());
            break;
        }
    }
    cout << ans << endl;

    return 0;
}