#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max 3

typedef char string[50];

typedef struct{
	string namaMenu;
	float hargaMenu;
	float hargaSetelahDiskon;
}Menu;

typedef struct{
	string nama;
	string id;
	float totalHarga;
	Menu menu[2];
}Pembeli;

void init(Pembeli p[]);
void addPembeli(Pembeli p[]);
void tampil(Pembeli p[]);
void editData(Pembeli p[], string id); 
void hapusData(Pembeli p[], string id);

Menu makeMenu(string namaMenu, int harga);
int isFull(Pembeli p[]);
int isEmpty(Pembeli p[]);
int isFound(Pembeli p[], string id);


int main(int argc, char *argv[]) {
	int pil;
	string id;
	Pembeli p[max];
	
	init(p);
		
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
				if(isFull(p)!=-1)
				{
					printf("\n---INPUT DATA PEMBELI---");
					addPembeli(p);
					printf("\nberhasil input data...");
				}else printf("\ndata sudah penuh!");
				break;
				
			case 2:
				printf("\n---Tampil data pembeli---");
				tampil(p);
				break;
				
			case 3:
				if(isEmpty(p)!=max)
				{
					printf("\n---Edit data Pembeli---");
					
					printf("\n\nMasukan ID yang diedit : "); fflush(stdin); gets(id);
					if(isFound(p, id)!=-1)
					{
						editData(p, id);
						printf("\nberhasil edit data...");
					}else printf("\ndata tidak ditemukan!");
				}else printf("\ndata masih kosong!");
				break;
				
			case 4:
				if(isEmpty(p)!=max)
				{
					printf("\n---Hapus data Pembeli---");
					
					printf("\n\nMasukan ID yang dihapus : "); fflush(stdin); gets(id);
					if(isFound(p, id)!=-1)
					{
						hapusData(p, id);
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

void init(Pembeli p[])
{
	int i, j;
	
	for(i=0;i<max;i++){
		strcpy(p[i].nama, "-");
		strcpy(p[i].id, "-");
		p[i].totalHarga = 0;
		
		for(j=0;j<2;j++){
			strcpy(p[i].menu[j].namaMenu, "-");
			p[i].menu[j].hargaMenu = 0;
			p[i].menu[j].hargaSetelahDiskon = 0;
		}
	}
}

void addPembeli(Pembeli p[])
{
	Pembeli temp;
	int i, harga;
	string nama, id, namaMenu;
	bool cek = true;
	
	do{
		printf("\nID Pembeli : "); fflush(stdin); gets(id);
		if(strlen(id)==0)
			printf("\nID harus diisi!");
		else cek = false;
	}while(cek);
	
	printf("Nama pembeli : "); fflush(stdin); gets(nama);
	
	strcpy(temp.nama, nama);
	strcpy(temp.id, id);
	
	for(i=0;i<2;i++){
		printf("\nMenu ke-%d", i+1);
		printf("\n\tNama Menu : "); fflush(stdin); gets(namaMenu);
		printf("\tHarga menu : "); scanf("%d", &harga);
		
		temp.menu[i] = makeMenu(namaMenu, harga);
		temp.totalHarga += temp.menu[i].hargaSetelahDiskon;
	}
	p[isFull(p)] = temp;
}

void tampil(Pembeli p[])
{
	int i, j;
	
	for(i=0;i<max;i++){
		if(strcmp(p[i].id, "-")!=0){
			
			printf("\n=========================================");
			printf("\nID pembeli : %s", p[i].id);
			printf("\nNama pembeli: %s", p[i].nama);
			printf("\nTotal harga : Rp%.2f.00", p[i].totalHarga);
			printf("\nDaftar Menu yang dipesan : ");
			
			for(j=0;j<2;j++){
				printf("\n\t|%s - Rp%.2f - Rp.%.2f|", p[i].menu[j].namaMenu, p[i].menu[j].hargaMenu, p[i].menu[j].hargaSetelahDiskon);
				
			}
		}
	}	
}
void editData(Pembeli p[], string id)
{
	int i = isFound(p, id);
	string newId, nama;
	bool cek;
	
	do{
		printf("\nID Pembeli : "); fflush(stdin); gets(newId);
		if(strlen(newId)==0)
			printf("\nID harus diisi!");
		else cek = false;
	}while(cek);
	
	printf("Nama pembeli : "); fflush(stdin); gets(nama);
	
	strcpy(p[i].nama, nama);
	strcpy(p[i].id, newId);
}

void hapusData(Pembeli p[], string id)
{
	int i = isFound(p, id);
	int j;
	
	strcpy(p[i].nama, "-");
	strcpy(p[i].id, "-");
	p[i].totalHarga = 0;
	
	for(j=0;j<2;j++){
		strcpy(p[i].menu[j].namaMenu, "-");
		p[i].menu[j].hargaMenu = 0;
		p[i].menu[j].hargaSetelahDiskon = 0;
	}
}

Menu makeMenu(string namaMenu, int harga)
{
	Menu temp;
	float persen = 15.5/100;
	
	temp.hargaMenu = harga;
	strcpy(temp.namaMenu, namaMenu);
	temp.hargaSetelahDiskon = harga-(persen * harga);
	return temp;	
}

int isFull(Pembeli p[])
{
	int i;
	
	for(i=0;i<max;i++){
		if(strcmp(p[i].id, "-")==0)
			return i;
	}
	
	return -1;
}
int isEmpty(Pembeli p[])
{
	int i, count = 0;
	
	for(i=0;i<max;i++){
		if(strcmp(p[i].id, "-")==0)
			count++;
	}
	
	return count;
}

int isFound(Pembeli p[], string id)
{
	int i;
	
	for(i=0;i<max;i++){
		if(strcmp(p[i].id, id)==0)
			return i;
	}
	
	return -1;
}
