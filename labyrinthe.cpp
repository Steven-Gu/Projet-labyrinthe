#include <iostream>
#include <vector>

using namespace std;

struct cell{
    bool gauche;
    bool droite;
    bool haut;
    bool bas;
    bool chemin = false;
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

void parcourir(labyrinthe l, int i, int j){
    l[i][j].chemin = true;
    if (l[i][j].bas == true && l[i + 1][j].chemin == false)
        parcourir(l, i + 1, j);
    if (l[i][j].haut == true && l[i - 1][j].chemin == false)
        parcourir(l, i - 1, j);
    if (l[i][j].droite == true && l[i][j + 1].chemin == false)
        parcourir(l, i, j + 1);
    if (l[i][j].gauche == true && l[i][j - 1].chemin == false)
        parcourir(l, i, j - 1);
    
}


void parcourirTraverser(labyrinthe l){
    for (int i = 0; i < l.size(); i++){
        for (int j = 0; j < l[i].size(); j++){
            l[i][j].chemin = false;
        }
    }

    for (int i = 0; i < l.size(); i++){
        for (int j = 0; j < l[i].size(); j++){
            if(l[i][j].chemin == false)
                parcourir(l, i, j);
        }
    }

}

int main(){
    labyrinthe l;
    int m = 4, n = 3;
    l = labyrinthe(n);
    for (int i = 0;i < n;i++)
        l[i] = vector<cell>(m);
    

    
    return 0;
}