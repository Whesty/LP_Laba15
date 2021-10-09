#include "PN.h"
#include <iostream>
using namespace std;
bool PolishNotation( LT::LexTable& lextable, IT::IdTable& idtable) {
	LT::Entry* stek = new LT::Entry;
	/*LT::Entry null;
	null.idxTI = 0;
	null.lexema = 'n';
	null.sn = 0;*/
	LT::LexTable newlextable = LT::Create(lextable.size+1);
	int idstek = 0;
	int idlex = 0;
	unsigned char* rez;
	bool r = false;
	int lextable_pos = 1;
	int comma = 1;
	cout << "1\n";
	for (int i = 0; i < lextable.size; i++)
	{
		if (lextable.table[i].sn == lextable_pos) {
			if ((lextable.table[i].lexema == LEX_OPERATOR) || (lextable.table[i].lexema == LEX_LEFTTHESIS) || (lextable.table[i].lexema == LEX_COMMA)) {
				cout << "stek + " << lextable.table[i].lexema << " size " << idstek << endl;

				stek[idstek++] = lextable.table[i];
			}
			else { 
				if (lextable.table[i].lexema == LEX_RIGHTTHESIS) {
					cout << comma << " " << idstek << " выгрузка из стека:\n";

					idstek--;
					while (idstek >= 0) {
						if (stek[idstek].lexema == LEX_LEFTTHESIS) {
							if (comma > 1) {
								newlextable.table[idlex].idxTI = comma;
								newlextable.table[idlex].lexema = LEX_COMMA;
								newlextable.table[idlex++].sn = lextable_pos;
								newlextable.size++;
								cout << "lex + " << LEX_COMMA << comma << " size " << idlex << endl;
								comma = 1;
							}
							idstek--;
							break; }
						if (stek[idstek].lexema == LEX_COMMA) {
							comma++;
							idstek--; continue;
						}
						else {
							newlextable.size++;
							cout << "lex + " << stek[idstek].lexema << " size " << idlex << endl;
							newlextable.table[idlex++] = stek[idstek--];
						}
					}
					continue;
				}
				cout << "lex + " << lextable.table[i].lexema << " size " << idlex << endl;
				newlextable.table[idlex++] = lextable.table[i]; 
				newlextable.size++;
			}
		}
		else {
			while (lextable.table[idlex].sn == lextable_pos)
			{
				newlextable.table[idlex++].lexema = NULL;
				newlextable.table[idlex - 1].sn = lextable_pos;
				newlextable.size++;
				cout << "lex + " << NULL << " size" << idlex << endl;

			}
			i = idlex-1;
			lextable_pos++;
			comma = 1;
			if (idstek > 0) {
				cout << "Произошла ошибка приобразования в польскую запись " << lextable.table[i].sn << endl;
				return false;
			}
			idstek = 0;
			cout << lextable_pos << endl;
			/*if (r) {
				cout << "Отстутствеут обязательный элемент ';' в строке " << lextable.table[i].sn << endl;;
				return false;
			}*/
		}
	}
	//ShowPN(newlextable, idtable);
	lextable = newlextable;

	return true;
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
			else cout << sni;
		}
		if (lextable.table[i].lexema == NULL) {
			cout << "null";
			continue;
		}
		if (lextable.table[i].lexema == LEX_COMMA) {
			cout << "@" << lextable.table[i].idxTI;
		}
		else
		cout << lextable.table[i].lexema;
	}
}