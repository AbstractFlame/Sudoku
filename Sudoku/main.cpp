#include <iostream> // input-output
#include "time.h" // rand()
#include "stdlib.h" // srand()
#include "math.h" // sqrt()

void sendDataToSudoku3000(short **table, bool **tableMap, const short &size, const short &blockSize);
void printTable(short **table, bool **tableMap, const short &size, const short &blockSize, const bool &SHOW_HIDDEN); // ki�rja a k�perny�re a sudoku t�bl�t
short generate(short **table, const short &size, const short &i, const short &j, const short &blockSize); // gener�l egy �j lemet a t�bl�ba
bool createTable(short **table, const short &size, const short &blockSize); // elk�sz�ti a t�bl�t
bool hide(short **table, bool **tableMap, const short &size, const short &blockSize, const short &i, const short &j, short &hiddenCounter); // megn�zi, hogy egy sz�mot elrejthet�nk-e
bool hide2(short **table, bool **tableMap, bool **blockMap, const short &size, const short &blockSize, const short &i, const short &j, short &hiddenCounter); // megn�zi, hogy egy sz�mot elrejthet�nk-e
bool cutTable(short **table, bool **tableMap, bool **blockMap, const short &size, const short &blockSize, const short &level);

int main(int argc, char* argv[]) {
	const bool SHOW_HIDDEN = true;
	if(atoi(argv[01]) != 9 && atoi(argv[1]) != 4 || atoi(argv[2]) < 0 || atoi(argv[2]) > 53)
		return 1;
	short size = (short)atoi(argv[1]); // a t�bla m�rete (size x size m�ret�)
	short unFilledCells = (short)atoi(argv[2]); // a neh�zs�gi szintet jel�li (min�l nagyobb az �rt�k, ann�l nehezebb)
	double s = size; // seg�dv�lt�z� a gy�kvon�shoz
	short blockSize = (short)sqrt(s); // meg�llap�tjuk a blokkok m�ret�t (blockSize x blockSize)
	short **table = new short*[size]; // a t�bla, amibe gener�ljuk a sudoku sz�mait
	bool **tableMap = new bool*[size]; // logikai t�bla, ami megmutatja, hogy a t�bla mely elemeit vett�k ki, illetve tartottuk meg
	bool **blockMap = new bool*[blockSize]; // az elrejt�s sor�n ebben t�roljuk azt, hogy ha az adott elrejtend� sz�mot m�r elrejtett�k volna, akkor a blokkj�ban mely helyeken z�rhatjuk ki megjelen�s�t
	
	srand((unsigned int)time(NULL)); // v�letlensz�m-gener�l�s inicializ�l�sa

	// t�bla deklar�l�sa
	for(short i=0; i<size; i++)
		table[i] = new short[size];

	// t�blat�rk�p deklar�l�sa
	for(short i=0; i<size; i++)
		tableMap[i] = new bool[size];

	// blokkt�rk�p deklar�l�sa
	for(short i=0; i<blockSize; i++)
		blockMap[i] = new bool[blockSize];

	// addig k�sz�t�nk t�bl�t, am�g nem kapunk befejezettet (ez max 1 m�sodpercet vehet ig�nybe egy mai sz�m�t�g�p eset�n)
	while(!createTable(table,size,blockSize));

	// a t�bl�b�l "v�letlenszer�en" kivesz�nk a neh�zs�gi szintnek megfelel� (size*level*3 db) sz�mot
	while(!cutTable(table, tableMap, blockMap, size, blockSize, unFilledCells));

	//printTable(table,tableMap,size,blockSize,SHOW_HIDDEN);	// t�bla ki�r�sa
	sendDataToSudoku3000(table,tableMap,size,blockSize); // t�bla ki�r�sa a szabv�nyos kimenetre a Sudoku300

	return 0;
}

