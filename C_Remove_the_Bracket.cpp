#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <complex>
#include <queue>
#include <set>
#include <unordered_set>
#include <list>
#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <stack>
#include <iomanip>
#include <fstream>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> p32;
typedef pair<ll, ll> p64;
typedef pair<double, double> pdd;
typedef vector<ll> v64;
typedef vector<int> v32;
typedef vector<vector<int>> vv32;
typedef vector<vector<ll>> vv64;
typedef vector<vector<p64>> vvp64;
typedef vector<p64> vp64;
typedef vector<p32> vp32;
ll MOD = 998244353;
double eps = 1e-12;
#define forn(i, e) for (ll i = 0; i < e; i++)
#define forsn(i, s, e) for (ll i = s; i < e; i++)
#define rforn(i, s) for (ll i = s; i >= 0; i--)
#define rforsn(i, s, e) for (ll i = s; i >= e; i--)
#define ln "\n"
#define dbg(x) cout << #x << " = " << x << ln
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define INF 2e18
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())
#define max(a, b) a > b ? a : b
#define ipt(n, r) forn(i, n) cin >> r[i];
#define ys cout << "YES" << endl;
#define no cout << "NO" << endl;

ll min(ll a, ll b)
{
    if (a > b)
        return b;
    else
        return a;
}
bool prime[200005];
void SieveOfEratosthenes(int n)
{
    memset(prime, true, sizeof(prime));
    for (int p = 2; p * p <= n; p++)
    {
        if (prime[p] == true)
        {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
}
const ll mod = 1e9 + 7;
ll add(ll a, ll b)
{
    ll ans = (a + b) % mod;
    if (ans < 0)
        ans += mod;
    return ans;
}
ll sub(ll a, ll b)
{
    ll ans = (a - b) % mod;
    if (ans < 0)
        ans += mod;
    return ans;
}
ll mul(ll a, ll b)
{
    ll ans = (a * b) % mod;
    if (ans < 0)
        ans += mod;
    return ans;
}
ll power(ll a, ll b, ll m)
{
    a %= m;
    long long res = 1;
    while (b > 0)
    {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}
ll inv(ll a)
{
    return power(a, mod - 2, mod);
}
void solve()
{
    ll n, k;
    cin >> n >> k;
    vector<ll> v(n);
    forn(i, n) cin >> v[i];
    vector<vector<ll>> DP(n, vector<ll>(2, 0));
    // if (v[1] >= k)
    // {
    //     DP[1][0] = v[0] * k;
    //     DP[1][1] = v[0] * (v[1] - k);
    // }
    // else
    // {
    //     DP[1][0] = 0;
    //     DP[1][1] = v[0] * v[1];
    // }
    // forsn(i, 2, n - 1)
    // {
    //     if (v[i] >= k)
    //     {
    //         if (v[i - 1] >= k)
    //         {
    //             ll k1 = DP[i - 1][0] + (v[i - 1] - k) * k;
    //             ll k2 = DP[i - 1][1] + k * k;
    //             DP[i][0] = min(k1, k2);
    //             k1 = DP[i - 1][0] + (v[i - 1] - k) * (v[i] - k);
    //             k2 = DP[i - 1][1] + k * (v[i] - k);
    //             DP[i][1] = min(k1, k2);
    //         }
    //         else
    //         {
    //             ll k1 = DP[i - 1][0] + v[i - 1] * k;
    //             DP[i][0] = min(k1, DP[i - 1][1]);
    //             k1 = DP[i - 1][0] + (v[i - 1]) * (v[i] - k);
    //             DP[i][1] = min(k1, DP[i - 1][1]);
    //         }
    //     }
    //     else
    //     {
    //         if (v[i - 1] >= k)
    //         {
    //             ll k1 = DP[i - 1][0];
    //             ll k2 = DP[i - 1][1];
    //             DP[i][0] = min(k1, k2);
    //             k1 = DP[i - 1][0] + (v[i - 1] - k) * k;
    //             k2 = DP[i - 1][1] + k * (v[i]);
    //             DP[i][1] = min(k1,k2);
    //         }
    //         else
    //         {
    //             ll k1 = DP[i - 1][0] + (v[i - 1]) * v[i];
    //             ll k2 = DP[i - 1][1];
    //             DP[i][0] = min(DP[i - 1][0], DP[i - 1][1]);
    //             DP[i][1] = min(k1, k2);
    //         }
    //     }
    // }
    // if (v[n - 2] >= k)
    // {
    //     ll k1 = DP[n - 2][0] + (v[n - 2] - k) * v[n - 1];
    //     ll k2 = DP[n - 2][1] + k * (v[n - 1]);
    // }
    // else
    // {
    //     ll k1 = DP[n - 2][0] + (v[n - 2]) * v[n - 1];
    //     ll k2 = DP[n - 2][1];
    // }
    vector<ll> L(n,k), R(n,k);
    DP.resize(n, vector<ll>(2, 0));
    map<ll,ll> mpL,mpR;
    forn(i,n)
    {
        if(v[i]>2*k) L[i] = k, R[i] = v[i]-k;
        else if(v[i] < 2*k) L[i] = max(v[i]-k,0), R[i] = min(k,v[i]);
        mpL[L[i]]++;
        mpR[R[i]]++;
    }
    DP[1][0] = v[0];
    DP[1][1] = v[0];
    DP[1][0] *= L[1];
    DP[1][1] *= R[1];
    map<ll,ll> mpD;
    forsn(i,2,n-1)
    {
        auto it = mpL.find(DP[i][0]);
        auto it1 = mpL.find(DP[i][1]);
        // if(it != mpL.end()) mpL.erase(it);
        if(it1 != mpL.end()) mpL.erase(it1);
        ll p1 = (v[i-1]-L[i-1])*(L[i]);
        ll p2 = (v[i-1]-R[i-1])*(L[i]);
        ll p3 = (v[i-1]-L[i-1])*(R[i]);
        ll p4 = (v[i-1]-R[i-1])*(R[i]);
        ll k1 = DP[i-1][0];
        k1+=p1;
        ll k2 = DP[i-1][1];
        k2+=p2;
        ll k3 = DP[i-1][0];
        k3+=p3;
        ll k4 = DP[i-1][1];
        k4+=p4;
        DP[i][0] = min(k1,k2);
        DP[i][1] = min(k3,k4);
        mpD[DP[i][0]]++;
        mpD[DP[i][1]]++;
    }
    ll p1 = (v[n-2]-L[n-2])*v[n-1];
    ll p2 = (v[n-2]-R[n-2])*v[n-1];
    ll k1 = DP[n-2][0]+p1;
    ll k2 = DP[n-2][1]+p2;
    cout << min(k1,k2) << endl;
}


int main()
{
    SieveOfEratosthenes(100005);
    fast_cin();
    ll t;
    cin >> t;
    for (int it = 1; it <= t; it++)
    {
        solve();
    }
    return 0;
}