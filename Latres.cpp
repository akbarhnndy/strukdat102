#include <iostream>
using namespace std;

struct NodeAntrean {
    char pelanggan[50];
    NodeAntrean* next;
};

struct QueuePelanggan {
    NodeAntrean* front;
    NodeAntrean* rear;
};

struct Aksi {
    char jenis;
    char menu[50];
    char pelanggan[50];
    bool masukAntrean;
    char dilayani[50];
};

struct NodeAksi {
    Aksi data;
    NodeAksi* next;
};

struct StackAksi {
    NodeAksi* top;
};

struct Menu {
    char nama[50];
    char kategori[50];
    int harga;
    bool tersedia;
    QueuePelanggan antrean;
};

struct Node {
    Menu data;
    Node* left;
    Node* right;
};

void init(QueuePelanggan& q);
bool isEmpty(QueuePelanggan& q);
bool enqueue(QueuePelanggan& q, char pelanggan[]);
bool dequeue(QueuePelanggan& q, char pelangganKeluar[]);
bool enqueueDepan(QueuePelanggan& q, char pelanggan[]);
bool hapusBelakang(QueuePelanggan& q);
void clear(QueuePelanggan& q);

void init(StackAksi& s);
bool isEmpty(StackAksi& s);
bool push(StackAksi& s, Aksi aksi);
bool pop(StackAksi& s, Aksi& aksiKeluar);
void clear(StackAksi& s);

bool insert(Node*& root, Menu menu);
Node* cari(Node* root, char nama[]);
Node* minimum(Node* root);
bool hapus(Node*& root, char nama[]);
void inorder(Node* root);
void tampilAntreanSemua(Node* root, bool& adaAntrean);
void clear(Node*& root);

void menuTambahMenu(Node*& root);
void menuLihatMenu(Node* root);
void menuCatatPesanan(Node* root, StackAksi& riwayat);
void menuTersediaKembali(Node* root, StackAksi& riwayat);
void menuHapusMenu(Node*& root);
void menuUndo(Node* root, StackAksi& riwayat);
void menuTampilAntrean(Node* root);
void menuTandaiHabis(Node* root, StackAksi& riwayat);
void jeda();

void init(QueuePelanggan& q) {
    q.front = NULL;
    q.rear = NULL;
}

bool isEmpty(QueuePelanggan& q) {
    return q.front == NULL;
}

bool enqueue(QueuePelanggan& q, char pelanggan[]) {
    NodeAntrean* baru = new NodeAntrean;
    int i = 0;

    while (pelanggan[i] != '\0' && i < 49) {
        baru->pelanggan[i] = pelanggan[i];
        i++;
    }
    baru->pelanggan[i] = '\0';
    baru->next = NULL;
    if (isEmpty(q))
        q.front = baru;
    else
        q.rear->next = baru;
    q.rear = baru;
    return true;
}

bool dequeue(QueuePelanggan& q, char pelangganKeluar[]) {
    if (isEmpty(q))
        return false;

    NodeAntrean* hapus = q.front;
    int i = 0;
    while (hapus->pelanggan[i] != '\0') {
        pelangganKeluar[i] = hapus->pelanggan[i];
        i++;
    }
    pelangganKeluar[i] = '\0';
    q.front = q.front->next;
    if (q.front == NULL)
        q.rear = NULL;
    delete hapus;
    return true;
}

bool enqueueDepan(QueuePelanggan& q, char pelanggan[]) {
    NodeAntrean* baru = new NodeAntrean;
    int i = 0;
    while (pelanggan[i] != '\0' && i < 49) {
        baru->pelanggan[i] = pelanggan[i];
        i++;
    }
    baru->pelanggan[i] = '\0';
    baru->next = q.front;
    q.front = baru;
    if (q.rear == NULL)
        q.rear = baru;
    return true;
}

bool hapusBelakang(QueuePelanggan& q) {
    if (isEmpty(q))
        return false;
    if (q.front == q.rear) {
        delete q.front;
        q.front = NULL;
        q.rear = NULL;
        return true;
    }
    NodeAntrean* bantu = q.front;
    while (bantu->next != q.rear)
        bantu = bantu->next;
    delete q.rear;
    q.rear = bantu;
    q.rear->next = NULL;
    return true;
}

void clear(QueuePelanggan& q) {
    while (!isEmpty(q)) {
        NodeAntrean* hapus = q.front;
        q.front = q.front->next;
        delete hapus;
    }
    q.rear = NULL;
}

