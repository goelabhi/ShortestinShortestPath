typedef pair<int,int> ipair;
typedef long long ll;
vector<ll> dstra(int A, int C, vector<vector<ipair>> &g){
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    vector<long long> dis(A, LLONG_MAX);
    dis[C] = 0;
    vector<bool> fin(A, false);
    pq.push({0,C});
    while(pq.size()){
        int u = pq.top().second;
        ll udis = pq.top().first;
        pq.pop();
        fin[u] = true;
        for(auto i: g[u]){
            int v = (i).first;
            int wt = (i).second;
            if(fin[v] == false && dis[v]>dis[u]+wt){
                dis[v] = dis[u]+wt;
                pq.push({dis[v],v});
            }
        }
    }
    return dis;
}
    
int Solution::solve(const int A, const vector<vector<int> > &B, const int C, const int D) {
    vector<vector<ipair>> g(A);
    
    for(int i=0;i<B.size();i++){
        g[B[i][0]-1].push_back({B[i][1]-1,B[i][2]});
        g[B[i][1]-1].push_back({B[i][0]-1,B[i][2]});
    }
    vector<long long> dC = dstra(A,C-1,g);
    ll spath = dC[D-1];
    
    vector<ll> dD = dstra(A,D-1,g);
    
    int ans = INT_MAX;
    for(int i=0; i<B.size();i++){
        if(dC[B[i][0]-1] + B[i][2] + dD[B[i][1]-1] == spath)
            ans = min(ans,B[i][2]);
        if(dC[B[i][1]-1] + B[i][2] + dD[B[i][0]-1] == spath)
            ans = min(ans,B[i][2]);
    }
    return ans;

}

