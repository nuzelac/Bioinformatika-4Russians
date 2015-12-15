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
#include <unordered_map>

using namespace std;

std::map<int, string> hashevi;
//std::unordered_map<int, int> myMap;
int myMap[17000000];
//int myMap[
string text;
string nizA;
string nizB;
int tVrijednost;
vector<string> E(4);
vector<string> O(3);
ofstream outputFile("E:\program3data.txt");
//...
int triNaTVrijednost;
int cetiriNaTVrijenost;
int cetiriNaTVrijenostNaKvadrat;


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

inline int spoji_hasheve(int h1, int h2, int h3, int h4) {
//    int h_konacno = h1;
//    h_konacno = h_konacno * pow(4, tVrijednost) + h2;
//    h_konacno = h_konacno * pow(4, tVrijednost) + h3;
//    h_konacno = h_konacno * pow(4, tVrijednost) + h4;
    
    int h_desni = h3 * cetiriNaTVrijenost + h4;
    int h_lijevi = h1 * triNaTVrijednost + h2;
    int h_konacno = h_lijevi * cetiriNaTVrijenostNaKvadrat + h_desni;
    
//    maksimalni = max(maksimalni, h_konacno);

    return h_konacno;
}

int u_hash(string pomak1, string pomak2, string &a1, string &a2) {
    int h1 = pretvori_pomak(pomak1);
    int h2 = pretvori_pomak(pomak2);
    int h3 = pretvori_slova(a1);
    int h4 = pretvori_slova(a2);
    
    //            printf("%d %d %d %d\n", h1, h2, h3, h4);
    
    int h_konacno = spoji_hasheve(h1, h2, h3, h4);
    
//    if(hashevi.count(h_konacno) > 0) {
//        string s1 = hashevi[h_konacno];
//        string s2 = pomak1 + pomak2 + a1 + a2;
//        if(s1 != s2) {
//            printf("Vec postoji: %s\n", s1.c_str());
//            printf("Moje: %s\n", s2.c_str());
//            exit(-1);
//        }
//    }
//    hashevi[h_konacno] = pomak1 + pomak2 + a1 + a2;

    return h_konacno;
}

int u_hash(string pomak1, int h2, string &a1, string &a2) {
    int h1 = pretvori_pomak(pomak1);
    int h3 = pretvori_slova(a1);
    int h4 = pretvori_slova(a2);
    
    int h_konacno = spoji_hasheve(h1, h2, h3, h4);
    return h_konacno;
}

int u_hash(int h1, string pomak2, string &a1, string &a2) {
    int h2 = pretvori_pomak(pomak2);
    int h3 = pretvori_slova(a1);
    int h4 = pretvori_slova(a2);
    
    int h_konacno = spoji_hasheve(h1, h2, h3, h4);
    return h_konacno;
}

