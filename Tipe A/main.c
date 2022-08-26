#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define max 3

typedef char string[50];

typedef struct {
	int harga;
	float tarifPajak;
	string jenis;
}Kendaraan;

typedef struct {
	string nama;
	float totalPajak;
	string NIK;
	Kendaraan kendaraan[2];
}Pemilik;

void init(Pemilik p[]);
void addPemilik(Pemilik p[]);
void tampil(Pemilik p[]);
void editData(Pemilik p[], string NIK);
void hapusData(Pemilik p[], string NIK);

Kendaraan makeKendaraan(int harga, string jenis);
int isFull(Pemilik p[]);
int isEmpty(Pemilik p[]);
int isFound(Pemilik p[], string NIK);

int main(int argc, char *argv[]) {
	
	bool cek = true;
	int pil, harga, i;
	string jenis, NIK, nama;
	
	Pemilik p[max];
	Kendaraan k[2];
	
	init(p);
	do{
		system("cls");
		printf("[1] Tambah data");
		printf("\n[2] Tampil data");
		printf("\n[3] Ubah data");
		printf("\n[4] Hapus data");
		printf("\n[0] Exit");
		printf("\n>>> "); scanf("%d", &pil);
		
		switch(pil) {
			case 1:
				if(isFull(p) != -1)
				{
					printf("\n---INPUT DATA---");
					addPemilik(p);
					printf("\nberhasil input data...");
				} else printf("\ndata sudah penuh!");
				break;
				
			case 2:
				printf("\n---Tampil data wajib pajak---");
				tampil(p);
				break;
				
			case 3:
				if(isEmpty(p)!=max)
				{
					printf("\n---Edit Data wajib pajak---");
					
					printf("\n\nMasukan NIK yang diedit : "); fflush(stdin); gets(NIK);
					if(isFound(p, NIK)!=-1)
					{
						editData(p, NIK);
						printf("\nBerhasil edit data...");
					}
					else printf("\nData tidak ditemukan...");
					
				} else printf("\ndata kosong!");
				break;
				
			case 4:
				if(isEmpty(p)!=max)
				{
					printf("\n---Hapus Data wajib pajak---");
					
					printf("\n\nMasukan NIK yang dihapus : "); fflush(stdin); gets(NIK);
					
					if(isFound(p, NIK)!=-1)
					{
						hapusData(p, NIK);
						printf("\nData berhasil di hapus...");
					}else printf("\nData tidak ditemukan...");
				} else printf("\ndata masih kosong!");
				
				break;
				
			default:
				printf("\nPermintaan tidak ditemukan!");
				break;
				
			case 0:
				printf("\nkeluar program...");
				break;
		}getch();
	}while(pil!=0);
	
	
	return 0;
}

void init(Pemilik p[]) 
{
	int i, j;
	
	for (i=0;i<max;i++){
		strcpy(p[i].nama, "-");
		strcpy(p[i].NIK, "-");
		p[i].totalPajak = 0;
		
		for(j=0;j<2;j++) {
			p[i].kendaraan[j].harga = 0;
			p[i].kendaraan[j].tarifPajak = 0;
			strcpy(p[i].kendaraan[j].jenis, "-");
		}
	}
}

void addPemilik(Pemilik p[]) 
{
	Pemilik temp;
	int i;
	bool cek = true;
	int harga;
	string jenis, NIK, nama;
	
	do{
		printf("\nNIK Pemilik : "); fflush(stdin); gets(NIK);
		if(strlen(NIK)==0){
			printf("\nNIK harus di isi");
		} else cek = false;
	}while(cek);
					
	printf("Nama Pemilik : "); fflush(stdin); gets(nama);
	
	strcpy(temp.nama, nama);
	strcpy(temp.NIK, NIK);
					
	for(i=0;i<2;i++){
		printf("\nKendaraan ke-%d", i+1);
		printf("\n\tJenis kendaraan : "); fflush(stdin); gets(jenis);
		printf("\tHarga kendaraan : "); scanf("%d", &harga);
						
		temp.kendaraan[i] = makeKendaraan(harga, jenis);
		temp.totalPajak += temp.kendaraan[i].tarifPajak;
	}
	
	p[isFull(p)] = temp;
}

void tampil(Pemilik p[])
{
	int i, j;
	
	for(i=0;i<max;i++){
		if(strcmp(p[i].nama, "-")!=0){
			printf("\n=========================================");
			printf("\nNIK : %s", p[i].NIK);
			printf("\nNama : %s", p[i].nama);
			printf("\nTotal Pajak : Rp.%.2f", p[i].totalPajak);
			printf("\nDaftar Kendaraan:");
			
			for(j=0;j<2;j++){
				printf("\n\t|%s - Rp.%d - Rp.%.2f|", p[i].kendaraan[j].jenis, p[i].kendaraan[j].harga, p[i].kendaraan[j].tarifPajak);
			}
		}
		
	}
}

void editData(Pemilik p[], string oldNIK)
{
	string nama, NIK;
	bool cek;
	int i;
	
	do{
		printf("\nNIK Pemilik : "); fflush(stdin); gets(NIK);
		if(strlen(NIK)==0){
			printf("\nNIK harus di isi");
		} else cek = false;
	}while(cek);
					
	printf("Nama Pemilik : "); fflush(stdin); gets(nama);
	
	i = isFound(p, oldNIK);
	
	strcpy(p[i].nama, nama);
	strcpy(p[i].NIK, NIK);
}

void hapusData(Pemilik p[], string NIK)
{
	int i = isFound(p, NIK);
	int j;
	
	strcpy(p[i].nama, "-");
	strcpy(p[i].NIK, "-");
	p[i].totalPajak = 0;
	
	for(j=0;j<2;j++){
		strcpy(p[i].kendaraan[j].jenis, "-");
		p[i].kendaraan[j].harga = 0;
		p[i].kendaraan[j].tarifPajak = 0;
	}
	 
	
}

Kendaraan makeKendaraan(int harga, string jenis) 
{
	Kendaraan temp;
	
	temp.harga = harga;
	strcpy(temp.jenis, jenis);
	temp.tarifPajak = harga * (1.5/100);
	return temp;
}

int isFull(Pemilik p[]) 
{
	int i;
	
	for (i=0;i<max;i++){
		if(strcmp(p[i].nama, "-")==0){
			return i;
		}
	}
	return -1;
}

int isEmpty(Pemilik p[])
{
	int i;
	int count = 0;
	
	for (i=0;i<max;i++){
		if(strcmp(p[i].nama, "-")==0){
			count++;
		}
	}
	return count;
}

int isFound(Pemilik p[], string NIK)
{
	int i;
	
	for (i=0;i<max;i++){
		if(strcmp(p[i].NIK, NIK)==0){
			return i;
		}
	}
	return -1;
}

