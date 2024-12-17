#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

const int MAX_TRANSAKSI = 100; 
int jumlahTransaksi = 3;

struct Transaksi {
    string tanggal;
    string kategori;
    string deskripsi;
    long long harga;
    string jenis; 
    Transaksi* next; 
};

Transaksi* head = nullptr; // Pointer ke transaksi pertama
Transaksi* transaksiHashTable[MAX_TRANSAKSI]; // Hash table untuk menyimpan transaksi berdasarkan nomor urut
stack<Transaksi*> transaksiStack; // Stack untuk menyimpan transaksi
queue<Transaksi*> transaksiQueue; // Queue untuk menyimpan transaksi

int hashFunction(int nomorTransaksi) {
    return (nomorTransaksi - 1) % MAX_TRANSAKSI;
}

void tambahTransaksi() {
    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        cout << "Batas transaksi sudah mencapai maksimum." << endl;
        return;
    }

    Transaksi* newTransaksi = new Transaksi();
    cout << "Masukkan tanggal (tanggal/bulan/tahun): ";
    cin >> newTransaksi->tanggal;
    cout << "Masukkan kategori: ";
    cin >> newTransaksi->kategori;
    cout << "Masukkan deskripsi transaksi: ";
    cin.ignore();
    getline(cin, newTransaksi->deskripsi);
    cout << "Masukkan harga: Rp.";
    cin >> newTransaksi->harga;
    cout << "Masukkan jenis transaksi (Pemasukan / Pengeluaran): ";
    cin >> newTransaksi->jenis;

    newTransaksi->next = nullptr;

    if (head == nullptr) {
        head = newTransaksi;
    } else {
        Transaksi* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newTransaksi;
    }

    transaksiHashTable[jumlahTransaksi] = newTransaksi; // Tambahkan transaksi ke hash table
    jumlahTransaksi++;
    cout << "Transaksi berhasil ditambahkan" << endl;
}

void tampilkanTransaksi() {
    cout << "Daftar Transaksi: \n" << endl;
    Transaksi* current = head;
    int nomorTransaksi = 1;

    while (current != nullptr) {
        cout << "Transaksi ke-" << nomorTransaksi << ": \n"
            << "Tanggal: " << current->tanggal << "\n"
            << "Kategori: " << current->kategori << "\n"
            << "Deskripsi: " << current->deskripsi << "\n"
            << "Harga: Rp." << current->harga << "\n"
            << "Jenis: " << current->jenis << "\n" << endl;

        current = current->next;
        nomorTransaksi++;
    }
}

void cariTransaksi() {
    int nomorTransaksi;
    cout << "Masukkan nomor transaksi yang ingin dicari: ";
    cin >> nomorTransaksi;

    if (nomorTransaksi > jumlahTransaksi || nomorTransaksi < 1) {
        cout << "Nomor transaksi tidak valid." << endl;
        return;
    }

    Transaksi* transaksi = transaksiHashTable[hashFunction(nomorTransaksi)];
    if (transaksi != nullptr) {
        cout << "Detail Transaksi: \n"
            << "Tanggal: " << transaksi->tanggal << "\n"
            << "Kategori: " << transaksi->kategori << "\n"
            << "Deskripsi: " << transaksi->deskripsi << "\n"
            << "Harga: Rp." << transaksi->harga << "\n"
            << "Jenis: " << transaksi->jenis << "\n" << endl;
    } else {
        cout << "Transaksi tidak ditemukan." << endl;
    }
}

void hapusTransaksiBiasa() {
    if (head == nullptr) {
        cout << "Tidak ada transaksi yang dapat dihapus." << endl;
        return;
    }

    int nomorTransaksi;
    tampilkanTransaksi();
    cout << "Masukkan nomor transaksi yang ingin dihapus: ";
    cin >> nomorTransaksi;

    if (nomorTransaksi > jumlahTransaksi || nomorTransaksi < 1) {
        cout << "Nomor transaksi tidak valid." << endl;
        return;
    }

    Transaksi* current = head;
    Transaksi* previous = nullptr;
    int nomorTransaksiSaatIni = 1;
    while (current != nullptr && nomorTransaksiSaatIni < nomorTransaksi) {
        previous = current;
        current = current->next;
        nomorTransaksiSaatIni++;
    }

    if (current == nullptr) {
        cout << "Nomor transaksi tidak valid." << endl;
        return;
    }

    if (previous == nullptr) {
        head = current->next;
    } else {
        previous->next = current->next;
    }

    delete current;
    transaksiHashTable[hashFunction(nomorTransaksi)] = nullptr; // Hapus dari hash table
    cout << "Transaksi berhasil dihapus." << endl;
}

