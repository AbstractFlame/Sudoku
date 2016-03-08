#include <iostream> // input-output
#include "time.h" // rand()
#include "stdlib.h" // srand()
#include "math.h" // sqrt()

void sendDataToSudoku3000(short **table, bool **tableMap, const short &size, const short &blockSize);
void printTable(short **table, bool **tableMap, const short &size, const short &blockSize, const bool &SHOW_HIDDEN); // kiírja a képernyõre a sudoku táblát
short generate(short **table, const short &size, const short &i, const short &j, const short &blockSize); // generál egy új lemet a táblába
bool createTable(short **table, const short &size, const short &blockSize); // elkészíti a táblát
bool hide(short **table, bool **tableMap, const short &size, const short &blockSize, const short &i, const short &j, short &hiddenCounter); // megnézi, hogy egy számot elrejthetünk-e
bool hide2(short **table, bool **tableMap, bool **blockMap, const short &size, const short &blockSize, const short &i, const short &j, short &hiddenCounter); // megnézi, hogy egy számot elrejthetünk-e
bool cutTable(short **table, bool **tableMap, bool **blockMap, const short &size, const short &blockSize, const short &level);

int main(int argc, char* argv[]) {
	const bool SHOW_HIDDEN = true;
	if(atoi(argv[01]) != 9 && atoi(argv[1]) != 4 || atoi(argv[2]) < 0 || atoi(argv[2]) > 53)
		return 1;
	short size = (short)atoi(argv[1]); // a tábla mérete (size x size méretû)
	short unFilledCells = (short)atoi(argv[2]); // a nehézségi szintet jelöli (minél nagyobb az érték, annál nehezebb)
	double s = size; // segédváltózó a gyökvonáshoz
	short blockSize = (short)sqrt(s); // megállapítjuk a blokkok méretét (blockSize x blockSize)
	short **table = new short*[size]; // a tábla, amibe generáljuk a sudoku számait
	bool **tableMap = new bool*[size]; // logikai tábla, ami megmutatja, hogy a tábla mely elemeit vettük ki, illetve tartottuk meg
	bool **blockMap = new bool*[blockSize]; // az elrejtés során ebben tároljuk azt, hogy ha az adott elrejtendõ számot már elrejtettük volna, akkor a blokkjában mely helyeken zárhatjuk ki megjelenését
	
	srand((unsigned int)time(NULL)); // véletlenszám-generálás inicializálása

	// tábla deklarálása
	for(short i=0; i<size; i++)
		table[i] = new short[size];

	// táblatérkép deklarálása
	for(short i=0; i<size; i++)
		tableMap[i] = new bool[size];

	// blokktérkép deklarálása
	for(short i=0; i<blockSize; i++)
		blockMap[i] = new bool[blockSize];

	// addig készítünk táblát, amíg nem kapunk befejezettet (ez max 1 másodpercet vehet igénybe egy mai számítógép esetén)
	while(!createTable(table,size,blockSize));

	// a táblából "véletlenszerûen" kiveszünk a nehézségi szintnek megfelelõ (size*level*3 db) számot
	while(!cutTable(table, tableMap, blockMap, size, blockSize, unFilledCells));

	//printTable(table,tableMap,size,blockSize,SHOW_HIDDEN);	// tábla kiírása
	sendDataToSudoku3000(table,tableMap,size,blockSize); // tábla kiírása a szabványos kimenetre a Sudoku300

	return 0;
}

void sendDataToSudoku3000(short **table, bool **tableMap, const short &size, const short &blockSize) {
	// a sudoku tábla "elküldése"
	for(short i=0; i<size; i++)
		for(short j=0; j<size; j++)
			std::cout << table[i][j];
	
	// a táblatérkép elküldése
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
	bool *tryed = new bool[size]; // az aktuális cellához kipróbált számok

	// tryed inicializálása
	for(short c=0; c<size; c++)
		tryed[c] = false;

	// igazra állítjuk azokat a számokat, amik már szerepelnek az aktuális sorban, vagy az aktuális oszlopban
	for(short ii=0; ii<i; ii++)
		tryed[table[ii][j]-1] = true;
	for(short jj=0; jj<j; jj++)
		tryed[table[i][jj]-1] = true;

	// igazra állítjuk azokat a számokat, amik már szerepelnek az aktuális blokkban
	short iSartBlock = i-i%blockSize ; // megállapítjuk a block elsõ sorának indexét
	short jStartBlock = j-j%blockSize; // megállapítjuk a block elsõ oszlopának indexét
	for(short ii=iSartBlock; ii<i; ii++)
		for(short jj=jStartBlock; jj<jStartBlock+blockSize; jj++)
			tryed[table[ii][jj]-1] = true;

	// step-edik elemtõl a végéig, majd az elejétõl a step-eid elemig végignézzük az elemeket, és az elsõ hamisnál megtaláltuk a cellába írható számot
	short step = rand()%size; // véletlenszerûen meghatározzuk, hogy hányadik elemtõl nézzük a még nem létezõ szám keresésését
	short cc = step; // tryed tömb számlálója
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
	// tábla feltöltése
	for(short i=0; i<size; i++)
		for(short j=0; j<size; j++)
			if((table[i][j] = generate(table,size,i,j,blockSize)) == 0)
				return false;
	return true;
}

