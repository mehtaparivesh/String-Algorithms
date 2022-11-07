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
long long merge(vi &arr, int left, int mid, int right)
{
    int i = left, j = mid, k = 0;
    long long invCount = 0;
    int temp[(right - left + 1)];

    while ((i < mid) && (j <= right))
    {
        if (arr[i] <= arr[j])
        {
            temp[k] = arr[i];
            ++k;
            ++i;
        }
        else
        {
            temp[k] = arr[j];
            invCount += (mid - i);
            ++k;
            ++j;
        }
    }

    while (i < mid)
    {
        temp[k] = arr[i];
        ++k;
        ++i;
    }

    while (j <= right)
    {
        temp[k] = arr[j];
        ++k;
        ++j;
    }

    for (i = left, k = 0; i <= right; i++, k++)
    {
        arr[i] = temp[k];
    }

    return invCount;
}
long long mergeSort(vi &arr, int left, int right)
{
    long long invCount = 0;

    if (right > left)
    {
        int mid = (right + left) / 2;
        invCount = mergeSort(arr, left, mid);
        invCount += mergeSort(arr, mid + 1, right);
        invCount += merge(arr, left, mid + 1, right);
    }
    return invCount;
}

long long getInversions(vi &arr, int n)
{
    return mergeSort(arr, 0, n - 1);
}

int main(int argc, char const *argv[])
{
    file_i_o();
    ll n;
    cin >> n;
    string s;
    cin >> s;

    map<ll, list<ll>> m;
    for (int i = 0; i < s.size(); i++)
    {
        m[s[i]].push_back(i);
    }

    vi v(s.size());
    string reversed = s;
    reverse(reversed.begin(), reversed.end());

    for (int i = 0; i < reversed.size(); i++)
    {

        v[i] = m[reversed[i]].front();
        m[reversed[i]].pop_front();
    }
    cout << getInversions(v, v.size()) << endl;

    return 0;
}