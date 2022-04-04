#include <iostream>
#include <vector>
#include <cstdlib>

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


bool estLabyrinthe(labyrinthe l, vector<vector<bool> > &passed){
    bool V = true;

}

labyrinthe pseudeGenerer(int a, int b){
    labyrinthe l;
    for(int i = 0; i < a; i++){
        for(int j = 0; j < b; j++){
            if(rand()> RAND_MAX/2){
                l[i][j].bas == false;
            }
            if(rand()> RAND_MAX/2){
                l[i][j].haut == false;
            }
            if(rand()> RAND_MAX/2){
                l[i][j].gauche == false;
            }
            if(rand()> RAND_MAX/2){
                l[i][j].droite == false;
            }
        }
    }
    for(int bord = 0; bord < b; bord++){
        l[0][bord].haut = false;// the top side
        l[a-1][bord].bas = false;//the bottom side
    }
    for(int side = 0; side < a; side++){
        l[side][0].gauche = false;
        l[side][b-1].droite = false;
    }
    return l;
}


void dessine(labyrinthe l){
    stringstream s;
    for(int len = 0;len < l[i].size()*3 + 1;len++){
        s<<"*";
    }
    s<<endl;
    for(int i = 0; i < l[i].size();i++){
        s<<"*";
        for(int j = 0; j < l[i].size();j++){
            if(l[i][j].droite == false){
                s<<"  *";
            }else if(l[i][j].droite != false){
                s<<"   ";
            }
        }
        s<<endl;
        s<<"*";
        for(int k = 0; k < l[i].size();k++){
            if(l[i][k].droite == false){
                s<<"***";
            }else if(l[i][k].droite != false){
                s<<"  *";
            }
        }
        s<<endl;
    }
    cout<<s<<endl;
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