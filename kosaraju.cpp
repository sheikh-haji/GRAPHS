#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<math.h>
#include<bits/stdc++.h>
#include<stack>
#include<queue>
#include<list>
#include<vector>
#include<bitset>
#include<unordered_map> 
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// #include "boost/algorithm/string.hpp"
#define fio ios_base::sync_with_stdio(false)
#define mod 1000000007
#define mod1 mod
#define mod2 1000000007
#define li long long int
#define ll li
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define readi(x) scanf("%d",&x)
#define  reads(x)  scanf("%s", x)
#define readl(x) scanf("%I64d",&x)
#define rep(i,n) for(i=0;i<n;i++)
#define revp(i,n) for(i=(n-1);i>=0;i--)
#define myrep1(i,a,b) for(i=a;i<=b;i++)
#define myrep2(i,a,b) for(i=b;i>=a;i--)
#define pb push_back
#define mp make_pair
#define fi first
#define sec second
#define MAXN 1000000000000000005
#define MINN -10000000000000000
#define INTMAX 1000001000
#define pii pair<ll,ll> 
#define pdd pair<double,double>
#define pic pair<int,char>
#define N 1000005
#define lgn 20
#define ddouble long double
#define minus minu
#define PI 3.1415926535
#define lgn 20
 
 
// #define INTMAX 200000000 
 
// using namespace boost;
// #define si short int
 
using namespace std;
using namespace __gnu_pbds;             
typedef priority_queue<ll, vector<ll > > max_pq;
typedef priority_queue<pii, vector<pii> , greater<pii>  > min_pq;
ll toint(const string &s) {stringstream ss; ss << s; ll x; ss >> x; return x;}
string tostring ( ll number ){stringstream ss; ss<< number; return ss.str();}
 
// using namespace __gnu_pbds;         
// typedef priority_queue<pair<ll,char> , vector<pair<ll , char> > > max_pq;
// typedef priority_queue<pii , vector<pii > ,greater<pii > > min_pq;
typedef tree<pii , null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> OST;
// typedef priority_queue<pair < ll , pair < pii , ll > >  , vector<pair < ll , pair < pii , ll > >  > ,greater<pair < ll , pair < pii , ll > >  > > min_pq;
#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template <typename Arg1>
    void __f(const char* name, Arg1&& arg1){
        cout << name << " : " << arg1 << std::endl;
        //use cerr if u want to display at the bottom
    }
    template <typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
    }
#else
#define trace(...)
#endif
#define nn 2000005
ll n,m;
ll color[ N ];
vector < vector < ll > > adjlist ( N );
vector < vector < ll > > revlist ( N );
vector < vector < ll > > daglist( N );
stack < ll > s;
ll visited[ N ];
ll od[ N ];
set < pii > edges;
ll col = 0;
void dfs ( ll i )
{
    visited[i] = 1;
    for ( auto it : adjlist[i] )
        if ( !visited[it])
            dfs(it);
    s.push(i);
}
void dfsr ( ll i , ll which )
{
    visited[i] = 1;
    color[i]=which;
    for ( auto it : revlist[i] )
        if ( !visited[it])
            dfsr(it,which);
}
void kosaraju ( )
{
    for ( ll i = 1; i <= n; i ++)
        if ( !visited[i] )
            dfs(i);
    memset(visited,0,sizeof visited);
    while ( !s.empty() )
    {
        ll x = s.top();
        s.pop();
        if ( !visited[x] )
        {
            col++;
            dfsr(x,col);
        }
    }
}
void dagconstruct( )
{
    for ( ll i = 1; i <= n; i ++)
    {
        for ( auto it : adjlist[i] )
        {
            if ( color[it] != color[i] and edges.find({color[i],color[it]}) == edges.end() )
            {
                daglist[color[i]].pb(color[it]);
                od[color[i]]++;
                edges.insert({color[i],color[it]});
            }
        }
    }
}
void findcapital()
{
    ll cnt = 0;
    ll node;
    for ( ll i = 1; i <= col; i ++)
    {
        if ( od[i] == 0 )
            node = i;
        cnt += ( od[i] == 0 );
    }
    if ( cnt == 1 )
    {
        vector < ll > vec;
        for ( ll i = 1; i <= n; i ++)
            if ( color[i] == node )
                vec.pb(i);
        cout << vec.size() <<"\n";
        for ( auto it : vec )
            cout << it <<" ";
    }
    else
    {
        cout <<"0\n";
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    #endif
    cin >> n >> m;
    while ( m-- )
    {
        ll a,b;
        cin >> a >> b;
        adjlist[a].pb(b);
        revlist[b].pb(a);
    }
    kosaraju();
    dagconstruct();
    findcapital();
}