// cppttest.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <thread>
#include <stack>

using namespace std;

std::map<int, string> hashevi;
string text;
string nizA;
string nizB;
int tVrijednost;

signed char* E = new signed char[4];
int* O = new int[3];
ofstream outputFile("/Volumes/Zvijer/Google Drive/FER/BIO/bioinformatika4russians/source/bla.txt");


int triNaTVrijednost;
int cetiriNaTVrijenost;
int cetiriNaTVrijenostNaKvadrat;
uint8_t *downOffsets;
uint8_t *rightOffsets;

int pretvori_pomak(string pomak) {
    int rez = 0;
    int potencija = 3;
    for(int i = 0; i < pomak.size(); ++i) {
        int val;
        if(pomak[i] == '-') {
            val = 0;
            i++;
        } else if(pomak[i] == '0') {
            val = 1;
        } else {
            val = 2;
        }
        
        rez = rez * potencija + val;
    }
    
    return rez;
}

inline int pretvori_slova(string &slova) {
    int rez = 0;
    int potencija = 4;
    for(int i = 0; i < slova.size(); ++i) {
        int val;
        if(slova[i] == 'A') {
            val = 0;
        } else if(slova[i] == 'C'){
            val = 1;
        } else if(slova[i] == 'T'){
            val = 2;
        } else if(slova[i] == 'G'){
            val = 3;
        }
        
        rez = rez * potencija + val;
    }
    
    return rez;
}

int maksimalni = 0;
int K;

inline int spoji_hasheve(int h1, int h2, int h3, int h4) {
    return h1 * triNaTVrijednost * cetiriNaTVrijenostNaKvadrat + h2 * cetiriNaTVrijenostNaKvadrat + h3 * cetiriNaTVrijenost + h4;
}

int u_hash(string pomak1, string pomak2, string &a1, string &a2) {
    int h1 = pretvori_pomak(pomak1);
    int h2 = pretvori_pomak(pomak2);
    int h3 = pretvori_slova(a1);
    int h4 = pretvori_slova(a2);
    
    int h_konacno = spoji_hasheve(h1, h2, h3, h4);
    
    return h_konacno;
}

int u_hash(int h1, string pomak2, int h3, int h4) {
    int h2 = pretvori_pomak(pomak2);
    
    int h_konacno = spoji_hasheve(h1, h2, h3, h4);
    return h_konacno;
}

int u_hash(string pomak1, int h2, int h3, int h4) {
    int h1 = pretvori_pomak(pomak1);
    
    int h_konacno = spoji_hasheve(h1, h2, h3, h4);
    return h_konacno;
}

int u_hash(string pomak1, string pomak2, int h3, int h4) {
    int h1 = pretvori_pomak(pomak1);
    int h2 = pretvori_pomak(pomak2);
    
    int h_konacno = spoji_hasheve(h1, h2, h3, h4);
    return h_konacno;
}

int u_hash(int h1, int h2, int h3, int h4) {
    int h_konacno = spoji_hasheve(h1, h2, h3, h4);
    return h_konacno;
}

class Cell {
    
public:
    int value;
    bool top;
    bool left;
    Cell() {};
    Cell(int val) { value = val; }
    
    string writeLeft() {
        if (left == true)
            return "T";
        else return "F";
    }
    string writeTop() {
        if (top == true)
            return "T";
        else return "F";
    }
    
};