void sendDataToSudoku3000(short **table, bool **tableMap, const short &size, const short &blockSize) {
	// a sudoku t�bla "elk�ld�se"
	for(short i=0; i<size; i++)
		for(short j=0; j<size; j++)
			std::cout << table[i][j];
	
	// a t�blat�rk�p elk�ld�se
	for(short i=0; i<size; i++)
		for(short j=0; j<size; j++)
			std::cout << tableMap[i][j] ? 1 : 0;
}

void printTable(short **table, bool **tableMap, const short &size, const short &blockSize, const bool &SHOW_HIDDEN) {
	for(short i=0; i<size*2+1; i++)
		std::cout << "-";
	std::cout << "\n";
	for(short i=0; i<size; i++) {
		std::cout << "|";
		for(short j=0; j<size; j++)
			if(!SHOW_HIDDEN || tableMap[i][j])
				if((j+1)%blockSize==0)
					std::cout << "|" << table[i][j];
				else
					std::cout << " " << table[i][j];
			else
				if((j+1)%blockSize==0)
					std::cout << " |";
				else
					std::cout << "  ";
		if((i+1)%blockSize==0) {
			std::cout << "\n";
			for(short i=0; i<size*2+1; i++)
				std::cout << "-";
			std::cout << "\n";
		}
		else
			std::cout << "\n";
	}
}

short generate(short **table, const short &size, const short &i, const short &j, const short &blockSize) {
	bool *tryed = new bool[size]; // az aktu�lis cell�hoz kipr�b�lt sz�mok

	// tryed inicializ�l�sa
	for(short c=0; c<size; c++)
		tryed[c] = false;

	// igazra �ll�tjuk azokat a sz�mokat, amik m�r szerepelnek az aktu�lis sorban, vagy az aktu�lis oszlopban
	for(short ii=0; ii<i; ii++)
		tryed[table[ii][j]-1] = true;
	for(short jj=0; jj<j; jj++)
		tryed[table[i][jj]-1] = true;

	// igazra �ll�tjuk azokat a sz�mokat, amik m�r szerepelnek az aktu�lis blokkban
	short iSartBlock = i-i%blockSize ; // meg�llap�tjuk a block els� sor�nak index�t
	short jStartBlock = j-j%blockSize; // meg�llap�tjuk a block els� oszlop�nak index�t
	for(short ii=iSartBlock; ii<i; ii++)
		for(short jj=jStartBlock; jj<jStartBlock+blockSize; jj++)
			tryed[table[ii][jj]-1] = true;

	// step-edik elemt�l a v�g�ig, majd az elej�t�l a step-eid elemig v�gign�zz�k az elemeket, �s az els� hamisn�l megtal�ltuk a cell�ba �rhat� sz�mot
	short step = rand()%size; // v�letlenszer�en meghat�rozzuk, hogy h�nyadik elemt�l n�zz�k a m�g nem l�tez� sz�m keres�s�s�t
	short cc = step; // tryed t�mb sz�ml�l�ja
	for(short c=step; c<step+size; c++) {
		if(cc == size)
			cc = 0;
		if(!tryed[cc])
			return cc+1;
		cc++;
	}
	return 0;
}

bool createTable(short **table, const short &size, const short &blockSize) {
	// t�bla felt�lt�se
	for(short i=0; i<size; i++)
		for(short j=0; j<size; j++)
			if((table[i][j] = generate(table,size,i,j,blockSize)) == 0)
				return false;
	return true;
}

