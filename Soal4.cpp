#include <iostream>
#include <string>
using namespace std;

const int SIZE = 20;

enum Status { KOSONG, TERISI, DIHAPUS };

struct Slot {
    long long key = 0;
    string value;
    Status status = KOSONG;
};

class HashTable {
    Slot tabel[SIZE];
    int hash1(long long key) { return key % 20; }
    int hash2(long long key) { return 19 - (key % 19); }
public:
    bool insert(long long key, const string &value) {
        if (search(key) != -1) { cout << "Key " << key << " sudah ada.\n"; return false; }
        int h1 = hash1(key), h2 = hash2(key);
        for (int i = 0; i < SIZE; i++) {
            int idx = (h1 + i * h2) % SIZE;
            if (tabel[idx].status != TERISI) {
                tabel[idx].key = key; tabel[idx].value = value; tabel[idx].status = TERISI;
                if (i > 0) cout << "  [Collision] " << key << " ditempatkan di indeks " << idx << " setelah " << i << " probe\n";
                else cout << "  " << key << " -> indeks " << idx << "\n";
                return true;
            }
        }
        cout << "Tabel penuh / tidak ditemukan slot untuk " << key << "\n";
        return false;
    }
    int search(long long key) {
        int h1 = hash1(key), h2 = hash2(key);
        for (int i = 0; i < SIZE; i++) {
            int idx = (h1 + i * h2) % SIZE;
            if (tabel[idx].status == KOSONG) return -1;
            if (tabel[idx].status == TERISI && tabel[idx].key == key) return idx;
        }
        return -1;
    }
    bool remove(long long key) {
        int idx = search(key);
        if (idx == -1) { cout << "Key " << key << " tidak ditemukan.\n"; return false; }
        tabel[idx].status = DIHAPUS;
        cout << "Key " << key << " (" << tabel[idx].value << ") dihapus dari indeks " << idx << "\n";
        return true;
    }
    void display() {
        cout << "Idx | NIM        | Nama\n----+------------+----------------\n";
        for (int i = 0; i < SIZE; i++) {
            cout << (i < 10 ? " " : "") << i << "  | ";
            if (tabel[i].status == TERISI) cout << tabel[i].key << " | " << tabel[i].value;
            else if (tabel[i].status == DIHAPUS) cout << "(dihapus)";
            else cout << "-";
            cout << "\n";
        }
    }
    void cari(long long key) {
        int idx = search(key);
        if (idx == -1) cout << "NIM " << key << " tidak ditemukan.\n";
        else cout << "NIM " << key << " ditemukan di indeks " << idx << ": " << tabel[idx].value << "\n";
    }
};

int main() {
    HashTable ht;

    // 15 data uji (sebagian sengaja memicu collision: key % 20 sama)
    struct D { long long nim; const char *nama; };
    D data[] = {
        {251401001,"Andi"},   {251401002,"Budi"},  {251401003,"Citra"},
        {251401004,"Dewi"},   {251401005,"Eko"},   {251401006,"Fajar"},
        {251401007,"Gita"},   {251401008,"Hana"},  {251401009,"Indra"},
        {251401010,"Joko"},   {251401021,"Kiki"},  {251401041,"Lina"},   // 021,041 collision dgn 001
        {251401022,"Maya"},   {251401042,"Nando"}, {251401061,"Oka"}     // collision dgn 001/002
    };
    cout << "=== INSERT 15 DATA UJI ===\n";
    for (auto &d : data) ht.insert(d.nim, d.nama);

    cout << "\n=== DISPLAY ===\n"; ht.display();

    cout << "\n=== SEARCH ===\n";
    ht.cari(251401041);
    ht.cari(251401999);

    cout << "\n=== REMOVE ===\n";
    ht.remove(251401021);
    ht.remove(251401999);
    ht.cari(251401021);
    ht.cari(251401041);   // tetap ditemukan setelah penghapusan (tombstone)

    cout << "\n=== DISPLAY SETELAH HAPUS ===\n"; ht.display();

    // menu interaktif
    int pilih;
    do {
        cout << "\n--- MENU ---\n1. Insert\n2. Search\n3. Remove\n4. Display\n0. Keluar\nPilih: ";
        cin >> pilih;
        if (pilih == 1) { long long k; string n; cout << "NIM: "; cin >> k; cout << "Nama: "; cin >> n; ht.insert(k, n); }
        else if (pilih == 2) { long long k; cout << "NIM: "; cin >> k; ht.cari(k); }
        else if (pilih == 3) { long long k; cout << "NIM: "; cin >> k; ht.remove(k); }
        else if (pilih == 4) ht.display();
    } while (pilih != 0);
    return 0;
}
