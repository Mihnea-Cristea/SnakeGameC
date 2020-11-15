#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <time.h>
#include <iostream>

using namespace std;

const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;

class harta{};

class punct
{
    int x,y;
    public : friend class sarpe_interactiuni;
};

class info_joc
{
private:
    vector<int> scor;
    scor.push_back(60);
    scor.push_back(40);
    scor.push_back(20);

    int minim = 0, row, coloana, scor_curent = 0, scor_best = 0, jocuri_jucate = 0;

    int PanalaHiscore = scor[2];

public:
    void update_scor_curent()
    {
            scor_curent += 10;
            update_PanaLaHiscore();
    }
    void update_scor_best()
    {

        if (scor_curent > scor_best) scor_best = scor_curent;

    }

    void update_PanaLaHiscore()
    {
        for (int i = 1; i <= 3; i++)
        {
            if (scor_curent < scor[i]) PanalaHiscore = scor[i] - scor_curent;
            else if (scor_curent >= scor[0]) PanalaHiscore = 0;
        }
    }

    void updateTabelaDeScor()
    {
        for (int tracker = 1; tracker <= scor.size(); tracker++)
        {
            if (scor_curent > scor[tracker])
            {
                scor.insert(scor.begin() + tracker, scor_curent);
                scor.erase(scor.begin()+scor.size());
                return;
            }
        }
    }
    void generare_TabelaDeScor(int row) {
        if (row == 1) cout << setw(22) << "Scor curent:" << setw(13) << scor_curent;
        if (row == 2) cout << setw(26) << "Pana la high-Score: " << setw(9) << PanalaHiscore;
        if (row == 5) cout << setw(35) << "Top scoruri                 ";
        if (row == 6) cout << setw(35) << "===========================";
        if (row == 7) cout << setw(17) << "Locul 1" << setw(18) << scor[0];
        if (row == 8) cout << setw(17) << "Locul 2" << setw(18) << scor[1];
        if (row == 9) cout << setw(17) << "Locul 3" << setw(18) << scor[2];
        if (row == 12) cout << setw(35) << "Sesiune curenta          ";
        if (row == 13) cout << setw(35) << "===========================";
        if (row == 14) cout << setw(21) << "Jocuri jucate:" << setw(14) << jocuri_jucate;
        if (row == 15) cout << setw(21) << "Cel mai bun scor:" << setw(14) << scor_best;
    }
};

class sarpe_interactiuni : public harta , public info_joc
{

    bool viu = true;   /// viata
    vector<punct> sarpe;


public:

    void corp_sarpe()
    {
        punct p(sarpe[0]);    /// am un pct initial dupa care adaug pe directia curenta n elemente
        p.x++;  p.y++;        /// ( sugestiv )
        sarpe.push_back(p);   /// adaug la p pe directie ( x sau y )
    }

    void update_poz_mar()     /// genereaza marul intre pozitia 2 si dimensiune totala - 2
    {
        bool unic = false;

        pozitie_mar.x = rand() % (lungime - 4) + 2;
        pozitie_mar.y = rand() % (inaltime - 4) + 2;
    }

    void conditie_sarpe()  /// verifica daca sarpele a mancat vreun mar sau a murit lovindu-se in perete sau mancandu se singur
    {
        if ( sarpe[0].x == 0  || sarpe[0].x == lungime - 1  || sarpe[0].y == 0  ||  sarpe[0].y == inaltime - 1)  /// sarpe[0].x / .y reprezinta coordonatele capului sarpelui, corect ?
            viu = false;

        for (int i = 1; i <= scor_curent / 10; i++)
        {
            if (sarpe[i].x == pctOX && sarpe[i].y == pctOY)
            {
                viu = false;
            }
        }
    }
};

class joc : public harta , public sarpe_interactiuni ,
{
    enum directie { UP, DOWN, LEFT, RIGHT };
    directie dir;

    void get_tasta()
    {
        if get_movement_sarpe()    /// nu stiu la astea 2 ce as putea sa scriu, in mintea mea e cazul daca se apasa tasta se intra in switch (get_char_apasat), am nevoie de putin ajutor, doar sa mi spui cu ce ar trebui sa inlocuiesc
            switch ///get_char
            {
            case 'a': case 'A': case KEY_LEFT:
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd': case 'D': case KEY_RIGHT:
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w': case 'W': case KEY_UP:
                if (dir != DOWN) dir = UP;
                break;
            case 's': case 'S': case KEY_DOWN:
                if (dir != UP) dir = DOWN;
                break;
            }
    }

    void get_movement_sarpe()
    {
        if (dir == LEFT) pctOX--;
        else if (dir == RIGHT) pctOX++;
        else if (dir == UP) pctOY--;
        else if (dir == DOWN) pctOY++;
        else return 0;
    }

    void generare_mar()  /// generarea marului pt prima data
    {
        pozitie_mar.x = rand() % (lungime - 4) + 2;
        pozitie_mar.y = rand() % (latime - 4) + 2;
    }

    int gasit_mar ()
    {
        if (pozitie_mar.x == sarpe[0].x && pozitie_mar.y == sarpe[0].y)
           return 1;
        return 0;
    }


    void deseneaza_harta()
    {
        system("cls");
        for (row = 0; row < inaltime; row++)
            {
            for (coloana = 0; coloana < lungime; coloana++)
            {
                if (row == 0 || row == inaltime - 1) cout << "*";
                else if (coloana == 0 || coloana == lungime - 1) cout << "*";
                else if (row == pctOY && coloana == pctOX) cout << "X";
                else if (row == pozitie_mar.y && coloana == pozitie_mar.x) cout << "O";
                else
                {
                    bool afiseaza_spatiu = true;
                    for (int corp = 1; corp < (scor_curent+10)/10; corp++)
                    {
                        if (sarpe[corp].x == coloana && sarpe[corp].y == row)
                        {
                            cout << "X";
                            afiseaza_spatiu = false;
                        }
                    }
                    if (afiseaza_spatiu)
                    {
                        cout << " ";
                    }
                }
            }
            generare_TabelaDeScor(row);
            cout << endl;
        }
    }
    void playGame()
     {
        while (viu)
        {
            deseneaza_harta();
            get_tasta();
            get_movement_sarpe();
            corp_sarpe();
            conditie_sarpe();
            Sleep(100);
        }
    }

};

class harta
{
    /// sarpe,mar, coordonate de lungime si inaltime

    int lungime = 30 , inaltime = 20;


    punct pozitie_mar;
    pozitie_mar.x = rand() % (lungime - 4) + 2;
    pozitie_mar.y = rand() % (latime - 4) + 2;
    int pctOX = lungime / 2, pctOY = inaltime / 2;
    deseneaza_harta();

};

int main()
{
    srand(time(NULL));

    joc play;
    play.playGame();

    system("PAUSE");
}
