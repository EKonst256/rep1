#include<iostream>
#include<cmath>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

using ll = long long;

using vll = vector<ll>;

map<ll, vll> adj;
vector<vll> dist;
vll father; 
ll mx_dist;
vll degree;


void prepare(ll n) {
    adj.clear();
    dist.clear();
    dist.clear();
    dist.resize(n + 1);
    father.clear();
    father.resize(n + 1);
    degree.clear();
    degree.resize(n + 1);
    mx_dist = 0;
}
void deep_search(ll v, ll cur) {
    dist[cur].push_back(v);
    mx_dist = max(cur, mx_dist);
    for(ll i: adj[v]) {
        if(i == father[v]) continue;
        father[i] = v;
        deep_search(i, cur + 1);
    }
    return;
}

void find_degree(ll n) {
    for(ll i: dist[n]) {
        if(adj[i].size() == 1) degree[i] = n;
        else {
            for(ll j: adj[i]) {
                if(j != father[i]) {
                    degree[i] = max(degree[i], degree[j]);
                }
            }
        }
    }
    if(n == 0) return;
    find_degree(n - 1);
    return;
}

int main() {
    ll t{};
    cin >> t;
    while(t--) {
        ll n{}, a{}, b{}, ans = 1e9, cur_ans{}, cur{};
        cin >> n;
        prepare(n);
        for(ll i = 1; i < n; i++) {
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        deep_search(1, 0);
        vll degree_for_n(mx_dist + 1);
        vll subdist(mx_dist + 2);
        for(ll i = 0; i <= mx_dist; i++) subdist[i + 1] = subdist[i] + dist[i].size();
        find_degree(mx_dist);
        for(ll i = 0; i <= n; i++) {
            degree_for_n[degree[i]]++;
        }
        degree_for_n[0] = 0;
        for(ll i = 1; i <= mx_dist; i++) {
            cur += degree_for_n[i - 1];
            cur_ans = cur + (subdist[mx_dist + 1] - subdist[i + 1]);
            ans = min(ans, cur_ans);
        }
        cout << ans << "\n";
    }
    return 0;
}