bool hide(short **table, bool **tableMap, const short &size, const short &blockSize, const short &i, const short &j, short &hiddenCounter) {
	// ha m�r kivett�k a sz�mot az aktu�lis helyr�l, akkor nem siker�lt �jb�l kivenni :)
	if(!tableMap[i][j])
		return false;

	bool iHiddenExists = false; // van-e a sorban m�r kivett sz�m
	bool jHiddenExists = false; // van-e az oszlopban m�r kivett sz�m
	bool bHiddenExists = false; // van-e a blokkban m�r kivett sz�m
	short iBlockFirst = i-i%blockSize; // a blokk els� oszlop�nak indexe
	short jBlockFirst = j-j%blockSize; // a blokk els� oszlop�nak indexe
	short iBlock, jBlock; // a blokk aktu�lis elem�nek indexei
	// el�sz�r megn�zz�k, hogy az adott oszlopb�l, sorb�l, vagy blockb�l van-e olyan, amelyikb�l eddig m�g nem vett�nk ki sz�mot.
	// ha az aktu�lis sorb�l, oszlopb�l, �s blokkb�l is kivett�nk m�r sz�mot, akkor is megszak�tjuk a ciklust �s m�shogy vizsg�l�dunk tov�bb
	short c;
	for(c=0; c<size && !iHiddenExists; c++)
		if(!tableMap[i][c])
			iHiddenExists = true;
	if(iHiddenExists)
		for(c=0; c<size && !jHiddenExists; c++)
			if(!tableMap[c][j])
				jHiddenExists = true;
	if(iHiddenExists && jHiddenExists)
		for(c=0; c<size && !bHiddenExists; c++) {
			iBlock = iBlockFirst+(short)ceil( (float)(c+1)/blockSize)-1;
			jBlock = jBlockFirst+c%blockSize;
			if(!tableMap[iBlock][jBlock])
				bHiddenExists = true;
		}
	if(!iHiddenExists || !jHiddenExists || !bHiddenExists) {
		tableMap[i][j] = false;
		hiddenCounter++;
		return true;
	}
	return false;
}

bool hide2(short **table, bool **tableMap, bool **blockMap, const short &size, const short &blockSize, const short &i, const short &j, short &hiddenCounter) {
	// ha m�r kivett�k a sz�mot az aktu�lis helyr�l, akkor nem siker�lt �jb�l kivenni :)
	if(!tableMap[i][j])
		return false;

	bool iHiddenExists = false; // van-e a sorban m�r kivett sz�m
	bool jHiddenExists = false; // van-e az oszlopban m�r kivett sz�m
	bool bHiddenExists = false; // van-e a blokkban m�r kivett sz�m
	short iBlockFirst = i-i%blockSize; // a blokk els� oszlop�nak indexe
	short jBlockFirst = j-j%blockSize; // a blokk els� oszlop�nak indexe
	short iBlock, jBlock; // a blokk aktu�lis elem�nek indexei
	short opportunities = size; // itt t�roljuk, hogy a blokkon bel�l m�g h�ny helyre �rhatn�nk be az elt�ntetend� sz�mot. Ha ez 1-re cs�kken, akkor elt�ntethetj�k

	// blokkt�rk�p inicializ�l�sa
	for(short ic = 0; ic<blockSize; ic++)
		for(short jc = 0; jc<blockSize; jc++)
			if(tableMap[ic+iBlockFirst][jc+jBlockFirst]) {
				blockMap[ic][jc] = false;
				opportunities--;
			}
			else
				blockMap[ic][jc] = true;
	
	// "megpr�b�ljuk kiz�rni a blokk t�bbi cell�j�t"
	for(iBlock = iBlockFirst; iBlock<iBlockFirst+blockSize; iBlock++)
		for(jBlock = jBlockFirst; jBlock<jBlockFirst+blockSize; jBlock++)
			if(blockMap[iBlock-iBlockFirst][jBlock-jBlockFirst]) {
				// el�sz�r kider�tj�k, hogy a block aktu�lis cell�j�nak sor�ban szerepel-e az elrejteni k�v�nt sz�m
				bool appear = false; // ez jelzi, hogy az adott cell�nak a sor�ban, vagy oszlop�ban megjelenik-e az elt�ntetni k�v�nt sz�m
				short c;

				// iBlock-adik sor megvizsg�l�sa
				for(c=0; c<jBlockFirst; c++)
					if(table[iBlock][c] == table[i][j] && tableMap[iBlock][c]) {
						appear = true;
						break;
					}
				if(!appear)
					for(c=jBlockFirst+blockSize; c<size; c++)
						if(table[iBlock][c] == table[i][j] && tableMap[iBlock][c]) {
							appear = true;
							break;
						}
				if(appear)
					for(c=jBlockFirst; c<jBlockFirst+blockSize; c++)
						if(blockMap[iBlock-iBlockFirst][c-jBlockFirst]) {
							opportunities--;
							blockMap[iBlock-iBlockFirst][c-jBlockFirst] = false;
						}

				// jBlock-adik oszlop megvizsg�l�sa
				for(c=0; c<iBlockFirst; c++)
					if(table[c][jBlock] == table[i][j] && tableMap[iBlock][c]) {
						appear = true;
						break;
					}
				if(!appear)
					for(c=iBlockFirst+blockSize; c<size; c++)
						if(table[c][jBlock] == table[i][j] && tableMap[iBlock][c]) {
							appear = true;
							break;
						}
				if(appear)
					for(c=iBlockFirst; c<iBlockFirst+blockSize; c++)
						if(blockMap[c-iBlockFirst][jBlock-jBlockFirst]) {
							opportunities--;
							blockMap[c-iBlockFirst][jBlock-jBlockFirst] = false;
						}
			}

	// ha elfogyott az �sszes lehet�s�g, akkor a k�s�bbi kit�lt�s sor�n egy�rtelm� a kivenni k�v�nt sz�m helye a blockba: (i,j)
	if(opportunities == 0) {
		tableMap[i][j] = false;
		hiddenCounter++;
		return true;
	}
	return false;
}