void init(StackAksi& s) {
    s.top = NULL;
}

bool isEmpty(StackAksi& s) {
    return s.top == NULL;
}

bool push(StackAksi& s, Aksi aksi) {
    NodeAksi* baru = new NodeAksi;
    baru->data = aksi;
    baru->next = s.top;
    s.top = baru;
    return true;
}

bool pop(StackAksi& s, Aksi& aksiKeluar) {
    if (isEmpty(s))
        return false;
    NodeAksi* hapus = s.top;
    aksiKeluar = hapus->data;
    s.top = s.top->next;
    delete hapus;
    return true;
}

void clear(StackAksi& s) {
    Aksi aksi;
    while (pop(s, aksi));
}

bool insert(Node*& root, Menu menu) {
    if (root == NULL) {
        root = new Node;
        root->data = menu;
        root->left = NULL;
        root->right = NULL;
        return true;
    }
    int i = 0;
    while (menu.nama[i] != '\0' &&
           root->data.nama[i] != '\0' &&
           menu.nama[i] == root->data.nama[i]) {
        i++;
    }
    if (menu.nama[i] == root->data.nama[i])
        return false;
    else if (menu.nama[i] < root->data.nama[i])
        return insert(root->left, menu);
    else
        return insert(root->right, menu);
}

Node* cari(Node* root, char nama[]) {
    if (root == NULL)
        return NULL;
    int i = 0;
    while (nama[i] != '\0' &&
           root->data.nama[i] != '\0' &&
           nama[i] == root->data.nama[i]) {
        i++;
    }
    if (nama[i] == root->data.nama[i])
        return root;
    else if (nama[i] < root->data.nama[i])
        return cari(root->left, nama);
    else
        return cari(root->right, nama);
}

Node* minimum(Node* root) {
    Node* bantu = root;
    while (bantu != NULL && bantu->left != NULL)
        bantu = bantu->left;
    return bantu;
}

bool hapus(Node*& root, char nama[]) {
    if (root == NULL)
        return false;
    int i = 0;
    while (nama[i] != '\0' &&
           root->data.nama[i] != '\0' &&
           nama[i] == root->data.nama[i]) {
        i++;
    }
    if (nama[i] < root->data.nama[i])
        return hapus(root->left, nama);
    else if (nama[i] > root->data.nama[i])
        return hapus(root->right, nama);
    if (root->left == NULL) {
        Node* hapusNode = root;
        root = root->right;
        delete hapusNode;
    }
    else if (root->right == NULL) {
        Node* hapusNode = root;
        root = root->left;
        delete hapusNode;
    }
    else {
        Node* pengganti = minimum(root->right);
        root->data = pengganti->data;
        hapus(root->right, pengganti->data.nama);
    }
    return true;
}

void inorder(Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);

    cout << "\nNama Menu : " << root->data.nama;
    cout << "\nKategori  : " << root->data.kategori;
    cout << "\nHarga     : Rp" << root->data.harga;
    cout << "\nStatus    : ";

    if (root->data.tersedia)
        cout << "Tersedia";
    else
        cout << "Habis";
    cout << "\n-----------------------------";
    inorder(root->right);
}

void tampilAntreanSemua(Node* root, bool& adaAntrean) {
    if (root == NULL)
        return;
    tampilAntreanSemua(root->left, adaAntrean);

    if (!isEmpty(root->data.antrean)) {
        adaAntrean = true;
        cout << "\nMenu: " << root->data.nama << endl;

        NodeAntrean* bantu = root->data.antrean.front;
        int nomor = 1;
        while (bantu != NULL) {
            cout << nomor << ". " << bantu->pelanggan << endl;
            bantu = bantu->next;
            nomor++;
        }
    }
    tampilAntreanSemua(root->right, adaAntrean);
}

void clear(Node*& root) {
    if (root == NULL)
        return;
    clear(root->left);
    clear(root->right);
    clear(root->data.antrean);
    delete root;
    root = NULL;
}

void menuTambahMenu(Node*& root) {
    Menu menu;
    init(menu.antrean);
    cout << "\n=== TAMBAH MENU ===\n";
    cout << "Nama menu : ";
    cin >> ws;
    cin.getline(menu.nama, 50);
    cout << "Kategori  : ";
    cin.getline(menu.kategori, 50);
    cout << "Harga     : ";

    while (!(cin >> menu.harga) || menu.harga < 0) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Harga tidak valid. Masukkan ulang: ";
    }
    cin.ignore(10000, '\n');
    menu.tersedia = true;
    if (insert(root, menu))
        cout << "\nMenu berhasil ditambahkan.\n";
    else
        cout << "\nNama menu sudah terdaftar.\n";
}

