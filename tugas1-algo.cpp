#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

struct karyawan {
    int id;
    char nama[50];
};

struct barang {
    char namaBarang[100];
    int harga;
    int stok;
};

struct karyawan karyawanData[100];
int jumlahKaryawan = 0;
struct barang barangData[100];
int jumlahBarang = 0;

//bagian admin

void tambahDataKaryawan(struct karyawan arr[], int *jumlah) {
    FILE *admin = fopen("kar.txt", "ab");
    if (admin == NULL) {
        cout << "Error membuka file\n";
        return;
    }

    int n;
    cout << "Masukkan jumlah karyawan yang ingin ditambah: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        struct karyawan baru;
        cout << "ID karyawan   : ";
        cin >> baru.id;
        cout << "Nama karyawan : ";
        cin.ignore();
        cin.getline(baru.nama,50);
        
        fwrite(&baru,sizeof(struct karyawan),1,admin);
        arr[*jumlah] = baru;
        (*jumlah)++;
    }

    fclose(admin);
    cout << "Data berhasil disimpan!\n";
}

void dataKaryawan(struct karyawan arr[], int n) {
    FILE *admin = fopen("kar.txt","rb");
    
    if(admin == NULL){
        cout << "Belum ada data\n";
        return;
    }

    struct karyawan temp;
    int i=1;
    cout << "Daftar Karyawan\n";
    while(fread(&temp,sizeof(struct karyawan),1,admin)){
        cout<<"Karyawan ke-"<<i++<<endl;
        cout<<"Nama : "<<temp.nama<<endl;
        cout<<"ID   : "<<temp.id<<endl<<endl;
    }

    fclose(admin);
}

void searching(struct karyawan arr[], int n){
    int cari;
    bool found=false;

    cout<<"Masukkan ID karyawan yang dicari: ";
    cin>>cari;

    FILE *admin=fopen("kar.txt","rb");

    struct karyawan temp;
    while(fread(&temp,sizeof(struct karyawan),1,admin)){
        if(temp.id==cari){
            cout<<"Data ditemukan!\n";
            cout<<"ID   : "<<temp.id<<endl;
            cout<<"Nama : "<<temp.nama<<endl;
            found=true;
            break;
        }
    }

    fclose(admin);

    if(!found){
        cout<<"Data tidak ditemukan\n";
    }
}

void loginadmin(){
    string username;
    int password;
    int pilihan;

    cout<<"Masukkan username: ";
    cin>>username;
    cout<<"Masukkan password: ";
    cin>>password;

    if(username=="Admin" && password==123){
        do{
            cout<<"\n1. Tambah data karyawan\n";
            cout<<"2. Lihat data karyawan\n";
            cout<<"3. Searching data karyawan\n";
            cout<<"4. Logout\n";
            cout<<"Pilih menu: ";
            cin>>pilihan;

            switch(pilihan){
                case 1:
                tambahDataKaryawan(karyawanData,&jumlahKaryawan);
                break;
                case 2:
                dataKaryawan(karyawanData,jumlahKaryawan);
                break;
                case 3:
                searching(karyawanData,jumlahKaryawan);
                break;
                case 4:
                return;
                default:
                cout<<"Pilihan tidak valid\n";
            }

        }while(true);
    }

    else{
        cout<<"Anda bukan admin\n";
    }
}

//bagian karyawan

void tambahbarang(){
    int n;
    
    cout<<"Masukkan jumlah barang: ";
    cin>>n;

    FILE *f=fopen("brg.txt","ab");
    if (f == NULL) {
		cout << "error opening brg.txt";
		return;
	}

    if(f==NULL) return;
    for(int i=0;i<n;i++){
        struct barang baru;
        cout<<"Data barang ke-"<<i+1<<endl;
        cout<<"Nama barang : ";
        cin.ignore();
        cin.getline(baru.namaBarang,100);
        cout<<"Harga barang : ";
        cin>>baru.harga;
        cout<<"Stok barang : ";
        cin>>baru.stok;

        fwrite(&baru,sizeof(struct barang),1,f);

        barangData[jumlahBarang]=baru;
        jumlahBarang++;
        
        cout<<"====================\n\n";
    }
    fclose(f);

    cout<<"Data berhasil ditambahkan\n";
}