class Blok {
    
public:
    uint8_t downOffsets = 0;
    uint8_t rightOffsets = 0;
    int sumaDown = 0;
    Cell** matrix = NULL;
    Blok() {};
    Blok(int tVal, signed char* topS, signed char* leftS, int* topO, int* leftO) {
        
        matrix = new Cell*[tVal + 1];
        
        for (int i = 0; i < tVal + 1; i++) {
            matrix[i] = new Cell[tVal + 1];
        }
        matrix[0][0] = Cell(0);
        
        for (int i = 1; i < tVal + 1; i++) {
            matrix[0][i] = Cell(matrix[0][i - 1].value + topO[i - 1]);
            matrix[0][i].left = true;
            matrix[0][i].top = false;
            matrix[i][0] = Cell(matrix[i - 1][0].value + leftO[i - 1]);
            matrix[i][0].left = false;
            matrix[i][0].top = true;        }
        for (int i = 1; i < tVal + 1; i++) {
            for (int j = 1; j < tVal + 1; j++) {
                if (topS[j - 1] == leftS[i - 1]) {
                    
					matrix[i][j] = Cell(matrix[i - 1][j - 1].value);
                    matrix[i][j].top = true;
                    matrix[i][j].left = true;
                }
                
                else if (matrix[i - 1][j - 1].value <= matrix[i - 1][j].value && matrix[i - 1][j - 1].value <= matrix[i][j - 1].value) {
                    
					matrix[i][j] = Cell(matrix[i - 1][j - 1].value + 1);                    matrix[i][j].top = true;
                    matrix[i][j].left = true;
                }
                else if (matrix[i - 1][j].value <= matrix[i - 1][j - 1].value && matrix[i - 1][j].value <= matrix[i][j - 1].value) {
                    
					matrix[i][j] = Cell(matrix[i - 1][j].value + 1);
                    matrix[i][j].top = true;
                    matrix[i][j].left = false;
                }
                else {
                    
					matrix[i][j] = Cell(matrix[i][j - 1].value + 1);
                    matrix[i][j].top = false;
                    matrix[i][j].left = true;
                }
            }
        }
        
        //down offsets
        for (int i = 1; i <= tVal; i++) {
            downOffsets = downOffsets * 3 + (matrix[tVal][i].value - matrix[tVal][i-1].value + 1);
            sumaDown = sumaDown + (matrix[tVal][i].value - matrix[tVal][i - 1].value);
        }

        //right offsets
        for (int i = 1; i <= tVal; i++)
            rightOffsets = rightOffsets * 3 + (matrix[i][tVal].value - matrix[i - 1][tVal].value + 1);
    }
    
    string ispisi(vector<string> offsetA, vector<string> offsetB, string topS, string leftS) {
        string s = "";
        for (int i = 0; i < offsetA.size(); i++)
            s = s + offsetA[i];
        for (int i = 0; i < offsetA.size(); i++)
            s = s + offsetB[i];
        s = s + topS + leftS;
        return s;
    }
    
    int getDownOffsets(int tVal) {
        return downOffsets;
    }
    int getRightOffsets(int tVal) {
        return rightOffsets;
    }
};
void ispisi(vector<string> v) {
    for (int i = 0; i < v.size(); i++)
        cout << v[i];
    cout << endl;
    
}

string getString(vector<string> combo) {
    string s = "";
    for (int i = 0; i < combo.size(); i++)
        s = s + (string)combo[i];
    return s;
}

Blok *blokovi = NULL;

void generiraj(int i, int tVrijednost, vector<int> &counters) {
    if(i == tVrijednost * 4) {
        int* topO = new int[tVrijednost];
        int* leftO = new int[tVrijednost];
        signed char* topS = new signed char[tVrijednost];
        signed char* leftS = new signed char[tVrijednost];
        
        string s[4];
        for(int k = 0; k < 4; ++k) {
            s[k] = "";
            for(int i = tVrijednost * k; i < tVrijednost * (k+1); ++i) {
                if(k < 2) {
                    s[k] += to_string(O[counters[i]]);
                } else {
                    s[k] += E[counters[i]];
                }
            }
            
        }
        int hashirano = u_hash(s[0], s[1], s[2], s[3]);
        
        for (int i = 0; i < tVrijednost; i++)
            topO[i] = O[counters[i]];
        for (int i = tVrijednost; i < tVrijednost * 2; i++)
            leftO[i-tVrijednost] = O[counters[i]];
        for (int i = tVrijednost*2; i < tVrijednost*3; i++)
            topS[i-tVrijednost*2] = E[counters[i]];
        for (int i = tVrijednost*3; i < tVrijednost * 4; i++)
            leftS[i-tVrijednost*3] = E[counters[i]];
        
        Blok b = Blok(tVrijednost, topS, leftS, topO, leftO);
        
        blokovi[hashirano] = b;
        downOffsets[hashirano] = b.downOffsets;
        rightOffsets[hashirano] = b.rightOffsets;
        printf("%d %d\n", downOffsets[hashirano], rightOffsets[hashirano]);
        
        delete[] topO;
        delete[] leftO;
        delete[] topS;
        delete[] leftS;
        
        return;
    } else {
        bool generiraj_slova = i >= tVrijednost*2;
        int k = generiraj_slova ? 4 : 3;
        
        for(int l = 0; l < k; ++l) {
            if(generiraj_slova) {
                counters[i] = l;
            } else {
                counters[i] = l;
            }
            generiraj(i+1, tVrijednost, counters);
        }
    }
}

int calculateTValue(int lenA, int lenB) noexcept(true) {
    int len = 0;
    if (lenA > lenB)
        len = lenA;
        else
            len = lenB;
            double t = (log(len) / log(12)) / 2;
            
            return ((int)t + 1);
}

