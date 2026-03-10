#include <stdio.h>
#include <stdlib.h> // Untuk system("cls") dan exit()
#include <string.h> // Untuk strcpy

#define MAX_PENUMPANG 50
#define MAX_KURSI 20
#define MAX_NAMA 50
#define MAX_TUJUAN 50

// Struktur untuk menyimpan data tiket
struct Tiket {
    char nama_penumpang[MAX_NAMA];
    char tujuan[MAX_TUJUAN];
    float harga;
    int nomor_kursi;
};

int main() {
    struct Tiket daftar_tiket[MAX_PENUMPANG];
    int jumlah_tiket_terisi = 0;
    int kursi_terisi[MAX_KURSI + 1]; // +1 karena kursi dimulai dari 1
    int i;
    int pilihan;

    // Inisialisasi semua kursi kosong (0 = kosong, 1 = terisi)
    for (i = 0; i <= MAX_KURSI; i++) {
        kursi_terisi[i] = 0;
    }

    do {
        // Membersihkan layar konsol (khusus Windows)
        system("cls"); 

        printf("===========================================\n");
        printf("  SISTEM TICKETING KOPERASI BINTANG TAPANULI\n");
        printf("===========================================\n");
        printf("1. Pesan Tiket\n");
        printf("2. Lihat Daftar Tiket\n");
        printf("3. Keluar\n");
        printf("Pilih menu: ");

        // Penanganan error untuk input pilihan menu
        while (scanf("%d", &pilihan) != 1 || pilihan < 1 || pilihan > 3) {
            printf("Input tidak valid. Mohon masukkan angka 1, 2, atau 3: ");
            while (getchar() != '\n'); // Membersihkan buffer input
        }
        while (getchar() != '\n'); // Membersihkan buffer input setelah scanf

        switch (pilihan) {
            case 1: {
                int jumlah_pesan;
                printf("\n--- PESAN TIKET ---\n");
                printf("Berapa tiket yang ingin Anda pesan (maksimal %d)? ", MAX_PENUMPANG - jumlah_tiket_terisi);

                // Penanganan error untuk jumlah tiket yang dipesan
                while (scanf("%d", &jumlah_pesan) != 1 || jumlah_pesan <= 0 || (jumlah_tiket_terisi + jumlah_pesan) > MAX_PENUMPANG) {
                    printf("Jumlah tiket tidak valid atau melebihi kapasitas. Masukkan angka positif dan tidak melebihi %d: ", MAX_PENUMPANG - jumlah_tiket_terisi);
                    while (getchar() != '\n');
                }
                while (getchar() != '\n');

                for (i = 0; i < jumlah_pesan; i++) {
                    if (jumlah_tiket_terisi < MAX_PENUMPANG) {
                        printf("\nData Tiket ke-%d:\n", i + 1);

                        // Input Nama Penumpang
                        printf("Nama Penumpang: ");
                        fgets(daftar_tiket[jumlah_tiket_terisi].nama_penumpang, MAX_NAMA, stdin);
                        daftar_tiket[jumlah_tiket_terisi].nama_penumpang[strcspn(daftar_tiket[jumlah_tiket_terisi].nama_penumpang, "\n")] = 0; // Hapus newline

                        // Input Tujuan
                        printf("Tujuan: ");
                        fgets(daftar_tiket[jumlah_tiket_terisi].tujuan, MAX_TUJUAN, stdin);
                        daftar_tiket[jumlah_tiket_terisi].tujuan[strcspn(daftar_tiket[jumlah_tiket_terisi].tujuan, "\n")] = 0; // Hapus newline

                        // Input Harga Tiket dengan validasi
                        printf("Harga Tiket: Rp ");
                        while (scanf("%f", &daftar_tiket[jumlah_tiket_terisi].harga) != 1 || daftar_tiket[jumlah_tiket_terisi].harga < 0) {
                            printf("Harga tidak valid. Mohon masukkan angka positif: Rp ");
                            while (getchar() != '\n');
                        }
                        while (getchar() != '\n'); // Membersihkan buffer input

                        // Input Nomor Kursi dengan validasi
                        int temp_kursi;
                        printf("Nomor Kursi (1-%d): ", MAX_KURSI);
                        while (scanf("%d", &temp_kursi) != 1 || temp_kursi < 1 || temp_kursi > MAX_KURSI || kursi_terisi[temp_kursi] == 1) {
                            if (kursi_terisi[temp_kursi] == 1) {
                                printf("Kursi nomor %d sudah terisi. Mohon pilih kursi lain: ", temp_kursi);
                            } else {
                                printf("Nomor kursi tidak valid. Mohon masukkan angka antara 1 dan %d: ", MAX_KURSI);
                            }
                            while (getchar() != '\n');
                        }
                        while (getchar() != '\n'); // Membersihkan buffer input

                        daftar_tiket[jumlah_tiket_terisi].nomor_kursi = temp_kursi;
                        kursi_terisi[temp_kursi] = 1; // Tandai kursi sebagai terisi
                        jumlah_tiket_terisi++;
                        printf("Tiket berhasil dipesan!\n");
                    } else {
                        printf("Maaf, kapasitas penumpang sudah penuh.\n");
                        break; // Keluar dari loop pemesanan tiket
                    }
                }
                printf("\nTekan ENTER untuk kembali ke menu...");
                getchar(); // Menunggu user menekan enter
                break;
            }
            case 2: {
                printf("\n--- DAFTAR TIKET YANG TERPESAN ---\n");
                if (jumlah_tiket_terisi == 0) {
                    printf("Belum ada tiket yang dipesan.\n");
                } else {
                    printf("----------------------------------------------------------------------------------\n");
                    printf("| %-3s | %-20s | %-15s | %-10s | %-10s |\n", "No", "Nama Penumpang", "Tujuan", "Harga", "Kursi");
                    printf("----------------------------------------------------------------------------------\n");
                    for (i = 0; i < jumlah_tiket_terisi; i++) {
                        printf("| %-3d | %-20s | %-15s | Rp %-7.2f | %-10d |\n",
                               i + 1,
                               daftar_tiket[i].nama_penumpang,
                               daftar_tiket[i].tujuan,
                               daftar_tiket[i].harga,
                               daftar_tiket[i].nomor_kursi);
                    }
                    printf("----------------------------------------------------------------------------------\n");
                }
                printf("\nTekan ENTER untuk kembali ke menu...");
                getchar(); // Menunggu user menekan enter
                break;
            }
            case 3: {
                printf("\nTerima kasih telah menggunakan Sistem perasi Bintang Tapanuli.\n");
                break;
            }
        }
    } while (pilihan != 3);

    return 0;
}