bool hide(short **table, bool **tableMap, const short &size, const short &blockSize, const short &i, const short &j, short &hiddenCounter) {
	// ha már kivettük a számot az aktuális helyrõl, akkor nem sikerült újból kivenni :)
	if(!tableMap[i][j])
		return false;

	bool iHiddenExists = false; // van-e a sorban már kivett szám
	bool jHiddenExists = false; // van-e az oszlopban már kivett szám
	bool bHiddenExists = false; // van-e a blokkban már kivett szám
	short iBlockFirst = i-i%blockSize; // a blokk elsõ oszlopának indexe
	short jBlockFirst = j-j%blockSize; // a blokk elsõ oszlopának indexe
	short iBlock, jBlock; // a blokk aktuális elemének indexei
	// elõször megnézzük, hogy az adott oszlopból, sorból, vagy blockból van-e olyan, amelyikbõl eddig még nem vettünk ki számot.
	// ha az aktuális sorból, oszlopból, és blokkból is kivettünk már számot, akkor is megszakítjuk a ciklust és máshogy vizsgálódunk tovább
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
	// ha már kivettük a számot az aktuális helyrõl, akkor nem sikerült újból kivenni :)
	if(!tableMap[i][j])
		return false;

	bool iHiddenExists = false; // van-e a sorban már kivett szám
	bool jHiddenExists = false; // van-e az oszlopban már kivett szám
	bool bHiddenExists = false; // van-e a blokkban már kivett szám
	short iBlockFirst = i-i%blockSize; // a blokk elsõ oszlopának indexe
	short jBlockFirst = j-j%blockSize; // a blokk elsõ oszlopának indexe
	short iBlock, jBlock; // a blokk aktuális elemének indexei
	short opportunities = size; // itt tároljuk, hogy a blokkon belül még hány helyre írhatnánk be az eltûntetendõ számot. Ha ez 1-re csökken, akkor eltüntethetjük

	// blokktérkép inicializálása
	for(short ic = 0; ic<blockSize; ic++)
		for(short jc = 0; jc<blockSize; jc++)
			if(tableMap[ic+iBlockFirst][jc+jBlockFirst]) {
				blockMap[ic][jc] = false;
				opportunities--;
			}
			else
				blockMap[ic][jc] = true;
	
	// "megpróbáljuk kizárni a blokk többi celláját"
	for(iBlock = iBlockFirst; iBlock<iBlockFirst+blockSize; iBlock++)
		for(jBlock = jBlockFirst; jBlock<jBlockFirst+blockSize; jBlock++)
			if(blockMap[iBlock-iBlockFirst][jBlock-jBlockFirst]) {
				// elõször kiderítjük, hogy a block aktuális cellájának sorában szerepel-e az elrejteni kívánt szám
				bool appear = false; // ez jelzi, hogy az adott cellának a sorában, vagy oszlopában megjelenik-e az eltûntetni kívánt szám
				short c;

				// iBlock-adik sor megvizsgálása
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

				// jBlock-adik oszlop megvizsgálása
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

	// ha elfogyott az összes lehetõség, akkor a késõbbi kitöltés során egyértelmû a kivenni kívánt szám helye a blockba: (i,j)
	if(opportunities == 0) {
		tableMap[i][j] = false;
		hiddenCounter++;
		return true;
	}
	return false;
}

bool cutTable(short **table, bool **tableMap, bool **blockMap, const short &size, const short &blockSize, const short &unFilledCells) {
	short i, j; // sor és oszlopindexek
	short hiddenCounter = 0;	
	int cCounter = 0; // megszámoljuk, hogy folytonosan hányadszorra nem tudtunk kivenni egy újabb számot
	short cAlias = 0; // az elõzõleg kivett szám sorszámát mutatja
	short c = 0;

	// táblatérkép inicializálása
	for(short i=0; i<size; i++)
		for(short j=0; j<size; j++)
			tableMap[i][j] = true;

	// A hide() függvénnyel eltûntetünk size*2 számot, vagy amennyit "záros határidõn belül tudunk"
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
	
	// a hide2 algoritmussal eltüntetünk még annyi számot, hogy összesen level+blockSize darab rejtett számunk legyen
	cCounter = 0; // megszámoljuk, hogy az aktuális c érték hányszor jelentkezett már
	cAlias = 0; // az elõzõ c értéket mutatja
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

	// ha el tudtunk tüntetni a kívánt mennyiségû számot, akkor elkészült a kiegészíthetõ sudoku táblánk
	if(hiddenCounter >= unFilledCells)
		return true;
	else
		return false;
}