int** calculatematricaUdaljenost(int lenA, int lenB, int *podnizA, int *podnizB) {
    int** matrica = NULL;
    matrica = new int*[lenB / tVrijednost];
    
    
    /* Your algorithm here */
    
    
    
    int lenb = lenB / tVrijednost;
    int lena = lenA / tVrijednost;
    for (int h = 0; h < lenb; h++)
        matrica[h] = new int[lena];
    
    
    for (int i = 0; i < lenb; i++) {
        for (int j = 0; j < lena; j++) {
            matrica[i][j] = 0;
        }
    }
    
    
    //    string s = "";
    //    string &leftS;
    //    string topS;
    
    
    int cnter = 0;
    double duration = 0;
    std::clock_t start;
    start = std::clock();
    string sL = "";
    string sT = "";
    for (int k = 0; k < tVrijednost; k++)
        sT = sT + "1";
    for (int k = 0; k < tVrijednost; k++)
        sL = sL + "1";
    int leftS = podnizB[0];
    int topS = podnizA[0];
    //    s = sT + sL + topS + leftS;
    
    int hashirano = u_hash(sT, sL, topS, leftS);
    
    printf("lena %d lenb %d\n", lena, lenb);
    
    matrica[0][0] = hashirano;
    for (int k = 1; k < lena; k++) {
        topS = podnizA[k];
        hashirano = u_hash(sT, blokovi[matrica[0][k - 1]].rightOffsets, topS, leftS);
        matrica[0][k] = hashirano;
    }
    int initialtopS = podnizA[0];
    
    int maks = 0;
    for(int i = 0; i < triNaTVrijednost * triNaTVrijednost * cetiriNaTVrijenost * cetiriNaTVrijenost; ++i) {
//        if(i > 0 && blokovi[i-1].downOffsets == blokovi[i].downOffsets) {
//            continue;
//        }
//        
//        printf("%d %d\n", i, blokovi[i].downOffsets);

        if(blokovi[i].downOffsets > maks) {
            maks = blokovi[i].rightOffsets;
        }
//        maks = max(maks, blokovi[i].downOffsets);
    }
    
    
    for (int i = 1; i < lenb; i++) {
        
        leftS = podnizB[i];
        
        hashirano = u_hash(downOffsets[matrica[i - 1][0]], sL, initialtopS, leftS);
        //        hashirano = 100;
        matrica[i][0] = hashirano;
        //        matrica[i][i] = 100;
        if (cnter % 1000 == 0) {
            cout << cnter << endl;
            duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
            start = std::clock();
            std::cout << "Computation of 1000 blocks takes time:" << duration << " s \n";
        }
        cnter++;
        
        
        for (int j = 1; j < lena; j++) {
            matrica[i][j] = spoji_hasheve(downOffsets[matrica[i - 1][j]], rightOffsets[matrica[i][j - 1]], podnizA[j], leftS);
        }
        
    }
    return matrica;
}

void ucitajNizove() {
    ifstream infile("/Volumes/Zvijer/Google Drive/FER/BIO/repo/primjer-50000.in");
    if (!infile.is_open()) {
        cout << " Failed to open file" << endl;
    }
    else {
        cout << "Opened OK" << endl;
    }
    int cnt = 0;
    while (!infile.eof()) // To get you all the lines.
    {
        getline(infile, text); // Saves the line in STRING.
        if (cnt == 0)
            nizA = text;
        else if (cnt == 1)
            nizB = text;
        cnt++;
        
        //cout << text << endl; // Prints our STRING.
    }
    infile.close();
}

size_t getSizeBlokovi() {
    size_t val = pow(3, tVrijednost * 2)*pow(4, tVrijednost * 2);
    return val;
}

