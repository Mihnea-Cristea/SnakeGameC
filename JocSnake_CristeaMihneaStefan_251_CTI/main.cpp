#include <vector>
#include <stdlib.h>
#include <iomanip>
using namespace std;
const int UP 72
const int DOWN 80
const int LEFT 75
const int RIGHT 77
class punct
{
    int x,y;
};

class info_joc
{
private:
    vector<int> scor = { 60, 40, 20 };

    punct coordonate_harta; /// int latime = 30 , inaltime = 20;
    coordonate_harta.x = 30 , coordonate_harta.y = 20;

    punct pozitie_mar; /// int MarPozitieX = rand() % (latime - 4) + 2;
    pozitie_mar.x = rand() % (coordonate_harta.x - 4) + 2;
    pozitie_mar.y = rand() % (coordonate_harta.y - 4) + 2;                  /// int MarPozitieY = rand() % (inaltime - 4) + 2;
    vector<punct> sarpe;



    int Ox = latime / 2, Oy = inaltime / 2;

    bool viu = true, mort = false;

    int minim = 0, row, coloana, scor_curent = 0, scor_best = 0, JocuriJucate = 0;

    int PanalaHiscore = scor[2];

public:
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
};

class sarpe_interactiuni : public info_joc
{
public:
    void corp_sarpe()
    {
        sarpe.x.insert(sarpe.x.begin(), Ox);
        sarpe.y.insert(sarpe.y.begin(), Oy);
    }

    void reset_corp_sarpe()
    {
        for (int erase = 0; erase < sarpe.x.size(); erase++)
            {
                sarpe.x.erase(sarpe.x.begin() + erase);
                sarpe.y.erase(sarpe.y.begin() + erase);
            }
    }

    void update_poz_mar() /// genereaza marul intre pozitia 2 si dimensiune totala - 2
    {
        bool unic = false;
        while (!unic)
        {
            pozitie_mar.x = rand() % (coordonate_harta.x - 4) + 2;
            pozitie_mar.y = rand() % (coordonate_harta.y - 4) + 2;

            for (int i = 0; i < sarpe.x.size(); i++)
            {
                if (pozitie_mar.x == sarpe[i].x && pozitie_mar.y == sarpe[i].y) break;
                else unic = true;
            }
        }
    }

    void getSnakeCondition()  /// verifica daca sarpele a mancat vreun mar sau a murit lovindu-se in perete sau mancandu se singur
    {
        if (pozitie_mar.x == Ox && pozitie_mar.y == Oy)
        {
            scor_curent += 10;
            update_PanaLaHiscore();
            update_poz_mar();
        }

        if (Ox == 0  ||  Ox == coordonate_harta.x - 1  ||  Oy == 0  ||  Oy == coordonate_harta.y - 1) {
            viu = false;
        }

        for (int i = 1; i <= scor_curent / 10; i++) {
            if (sarpe[i].x == Ox && sarpe[i].y == Oy) {
                viu = false;
            }
        }
    }
};
