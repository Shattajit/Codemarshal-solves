#include<bits/stdc++.h>
#define ll long long int
#define pb push_back
#define se second
#define fi first
using namespace std;

int dx[8] = { 1, -1, 0, 0};
int dy[8] = { 0, 0, 1, -1};

/*
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

typedef tree <
    pair<ll ,ll>,
    null_type,
    less<pair<ll ,ll>>,
    rb_tree_tag,
    tree_order_statistics_node_update> ordered_set;
*/

const ll mod = 1e9+7;
const int N = 2e6+10;

long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

void solve(int tc)
{
    ll n,q,i,j,l,r;

    cin>>n>>q;

    ll ar[n+5], cnt[n+5][50];

    for(i=0;i<=n;i++)
    {
        for(j=0;j<=49;j++)
        {
            cnt[i][j] = 0;
        }
    }

    for(i=1;i<=n;i++)
    {
        cin>>ar[i];

        for(j=0;j<=40;j++)
        {
            cnt[i][j] = cnt[i-1][j];

            if(((ar[i]>>j)&1)==1)
            {
                cnt[i][j]++;
            }
        }
    }
    ll ans = 0;

    while(q--)
    {
        cin>>l>>r;

        ans = 0;

        for(j=0;j<=40;j++)
        {
            if(cnt[r][j]-cnt[l-1][j]==0)
            {
                continue;
            }
            else
            {
                ans = (ans + (binpow(2ll, j, mod)*binpow(2ll, r-l, mod))%mod)%mod;
            }
        }

        cout<<ans<<"\n";
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    //pre();

    int tc = 1;
    //cin>>tc;

    for(int tt=1;tt<=tc;tt++)
    {
        solve(tt);
    }
    return 0;
}