void urediNizove() {
    while (nizA.size() % tVrijednost != 0)
        nizA = nizA.substr(0, nizA.size() - 1);
    while (nizB.size() % tVrijednost != 0)
        nizB = nizB.substr(0, nizB.size() - 1);
}
void editScript(int** Matrix) {
    
    
    
    int i = (int)nizB.size()/tVrijednost-1; // {i = ROWS in int**}
    int j = (int)nizA.size()/tVrijednost-1; // {j = COLS in int**}
    int a = tVrijednost;
    int b = tVrijednost;
    int cnterB = (int)nizB.size()-1;
    int cnterA = (int)nizA.size()-1;
    Cell** matrix;
    //a = 0 -> got top in matrica {a = ROWS in Cell**}
    //b = 0 - > got left in matrica {b = COLS in Cell**}
    int cnter = 0;
    int size;
    if (nizA.size() > nizB.size())
        size = (int)nizA.size();
    else size = (int)nizB.size();
    int val = size * 2;
    vector<char> first(val);
    vector<char> second(val);
    vector<char> middle(val);
    
    cout << i << " " << j << endl;
    while ( (i+j)!=0 )
    {
        matrix = blokovi[Matrix[i][j]].matrix;
        while (true) {
            if (matrix[a][b].top == true && matrix[a][b].left == true) {
                a--;
                b--;
                first.insert(first.begin(), nizA[cnterA]);
                second.insert(second.begin(), nizB[cnterB]);
                if (nizA[cnterA] == nizB[cnterB]) {
                    middle.insert(middle.begin(), '|');
                }
                else middle.insert(middle.begin(), '.');
                cnterA--;
                cnterB--;
            }
            else if (matrix[a][b].top == true) {
                a--;
                second.insert(second.begin(), nizB[cnterB]);
                first.insert(first.begin(), '-');
                middle.insert(middle.begin(), ' ');
                cnterB--;
            }
            else {
                b--;
                second.insert(second.begin(), '-');
                first.insert(first.begin(), nizA[cnterA]);
                middle.insert(middle.begin(), ' ');
                cnterA--;
            }
            cnter++;
            if (i == 0 && j != 0) {
                if (a <= 0)
                    a = 0;
                if (b == 0)
                    break;
            }
            else if (j == 0 && i != 0) {
                if (b <= 0)
                    b = 0;
                if (a == 0)
                    break;
            }
            else {
                if (a == 0 || b == 0)
                    break;
            }
            
        }
        if (a == 0 && b == 0) {
            if (i == 0) {
                j--;
                a = 0;
                b = tVrijednost;
            } else if(j == 0) {
                i--;
                b = 0;
                a = tVrijednost;
            }
            else {
                i--;
                j--;
                a = tVrijednost;
                b = tVrijednost;
            }
            
        }
        else if (a == 0) {
            i--;
            a = tVrijednost;
        }
        else if (b == 0) {
            j--;
            b = tVrijednost;
        }
        //cout << i << " " << j << endl;
    }
    
    matrix = blokovi[Matrix[0][0]].matrix;
    while (true) {
        if (matrix[a][b].top == true && matrix[a][b].left == true) {
            a--;
            b--;
            first.insert(first.begin(), nizA[cnterA]);
            second.insert(second.begin(), nizB[cnterB]);
            if (nizA[cnterA] == nizB[cnterB]) {
                middle.insert(middle.begin(), '|');
            }
            else middle.insert(middle.begin(), '.');
            cnterA--;
            cnterB--;
        }
        else if (matrix[a][b].top == true) {
            a--;
            second.insert(second.begin(), nizB[cnterB]);
            first.insert(first.begin(), '-');
            middle.insert(middle.begin(), ' ');
            cnterB--;
        }
        else {
            b--;
            second.insert(second.begin(), '-');
            first.insert(first.begin(), nizA[cnterA]);
            middle.insert(middle.begin(), ' ');
            cnterA--;
        }
        cnter++;
        if (a == 0 && b == 0)
            break;
    }
    /*
     for (int i = 0; i < cnter; i++)
     cout << prvi[i];
     cout << endl;
     for (int i = 0; i < cnter; i++)
     cout << srednji[i];
     cout << endl;
     for (int i = 0; i < cnter; i++)
     cout << drugi[i];
     cout << endl;
     */
    
    int x = 1;
    if (size > 100)
        x = 60;
    else x = cnter;
    for (int j = 0; j < cnter; j = j + x) {
        outputFile << "Lines:" << j << " - " << (j+x) << endl;
        for (int i = j; i < j + x && i < cnter ;i++) {
            outputFile << first[i];
        }
        outputFile << endl;
        for (int i = j; i < j + x && i < cnter; i++) {
            outputFile << middle[i];
        }
        outputFile << endl;
        for (int i = j; i < j + x && i < cnter; i++) {
            outputFile << second[i];
        }
        outputFile << endl;
    }
    outputFile << endl;
}

void writeMinDistance(int** matrica) {
    
    int min = 0;
    
    for (int j = 0; j < nizA.size() / tVrijednost; j++) {
        min = min + blokovi[matrica[nizB.size() / tVrijednost - 1][j]].sumaDown;
    }
    min = min + (int)nizB.size();
    cout << "MIN DISTANCE:" << min << endl;
    
}

