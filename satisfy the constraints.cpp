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

const int mod = 1000000007;
const int N = 2e6+5;

vector<int>st[N+1], en[N+1];
set<pair<int, int>>cnt[N+1];
multiset<int>cur[N+1];

vector<int> lp(N+1);
vector<int> pr;
int ans[N+1], now[N+1];

void clr()
{
    for(int i=0;i<N;i++) now[i] = 0;
}
void linear_seive()
{
    for (int i=2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) {
                break;
            }
        }
    }
    cnt[1].insert({1, 1});

    for(int i=2;i<N;i++)
    {
        int x = i;

        while(x>1)
        {
            int y = lp[x];

            int val = 0;

            while(x%y==0)
            {
                x /= y;
                val++;
            }
            cnt[i].insert({y, val});
        }
    }
}
ll Big_Mod(ll e, ll x)
{
    if(!x) return 1;

    ll p = Big_Mod(e, x/2);

    p = (p * p)%mod;

    if(x%2) p = (p * e)%mod;

    return p;
}

void solve(int tc)
{
    clr();

    int n,q;

    scanf("%d %d", &n, &q);

    int i,j,k,u,v,x,where;

    for(i=1;i<=q;i++)
    {
        scanf("%d %d %d", &u, &v, &x);

        st[u].pb(x);
        en[v].pb(x);
    }
    for(i=0;i<=n;i++)
    {
        ans[i] = 1;
    }

    ll tot = 1;

    for(i=1;i<=n;i++)
    {
        for(auto start: st[i])
        {
            x = start;

            for(auto it: cnt[x])
            {
                if(now[it.fi]<it.se)
                {
                    tot = (tot * Big_Mod(Big_Mod(it.fi, now[it.fi]), mod-2))%mod;

                    cur[it.fi].insert(it.se);

                    now[it.fi] = it.se;

                    tot = (tot * Big_Mod(it.fi, now[it.fi]))%mod;
                }
                else
                {
                    cur[it.fi].insert(it.se);
                }
            }
        }
        ans[i] = tot;

        for(auto endi: en[i])
        {
            x = endi;

            for(auto it: cnt[x])
            {
                if(now[it.fi]==it.se)
                {
                    tot = (tot * Big_Mod(Big_Mod(it.fi, it.se), mod-2))%mod;

                    auto id = cur[it.fi].end();

                    id--;

                    cur[it.fi].erase(id);

                    if(cur[it.fi].size())
                    {
                        id = cur[it.fi].end();

                        id--;

                        now[it.fi] = *id;

                        tot = (tot * Big_Mod(it.fi, *id))%mod;
                    }
                    else
                    {
                        now[it.fi] = 0;
                    }
                }
                else
                {
                    cur[it.fi].erase(cur[it.fi].find(it.se));
                }
            }
        }
        st[i].clear();
        en[i].clear();
    }
    printf("Case %d: ", tc);

    for(i=1;i<n;i++)
    {
        printf("%d ",ans[i]);
    }
    printf("%d\n", ans[n]);
}
int32_t main()
{
    linear_seive();

    int tc = 1;
    scanf("%d", &tc);

    for(int tt=1;tt<=tc;tt++)
    {
        solve(tt);
    }
    return 0;
}
