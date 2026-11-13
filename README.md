# Quiz Lab Struktur Data 3 & 4

**Nama:** Naufal Rasyiq Dziqri Simanjuntak
**NIM:** 251401002
**KOM:** B Struktur Data

**Video penjelasan:** (https://www.youtube.com/watch?v=KO56knchasQ)

## Struktur Folder

```
.
├── README.md
└── src/
    ├── soal1_nilai_mahasiswa.cpp
    ├── soal2_perpustakaan.cpp
    ├── soal3_rute_kampus.cpp
    └── soal4_hash_table.cpp
```

## Deskripsi Program

1. **Sistem Pengelolaan Nilai Mahasiswa**: Dynamic Array untuk nilai, Single Linked List untuk data mahasiswa, Insertion Sort, Linear Search (NIM), dan Binary Search (nilai).
2. **Antrean dan Buku Perpustakaan**: Queue (FIFO) untuk antrean, Stack (LIFO) untuk riwayat pengembalian, BST untuk ID buku dengan traversal Pre-Order, In-Order, dan Post-Order.
3. **Pencarian Rute Kampus**: Graf 6 vertex (A-F) dengan Adjacency Matrix, BFS, DFS, dan Dijkstra untuk rute terpendek.
4. **Hash Table**: Ukuran 20, Double Hashing, dengan Insert, Search, Remove, dan Display. Diuji dengan 15 data termasuk collision dan penghapusan.

## Cara Menjalankan

1. Buka folder proyek di VS Code, lalu buka terminal (`Ctrl + `` ` ``).
2. Kompilasi dan jalankan, misalnya soal 1:

```bash
g++ -std=c++11 src/soal1_nilai_mahasiswa.cpp -o soal1
./soal1
```

Untuk soal 2 sampai 4, ganti nama file dan outputnya. Jalankan dengan `.\soal1.exe`.
