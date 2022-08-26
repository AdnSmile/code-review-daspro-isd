#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max 3

typedef char string[50];

typedef struct{
	string namaMatkul;
	int sks;
	int harga;
}Matkul;

typedef struct{
	string nama;
	int sppVariabel;
	string npm;
	Matkul matkul[2];
}Mahasiswa;

void init(Mahasiswa m[]);
void addMahasiswa(Mahasiswa m[]);
void tampil(Mahasiswa m[]);
void editData(Mahasiswa m[], string npm);
void hapusData(Mahasiswa m[], string npm);

Matkul makeMatkul(string namaMatkul, int sks);
int isFull(Mahasiswa m[]);
int isEmpty(Mahasiswa m[]);
int isFound(Mahasiswa m[], string npm);


int main(int argc, char *argv[]) {
	
	int pil;
	Mahasiswa mhs[max];
	string npm;
	
	init(mhs);
	
	do{
		system("cls");
		printf("[1] Tambah data");
		printf("\n[2] Tampil data");
		printf("\n[3] Ubah data");
		printf("\n[4] Hapus data");
		printf("\n[0] Exit");
		printf("\n>>> "); scanf("%d", &pil);
		
		switch(pil){
			case 1:
				if(isFull(mhs) != -1)
				{
					printf("\n---INPUT DATA MAHASISWA---");
					addMahasiswa(mhs);
					printf("\nberhasil input data...");
				} else printf("\ndata sudah penuh!");
				break;
				
			case 2:
				printf("\n---Tampil data mahasiswa---");
				tampil(mhs);
				break;
				
			case 3:
				if(isEmpty(mhs)!=max)
				{
					printf("\n---Edit data mahasiswa---");
					
					printf("\n\nMasukan NPM yang diedit : "); fflush(stdin); gets(npm);
					if(isFound(mhs, npm)!=-1)
					{
						editData(mhs, npm);
						printf("\nberhasil edit data...");
					} else printf("\nData tidak ditemukan...");
				}else printf("\ndata masih kosong!");
				break;
				
			case 4:
				if(isEmpty(mhs)!=max)
				{
					printf("\n---Hapus data mahasiswa---");	
					
					printf("\n\nMasukan NPM yang dihapus : "); fflush(stdin); gets(npm);
					if(isFound(mhs, npm)!=-1)
					{
						hapusData(mhs, npm);
						printf("\ndata berhasil dihapus...");
					} else printf("\ndata tidak ditemukan...");
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

void init(Mahasiswa m[])
{
	int i, j;
	
	for(i=0;i<max;i++){
		strcpy(m[i].nama, "-");
		strcpy(m[i].npm, "-");
		m[i].sppVariabel = 0;
		
		for(j=0;j<2;j++){
			strcpy(m[i].matkul[j].namaMatkul, "-");
			m[i].matkul[j].sks = 0;
			m[i].matkul[j].harga = 0;
		}
	}
}

void addMahasiswa(Mahasiswa m[])
{
	Mahasiswa temp;
	int i, sks, harga;
	string namaMatkul, nama, npm;
	bool cek = true;
	
	do{
		printf("\nNPM Mahasiswa : "); fflush(stdin); gets(npm);
		if(strlen(npm)==0)
			printf("\nNPM harus diisi");
		else cek = false;
	}while(cek);
	
	printf("Nama Mahasiswa : "); fflush(stdin); gets(nama);
	
	strcpy(temp.nama, nama);
	strcpy(temp.npm, npm);
	
	for(i=0;i<2;i++){
		printf("\nMatkul ke-%d", i+1);
		printf("\n\tNama Matkul : "); fflush(stdin); gets(namaMatkul);
		printf("\n\tSKS Matkul : "); scanf("%d", &sks);
		
		temp.matkul[i] = makeMatkul(namaMatkul, sks);
		temp.sppVariabel += temp.matkul[i].harga;
	}
	
	m[isFull(m)] = temp;
}

void tampil(Mahasiswa m[])
{
	int i, j;
	
	for(i=0;i<max;i++){
		if(strcmp(m[i].npm, "-")!=0){
			
			printf("\n=========================================");
			printf("\nNPM : %s", m[i].npm);
			printf("\nNama : %s", m[i].nama);
			printf("\nSPP Variabel : %d", m[i].sppVariabel);
			printf("\nDaftar Mata Kuliah : ");
			
			for(j=0;j<2;j++){
				printf("\n\t|%s - %d - Rp.%d|", m[i].matkul[j].namaMatkul, m[i].matkul[j].sks, m[i].matkul[j].harga);
				
			}
		}
	}	
}

void editData(Mahasiswa m[], string npm)
{
	int i = isFound(m, npm);
	string newNpm, nama;
	bool cek=true;
	
	do{
		printf("\nNPM Mahasiswa : "); fflush(stdin); gets(newNpm);
		if(strlen(newNpm)==0)
			printf("\nNPM harus diisi");
		else cek = false;
	}while(cek);
	
	printf("Nama Mahasiswa : "); fflush(stdin); gets(nama);
	
	strcpy(m[i].nama, nama);
	strcpy(m[i].npm, newNpm);
}

void hapusData(Mahasiswa m[], string npm)
{
	int i = isFound(m, npm);
	int j;
	
	strcpy(m[i].nama, "-");
	strcpy(m[i].npm, "-");
	m[i].sppVariabel = 0;
	
	for(j=0;j<2;j++){
		strcpy(m[i].matkul[j].namaMatkul, "-");
		m[i].matkul[j].harga = 0;
		m[i].matkul[j].sks = 0;
	}
}

Matkul makeMatkul(string namaMatkul, int sks)
{
	Matkul temp;
	
	temp.sks = sks;
	strcpy(temp.namaMatkul, namaMatkul);
	temp.harga = sks * 250000;
	
	return temp;
}

int isFull(Mahasiswa m[])
{
	int i;
	
	for(i=0;i<max;i++){
		if(strcmp(m[i].npm, "-")==0)
			return i;
	}
	
	return -1;
}

int isEmpty(Mahasiswa m[])
{
	int i, count = 0;
	
	for(i=0;i<max;i++){
		if(strcmp(m[i].npm, "-")==0)
			count++;
	}
	return count;
}

int isFound(Mahasiswa m[], string npm)
{
	int i;
	
	for(i=0;i<max;i++){
		if(strcmp(m[i].npm, npm)==0)
			return i;
	}
	return -1;
}