void menuLihatMenu(Node* root) {
    cout << "\n=== DAFTAR MENU ===\n";
    if (root == NULL) {
        cout << "Belum ada menu yang terdaftar.\n";
        return;
    }
    inorder(root);
    cout << endl;
}

void menuCatatPesanan(Node* root, StackAksi& riwayat) {
    char namaMenu[50];
    char namaPelanggan[50];
    cout << "\n=== CATAT PESANAN ===\n";
    cout << "Nama menu      : ";
    cin >> ws;
    cin.getline(namaMenu, 50);

    Node* node = cari(root, namaMenu);
    if (node == NULL) {
        cout << "\nMenu tidak ditemukan.\n";
        return;
    }
    cout << "Nama pelanggan : ";
    cin.getline(namaPelanggan, 50);
    Aksi aksi;
    aksi.jenis = 'P';

    int i = 0;
    while (node->data.nama[i] != '\0') {
        aksi.menu[i] = node->data.nama[i];
        i++;
    }
    aksi.menu[i] = '\0';
    i = 0;
    while (namaPelanggan[i] != '\0') {
        aksi.pelanggan[i] = namaPelanggan[i];
        i++;
    }
    aksi.pelanggan[i] = '\0';
    aksi.dilayani[0] = '\0';

    if (node->data.tersedia) {
        aksi.masukAntrean = false;
        push(riwayat, aksi);
        cout << "\nPesanan berhasil dicatat.\n";
    }
    else {
        aksi.masukAntrean = true;
        enqueue(node->data.antrean, namaPelanggan);
        push(riwayat, aksi);
        cout << "\nMenu sedang habis.";
        cout << "\nPelanggan masuk ke antrean.\n";
    }
}

void menuTersediaKembali(Node* root, StackAksi& riwayat) {
    char namaMenu[50];
    char pelangganKeluar[50];
    cout << "\n=== MENU TERSEDIA KEMBALI ===\n";
    cout << "Nama menu: ";
    cin >> ws;
    cin.getline(namaMenu, 50);

    Node* node = cari(root, namaMenu);
    if (node == NULL) {
        cout << "\nMenu tidak ditemukan.\n";
        return;
    }
    if (node->data.tersedia) {
        cout << "\nMenu sudah tersedia.\n";
        return;
    }

    Aksi aksi;
    aksi.jenis = 'T';
    aksi.masukAntrean = false;
    aksi.dilayani[0] = '\0';

    int i = 0;
    while (node->data.nama[i] != '\0') {
        aksi.menu[i] = node->data.nama[i];
        i++;
    }
    aksi.menu[i] = '\0';
    node->data.tersedia = true;

    if (dequeue(node->data.antrean, pelangganKeluar)) {
        i = 0;
        while (pelangganKeluar[i] != '\0') {
            aksi.dilayani[i] = pelangganKeluar[i];
            i++;
        }
        aksi.dilayani[i] = '\0';
        aksi.masukAntrean = true;

        cout << "\nMenu tersedia kembali.";
        cout << "\nPelanggan yang dilayani: " << pelangganKeluar << endl;
    }
    else {
        cout << "\nMenu tersedia kembali.";
        cout << "\nTidak ada pelanggan dalam antrean.\n";
    }
    push(riwayat, aksi);
}

void menuHapusMenu(Node*& root) {
    char namaMenu[50];
    cout << "\n=== HAPUS MENU ===\n";
    cout << "Nama menu: ";
    cin >> ws;
    cin.getline(namaMenu, 50);

    Node* node = cari(root, namaMenu);
    if (node == NULL) {
        cout << "\nMenu tidak ditemukan.\n";
        return;
    }
    clear(node->data.antrean);

    if (hapus(root, namaMenu))
        cout << "\nMenu berhasil dihapus.\n";
    else
        cout << "\nMenu gagal dihapus.\n";
}

