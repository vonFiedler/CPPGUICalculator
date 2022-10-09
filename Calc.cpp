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
bool dMode = false;
bool nMode = false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------




void __fastcall TForm1::NumberClick(TObject *Sender)
{
	TButton* b = ((TButton*)Sender);
	if(nMode == true) {
		if(EditDisplay->Text == "0") {
			EditDisplay->Text = '-';
		}
		else {
			EditDisplay->Text = EditDisplay->Text + '-';
		}
		nMode = false;
	}

	if(fMode == false) {
		dMode = true;
    }

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
		dMode = false;
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
		dMode = false;
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
		dMode = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SubClick(TObject *Sender)
{
	if(fMode == true) {
		TButton* b = ((TButton*)Sender);
		EditDisplay->Text = EditDisplay->Text + L"─";
		lastChar = '-';
		fMode = false;
		dMode = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MulClick(TObject *Sender)
{
	if(fMode == true) {
		TButton* b = ((TButton*)Sender);
		EditDisplay->Text = EditDisplay->Text + '*';
		lastChar = '*';
		fMode = false;
		dMode = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DivClick(TObject *Sender)
{
	if(fMode == true) {
		TButton* b = ((TButton*)Sender);
		EditDisplay->Text = EditDisplay->Text + '/';
		lastChar = '/';
		fMode = false;
        dMode = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DotClick(TObject *Sender)
{
	if(dMode == true) {
		TButton* b = ((TButton*)Sender);
		EditDisplay->Text = EditDisplay->Text + '.';
		lastChar = '.';
		dMode = false;
		fMode = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::NegClick(TObject *Sender)
{
	if(lastChar == '(' || lastChar == '+' || lastChar == '-' || lastChar == '*'
		|| lastChar == '/' || EditDisplay->Text == "0") {
		TButton* b = ((TButton*)Sender);
		if(nMode == false) {
			nMode = true;
		}
		else {
			nMode = false;
		}
	}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::PowClick(TObject *Sender)
{
	if(fMode == true) {
		TButton* b = ((TButton*)Sender);
		EditDisplay->Text = EditDisplay->Text + "^(";
		pCount++;
		lastChar = '(';
		dMode = false;
		fMode = false;
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ClearClick(TObject *Sender)
{
	EditDisplay->Text = "0";
	lastChar = '0';
	fMode = false;
	dMode = false;
	nMode = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SinClick(TObject *Sender)
{
	if(fMode == false) {
		if(EditDisplay->Text == "0") {
			EditDisplay->Text = "sin(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "sin(";
		}
		pCount++;
		lastChar = '(';
		dMode = false;
		fMode = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CosClick(TObject *Sender)
{
	if(fMode == false) {
		if(EditDisplay->Text == "0") {
			EditDisplay->Text = "cos(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "cos(";
		}
		pCount++;
		lastChar = '(';
		dMode = false;
		fMode = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TanClick(TObject *Sender)
{
	if(fMode == false) {
		if(EditDisplay->Text == "0") {
			EditDisplay->Text = "tan(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "tan(";
		}
		pCount++;
		lastChar = '(';
		dMode = false;
		fMode = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CotClick(TObject *Sender)
{
	if(fMode == false) {
		if(EditDisplay->Text == "0") {
			EditDisplay->Text = "cot(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "cot(";
		}
		pCount++;
		lastChar = '(';
		dMode = false;
		fMode = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LnClick(TObject *Sender)
{
	if(fMode == false) {
		if(EditDisplay->Text == "0") {
			EditDisplay->Text = "ln(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "ln(";
		}
		pCount++;
		lastChar = '(';
		dMode = false;
		fMode = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::LogClick(TObject *Sender)
{
	if(fMode == false) {
		if(EditDisplay->Text == "0") {
			EditDisplay->Text = "log(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "log(";
		}
		pCount++;
		lastChar = '(';
		dMode = false;
		fMode = false;
	}
}
//---------------------------------------------------------------------------