void bubble(struct barang arr[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1-i;j++){
            if(arr[j].harga>arr[j+1].harga){
                struct barang temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }

    for(int i=0;i<n;i++){
        cout<<"Data barang ke-"<<i+1<<endl;
        cout<<arr[i].namaBarang<<endl;
        cout<<arr[i].harga<<endl;
        cout<<arr[i].stok<<endl;
        cout<<"====================\n\n";
    }
}


void quick(struct barang arr[],int awal,int akhir){
    if(awal<akhir){
        int pivot=arr[(awal+akhir)/2].harga;
        int low=awal;
        int high=akhir;
        
        while(low<=high){
            while(arr[low].harga>pivot) low++;
            while(arr[high].harga<pivot) high--;

            if(low<=high){
                struct barang temp=arr[low];
                arr[low]=arr[high];
                arr[high]=temp;

                low++;
                high--;
            }
        }
        if(awal<high) quick(arr,awal,high);
        if(low<akhir) quick(arr,low,akhir);
    }
    for(int i=0;i<jumlahBarang;i++){
        cout<<"Data barang ke-"<<i+1<<endl;
        cout<<arr[i].namaBarang<<endl;
        cout<<arr[i].harga<<endl;
        cout<<arr[i].stok<<endl;
        cout<<"====================\n\n";
    }
}


void lihatbarang(){
    FILE *f=fopen("brg.txt","rb");
    
    if(f){
        jumlahBarang=0;
        while(fread(&barangData[jumlahBarang],sizeof(struct barang),1,f)){
            jumlahBarang++;
        }
        fclose(f);
    }
    int pilihan;

    cout<<"\n1. Ascending (Bubble Sort)\n";
    cout<<"2. Descending (Quick Sort)\n";
    cout<<"Pilih: ";
    cin>>pilihan;

    struct barang tempData[100];

    for(int i=0;i<jumlahBarang;i++){
        tempData[i]=barangData[i];
    }

    switch(pilihan){
        case 1:
        bubble(tempData,jumlahBarang);
        break;
        case 2:
        quick(tempData,0,jumlahBarang-1);
        break;
        default:
        cout<<"Pilihan tidak valid\n";
    }
}

void cariBarang(){
    int pilih;
    char cari[100];
    bool found=false;

    FILE *f=fopen("brg.txt","rb");

    if(f==NULL){
        cout<<"File tidak ditemukan\n";
        return;
    }

    jumlahBarang=0;

    while(fread(&barangData[jumlahBarang],sizeof(struct barang),1,f)){
        jumlahBarang++;
    }

    fclose(f);

    cout<<"1. Sequential Search\n";
    cout<<"2. Binary Search\n";
    cout<<"Pilih: ";
    cin>>pilih;
    cin.ignore();

    cout<<"Masukkan nama barang: ";
    cin.getline(cari,100);

    switch(pilih){
        case 1:
        for(int i=0;i<jumlahBarang;i++){
            if(strcmp(barangData[i].namaBarang,cari)==0){
                cout<<"Barang ditemukan!\n";
                cout<<"Nama : "<<barangData[i].namaBarang<<endl;
                cout<<"Harga : "<<barangData[i].harga<<endl;
                cout<<"Stok : "<<barangData[i].stok<<endl;
                found=true;
                break;
            }
        }

        if(!found){
            cout<<"Barang tidak ditemukan\n";
        }
        break;

        case 2:
        for(int i=0;i<jumlahBarang-1;i++){
            for(int j=0;j<jumlahBarang-1-i;j++){
                if(strcmp(barangData[j].namaBarang,barangData[j+1].namaBarang)>0){
                    struct barang temp=barangData[j];
                    barangData[j]=barangData[j+1];
                    barangData[j+1]=temp;
                }
            }
        }

        int kiri=0;
        int kanan=jumlahBarang-1;

        while(kiri<=kanan){
            int tengah=(kiri+kanan)/2;
            int hasil=strcmp(barangData[tengah].namaBarang,cari);
            
            if(hasil==0){
                cout<<"Barang ditemukan!\n";
                cout<<"Nama : "<<barangData[tengah].namaBarang<<endl;
                cout<<"Harga : "<<barangData[tengah].harga<<endl;
                cout<<"Stok : "<<barangData[tengah].stok<<endl;
                found=true;
                break;
            } else if(hasil<0){
                kiri=tengah+1;
            } else{
                kanan=tengah-1;
            }
        }
        if(!found){
            cout<<"Barang tidak ditemukan\n";
        }
        break;
    }
}

void edit(){
    char cari[100];
    bool found=false;

    cout<<"Masukkan nama barang yang ingin diedit: ";
    cin.ignore();
    cin.getline(cari,100);

    for(int i=0;i<jumlahBarang;i++){
        if(strcmp(barangData[i].namaBarang,cari)==0){
            cout<<"Data lama\n";
            cout<<barangData[i].namaBarang<<" "<<barangData[i].harga<<endl;
            cout<<"Nama baru : ";
            cin.getline(barangData[i].namaBarang,100);
            cout<<"Harga baru : ";
            cin>>barangData[i].harga;
            cout<<"Stok baru : ";
            cin>>barangData[i].stok;

            found=true;
            break;
        }
    }
    if(!found){
        cout<<"Barang tidak ditemukan\n";
    }else{
        FILE *f=fopen("brg.txt","wb");

        for(int i=0;i<jumlahBarang;i++){
            fwrite(&barangData[i],sizeof(struct barang),1,f);
        }

        fclose(f);
		cout<<"Data berhasil diupdate\n";
    }
}

void karyawanm(){
    int pilihan;
    
    do{
        cout<<"\n== MENU KARYAWAN ==\n";
        cout<<"1. Tambah data barang\n";
        cout<<"2. Lihat data barang\n";
        cout<<"3. Cari barang\n";
        cout<<"4. Edit data barang\n";
        cout<<"5. Logout\n";
        cout<<"Pilih menu: ";
        cin>>pilihan;

        switch(pilihan){
            case 1: tambahbarang(); break;
            case 2: lihatbarang(); break;
            case 3: cariBarang(); break;
            case 4: edit(); break;
            case 5: return;
            default:
            cout<<"Pilihan tidak valid\n";
        }
    }while(true);
}


int main(){
    int pilihan;
    string ulang;

    do{
        cout<<"\n==========WELCOME TO COCOA HEAVEN==========\n";
        cout<<"1. Login Admin\n";
        cout<<"2. Karyawan\n";
        cout<<"3. Keluar\n";
        cout<<"Masukkan pilihan: ";
        cin>>pilihan;

        switch(pilihan){
            case 1: loginadmin(); break;
            case 2: karyawanm(); break;
            case 3:
            cout<<"Terima kasih\n";
            return 0;
            default:
            cout<<"Pilihan tidak valid\n";
        }

        cout<<"\nKembali ke menu utama? (y/n): ";
        cin>>ulang;

    }while(ulang=="y"||ulang=="Y");
    return 0;
}
