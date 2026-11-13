#include <iostream>
#include <string>
using namespace std;

// ===== Single Linked List: data mahasiswa =====
struct Mahasiswa {
    string nim, nama;
    double nilai;
    Mahasiswa *next;
};

class ListMahasiswa {
public:
    Mahasiswa *head = nullptr;
    int jumlah = 0;

    void tambah(const string &nim, const string &nama, double nilai) {
        Mahasiswa *baru = new Mahasiswa{nim, nama, nilai, nullptr};
        if (!head) head = baru;
        else {
            Mahasiswa *t = head;
            while (t->next) t = t->next;
            t->next = baru;
        }
        jumlah++;
    }
    // Linear Search berdasarkan NIM
    Mahasiswa *cariNIM(const string &nim) {
        for (Mahasiswa *t = head; t; t = t->next)
            if (t->nim == nim) return t;
        return nullptr;
    }
    void tampil() {
        cout << "NIM\t\tNama\t\tNilai\n";
        for (Mahasiswa *t = head; t; t = t->next)
            cout << t->nim << "\t" << t->nama << "\t\t" << t->nilai << "\n";
    }
    ~ListMahasiswa() {
        while (head) { Mahasiswa *t = head; head = head->next; delete t; }
    }
};

// ===== Dynamic Array: kumpulan nilai =====
class DynArray {
public:
    double *data;
    int size, cap;
    DynArray() : size(0), cap(2) { data = new double[cap]; }
    ~DynArray() { delete[] data; }
    void push(double v) {
        if (size == cap) {
            cap *= 2;
            double *baru = new double[cap];
            for (int i = 0; i < size; i++) baru[i] = data[i];
            delete[] data;
            data = baru;
        }
        data[size++] = v;
    }
    // Insertion Sort (kecil -> besar)
    void insertionSort() {
        for (int i = 1; i < size; i++) {
            double key = data[i];
            int j = i - 1;
            while (j >= 0 && data[j] > key) { data[j + 1] = data[j]; j--; }
            data[j + 1] = key;
        }
    }
    // Binary Search (array harus sudah terurut), return index atau -1
    int binarySearch(double target) {
        int lo = 0, hi = size - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (data[mid] == target) return mid;
            if (data[mid] < target) lo = mid + 1;
            else hi = mid - 1;
        }
        return -1;
    }
    void tampil() {
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << "\n";
    }
};

int main() {
    ListMahasiswa list;
    DynArray nilai;
    bool terurut = false;
    int pilih;

    // data awal
    list.tambah("251401001", "Andi", 85); nilai.push(85);
    list.tambah("251401002", "Budi", 70); nilai.push(70);
    list.tambah("251401003", "Citra", 92); nilai.push(92);
    list.tambah("251401004", "Dewi", 60); nilai.push(60);

    do {
        cout << "\n=== SISTEM PENGELOLAAN NILAI MAHASISWA ===\n"
             << "1. Tambah mahasiswa\n2. Tampilkan data mahasiswa\n"
             << "3. Urutkan nilai (Insertion Sort)\n4. Cari mahasiswa by NIM (Linear Search)\n"
             << "5. Cari nilai (Binary Search)\n6. Tampilkan semua\n0. Keluar\nPilih: ";
        cin >> pilih;
        if (pilih == 1) {
            string nim, nama; double n;
            cout << "NIM: "; cin >> nim;
            cout << "Nama: "; cin >> nama;
            cout << "Nilai: "; cin >> n;
            list.tambah(nim, nama, n);
            nilai.push(n);
            terurut = false;
        } else if (pilih == 2) {
            list.tampil();
        } else if (pilih == 3) {
            nilai.insertionSort();
            terurut = true;
            cout << "Nilai terurut: "; nilai.tampil();
        } else if (pilih == 4) {
            string nim; cout << "NIM dicari: "; cin >> nim;
            Mahasiswa *m = list.cariNIM(nim);
            if (m) cout << "Ditemukan: " << m->nim << " | " << m->nama << " | " << m->nilai << "\n";
            else cout << "NIM tidak ditemukan.\n";
        } else if (pilih == 5) {
            if (!terurut) { cout << "Urutkan nilai dulu (menu 3).\n"; continue; }
            double n; cout << "Nilai dicari: "; cin >> n;
            int idx = nilai.binarySearch(n);
            if (idx >= 0) cout << "Nilai " << n << " ditemukan di indeks " << idx << "\n";
            else cout << "Nilai tidak ditemukan.\n";
        } else if (pilih == 6) {
            cout << "-- Data mahasiswa --\n"; list.tampil();
            cout << "-- Nilai (urutan array saat ini) --\n"; nilai.tampil();
        }
    } while (pilih != 0);
    return 0;
}