bool cutTable(short **table, bool **tableMap, bool **blockMap, const short &size, const short &blockSize, const short &unFilledCells) {
	short i, j; // sor �s oszlopindexek
	short hiddenCounter = 0;	
	int cCounter = 0; // megsz�moljuk, hogy folytonosan h�nyadszorra nem tudtunk kivenni egy �jabb sz�mot
	short cAlias = 0; // az el�z�leg kivett sz�m sorsz�m�t mutatja
	short c = 0;

	// t�blat�rk�p inicializ�l�sa
	for(short i=0; i<size; i++)
		for(short j=0; j<size; j++)
			tableMap[i][j] = true;

	// A hide() f�ggv�nnyel elt�ntet�nk size*2 sz�mot, vagy amennyit "z�ros hat�rid�n bel�l tudunk"
	for(short c = 0; hiddenCounter<unFilledCells && (c<size*2 || (cAlias>12 && cCounter<10)) && cCounter<50; c++) {
		i = rand()%size;
		j = rand()%size;
		cAlias = c-1;
		if(!hide(table, tableMap, size, blockSize, i, j, hiddenCounter))
			c--;
		if(cAlias == c)
			cCounter++;
	}
	//std::cout << "hide algoritmus: " << (short)hiddenCounter << "\n";
	
	// a hide2 algoritmussal elt�ntet�nk m�g annyi sz�mot, hogy �sszesen level+blockSize darab rejtett sz�munk legyen
	cCounter = 0; // megsz�moljuk, hogy az aktu�lis c �rt�k h�nyszor jelentkezett m�r
	cAlias = 0; // az el�z� c �rt�ket mutatja
	for(c = 0; ((cAlias>12 && cCounter<50) || cCounter<100) && hiddenCounter<unFilledCells; c++) {
		i = rand()%size;
		j = rand()%size;
		cAlias = c-1;
		if(!hide2(table, tableMap, blockMap, size, blockSize, i, j, hiddenCounter))
			c--;
		if(cAlias == c)
			cCounter++;
	}
	//std::cout << "hide2 algoritmus: " << (short)hiddenCounter << "\n";

	// ha el tudtunk t�ntetni a k�v�nt mennyis�g� sz�mot, akkor elk�sz�lt a kieg�sz�thet� sudoku t�bl�nk
	if(hiddenCounter >= unFilledCells)
		return true;
	else
		return false;
}