#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "rlutil.h"

using namespace std;

struct punct {
    int x, y;

    punct(int x, int y) : x(x), y(y) {}
    /// sau punct (int a,int b) {x=a;y=b;}

    punct(int lungime, int inaltime, bool) : x(lungime / 2), y(inaltime / 2) {}

    bool operator==(const punct &rhs) const {
        return x == rhs.x
               &&
               y == rhs.y;
    }

    friend ostream &operator<<(ostream &os, const punct &punct) {   ///operator de afisare
        os << "x: " << punct.x << " y: " << punct.y;
        return os;
    }

    bool operator!=(const punct &rhs) const {
        return !(rhs == *this);
    }
};

class info_joc {
protected:
    vector<int> scor = {60, 40, 20};

    int scor_curent = 0, scor_best = 0, jocuri_jucate = 0;
public:
    const vector<int> &getScor() const {
        return scor;
    }

    void setScor(const vector<int> &scor) {
        info_joc::scor = scor;
    }

    int getScorCurent() const {
        return scor_curent;
    }

    void setScorCurent(int scorCurent) {
        scor_curent = scorCurent;
    }

    int getScorBest() const {
        return scor_best;
    }

    void setScorBest(int scorBest) {
        scor_best = scorBest;
    }

    int getJocuriJucate() const {
        return jocuri_jucate;
    }

    void setJocuriJucate(int jocuriJucate) {
        jocuri_jucate = jocuriJucate;
    }

    int getPanalaHiscore() const {
        return PanalaHiscore;
    }

    void setPanalaHiscore(int panalaHiscore) {
        PanalaHiscore = panalaHiscore;
    }

protected:

    int PanalaHiscore = scor[2];

public:
    void update_scor_curent() {
        scor_curent += 10;
        update_PanaLaHiscore();
//            update_TabelaDeScor();
    }

    void update_PanaLaHiscore() {
        for (int i = 1; i <= 3; i++) {
            if (scor_curent < scor[i]) PanalaHiscore = scor[i] - scor_curent;
            else if (scor_curent >= scor[0]) PanalaHiscore = 0;
//            , scor_best=scor_curent,scor[0]=scor_curent;
        }
    }

