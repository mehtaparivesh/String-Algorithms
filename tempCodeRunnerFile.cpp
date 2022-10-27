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
ll helper(ll start, ll end, string &s)
{
    if (start == end - 1)
        return 0;
    ll ans = 0;
    for (int i = start + 1; i < end; i++)
    {
        bool x = (start != -1 and s[i] - s[start] == 1) or (end < s.size() and s[i] - s[end] == 1);
        ll a = helper(start, i, s);
        ll b = helper(i, end, s);
        ans = max(ans, a + b + (ll)x);
    }
    return ans;
}
int main(int argc, char const *argv[])
{
    file_i_o();
    ll n;
    cin >> n;
    string s;
    cin >> s;
    // cout << helper(-1, s.size(), s) << endl;
    ll ans = 0;
    for (char ch = 'z'; ch > 'a'; ch--)
    {
        loop(i, 0, n - 1)
        {
            if (s.size() == 1)
                break;
            if (s[i] != ch)
                continue;
            if (i == 0)
            {
                if (s[i + 1] == ch - 1)
                {
                    ans++;
                    s = s.substr(i + 1);