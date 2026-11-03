// UTS Praktikum Paket B: Fotokopi Kampus.
// Lengkapi TODO 1 sampai TODO 6 sesuai lembar soal. Bagian yang sudah ada jangan diubah kecuali diminta.
// Bangun dengan baseline kelas; program harus bebas warning. Uji dengan: ./fotokopi < contoh_masukan.txt
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    const int HARGA_KECIL = 300;     // 1 sampai 50 halaman
    const int HARGA_SEDANG = 250;    // 51 sampai 200 halaman
    const int HARGA_BESAR = 200;     // lebih dari 200 halaman
    const int BATAS_KECIL = 50;
    const int BATAS_SEDANG = 200;
    const int MAKS_HALAMAN = 1000;

    int jumlah = 0;
    cout << "=== Fotokopi Kampus ===\n";
    cout << "Jumlah pesanan: ";
    cin >> jumlah;
    while (cin.fail() || jumlah < 1) {           // contoh pembacaan aman; pakai pola ini untuk halaman
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Harus bilangan bulat paling sedikit 1. Jumlah pesanan: ";
        cin >> jumlah;
    }
    cin.ignore(1000, '\n');

    cout << fixed << setprecision(2);

    int total_halaman = 0;
    int total_pendapatan = 0;
    int banyak_kecil = 0;
    int banyak_sedang = 0;
    int banyak_besar = 0;
    // TODO 5a
    int biaya_terbesar = -1;
    string nama_terbesar;

    for (int i = 1; i <= jumlah; i++) {
        string nama;
        int halaman = 0;
        char warna = ' ';

        cout << "\n--- Pesanan ke-" << i << " dari " << jumlah << " ---\n";

        // TODO 1: baca nama, validasi, lalu ubah menjadi Huruf Besar Di Awal Kata.
        bool nama_sah = false;

while (!nama_sah) {
    cout << "Nama pemesan : ";

    if (!getline(cin, nama)) {
        return 0;
    }

    bool hanya_spasi = true;
    bool ada_angka = false;

    for (char c : nama) {
        unsigned char uc = static_cast<unsigned char>(c);

        if (!isspace(uc)) {
            hanya_spasi = false;
        }

        if (isdigit(uc)) {
            ada_angka = true;
        }
    }

    if (hanya_spasi) {
        cout << "Nama tidak boleh kosong.\n";
    } 
    else if (ada_angka) {
        cout << "Nama tidak boleh mengandung angka.\n";
    } 
    else {
        nama_sah = true;
    }
}

// Mengubah menjadi huruf besar di awal kata
bool awal_kata = true;

for (char &c : nama) {
    unsigned char uc = static_cast<unsigned char>(c);

    if (isspace(uc)) {
        awal_kata = true;
    } else {
        c = static_cast<char>(
            awal_kata ? toupper(uc) : tolower(uc)
        );
        awal_kata = false;
    }
}

        // TODO 2: baca halaman dengan aman (bilangan bulat 1 sampai MAKS_HALAMAN), pola seperti jumlah di atas.
        //         Pesan penolakan: "Harus bilangan bulat 1 sampai 1000. Halaman: "
        bool halaman_sah = false;

while (!halaman_sah) {
    cout << "Halaman (1-" << MAKS_HALAMAN << "): ";

    string input_halaman;
    getline(cin, input_halaman);

    stringstream ss(input_halaman);
    int nilai;
    char sisa;

    if ((ss >> nilai) && !(ss >> sisa) &&
        nilai >= 1 && nilai <= MAKS_HALAMAN) {
        halaman = nilai;
        halaman_sah = true;
    } else {
        cout << "Harus bilangan bulat 1 sampai 1000. Halaman: \n";
    }
}

        // TODO 3: baca warna (char), jadikan huruf besar, ulangi selama bukan 'Y' atau 'T'.
        //         Pesan penolakan: "Hanya Y atau T. Berwarna (Y/T): "
        bool warna_sah = false;

while (!warna_sah) {
    cout << "Berwarna (Y/T): ";

    string input_warna;
    getline(cin, input_warna);

    if (input_warna.size() == 1) {
        warna = toupper(
            static_cast<unsigned char>(input_warna[0])
        );

        if (warna == 'Y' || warna == 'T') {
            warna_sah = true;
        }
    }

    if (!warna_sah) {
        cout << "Hanya Y atau T. Berwarna (Y/T): \n";
    }
}

        // TODO 4: tentukan tarif, kategori, dan biaya pesanan.
        int harga_per_halaman = 0;
        if (halaman <= BATAS_KECIL) {
            harga_per_halaman = HARGA_KECIL;
            banyak_kecil++;
        } else if (halaman <= BATAS_SEDANG) {
            harga_per_halaman = HARGA_SEDANG;
            banyak_sedang++;
        } else {
            harga_per_halaman = HARGA_BESAR;
            banyak_besar++;
        }

        int biaya = halaman * harga_per_halaman;
        if (warna == 'Y') {
            biaya *= 2;
        }

        cout << "  " << left << setw(16) << nama << right << setw(6) << halaman;
        if (warna == 'Y') {
            cout << setw(7) << "Warna";
        } else {
            cout << setw(7) << "Hitam";
        }
        cout << setw(9) << biaya << "\n";

        total_halaman += halaman;
        total_pendapatan += biaya;
        // TODO 5b: simpan pesanan dengan biaya terbesar.
        if (biaya > biaya_terbesar) {
            biaya_terbesar = biaya;
            nama_terbesar = nama;
        }
    }

    cout << "\n=== Rekap Hari Ini ===\n";
    cout << "Jumlah pesanan    : " << jumlah << "\n";
    cout << "Total halaman     : " << total_halaman << "\n";
    cout << "Total pendapatan  : " << total_pendapatan << "\n";
    cout << "Rata-rata halaman : " << static_cast<double>(total_halaman) / jumlah << "\n";
    // TODO 5c
    cout << "Terbesar          : " << nama_terbesar
         << " (" << biaya_terbesar << ")\n";

    cout << "\nSebaran ukuran pesanan:\n";
    // TODO 6: perulangan luar memilih kategori, perulangan dalam menggambar batang.
    const string label_kategori[] = {"Kecil", "Sedang", "Besar"};
    const int jumlah_kategori[] = {banyak_kecil, banyak_sedang, banyak_besar};

    for (int i = 0; i < 3; i++) {
        cout << left << setw(7) << label_kategori[i] << "| ";
        for (int j = 0; j < jumlah_kategori[i]; j++) {
            cout << "#";
        }
        cout << " " << jumlah_kategori[i] << "\n";
    }

    return 0;
}