void menuUndo(Node* root, StackAksi& riwayat) {
    Aksi aksi;
    cout << "\n=== UNDO AKSI ===\n";
    if (!pop(riwayat, aksi)) {
        cout << "Belum ada aksi yang dapat dibatalkan.\n";
        return;
    }
    Node* node = cari(root, aksi.menu);
    if (node == NULL) {
        cout << "Menu sudah tidak tersedia dalam daftar.\n";
        return;
    }
    if (aksi.jenis == 'P') {
        if (aksi.masukAntrean) {
            if (hapusBelakang(node->data.antrean))
                cout << "Pesanan antrean berhasil dibatalkan.\n";
            else
                cout << "Antrean sudah kosong.\n";
        }
        else {
            cout << "Pesanan pelanggan berhasil dibatalkan.\n";
        }
    }
    else if (aksi.jenis == 'T') {
        node->data.tersedia = false;
        if (aksi.masukAntrean)
            enqueueDepan(node->data.antrean, aksi.dilayani);
        cout << "Pembaruan ketersediaan menu berhasil dibatalkan.\n";
    }
    else if (aksi.jenis == 'H') {
        node->data.tersedia = true;
        cout << "Status menu berhasil dikembalikan menjadi tersedia.\n";
    }
}

void menuTampilAntrean(Node* root) {
    bool adaAntrean = false;
    cout << "\n=== DAFTAR ANTREAN PELANGGAN ===\n";

    if (root == NULL) {
        cout << "Belum ada menu yang terdaftar.\n";
        return;
    }
    tampilAntreanSemua(root, adaAntrean);

    if (!adaAntrean)
        cout << "Belum ada pelanggan dalam antrean.\n";
}

void menuTandaiHabis(Node* root, StackAksi& riwayat) {
    char namaMenu[50];
    cout << "\n=== TANDAI MENU HABIS ===\n";
    cout << "Nama menu: ";
    cin >> ws;
    cin.getline(namaMenu, 50);

    Node* node = cari(root, namaMenu);
    if (node == NULL) {
        cout << "\nMenu tidak ditemukan.\n";
        return;
    }
    if (!node->data.tersedia) {
        cout << "\nMenu sudah berstatus habis.\n";
        return;
    }
    Aksi aksi;
    aksi.jenis = 'H';
    aksi.masukAntrean = false;
    aksi.dilayani[0] = '\0';
    aksi.pelanggan[0] = '\0';

    int i = 0;
    while (node->data.nama[i] != '\0') {
        aksi.menu[i] = node->data.nama[i];
        i++;
    }
    aksi.menu[i] = '\0';
    node->data.tersedia = false;
    push(riwayat, aksi);
    cout << "\nStatus menu berhasil diubah menjadi habis.\n";
}

void jeda() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

int main() {
    Node* root = NULL;
    StackAksi riwayat;
    init(riwayat);
    int pilihan = 0;

    do {
        cout << "\n================================";
        cout << "\n    SISTEM PESANAN RESTORAN";
        cout << "\n================================";
        cout << "\n1. Tambah Menu";
        cout << "\n2. Lihat Daftar Menu";
        cout << "\n3. Catat Pesanan Pelanggan";
        cout << "\n4. Catat Menu Tersedia Kembali";
        cout << "\n5. Hapus Menu";
        cout << "\n6. Undo Pesanan / Pembaruan Menu";
        cout << "\n7. Tampilkan Antrean Pelanggan";
        cout << "\n8. Tandai Menu Habis";
        cout << "\n9. Keluar";
        cout << "\n================================";
        cout << "\nPilih menu: ";

        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInput harus berupa angka.\n";
            continue;
        }
        cin.ignore(10000, '\n');

        switch (pilihan) {
            case 1:
                menuTambahMenu(root);
                jeda();
                break;

            case 2:
                menuLihatMenu(root);
                jeda();
                break;

            case 3:
                menuCatatPesanan(root, riwayat);
                jeda();
                break;

            case 4:
                menuTersediaKembali(root, riwayat);
                jeda();
                break;

            case 5:
                menuHapusMenu(root);
                jeda();
                break;

            case 6:
                menuUndo(root, riwayat);
                jeda();
                break;

            case 7:
                menuTampilAntrean(root);
                jeda();
                break;

            case 8:
                menuTandaiHabis(root, riwayat);
                jeda();
                break;

            case 9:
                cout << "\nTerima kasih telah menggunakan program.\n";
                break;

            default:
                cout << "\nPilihan tidak tersedia.\n";
                jeda();
        }
    } while (pilihan != 9);
    clear(root);
    clear(riwayat);
    return 0;
}