void hapusTransaksiStack() {
    if (head == nullptr) {
        cout << "Tidak ada transaksi yang dapat dihapus dari stack." << endl;
        return;
    }

    Transaksi* current = head;
    Transaksi* previous = nullptr;
    while (current->next != nullptr) {
        previous = current;
        current = current->next;
    }

    if (previous == nullptr) {
        head = nullptr;
    } else {
        previous->next = nullptr;
    }

    delete current;
    cout << "Transaksi terakhir pada stack berhasil dihapus." << endl;
}

void hapusTransaksiQueue() {
    if (head == nullptr) {
        cout << "Tidak ada transaksi yang dapat dihapus dari queue." << endl;
        return;
    }

    Transaksi* current = head;
    head = head->next;
    delete current;

    cout << "Transaksi pertama pada queue berhasil dihapus." << endl;
}

void updateTransaksi() {
    if (head == nullptr) {
        cout << "Tidak ada transaksi yang dapat diupdate." << endl;
        return;
    }

    int nomorTransaksi;
    tampilkanTransaksi();
    cout << "Masukkan nomor transaksi yang ingin diupdate: ";
    cin >> nomorTransaksi;

    Transaksi* current = head;
    int nomorTransaksiSaatIni = 1;
    while (current != nullptr && nomorTransaksiSaatIni < nomorTransaksi) {
        current = current->next;
        nomorTransaksiSaatIni++;
    }

    if (current == nullptr) {
        cout << "Nomor transaksi tidak valid." << endl;
        return;
    }

    cout << "Masukkan tanggal baru (tanggal/bulan/tahun): ";
    cin >> current->tanggal;
    cout << "Masukkan kategori baru: ";
    cin >> current->kategori;
    cout << "Masukkan deskripsi transaksi baru: ";
    cin.ignore();
    getline(cin, current->deskripsi);
    cout << "Masukkan harga baru: Rp.";
    cin >> current->harga;
    cout << "Masukkan jenis transaksi baru (Pemasukan / Pengeluaran): ";
    cin >> current->jenis;

    cout << "Transaksi berhasil diupdate." << endl;
}

void hapusSemuaTransaksi() {
    head = nullptr;
    cout << "Semua transaksi berhasil dihapus." << endl;
}

int main() {
    // Inisialisasi transaksi awal
    Transaksi* transaksi1 = new Transaksi();
    transaksi1->tanggal = "01/01/2024";
    transaksi1->kategori = "Makanan";
    transaksi1->deskripsi = "Makan di restoran A";
    transaksi1->harga = 100000;
    transaksi1->jenis = "Pengeluaran";

    Transaksi* transaksi2 = new Transaksi();
    transaksi2->tanggal = "02/01/2024";
    transaksi2->kategori = "Belanja";
    transaksi2->deskripsi = "Beli baju di mall";
    transaksi2->harga = 500000;
    transaksi2->jenis = "Pengeluaran";

    Transaksi* transaksi3 = new Transaksi();
    transaksi3->tanggal = "03/01/2024";
    transaksi3->kategori = "Gaji";
    transaksi3->deskripsi = "Gaji dari perusahaan";
    transaksi3->harga = 3000000;
    transaksi3->jenis = "Pemasukan";

    transaksi1->next = transaksi2;
    transaksi2->next = transaksi3;
    transaksi3->next = nullptr;
    head = transaksi1;

    transaksiHashTable[hashFunction(1)] = transaksi1;
    transaksiHashTable[hashFunction(2)] = transaksi2;
    transaksiHashTable[hashFunction(3)] = transaksi3;

    int pilihan;
    do {
        cout << "Menu Transaksi: \n";
        cout << "1. Tambah Transaksi\n";
        cout << "2. Tampilkan Transaksi\n";
        cout << "3. Cari Transaksi\n";
        cout << "4. Hapus Transaksi\n";
        cout << "5. Update Transaksi\n";
        cout << "6. Hapus Semua Transaksi\n";
        cout << "7. Hapus Transaksi Terakhir dari Stack\n";
        cout << "8. Hapus Transaksi Pertama dari Queue\n";
        cout << "0. Keluar\n";
        cout << "Pilihan Anda: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahTransaksi();
            break;
        case 2:
            tampilkanTransaksi();
            break;
        case 3:
            cariTransaksi();
            break;
        case 4:
            hapusTransaksiBiasa();
            break;
        case 5:
            updateTransaksi();
            break;
        case 6:
            hapusSemuaTransaksi();
            break;
        case 7:
            hapusTransaksiStack();
            break;
        case 8:
            hapusTransaksiQueue();
            break;
        case 0:
            cout << "Terima kasih! Program selesai." << endl;
            break;
        default:
            cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 0);

    return 0;
}