int u_hash(int h1, int h2, string &a1, string &a2) {
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
    int offset;
    int offsetExtraDR = 5; // down ROW
    int offsetExtraRC = 5; // right COLUMN
    int value;
    bool top;
    bool left;
    Cell() {};
    Cell(int val, int off) { offset = off; value = val; }
    /*
     int getOffset() { return offset; }
     int getDR() { return offsetExtraDR; }
     int getRC() { return offsetExtraRC; }
     
     int getValue() { return value; }
     bool getLeft() { return left; }
     bool getTop() { return top; }
     void setTop(bool val) { top = val; }
     void setLeft(bool val) { left = val; }
     void setOffset(int val) { offset = val; }
     void setOffsetDR(int val) { offsetExtraDR = val; }
     void setOffsetRC(int val) { offsetExtraRC = val; }
     */
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
    int downOffsets = 0;
    int rightOffsets = 0;
    //string leftOffsets = "";
    //string topOffsets = "";
    int sumaDown = 0;
    Cell** matrix = NULL;
    Blok() {};
    Blok(int tVal, string topS, string leftS, vector<string> topO, vector<string> leftO) {
        
        matrix = new Cell*[tVal + 1];
        
        for (int i = 0; i < tVal + 1; i++) {
            matrix[i] = new Cell[tVal + 1];
        }
        matrix[0][0] = Cell(0, 0);
        
        for (int i = 1; i < tVal + 1; i++) {
            matrix[0][i] = Cell(matrix[0][i - 1].value + stoi(topO[i - 1]), stoi(topO[i - 1]));
            matrix[0][i].left = true;
            matrix[0][i].top = false;
            matrix[i][0] = Cell(matrix[i - 1][0].value + stoi(leftO[i - 1]), stoi(leftO[i - 1]));
            matrix[i][0].left = false;
            matrix[i][0].top = true;
        }
        int min = 0;
        for (int i = 1; i < tVal + 1; i++) {
            for (int j = 1; j < tVal + 1; j++) {
                if (topS[j - 1] == leftS[i - 1]) {
                    
                    matrix[i][j] = Cell(matrix[i - 1][j - 1].value, 0);
                    matrix[i][j].top = true;
                    matrix[i][j].left = true;
                }
                
                else if (matrix[i - 1][j - 1].value <= matrix[i - 1][j].value && matrix[i - 1][j - 1].value <= matrix[i][j - 1].value) {
                    
                    matrix[i][j] = Cell(matrix[i - 1][j - 1].value + 1, 0);
                    matrix[i][j].top = true;
                    matrix[i][j].left = true;
                }
                else if (matrix[i - 1][j].value <= matrix[i - 1][j - 1].value && matrix[i - 1][j].value <= matrix[i][j - 1].value) {
                    
                    matrix[i][j] = Cell(matrix[i - 1][j].value + 1, 0);
                    matrix[i][j].top = true;
                    matrix[i][j].left = false;
                }
                else {
                    
                    matrix[i][j] = Cell(matrix[i][j - 1].value + 1, 0);
                    matrix[i][j].top = false;
                    matrix[i][j].left = true;
                }
            }
        }
        
        for (int i = 1; i < tVal + 1; i++) {
            matrix[tVal][i].offset = (matrix[tVal][i].value - matrix[tVal][i - 1].value);
            matrix[i][tVal].offset = (matrix[i][tVal].value - matrix[i - 1][tVal].value);
        }
        matrix[tVal][tVal].offsetExtraDR = (matrix[tVal][tVal].value - matrix[tVal][tVal - 1].value);
        matrix[tVal][tVal].offsetExtraRC = (matrix[tVal][tVal].value - matrix[tVal - 1][tVal].value);
        
        //down offsets
        for (int i = 1; i < tVal; i++) {
            downOffsets = downOffsets * 3 + (matrix[tVal][i].offset + 1);
            sumaDown = sumaDown + matrix[tVal][i].offset;
        }
        sumaDown = sumaDown + matrix[tVal][tVal].offsetExtraDR;
        downOffsets = downOffsets * 3 + (matrix[tVal][tVal].offsetExtraDR + 1);
//        printf("%d\n", matrix[tVal][tVal].offsetExtraDR);
        //right offsets
        for (int i = 1; i < tVal; i++)
            rightOffsets = rightOffsets * 3 + (matrix[i][tVal].offset + 1);
        rightOffsets = rightOffsets * 3 + (matrix[tVal][tVal].offsetExtraRC + 1);
        
        //top offsets
        //for (int i = 1; i <= tVal; i++)
        //	topOffsets = topOffsets + std::to_string(matrix[0][i].offset);
        //left offsets
        //	for (int i = 1; i <= tVal; i++)
        //	leftOffsets = leftOffsets + std::to_string(matrix[i][0].offset);
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
    void ispisiSVE(int tValue) {
        cout << "OFFSETS:" << endl;
        for (int i = 0; i < tValue + 1; i++) {
            for (int j = 0; j < tValue + 1; j++) {
                if (i == tValue && j == tValue)
                    cout << matrix[i][j].offsetExtraDR << "\\" << matrix[i][j].offsetExtraRC << matrix[i][j].writeLeft() << "|" << matrix[i][j].writeTop();
                else
                    cout << matrix[i][j].offset << " " << matrix[i][j].writeLeft() << "|" << matrix[i][j].writeTop();
            }
            cout << endl;
        }
        cout << "VALUES:" << endl;
        for (int i = 0; i < tValue + 1; i++) {
            for (int j = 0; j < tValue + 1; j++) {
                cout << matrix[i][j].value << " ";
            }
            cout << endl;
        }
        /*
         cout << "DOWN-ROW OFFSET:" << endl;
         cout << matrix[tValue][tValue].getDR() << endl;
         cout << "RIGHT-COLUMN OFFSET:" << endl;
         cout << matrix[tValue][tValue].getRC() << endl;
         */
    }
    int getDownOffsets(int tVal) {
        return downOffsets;
    }
    int getRightOffsets(int tVal) {
        return rightOffsets;
    }
    //	string gettopOffsets(int tVal) {
    //		return topOffsets;
    //	}
    //	string getLeftOffsets(int tVal) {
    //		return leftOffsets;
    //	}
    
    
    
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

void pretprocesiranje() {
    
    E[0] = "A";
    E[1] = "C";
    E[2] = "T";
    E[3] = "G";
    O[0] = "-1";
    O[1] = "0";
    O[2] = "1";
    vector<string> combo(tVrijednost * 4);
    
    vector<int> counters(tVrijednost * 4);
    for (int i = 0; i < tVrijednost * 4; i++)
        counters[i] = 0;
    int start = tVrijednost * 4 - 1;
    int hash = 0;
    int cnter = 0;
    vector<string> topO(tVrijednost);
    vector<string> leftO(tVrijednost);
    string topS = "";
    string leftS = "";
    int topOcnt = 0;
    int leftOcnt = 0;
//    std::hash<string> hash_fn;
    std::clock_t timer;
    double duration;
    
    timer = std::clock();
    
    while (counters[0] <= 2) {
        cnter++;
        hash = 0;
        
        for (int i = start; i >= 0; i--) {
            if (i > (start - 2 * tVrijednost)) {
                
                combo[i] = E[counters[i]];
            }
            else {
                
                combo[i] = O[counters[i]];
            }
        }
        counters[start]++;
        if (counters[start] > 3) {
            counters[start] = 0;
            bool repeat = true;
            int pomak = 1;
            
            while (repeat) {
                if ((start - pomak) > (start - 2 * tVrijednost)) {
                    if (counters[start - pomak] < 3) {
                        counters[start - pomak]++;
                        repeat = false;
                    }
                    else {
                        counters[start - pomak] = 0;
                        pomak++;
                    }
                }
                else {
                    if (counters[start - pomak] < 2) {
                        counters[start - pomak]++;
                        repeat = false;
                    }
                    else {
                        if (start - pomak == 0) {
                            repeat = false;
                            counters[0] = 3;
                        }
                        else {
                            counters[start - pomak] = 0;
                            pomak++;
                        }
                    }
                }
            }
        }
        
        
//        string s = getString(combo);
        string s[4];
        for(int k = 0; k < 4; ++k) {
            s[k] = "";
            for(int i = tVrijednost * k; i < tVrijednost * (k+1); ++i) {
                s[k] += combo[i];
            }
        }
        int hashirano = u_hash(s[0], s[1], s[2], s[3]);
        myMap[hashirano] = cnter - 1;
        //outputFile << cnter << endl;
        
        topS = "";
        leftS = "";
        topOcnt = 0;
        
        
        for (int i = 0; i < tVrijednost; i++)
            topO[topOcnt++] = combo[i];
        topOcnt = 0;
        for (int i = tVrijednost; i < tVrijednost * 2; i++)
            leftO[topOcnt++] = combo[i];
        for (int i = tVrijednost * 2; i < tVrijednost * 3; i++)
            topS = topS + combo[i];
        for (int i = tVrijednost * 3; i < tVrijednost * 4; i++)
            leftS = leftS + combo[i];
        
        
        
        Blok b = Blok(tVrijednost, topS, leftS, topO, leftO);
        
        blokovi[cnter - 1] = b;
        
        if (cnter % 100000 == 0) {
            duration = (std::clock() - timer) / (double)CLOCKS_PER_SEC;
            
            std::cout << "Duration of 100 000 blocs preprocessed:" << duration << '\n';
            cout << cnter << endl;
        }
        //cout << cnter << endl;
    }
    cout << cnter << endl;
    //blokovi.push_back(Blok());
    
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
    
    matrica[0][0] = myMap[hashirano];
    for (int k = 1; k < lena; k++) {
        topS = podnizA[k];
        hashirano = u_hash(sT, blokovi[matrica[0][k - 1]].rightOffsets, topS, leftS);
        matrica[0][k] = myMap[hashirano];
    }
    int initialtopS = podnizA[0];
    for (int i = 1; i < lenb; i++) {
        
        leftS = podnizB[i];
        
        hashirano = u_hash(blokovi[matrica[i - 1][0]].downOffsets, sL, initialtopS, leftS);
//        hashirano = 100;
        matrica[i][0] = myMap[hashirano];
//        matrica[i][i] = 100;
        if (cnter % 100 == 0) {
            cout << cnter << endl;
            duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
            start = std::clock();
            std::cout << "\Computation of 100 blocks takes time:" << duration << " s \n";
        }
        cnter++;
        
        
        for (int j = 1; j < lena; j++) {
            hashirano = spoji_hasheve(blokovi[matrica[i - 1][j]].downOffsets, blokovi[matrica[i][j - 1]].rightOffsets, podnizA[j], leftS);
//            hashirano = 100;
            matrica[i][j] = myMap[hashirano];
//            matrica[i][j] = 100;
            
        }
        
        //	duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
        
        //	std::cout << "\Computation of All blocks takes time:" << duration * 1000 << " ms \n";
        
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
void editScript(int** matrica) {
    /*
     int i = nizB.size();
     int j = nizA.size();
     int size;
     if (i > j)
     size = i;
     else size = j;
     int val = size * 2;
     vector<char> prvi(val);
     vector<char> drugi(val);
     vector<char> srednji(val);
     int cnt = 0;
     int brojPoklopljenih = 0;
     while (matrica[i][j].left != false || matrica[i][j].top != false) {
     //cout << i << " " << j << " " << size << endl;
     
     if (matrica[i][j].left == true && matrica[i][j].top == true) {
     prvi.insert(prvi.begin(), nizA[j - 1]);
     drugi.insert(drugi.begin(), nizB[i - 1]);
     if (nizA[j - 1] == nizB[i - 1]) {
     srednji.insert(srednji.begin(), '\|');
     brojPoklopljenih++;
     }
     else srednji.insert(srednji.begin(), '.');
     i--;
     j--;
     
     //cout << "TOPLEFT" << endl;
     
     }
     else if (matrica[i][j].left == true && matrica[i][j].top == false) {
     prvi.insert(prvi.begin(), nizA[j - 1]);
     drugi.insert(drugi.begin(), '-');
     srednji.insert(srednji.begin(), ' ');
     j--;
     
     
     //cout << "LEFT" << endl;
     }
     else {
     prvi.insert(prvi.begin(), '-');
     drugi.insert(drugi.begin(), nizB[i - 1]);
     srednji.insert(srednji.begin(), ' ');
     i--;
     
     //cout << "TOP" << endl;
     }
     cnt++;
     }
     int x = 1;
     if (size > 100)
     x = 50;
     else x = cnt;
     for (int j = 0; j < cnt; j = j + x) {
     for (int i = j; i < j + x; i++) {
     outputFile << prvi[i];
     }
     outputFile << endl;
     for (int i = j; i < j + x; i++) {
     outputFile << srednji[i];
     }
     outputFile << endl;
     for (int i = j; i < j + x; i++) {
     outputFile << drugi[i];
     }
     outputFile << endl;
     }
     outputFile << endl;
     cout << "Broj poklapanja: " << brojPoklopljenih << "\\" << cnt << " (" << ((double)brojPoklopljenih / (double)cnt) * 100 << " %)" << endl;
     */
}

void writeMinDistance(int** matrica) {
    
    int min = 0;
    
    for (int j = 0; j < nizA.size() / tVrijednost; j++) {
        min = min + blokovi[matrica[nizB.size() / tVrijednost - 1][j]].sumaDown;
    }
    min = min + nizB.size();
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
    int zadnji;
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
int main()
{
    std::clock_t start;
    double duration;
    
//    printf("%d\n", pretvori_slova("CC"));
//    return 0;
    
    
    
    ucitajNizove();
    tVrijednost = calculateTValue(nizA.size(), nizB.size());
    tVrijednost = 3;
    
    triNaTVrijednost = pow(3, tVrijednost);
    cetiriNaTVrijenost = pow(4, tVrijednost);
    cetiriNaTVrijenostNaKvadrat = cetiriNaTVrijenost * cetiriNaTVrijenost;
    urediNizove();
    cout << "Prvi string:" << nizA << endl;
    cout << "Drugi string:" << nizB << endl;
    
    cout << "T value;" << tVrijednost << endl;
    cout << getSizeBlokovi() << endl;
    //getchar() ;
    double memory = sizeof(Blok) * getSizeBlokovi();
    cout << "Memmory needed: " << ((memory / 1024) / 1024) << " MB" << endl;
    blokovi = new Blok[getSizeBlokovi()];
    
    cout << "Preprocessing STARTED" << endl;
    
    
    start = std::clock();
    pretprocesiranje();
    ;
    /*
     string s = "1111ATTC";
     std::hash<string> hash_f;
     cout << blokovi[myMap.find(hash_f(s))->second].ispisi() << endl;
     blokovi[myMap.find(hash_f(s))->second].ispisiSVE();
     getchar();
     */
    getsubArrays();
    cout << "Preprocessing DONE" << endl;
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    
    printf("Maksimalni hash: %d\n", maksimalni);
    
    std::cout << "Duration of preprocessing:" << duration << " s\n";
//    getchar();
    start = std::clock();
    
    /* Your algorithm here */
    
//    return 0;
    
    int** matricaUdaljenosti = calculatematricaUdaljenost(nizA.size(), nizB.size(), podnizA, podnizB);
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    
    std::cout << "Duration of calculating min distance:" << duration << '\n';
    //getchar();
    /*
     for (int i = 0; i < nizB.size() + 1; i++) {
     for (int j = 0; j < nizA.size() + 1; j++) {
     if (i%tVrijednost == 0 && j%tVrijednost == 0 && i>0 && j>0) {
     cout << matricaUdaljenosti[i][j].getDR() << "\\" << matricaUdaljenosti[i][j].getRC() << " " << matricaUdaljenosti[i][j].writeLeft() << "|" << matricaUdaljenosti[i][j].writeTop() << " ";
     }
     else {
     cout << matricaUdaljenosti[i][j].getOffset() << " " << matricaUdaljenosti[i][j].writeLeft() << "|" << matricaUdaljenosti[i][j].writeTop() << " ";;
     }
     }
     cout << endl;
     }
     */
    
    
    
    
    
    writeMinDistance(matricaUdaljenosti);
//    getchar();
    start = std::clock();
    
    /* Your algorithm here */
    
    
    
    editScript(matricaUdaljenosti);
    
    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    
    std::cout << "Duration of calculating edit script:" << duration << '\n';
    outputFile.close();
//    getchar();
    
    // delete all allocated memory
    delete[] blokovi;
    return 0;
}