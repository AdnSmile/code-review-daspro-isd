#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max 3

typedef char string[50];

typedef struct{
	string kodePesawat;
	int honor;
	float bonus;
}Pesawat;


typedef struct{
	string nama;
	string id;
	float totalHonor;
	Pesawat pesawat[2];
}Pilot;

void init(Pilot pilot[]); // inisialisasi data
void addPilot(Pilot pilot[]); // input data pilot dan pesawat
void tampil(Pilot pilot[]); // menampilkan data
void editData(Pilot pilot[], string id); // mengedit data
void hapusData(Pilot pilot[], string id); // menghapus data

Pesawat makePesawat(string kodePesawat, int honor); // construktor untuk pesawat, bertujuan mempermudah memasukan data pada pesawat
int isFull(Pilot pilot[]); // mengecek data penuh
int isEmpty(Pilot pilot[]); // mengecek data kosong
int isFound(Pilot pilot[], string id); // mencari data dengan id


int main(int argc, char *argv[]) {
	
	int pil;
	Pilot plt[max];
	string id;
	
	init(plt);
	
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
				if(isFull(plt) != -1)
				{
					printf("\n---INPUT DATA PILOT---");
					// input data di prosedur
					addPilot(plt);
					printf("\nberhasil input data...");
				} else printf("\ndata sudah penuh!");
				break;
				
			case 2:
				printf("\n---Tampil data Pilot---");
				tampil(plt);
				break;
				
			case 3:
				if(isEmpty(plt)!=max)
				{
					printf("\n---Ubah data Pilot---");
					
					// input data id di luar prosedur sehingga nilai id nanti di bawa kedalam parameter editData(plt, id)
					printf("\n\nMasukan ID Pilot yang diubah : "); fflush(stdin); gets(id);
					if(isFound(plt, id)!=-1)
					{
						editData(plt, id);
						printf("\nberhasil edit data...");
					} else printf("\ndata tidak ditemukan!");
				}else printf("\ndata masih kosong!");
				break;
				
			case 4:
				if(isEmpty(plt)!=max)
				{
					printf("\n---Hapus data Pilot---");
					
					printf("\n\nMasukan ID Pilot yang dihapus : "); fflush(stdin); gets(id);
					if(isFound(plt, id)!=-1)
					{
						hapusData(plt, id);
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

void init(Pilot pilot[])
{
	int i, j;
	
	for(i=0;i<max;i++){
		strcpy(pilot[i].nama, "-");
		strcpy(pilot[i].id, "-");
		pilot[i].totalHonor = 0;
		
		for(j=0;j<2;j++){
			strcpy(pilot[i].pesawat[j].kodePesawat, "-");
			pilot[i].pesawat[i].honor = 0;
			pilot[i].pesawat[i].bonus = 0;
		}
	}	
}

void addPilot(Pilot pilot[])
{
	// Input data pilot dan pesawat
	Pilot temp;
	int i, honor;
	string kodePesawat, id, nama;
	bool cek = true;
	
	do{
		printf("\nID Pilot : "); fflush(stdin); gets(id);
		if(strlen(id)==0)
			printf("\nID harus diisi");
		else cek = false;
	}while(cek);
	
	printf("Nama Pilot : "); fflush(stdin); gets(nama);
	
	// memasukan nama dan id kedalam temp. gets(temp.id) tidak dilakukan 
	// langsung untuk menghidari error begitujuga dengan nama
	strcpy(temp.id, id);
	strcpy(temp.nama, nama);
	
	for(i=0;i<2;i++){
		printf("\nPesawat ke-%d", i+1);
		printf("\n\tKode Pesawat : "); fflush(stdin); gets(kodePesawat);
		printf("\n\tHonor Pilot : "); scanf("%d", &honor);
		
		
		temp.pesawat[i] = makePesawat(kodePesawat, honor); // menggunakan fungsi makePesawat untuk memasukan data pesawat berdasarkan index
		temp.totalHonor += temp.pesawat[i].bonus;
	}
	
	pilot[isFull(pilot)] = temp; // variabel tampung temp dimasukan kedalam pilot[index]
}

void tampil(Pilot pilot[])
{
	int i, j;
	
	for(i=0;i<max;i++){
		if(strcmp(pilot[i].id, "-")!=0){
			printf("\n=========================================");
			printf("\nID Pilot : %s", pilot[i].id);
			printf("\nNama Pilot : %s", pilot[i].nama);
			printf("\nTotal Honor : Rp%.2f", pilot[i].totalHonor);
			printf("\nDaftar Pesawat : ");
			
			for(j=0;j<2;j++){
				printf("\n\t|%s - Rp%d.00 - Rp%.2f|", pilot[i].pesawat[j].kodePesawat, pilot[i].pesawat[j].honor, pilot[i].pesawat[j].bonus);
			}
		}
	}	
}

void editData(Pilot pilot[], string id)
{
	int i = isFound(pilot, id);
	string newId, nama;
	bool cek = true;
	
	do{
		printf("\nID Pilot : "); fflush(stdin); gets(newId);
		if(strlen(newId)==0)
			printf("\nID harus diisi");
		else cek = false;
	}while(cek);
	
	printf("Nama Pilot : "); fflush(stdin); gets(nama);
	
	strcpy(pilot[i].id, newId);
	strcpy(pilot[i].nama, nama);	
}

void hapusData(Pilot pilot[], string id)
{
	int i = isFound(pilot, id);
	int j;
	
	strcpy(pilot[i].id, "-");
	strcpy(pilot[i].nama, "-");
	pilot[i].totalHonor = 0;
	
	for(j=0;j<2;j++){
		strcpy(pilot[i].pesawat[j].kodePesawat, "-");
		pilot[i].pesawat[j].honor = 0;
		pilot[i].pesawat[j].bonus = 0;
	}
}

Pesawat makePesawat(string kodePesawat, int honor)
{
	Pesawat temp;
	
	strcpy(temp.kodePesawat, kodePesawat);
	temp.honor = honor;
	temp.bonus = honor + (honor*(4.5/100));
	
	return temp;
}

int isFull(Pilot pilot[])
{
	int i;
	
	for(i=0;i<max;i++){
		if(strcmp(pilot[i].id, "-")==0)
			return i;
	}
	return -1;
}

int isEmpty(Pilot pilot[])
{
	int i, count = 0;
	
	for(i=0;i<max;i++){
		if(strcmp(pilot[i].id, "-")==0)
			count++;
	}
	return count;
}

int isFound(Pilot pilot[], string id)
{
	int i;
	
	for(i=0;i<max;i++){
		if(strcmp(pilot[i].id, id)==0)
			return i;
	}
	return -1;
}
