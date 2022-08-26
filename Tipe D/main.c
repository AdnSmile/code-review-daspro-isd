#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define max 3

typedef char string[50];

typedef struct{
	int no;
	int repairCost;
	int biayaMobil;
}Mobil;

typedef struct{
	string nama;
	int spendTim;
	string kode;
	Mobil mobil[2];
}Tim;

void init(Tim t[]);
void addTim(Tim t[]);
void tampil(Tim t[]);
void editData(Tim t[], string kode);
void hapusData(Tim t[], string kode);

Mobil makeMobil(int no, int repairCost);
int isFull(Tim t[]);
int isEmpty(Tim t[]);
int isFound(Tim t[], string kode);

int main(int argc, char *argv[]) {
	int pil;
	Tim t[3];
	string kode;
	
	init(t);
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
				if(isFull(t) != -1)
				{
					printf("---INPUT DATA TIM F1---");
					addTim(t);
					printf("\nberhasil input data...");
				}
				break;
				
			case 2:
				printf("\n---Tampil data TIM F1---");
				tampil(t);
				break;
				
			case 3:
				if(isEmpty(t)!=max)
				{
					printf("\n---Edit data Tim F1---");
					
					printf("\n\nMasukan Kode yang diedit : "); fflush(stdin); gets(kode);
					if(isFound(t, kode)!=-1)
					{
						editData(t, kode);
						printf("\nberhasil edit data...");
					} else printf("\ndata tidak ditemukan");
				} else printf("\ndata masihh kosong!");
				
				break;
				
			case 4:
				if(isEmpty(t)!=-1)
				{
					printf("\n---Hapus data Tim F1---");
					
					printf("\n\nMasukan Kode Tim yang dihapus : "); fflush(stdin); gets(kode);
					if(isFound(t, kode)!=-1)
					{
						hapusData(t, kode);
						printf("\ndata berhasil dihapus...");
					}else printf("\ndata tidak ditemukan...");
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

void init(Tim t[])
{
	int i, j;
	
	for(i=0;i<max;i++){
		strcpy(t[i].nama, "-");
		strcpy(t[i].kode, "-");
		t[i].spendTim = 0;
		
		for(j=0;j<2;j++){
			t[i].mobil[j].repairCost = 0;
			t[i].mobil[j].no = 0;
			t[i].mobil[j].biayaMobil = 0;
		}
	}
}

void addTim(Tim t[])
{
	Tim temp;
	int i, no, repairCost;
	string nama, kode;
	bool cek = true;
	
	do{
		printf("\nKode Tim : "); fflush(stdin); gets(kode);
		if(strlen(kode)==0)
			printf("\nKode harus diisi!");
		else cek = false;
	}while(cek);
	
	printf("Nama Tim : "); fflush(stdin); gets(nama);
	
	strcpy(temp.nama, nama);
	strcpy(temp.kode, kode);
	
	for(i=0;i<2;i++){
		printf("\nMobil ke-%d", i+1);
		printf("\n\tNomor mobil : "); scanf("%d", &no);
		printf("\n\tRepai Cost  : "); scanf("%d", &repairCost);
		
		temp.mobil[i] = makeMobil(no, repairCost);
		temp.spendTim += temp.mobil[i].biayaMobil;
	}
	t[isFull(t)] = temp;
}

void tampil(Tim t[])
{
	int i,j;
	
	for(i=0;i<max;i++)
	{
		if(strcmp(t[i].kode, "-")!=0)
		{
			printf("\n=============================================");
			printf("\nKode Tim F1 : %s", t[i].kode);
			printf("\nNama Tim F1 : %s", t[i].nama);
			printf("\nSpending Tim F1 : $%d", t[i].spendTim);
			printf("\nDaftar Mobil : ");
			
			for(j=0;j<2;j++)
			{
				printf("\n\t|%d - $%d - $%d|", t[i].mobil[j].no, t[i].mobil[j].repairCost, t[i].mobil[j].biayaMobil);	
			}  
		}
	}	
}

void editData(Tim t[], string kode)
{
	int i = isFound(t, kode);
	string newKode, nama;
	bool cek=true;
	
	do{
		printf("\nKode Tim F1 baru : "); fflush(stdin); gets(newKode);
		if(strlen(newKode)==0)
			printf("\nKode harus diisi!");
		else cek = false;
	} while(cek);
	
	printf("Nama TIM F1 : "); fflush(stdin); gets(nama);
	
	strcpy(t[i].nama, nama);
	strcpy(t[i].kode, newKode);
}

void hapusData(Tim t[], string kode)
{
	int i = isFound(t, kode);
	int j;
	
	strcpy(t[i].nama, "-");
	strcpy(t[i].kode, "-");
	t[i].spendTim = 0;
	
	for(j=0;j<2;j++){
		t[i].mobil[j].no = 0;
		t[i].mobil[j].repairCost = 0;
		t[i].mobil[j].biayaMobil = 0;
	}
}

Mobil makeMobil(int no, int repairCost)
{
	Mobil temp;
	
	temp.no = no;
	temp.repairCost = repairCost;
	temp.biayaMobil = repairCost + (10*100);
	
	return temp;
}
int isFull(Tim t[])
{
	int i;
	
	for(i=0;i<max;i++){
		if(strcmp(t[i].kode, "-")==0)
			return i;
	}
	return -1;
}
int isEmpty(Tim t[])
{
	int i, count = 0;
	
	for(i=0;i<max;i++){
		if(strcmp(t[i].kode, "-")==0)
			count++;
	}
	return count;
}
int isFound(Tim t[], string kode)
{
	int i;
	
	for(i=0;i<max;i++){
		if(strcmp(t[i].kode, kode)==0)
			return i;
	}
	return -1;
}
