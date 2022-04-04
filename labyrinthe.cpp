#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

struct cell{
    bool gauche = true;
    bool droite = true;
    bool haut = true;
    bool bas = true;
    bool chemin = false;
};

using labyrinthe = vector<vector<cell>>;
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
   return m*n-n-m+1;
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
            else{
                s << " ";
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
int main(){
    labyrinthe l;
    int m = 15, n = 10;
    l = labyrinthe(n);
    for (int i = 0;i < n;i++){
        l[i] = vector<cell>(m);
        l[i][3].gauche = false;
        l[i][4].droite = false;
    }
    l[0][0].bas = false;
    l[1][0].haut = false;
    init_enceinte(l);
    
    cout << dessin(l);
    return 0;
}