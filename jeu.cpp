#include <iostream>
#include <vector>
#include <unistd.h> // Pour usleep
#include <xamgraph.h>

using namespace std;

// Fonction pour afficher la grille
void afficherGrille(const vector<vector<int>>& grille) {
    for (const auto& ligne : grille) {
        for (int cellule : ligne) {
            cout << (cellule ? 'O' : '.') << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

// Fonction pour compter les voisins vivants
int compterVoisinsVivants(const vector<vector<int>>& grille, int x, int y) {
    int voisinsVivants = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Ignorer la cellule elle-même
            int nouvelleX = x + i;
            int nouvelleY = y + j;
            if (nouvelleX >= 0 && nouvelleX < grille.size() && nouvelleY >= 0 && nouvelleY < grille[0].size()) {
                voisinsVivants += grille[nouvelleX][nouvelleY];
            }
        }
    }
    return voisinsVivants;
}

// Fonction pour mettre à jour la grille
void mettreAJourGrille(vector<vector<int>>& grille) {
    vector<vector<int>> nouvelleGrille = grille;
    for (int i = 0; i < grille.size(); ++i) {
        for (int j = 0; j < grille[0].size(); ++j) {
            int voisinsVivants = compterVoisinsVivants(grille, i, j);
            if (grille[i][j] == 1) {
                // Règle 1 et 3
                nouvelleGrille[i][j] = (voisinsVivants == 2 || voisinsVivants == 3) ? 1 : 0;
            } else {
                // Règle 4
                nouvelleGrille[i][j] = (voisinsVivants == 3) ? 1 : 0;
            }
        }
    }
    grille = nouvelleGrille;
}

int main() {
    // Initialisation de la grille
    int lignes = 10;
    int colonnes = 10;
    vector<vector<int>> grille(lignes, vector<int>(colonnes, 0));

    // Configuration initiale (exemple)
    grille[4][5] = 1;
    grille[5][6] = 1;
    grille[6][4] = 1;
    grille[6][5] = 1;
    grille[6][6] = 1;

    // Boucle principale du jeu
    while (true) {
        afficherGrille(grille);
        mettreAJourGrille(grille);
        usleep(500000); // Pause de 0.5 seconde
    }

    return 0;
}