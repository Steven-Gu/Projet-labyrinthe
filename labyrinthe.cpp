#include <iostream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <deque>

using namespace std;

struct cell{
    bool gauche = true;
    bool droite = true;
    bool haut = true;
    bool bas = true;
    bool chemin = false;
    bool position_now = false;
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
            else{
                s << setw(4) <<" ";
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


labyrinthe pseudeGenerer(int m, int n){
    labyrinthe l;
    l = vector<vector<cell> >(n);
    for(int i = 0; i < n; i++)
        l[i] = vector<cell> (m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(rand() > RAND_MAX / 2){
                if(i + 1 < n){
                    l[i][j].bas = false;
                    l[i + 1][j].haut = false;
                }
            }
            if(rand() > RAND_MAX / 2){
                if(j + 1 < m){
                    l[i][j].droite = false;
                    l[i][j + 1].gauche = false;
                }
            } 
        }
    }
    init_enceinte(l);
    return l;
}

bool retire_bas(labyrinthe &l, int i, int j){
    if (i == l.size() - 1 or l[i + 1][j].chemin == true)
        return false;
    l[i + 1][j].chemin =true;
    l[i][j].bas = true;
    l[i + 1][j].haut = true;
    return true;
}

bool retire_haut(labyrinthe &l, int i, int j){
    if (i == 0 or l[i - 1][j].chemin == true)
        return false;
    l[i - 1][j].chemin =true;
    l[i][j].haut = true;
    l[i - 1][j].bas = true;
    return true;
}


bool retire_droite(labyrinthe &l, int i, int j){
    if (j == l[i].size() - 1 or l[i][j + 1].chemin == true)
        return false;
    l[i][j + 1].chemin =true;
    l[i][j].droite = true;
    l[i][j + 1].gauche = true;
    return true;
}

bool retire_gauche(labyrinthe &l, int i, int j){
    if (j == 0 or l[i][j - 1].chemin == true)
        return false;
    l[i][j - 1].chemin =true;
    l[i][j].gauche = true;
    l[i][j - 1].droite = true;
    return true;
}

void retire_mur(deque<labyrinthe> &t){
    int n = t.size();
    int num = 0;
    while(num < n){
        labyrinthe l = t[0];
        int i = 0, j = 0;
        for(int x = 0; x < l.size(); x++){
            for (int y = 0; y < l[x].size(); y++){
                if(l[x][y].position_now){
                    i = x;
                    j = y;
                }
            }
        }
        if (retire_bas(l, i, j)){
            l[i][j].position_now = false;
            l[i + 1][j].position_now = true;
            t.push_back(l);
            
        }
        l = t[0];
        if (retire_haut(l, i, j)){
            l[i][j].position_now = false;
            l[i - 1][j].position_now = true;
            t.push_back(l);
        }
        l = t[0];
        if (retire_droite(l, i, j)){
            l[i][j].position_now = false;
            l[i][j + 1].position_now = true;
            t.push_back(l);
        }
        l = t[0];
        if (retire_gauche(l, i, j)){
            l[i][j].position_now = false;
            l[i][j - 1].position_now = true;
            t.push_back(l);
        }
        t.pop_front();
        num++; 
    }
}

deque<labyrinthe> labyrintheGenerer(int m, int n){
    deque<labyrinthe> t;
    labyrinthe l;
    l = vector<vector<cell> >(n);
    for(int i = 0; i < n; i++)
        l[i] = vector<cell> (m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            l[i][j].haut = false;
            l[i][j].bas = false;
            l[i][j].gauche = false;
            l[i][j].droite = false;
            l[i][j].position_now = false;
        }
    }
    l[0][0].position_now = true;
    l[0][0].chemin = true;
    t.push_back(l);
    for(int i = 0; i < m * n - 1; i++)
        retire_mur(t);
    return t;
 
}


void parcourir(labyrinthe &l, int i, int j){
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


void parcourirTraverser(labyrinthe &l){
    for (int i = 0; i < l.size(); i++){
        for (int j = 0; j < l[i].size(); j++){
            l[i][j].chemin = false;
        }
    }

    parcourir(l, 0, 0);
}

bool estlabyrinthe(labyrinthe &l){
    int m = l[0].size(); // colonne
    int n = l.size(); // ligne
    int nb_murs = murs(l);
    if (nb_murs != nbMurLab(l))
        return false;
    parcourirTraverser(l);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(l[i][j].chemin == false)
                return false;
        }
    }
    return true;
}


int main(){
    srand((unsigned)time(NULL));
    /*labyrinthe l;
    int num = 0;
    while (num <= 0){
        l = pseudeGenerer(3, 2);
        if ( estlabyrinthe(l)){
            num++;
            cout << dessin(l) << endl;
        }
    }*/
    deque<labyrinthe> d = labyrintheGenerer(3, 3);
    for(int i = 0; i < d.size(); i++){
        cout << dessin(d[i]) << endl;
    }
    cout << d.size() << endl;
      
    return 0;
}