    void update_TabelaDeScor() {
        for (unsigned int tracker = 0; tracker < scor.size(); tracker++) {
            if (scor_curent > scor[tracker]) {
                scor.insert(scor.begin() + tracker, scor_curent);
                scor.erase(scor.begin() + scor.size());
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

class harta {
    /// sarpe, mar, coordonate de lungime si inaltime
protected:

    int lungime = 30, inaltime = 20;
    punct pozitie_mar{rand() % (lungime - 4) + 2, rand() % (lungime - 4) + 2, true};
    int pctOX = lungime / 2, pctOY = inaltime / 2;
public:
    void setPozitieMar(const punct &pozitieMar) {
        pozitie_mar = pozitieMar;
    }

    void setLungime(int lungime) {
        harta::lungime = lungime;
    }

    void setInaltime(int inaltime) {
        harta::inaltime = inaltime;
    }

    void setPctOx(int pctOx) {
        pctOX = pctOx;
    }

    void setPctOy(int pctOy) {
        pctOY = pctOy;
    }

public:
    const punct &getPozitieMar() const {
        return pozitie_mar;
    }

    int getLungime() const {
        return lungime;
    }

    int getInaltime() const {
        return inaltime;
    }

    int getPctOx() const {
        return pctOX;
    }

    int getPctOy() const {
        return pctOY;
    }

    void deseneaza_harta(const vector<punct> &sarpe, info_joc &info) const {
        rlutil::cls();
        for (int row = 0; row < lungime; row++) {
            for (int coloana = 0; coloana < inaltime; coloana++) {
                if ((row == 0 || row == lungime - 1)
                    ||
                    (coloana == 0 || coloana == inaltime - 1))
                    cout << "*";
                else if (coloana == pozitie_mar.y && row == pozitie_mar.x) cout << "O";
                else {
                    bool afiseaza_spatiu = true;
                    for (int corp = 0; corp < sarpe.size(); corp++) {
                        if (sarpe[corp].y == coloana && sarpe[corp].x == row) {
                            cout << "X";
                            afiseaza_spatiu = false;
                        }
                    }
                    if (afiseaza_spatiu) {
                        cout << " ";
                    }
                }
            }
            info.generare_TabelaDeScor(row);
            cout << endl;
        }
    }

    friend class joc;
};


class sarpe_interactiuni {

protected:

    bool viu = true;
public:
    void setViu(bool viu);

    void setSarpe(const vector<punct> &sarpe);

protected:
    /// viata
    vector<punct> sarpe{};


public:
    sarpe_interactiuni(harta &h);

    punct &operator[](unsigned int i) {
        return sarpe[i];
    }

    const vector<punct> &getSarpe() const;

    bool isViu() const;

//    const punct &getCap() const;

    void corp_sarpe() {

        punct p(sarpe[0]);    /// am un pct initial dupa care adaug pe directia curenta n elemente
    }

    void conditie_sarpe(const info_joc &info,
                        const harta &h)  /// verifica daca sarpele a mancat vreun mar sau a murit lovindu-se in perete sau mancandu se singur && constructor de copiere ( harta h )
    {
        if (sarpe[0].x == 0 || sarpe[0].x == h.getLungime() - 1 || sarpe[0].y == 0 ||
            sarpe[0].y == h.getInaltime() - 1)  /// sarpe[0].x / .y reprezinta coordonatele capului sarpelui, corect ?
            viu = false;

        for (int i = 1; i <= info.getScorCurent() / 10; i++) {
            if (sarpe[i].x == h.getPctOx() && sarpe[i].y == h.getPctOy()) {
                viu = false;


            }
        }
    }

    friend class harta;

    void addCoada(const punct &punct);
};

bool sarpe_interactiuni::isViu() const {
    return viu;
}

//const punct &sarpe_interactiuni::getCap() const {
//    return sarpe[0];
//}

const vector<punct> &sarpe_interactiuni::getSarpe() const {
    return sarpe;
}

sarpe_interactiuni::sarpe_interactiuni(harta &h) {
    sarpe.emplace_back(h.getLungime(), h.getInaltime(), true);
}

void sarpe_interactiuni::addCoada(const punct &punct) {
    sarpe.push_back(punct);

}

void sarpe_interactiuni::setViu(bool viu) {
    sarpe_interactiuni::viu = viu;
}

void sarpe_interactiuni::setSarpe(const vector<punct> &sarpe) {
    sarpe_interactiuni::sarpe = sarpe;
}

class joc {
private:

    joc() = default;

    static joc *app;
    punct p;
    enum directie {
        UP, DOWN, LEFT, RIGHT
    };
    directie dir = LEFT;
    info_joc info{};
    harta h{};
    sarpe_interactiuni s{h};

    void get_tasta() {

        if (kbhit())    /// nu stiu la astea 2 ce as putea sa scriu, in mintea mea e cazul daca se apasa tasta se intra in switch (get_char_apasat), am nevoie de putin ajutor, doar sa mi spui cu ce ar trebui sa inlocuiesc
        {
            switch (getch()) {
                case 'a':
                case 'A':
                case rlutil::KEY_LEFT:
                    if (dir != RIGHT) dir = LEFT;
                    break;
                case 'd':
                case 'D':
                case rlutil::KEY_RIGHT:
                    if (dir != LEFT) dir = RIGHT;
                    break;
                case 'w':
                case 'W':
                case rlutil::KEY_UP:
                    if (dir != DOWN) dir = UP;
                    break;
                case 's':
                case 'S':
                case rlutil::KEY_DOWN:
                    if (dir != UP) dir = DOWN;
                    break;
            }
        }
    }

    void get_movement_sarpe() {

        auto &corp = s.getSarpe();
        auto cap = corp[0];
        if (dir == LEFT) cap.y--;
        else if (dir == RIGHT) cap.y++;
        else if (dir == UP) cap.x--;
        else if (dir == DOWN) cap.x++;

        for (auto i = corp.size() - 1; i >= 1u; --i) {
            s[i] = s[i - 1];
        }
        s[0] = cap;

    }

    void generare_mar()  /// generarea marului pt prima data
    {
        h.pozitie_mar = {rand() % (h.lungime - 4) + 2, rand() % (h.inaltime - 4) + 2, true};   ///operator =
    }

    int gasit_mar() {
        auto auc = s[s.getSarpe().size() - 1];
        if (h.pozitie_mar == s[0]) {
            generare_mar();
            info.update_scor_curent();
            switch (dir) {
                case UP:
                    auc.x++;
                    break;
                case DOWN:
                    auc.x--;
                    break;
                case LEFT:
                    auc.y++;
                    break;
                case RIGHT:
                    auc.y--;
                    break;
            }
            s.addCoada(auc);
            return 1;
        }
        return 0;
    }

public :
    joc(const joc &) = delete;   // e constructor de copiere si nu pot sa apelez in singleton
    joc &operator=(const joc &) = delete;

    static joc *get_app() {
        if (app == nullptr) { app = new joc(); }
        return app;
    }

    void init() {
        info.setScorCurent(0);
        s.setViu(1);
    }

    void endgame() {
        info.setJocuriJucate(info.getJocuriJucate() + 1);
        info.setScorBest(info.getScorCurent());
        info.update_TabelaDeScor();
    }

    void playGame() {
        init();
        while (s.isViu()) {
            h.deseneaza_harta(s.getSarpe(), info);
            get_movement_sarpe();
            get_tasta();
            s.corp_sarpe();
            gasit_mar();
            s.conditie_sarpe(info, h);

            rlutil::msleep(100);
        }
        endgame();
    }

    int keepPlaying() {
        char variabila;
        cout << "Doriti sa jucati inca un joc ?" << endl
             << "Apasati y pentru a mai juca sau n pentru a inchide aplicatia.";
        cin >> variabila;
        if (variabila == 'y') return 1;
        else return 0;
    }
};

joc *joc::app = nullptr;

int main() {
    srand(time(nullptr));

    joc *play = joc::get_app();
    do {
        play->playGame();
    } while (play->keepPlaying());

    rlutil::anykey("PAUSE");
}
// Call to implicitly-deleted default constructor of 'joc' la linie 382, am cautat pe internet dar tot nu stiu sa i dau de cap, pare a fi ultima problema din cod