int slovo_u_br(char c) {
    int val;
    if(c == 'A') {
        val = 0;
    } else if(c == 'C'){
        val = 1;
    } else if(c == 'T'){
        val = 2;
    } else if(c == 'G'){
        val = 3;
    }
    return val;
}

int *podnizA;
int *podnizB;
void getsubArrays() {
    podnizA = new int[nizA.size() / tVrijednost];
    //    podnizA.resize(nizA.size() / tVrijednost);
    podnizB = new int[nizB.size() / tVrijednost];
    //    podnizB.resize(nizB.size() / tVrijednost);
    for (int i = 0; i < nizA.size()/tVrijednost; i++) {
        podnizA[i] = 0;
        for(int j = 0; j < tVrijednost; ++j) {
            podnizA[i] = podnizA[i] * 4 + slovo_u_br(nizA[i*tVrijednost + j]);
        }
    }
    for (int i = 0; i < nizB.size() / tVrijednost; i++) {
        podnizB[i] = 0;
        for(int j = 0; j < tVrijednost; ++j) {
            podnizB[i] = podnizB[i] * 4 + slovo_u_br(nizB[i*tVrijednost + j]);
        }
    }
}

void paralelnoPretprocesiranje() {
    E[0] = 'A';
    E[1] = 'C';
    E[2] = 'T';
    E[3] = 'G';
    O[0] = -1;
    O[1] = 0;
    O[2] = 1;
    
    vector<thread> threads;

    for(int c0 = 0; c0 < 3; ++ c0) {
        for(int c1 = 0; c1 < 3; ++c1) {
            auto code = [c0, c1]() {
                vector<int> comb;
                comb.resize(tVrijednost * 4);
                comb[0] = c0;
                comb[1] = c1;
                generiraj(2, tVrijednost, comb);
            };
            threads.push_back(thread(code));
        }
    }
    
    for(auto& t: threads) {
        t.join();
    }
}


int main()
{
    std::clock_t start;
    double duration;
    
    //    printf("%d\n", pretvori_slova("CC"));
    //    return 0;
    
    ucitajNizove();
    tVrijednost = calculateTValue((int)nizA.size(), (int)nizB.size());
    tVrijednost = 3;
    
    triNaTVrijednost = pow(3, tVrijednost);
    cetiriNaTVrijenost = pow(4, tVrijednost);
    cetiriNaTVrijenostNaKvadrat = cetiriNaTVrijenost * cetiriNaTVrijenost;
    K = triNaTVrijednost * cetiriNaTVrijenostNaKvadrat;
    
    downOffsets = new uint8_t[triNaTVrijednost * triNaTVrijednost * cetiriNaTVrijenostNaKvadrat];
    rightOffsets = new uint8_t[triNaTVrijednost * triNaTVrijednost * cetiriNaTVrijenostNaKvadrat];
    
    
    urediNizove();
    cout << "Prvi string:" << nizA << endl;
    cout << "Drugi string:" << nizB << endl;
    
    cout << "T value;" << tVrijednost << endl;
    cout << getSizeBlokovi() << endl;
    //getchar() ;
    double memory = sizeof(Blok) * getSizeBlokovi() + getSizeBlokovi() * sizeof(Cell) * (tVrijednost + 1) * (tVrijednost + 1);
    cout << "Memmory needed: " << ((memory / 1024) / 1024) << " MB" << endl;
    blokovi = new Blok[getSizeBlokovi()];
    
    cout << "Preprocessing STARTED" << endl;
    
    
    start = std::clock();
//    pretprocesiranje();

    
    paralelnoPretprocesiranje();
    
    getsubArrays();
    cout << "Preprocessing DONE" << endl;
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    
    printf("Maksimalni hash: %d\n", maksimalni);
    
    std::cout << "Duration of preprocessing:" << duration << " s\n";
    //    getchar();
    start = std::clock();
    
    //    return 0;
    
    int** matricaUdaljenosti = calculatematricaUdaljenost((int)nizA.size(), (int)nizB.size(), podnizA, podnizB);
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    
    std::cout << "Duration of calculating min distance:" << duration << '\n';
    
    writeMinDistance(matricaUdaljenosti);

    
    start = std::clock();
    
    editScript(matricaUdaljenosti);
    
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    
    std::cout << "Duration of calculating edit script:" << duration << '\n';
    outputFile.close();
    //    getchar();
    
    // delete all allocated memory
    delete[] blokovi;
    return 0;
}


