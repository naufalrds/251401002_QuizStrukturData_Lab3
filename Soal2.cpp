#include <iostream>
#include <string>
using namespace std;

// ===== Queue (FIFO): antrean mahasiswa peminjam =====
struct QNode { string nama; QNode *next; };
class Queue {
    QNode *front = nullptr, *rear = nullptr;
public:
    void enqueue(const string &nama) {
        QNode *n = new QNode{nama, nullptr};
        if (!rear) front = rear = n;
        else { rear->next = n; rear = n; }
    }
    bool dequeue(string &out) {
        if (!front) return false;
        QNode *t = front; out = t->nama;
        front = front->next;
        if (!front) rear = nullptr;
        delete t; return true;
    }
    void tampil() {
        if (!front) { cout << "(antrean kosong)\n"; return; }
        cout << "Depan -> ";
        for (QNode *t = front; t; t = t->next) cout << t->nama << " -> ";
        cout << "Belakang\n";
    }
};

// ===== Stack (LIFO): riwayat pengembalian =====
struct SNode { string info; SNode *next; };
class Stack {
    SNode *top = nullptr;
public:
    void push(const string &info) { top = new SNode{info, top}; }
    bool pop(string &out) {
        if (!top) return false;
        SNode *t = top; out = t->info; top = top->next; delete t; return true;
    }
    void tampil() {
        if (!top) { cout << "(riwayat kosong)\n"; return; }
        cout << "Teratas -> ";
        for (SNode *t = top; t; t = t->next) cout << t->info << " | ";
        cout << "\n";
    }
};

// ===== BST: ID buku =====
struct BNode { int id; BNode *left, *right; };
class BST {
    BNode *root = nullptr;
    BNode *insert(BNode *n, int id) {
        if (!n) return new BNode{id, nullptr, nullptr};
        if (id < n->id) n->left = insert(n->left, id);
        else if (id > n->id) n->right = insert(n->right, id);
        else cout << "ID " << id << " sudah ada.\n";
        return n;
    }
    bool search(BNode *n, int id) {
        if (!n) return false;
        if (id == n->id) return true;
        return id < n->id ? search(n->left, id) : search(n->right, id);
    }
    void pre(BNode *n)  { if (n) { cout << n->id << " "; pre(n->left); pre(n->right); } }
    void in(BNode *n)   { if (n) { in(n->left); cout << n->id << " "; in(n->right); } }
    void post(BNode *n) { if (n) { post(n->left); post(n->right); cout << n->id << " "; } }
public:
    void insert(int id) { root = insert(root, id); }
    bool search(int id) { return search(root, id); }
    void tampil() {
        if (!root) { cout << "(BST kosong)\n"; return; }
        cout << "Pre-Order : "; pre(root);  cout << "\n";
        cout << "In-Order  : "; in(root);   cout << "\n";
        cout << "Post-Order: "; post(root); cout << "\n";
    }
};

int main() {
    Queue antrean; Stack riwayat; BST buku;
    int idAwal[] = {50, 30, 70, 20, 40, 60, 80};
    for (int id : idAwal) buku.insert(id);

    int pilih;
    do {
        cout << "\n=== PERPUSTAKAAN ===\n"
             << "1. Mahasiswa masuk antrean peminjaman\n"
             << "2. Layani peminjaman (dequeue)\n"
             << "3. Catat pengembalian buku (push riwayat)\n"
             << "4. Batalkan/lihat pengembalian terakhir (pop)\n"
             << "5. Tambah ID buku ke BST\n"
             << "6. Cari ID buku\n"
             << "7. Tampilkan antrean, riwayat, dan BST\n0. Keluar\nPilih: ";
        cin >> pilih;
        if (pilih == 1) {
            string nama; cout << "Nama mahasiswa: "; cin >> nama; antrean.enqueue(nama);
        } else if (pilih == 2) {
            string nama;
            if (antrean.dequeue(nama)) cout << nama << " dilayani (meminjam buku).\n";
            else cout << "Antrean kosong.\n";
        } else if (pilih == 3) {
            string nama; int id;
            cout << "Nama pengembali: "; cin >> nama;
            cout << "ID buku: "; cin >> id;
            riwayat.push(nama + " (buku " + to_string(id) + ")");
        } else if (pilih == 4) {
            string info;
            if (riwayat.pop(info)) cout << "Pengembalian terakhir: " << info << "\n";
            else cout << "Riwayat kosong.\n";
        } else if (pilih == 5) {
            int id; cout << "ID buku: "; cin >> id; buku.insert(id);
        } else if (pilih == 6) {
            int id; cout << "ID dicari: "; cin >> id;
            cout << (buku.search(id) ? "Buku ditemukan.\n" : "Buku tidak ditemukan.\n");
        } else if (pilih == 7) {
            cout << "-- Antrean --\n"; antrean.tampil();
            cout << "-- Riwayat Pengembalian --\n"; riwayat.tampil();
            cout << "-- Isi BST --\n"; buku.tampil();
        }
    } while (pilih != 0);
    return 0;
}
