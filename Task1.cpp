//created by Shivam Varshney
//https://cses.fi/problemset/task/1646
#include<bits/stdc++.h>
#pragma GCC optimise("Ofast")
#pragma GCC target("avx","avx2","fma")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
using namespace std;
#define int long long
#define all(x) x.begin(),x.end()
#define pi pair<int,int>
#define ff first
#define ss second

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<" "; _print(x); cerr << "\n";
#else
#define debug(x)
#endif

void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(bool t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << "{"; _print(p.ff); cerr << ","; _print(p.ss); cerr << "}";}
template <class T> void _print(vector <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(set <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T> void _print(multiset <T> v) {cerr << "[ "; for (T i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(map <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
template <class T, class V> void _print(multimap <T, V> v) {cerr << "[ "; for (auto i : v) {_print(i); cerr << " ";} cerr << "]";}
inline void read(int &n,vector<int> &v){for(int i = 0 ; i < n ; i++) cin>>v[i];}
inline void print(int &n,vector<int> &v){for(int i = 0 ; i < n ; i++) cout<<v[i]<<" ";cout<<"\n";}
inline void read(int &n,int &m,vector<vector<int>> &v){for(int i=0;i<n;i++){for(int j=0;j<m;j++){cin>>v[i][j];}}}
inline void print(int &n,int &m,vector<vector<int>> &v){for(int i=0 ;i<n;i++){for(int j=0;j<m;j++){cout<<v[i][j]<<" ";}cout<<"\n";}}
/*

    

*/


class SegTree{
public:
    vector<int> p;
    vector<int> v;
    SegTree(vector<int> &v){
        int n = v.size();
        p.resize(4*n,0);
        this->v.assign(v.begin(),v.end());
    }

    //query for [l,r]
    int query(int index,int l,int r,int low,int high){
        //No overlap
        //[l,r] [low,high] or [low,high] [l,r]
        
        /*---------------------------------*/
        if(r < low || high < l)
            return 0;               //depends on question
        /*---------------------------------*/


        //Complete Overlap
        //[l...low...high...r]
        if(l <= low && r >= high)
            return p[index];



        //Partial Overlap
        //[low...l...r...high] or [low....l...high...r] or [l...low...r....high]
        int mid = low+(high-low)/2;
        int left = query(2*index+1,l,r,low,mid);
        int right = query(2*index+2,l,r,mid+1,high);
        /*---------------------------------*/
        return left+right;          //depends on question
        /*---------------------------------*/
    }

    void update(int index,int low,int high,int i,int val){
        if(low == high){
            v[i] = val;
            p[index] = val;
        }

        int mid = low+(high-low)/2;
        if(i <= mid)
            update(2*index+1,low,mid,i,val);
        else
            update(2*index+2,mid+1,high,i,val);
        /*---------------------------------*/
        p[index] = p[2*index+1]+p[2*index+2];  //depends on question
        /*---------------------------------*/
    }

    void build(int index,int low,int high){
        if(low == high){
            p[index] = v[low];
            return;
        }

        int mid = low+(high-low)/2;
        build(2*index+1,low,mid);
        build(2*index+2,mid+1,high);
        p[index] = p[2*index+1]+p[2*index+2];
    }
};


void solve(){
   int n,q;cin>>n>>q;
   vector<int> v(n);
   read(n,v);   
   SegTree A(v);
   A.build(0,0,n-1);
   while(q--){
    int l,r;cin>>l>>r;
    int ans = A.query(0,l-1,r-1,0,n-1);
    cout<<ans<<"\n";
   }
}

signed main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
        freopen("Error.txt", "w", stderr);
    #endif

    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 1;
    // cin>>T;
    while(T--){
        solve();
    }
    cerr<<"time taken : "<<(float)clock()/CLOCKS_PER_SEC<<" secs"<<"\n";
    return 0;
}

