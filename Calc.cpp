//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Calc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
char lastChar = '0';
int pCount = 0;
bool fMode = false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------




void __fastcall TForm1::NumberClick(TObject *Sender)
{
	TButton* b = ((TButton*)Sender);

	if(EditDisplay->Text == "0") {
		EditDisplay->Text = b->Caption;
	}
	else {
		EditDisplay->Text = EditDisplay->Text + b->Caption;
	}
	lastChar = b->Caption[1];
	fMode = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ParenClick1(TObject *Sender)
{
	if(fMode == false) {
    	TButton* b = ((TButton*)Sender);

		if(EditDisplay->Text == "0") {
			EditDisplay->Text = '(';
		}
		else {
			EditDisplay->Text = EditDisplay->Text + '(';
		}
		lastChar = '(';
		pCount++;
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ParenClick2(TObject *Sender)
{
	if(lastChar != '(' && pCount > 0 && (fMode == true || lastChar == ')' )) {

		TButton* b = ((TButton*)Sender);

		if(EditDisplay->Text == "0") {
			EditDisplay->Text = ')';
		}
		else {
			EditDisplay->Text = EditDisplay->Text + ')';
		}
		lastChar = ')';
		pCount--;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AddClick(TObject *Sender)
{
	if(fMode == true) {
		TButton* b = ((TButton*)Sender);
		EditDisplay->Text = EditDisplay->Text + '+';
		lastChar = '+';
		fMode = false;
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SubClick(TObject *Sender)
{
	if(fMode == true) {
		TButton* b = ((TButton*)Sender);
		EditDisplay->Text = EditDisplay->Text + '�';
		lastChar = '�';
		fMode = false;
	}
}
//---------------------------------------------------------------------------

