#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll INF = (1LL << 60);

// 辺
struct Edge {
    int from;
    int to;
    int cost;
};

// ベルマンフォード法 (1.3 最短経路を再構築する)
// 負の閉路が存在する場合 true を返し, 負閉路の影響を受ける頂点は -INF
// にセットされる 頂点 T が負閉路の影響を受けない場合, 頂点 S からの最短経路を
// path に格納する dist は頂点数と同じサイズ, 全要素 INF で初期化しておく
bool BellmanFord(const vector<Edge> &eds, vector<ll> &dist, int S, int T,
                 vector<int> &path) {
    dist[S] = 0;

    vector<ll> p(ssize(dist), -1);

    bool changed = false;
    for(int i = 0; i < dist.size(); i++) {
        changed = false;
        // 各辺について
        for(const auto &ed : eds) {
            // (INF + cost) は INF なので処理しない
            if(dist[ed.from] == INF) continue;
            // to までの新しい距離
            const ll d = (dist[ed.from] + ed.cost);
            // d が現在の記録より小さければ更新
            if(d < dist[ed.to]) {
                dist[ed.to] = d;

                // 直前の頂点を記録
                p[ed.to] = ed.from;

                changed = true;
            }
        }

        // どの頂点も更新されなかったら終了
        if(!changed) {
            break;
        }
    }

    if(changed)  // 負閉路あり
    {
        // 頂点数分だけさらに繰り返し, 負閉路の影響を受ける頂点に -INF を伝播
        for(int i = 0; i < dist.size(); i++) {
            for(const auto &ed : eds) {
                if(dist[ed.from] == INF) continue;
                const ll d = (dist[ed.from] + ed.cost);
                // 負閉路の影響を受ける頂点を -INF に
                if(d < dist[ed.to]) dist[ed.to] = -INF;
            }
        }
    }
    if((dist[T] != INF) &&
       (dist[T] != -INF))  // 頂点 T に到達不可または負閉路が影響する場合は最短経路無し
    {
        // 経路を再構築
        for(int i = T; i != -1; i = p[i]) path.push_back(i);
        reverse(path.begin(), path.end());
    }
    return changed;
}