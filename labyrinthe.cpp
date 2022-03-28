#include <iostream>
#include <vector>

using namespace std;

struct cell{
    bool gauche;
    bool droite;
    bool haut;
    bool bas;
    bool chemin;
};

using labyrinthe = vector<vector<cell> >;
int murs (labyrinthe l){
    int f = 0;
    for(int i = 0;i < l.size();i++){
        for(int j = 0;j < l[i].size();j++){
            if(l[i][j].bas == false){
                f++;
            }
            if(l[i][j].haut == false){
                f++;
            }
            if(l[i][j].gauche == false){
                f++;
            }
            if(l[i][j].droite == false){
                f++;
            }
        }
    }
    int enceintes = 2 * (l.size() + l[0].size());
    return (f - enceintes) / 2;
}
int main(){
    labyrinthe l;
    int m = 4, n = 3;
    l = labyrinthe(n);
    for (int i = 0;i < n;i++)
        l[i] = vector<cell>(m);
    

    
    return 0;
}