#include "PN.h"
#include <iostream>
#define LEX_COMMA2 '@'
using namespace std;
bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable, int j) {
	LT::Entry* stek = new LT::Entry;
	/*LT::Entry null;
	null.idxTI = 0;
	null.lexema = 'n';
	null.sn = 0;*/
	LT::LexTable newlextable = LT::Create(lextable.size+1);
	int idstek = 0;
	int idlex = j;
	unsigned char* rez;
	bool r = false;
	int comma = 1;
	cout << "1\n";
	for (int i = j; i < lextable.size; i++)
	{
		if (lextable.table[i].sn == lextable_pos) {
			if ((lextable.table[i].lexema == LEX_OPERATOR) || (lextable.table[i].lexema == LEX_LEFTTHESIS) || (lextable.table[i].lexema == LEX_COMMA)) {
				//cout << "stek + " << lextable.table[i].lexema << " size " << idstek << endl;

				stek[idstek++] = lextable.table[i];
			}
			else { 
				if (lextable.table[i].lexema == LEX_RIGHTTHESIS) {
					//cout << comma << " " << idstek << " выгрузка из стека:\n";

					idstek--;
					while (idstek >= 0) {
						if (stek[idstek].lexema == LEX_LEFTTHESIS) {
							if (comma > 1) {
								lextable.table[idlex].idxTI = comma;
								lextable.table[idlex].lexema = LEX_COMMA2;
								lextable.table[idlex++].sn = lextable_pos;
								lextable.size++;
								//cout << "lex + " << LEX_COMMA << comma << " size " << idlex << endl;
								comma = 1;
							}
							idstek--;
							break; }
						if (stek[idstek].lexema == LEX_COMMA) {
							comma++;
							idstek--; continue;
						}
						else {
							lextable.size++;
							//cout << "lex + " << stek[idstek].lexema << " size " << idlex << endl;
							lextable.table[idlex++] = stek[idstek--];
						}
					}
					continue;
				}
				//cout << "lex + " << lextable.table[i].lexema << " size " << idlex << endl;
				lextable.table[idlex++] = lextable.table[i]; 
				lextable.size++;
			}
		}
		else {
			if (lextable.table[i].sn - 1 == lextable_pos) {
				while (lextable.table[idlex].sn == lextable_pos)
				{
					lextable.table[idlex++].lexema = NULL;
					lextable.table[idlex - 1].sn = lextable_pos;
					lextable.size++;
					//cout << "lex + " << NULL << " size" << idlex << endl;

				}
				i = idlex - 1;
				//lextable_pos++;
				comma = 1;
				if (idstek > 0) {
					cout << "Произошла ошибка приобразования в польскую запись " << lextable.table[i].sn << endl;
					return false;
				}
				idstek = 0;
				//cout << lextable_pos << endl;
				return true;
			}
		}
	}
	delete(stek);
	//lextable = newlextable;

	return true;
}
void preabr(LT::LexTable& lextable, IT::IdTable& idtable) {
	int lextable_pos = 0;
	for (int i = 0; i < lextable.size; i++) {
		if (lextable.table[i].sn > lextable_pos) {
			lextable_pos++;
			if (lextable.table[i + 1].lexema == '=') PolishNotation(lextable_pos, lextable, idtable, i);
		}
	}
}
void ShowPN(LT::LexTable& lextable, IT::IdTable& idtable) {
	int sni=1;
	cout << "01.";
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].sn > sni) {
			cout << endl;
			sni = lextable.table[i].sn;
			if (sni <= 9) cout << '0' << sni << ".";
			else cout << sni << ".";
		}
		if (lextable.table[i].lexema == NULL) {
			cout << "null";
			continue;
		}
		if (lextable.table[i].lexema == LEX_COMMA2) {
			cout << "@" << lextable.table[i].idxTI;
		}
		else
		cout << lextable.table[i].lexema;
	}
}