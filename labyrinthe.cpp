#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip>


using namespace std;

struct cell{
    bool gauche = true;
    bool droite = true;
    bool haut = true;
    bool bas = true;
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


int nbMurLab(labyrinthe &l){
    /*
        nb total de mur pseudo-lab : n(m-1)+m(n-1)
        nb de bordure entre les cellules qui ne sont pas murs : n (m − 1)
        nb_mur = n(m-1)+m(n-1) - n (m − 1) = (nm - n + nm - m) -n*m-1 = m*n-n-m+1
    */
   int m = l[0].size(); // colonne
   int n = l.size(); // ligne
   return m * n - n - m + 1;
}


labyrinthe pseudeGenerer(int a, int b){
    labyrinthe l;
    l = vector<vector<cell> >(a);
    for(int i = 0; i < a; i++){
        l[i] = vector<cell> (b);
        for(int j = 0; j < b; j++){
            if(rand() > RAND_MAX/2){
                if(i+1 < a){
                    l[i][j].bas = false;
                    l[i+1][j].haut = false;
                }
            }
            if(rand() > RAND_MAX/2){
                if(j+1 < b){
                    l[i][j].gauche = false;
                    l[i][j+1].droite = false;
                }
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



string dessin_ligne(int m){
    ostringstream s;
    //s<< " ";
    for(int i = 0;i<m;i++){
        s << setw(4) << "***";
    }
    s << endl;
    return s.str();
}


string dessin(labyrinthe &l){
    // m : colonne
    // n : ligne
    int m = l[0].size(); // colonne
    int n = l.size(); // ligne
    ostringstream s;
    s << dessin_ligne(m);
    for(int i = 0;i<n;i++){
        /*colonnes*/
        s << "|";
        for(int j = 0;j<m;j++){
            s << setw(3) <<" ";
            if(!l[i][j].droite){
                s << "|";
            }
        }
        s<< endl;
        /*lignes*/
        for(int j = 0;j<m;j++){
            if(!l[i][j].bas){
                s << setw(4) << "***";
            }
        }
        s<< endl;
    }
    return s.str();
}


void init_enceinte(labyrinthe &l){
    /*
        initialise les murs des enceintes à false
    */
    int m = l[0].size(); // colonne
    int n = l.size(); // ligne 
    for(int i = 0;i<n;i++){
        l[i][0].gauche = false;
        l[i][m-1].droite = false;
    }
    for(int j = 0;j<m;j++){
        l[0][j].haut = false;
        l[n-1][j].bas = false;
    }
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
    l = pseudeGenerer(2, 3);
    cout << dessin(l);
    

    
    return 0;
}