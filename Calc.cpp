﻿//---------------------------------------------------------------------------

#include <vcl.h>
#include "Calc.h"
#include <stack>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>
#include <stdexcept>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma hdrstop
using namespace std;
TForm1 *Form1;
char lastChar = '0';
int pCount = 0;
bool fMode = false;
bool dMode = false;
bool d2Mode = true;
bool nMode = false;

string infix = "0";

bool isMathOperator(char token) {
// this function checks if operand is a math operator
	switch (tolower(token)) {
		case '+': case '-': case '*': case '/':
		case '^': case 'c': case 's': case 't':
		case 'o': case 'l': case 'n':
			return true;
			break;
		default:
			return false;
			break;
	}
}// end of isMathOperator

string replaceAll(const string& source
	, const string& oldValue, const string& newValue) {
	if (oldValue.empty()) {
        return source;
    }
	string newString;
    newString.reserve(source.length());
	size_t lastPos = 0;
	size_t findPos;
	while (string::npos != (findPos = source.find(oldValue, lastPos))) {
        newString.append(source, lastPos, findPos - lastPos);
		newString += newValue;
		lastPos = findPos + oldValue.length();
	}
    newString += source.substr(lastPos);
    return newString;
}// end of replaceAll

int orderOfOperations(char token) {
// this function returns the priority of each math operator
	int priority = 0;
	switch (std::tolower(token)) {
		case 'c': case 's': case 't': case 'o': case 'l': case 'n':
            priority = 5;
			break;
		case '^':
            priority = 4;
			break;
		case '*': case '/':
			priority = 3;
			break;
		case '-':
			priority = 2;
			break;
		case '+':
			priority = 1;
			break;
	}
	return priority;
}// end of orderOfOperations

bool isNumeric(char value) {
	return isdigit(value) || value == '.' || value == '~';
}// end of isNumeric

bool isNumeric(string value) {
	for (unsigned index = 0; index < value.length(); ++index) {
		if (index == 0 && value[index] == '-' && value.length() > 1) {
			continue;
		}
		if (!isNumeric(value[index])) {
			return false;
		}
	}
	return true;
}// end of isNumeric

string convertInfixToPostfix(string infix) {
	string postfix;
	stack<char> charStack;
    // loop thru array until there is no more data
	for (unsigned x = 0; x < infix.length(); ++x) {
        // place numbers (standard, decimal, & negative)
		// numbers onto the 'postfix' string
		if (isNumeric(infix[x])) {
            if (postfix.length() > 0 && !isNumeric(postfix.back())) {
				if (!isspace(postfix.back())) {
                    postfix += " ";
				}
            }
			postfix += infix[x];

		} else if (isspace(infix[x])) {
            continue;

		} else if (isMathOperator(infix[x])) {
			if (postfix.length() > 0 && !isspace(postfix.back())) {
				postfix += " ";
            }
            // use the 'orderOfOperations' function to check equality
            // of the math operator at the top of the stack compared to
            // the current math operator in the infix string
            while ((!charStack.empty()) &&
				(orderOfOperations(charStack.top()) >= orderOfOperations(infix[x]))) {
                // place the math operator from the top of the
                // stack onto the postfix string and continue the
                // process until complete
				if (postfix.length() > 0 && !isspace(postfix.back())) {
                    postfix += " ";
                }
                postfix += charStack.top();
                charStack.pop();
            }
            // push the remaining math operator onto the stack
            charStack.push(infix[x]);
		}
	}

	// place any remaining math operators from the stack onto
    // the postfix array
	while (!charStack.empty()) {
        if (postfix.length() > 0 && !std::isspace(postfix.back())) {
            postfix += " ";
        }
        postfix += charStack.top();
        charStack.pop();
	}
	// replace all '~' symbols with a minus sign
	postfix = replaceAll(postfix, "~", "-");

	return postfix;
}// end of convertInfixToPostfix

double calculate(char mathOperator, double value1, double value2) {
// this function carries out the actual math process
    double ans = 0;
	switch (mathOperator) {
		case '+':
			ans = value1 + value2;
			break;
		case '-':
			ans = value1 - value2;
            break;
		case '*':
			ans = value1 * value2;
            break;
		case '/':
			ans = value1 / value2;
			break;
		case '^':
			ans = pow(value1, value2);
			break;
			ans = cos(value1);
            break;
		case 's':
			ans = sin(value1);
            break;
		case 't':
			ans = tan(value1);
			break;
		case 'o':
			ans = cos(value1) / sin(value1);
			break;
		case 'l':
			ans = log10(value1);
			break;
		case 'n':
			ans = log(value1);
			break;
        default:
            ans = 0;
            break;
	}
    return ans;
}// end of calculate

vector<string> split(const string& source, const string& delimiters) {
	size_t prev = 0;
	size_t currentPos = 0;
	vector<string> results;

	while ((currentPos = source.find_first_of(delimiters, prev)) != string::npos) {
		if (currentPos > prev) {
            results.push_back(source.substr(prev, currentPos - prev));
        }
        prev = currentPos + 1;
    }
    if (prev < source.length()) {
		results.push_back(source.substr(prev, string::npos));
	}
    return results;
}// end of split

double evaluatePostfix(const string& postfix) {
// this function evaluates a postfix expression
    // declare function variables
	double answer = 0;
	stack<double> doubleStack;

	// split string into tokens to isolate multi digit, negative and decimal
	// numbers, aswell as single digit numbers and math operators
	auto tokens = split(postfix, " ");

    // display the found tokens to the screen
    //for (unsigned x = 0; x < tokens.size(); ++x) {
    //    std::cout<< tokens.at(x) << std::endl;
    //}

	//std::cout << "\nCalculations:\n";

    // loop thru array until there is no more data
	for (unsigned x = 0; x < tokens.size(); ++x) {
        auto token = tokens[x];

        // push numbers & negative numbers onto the stack
        if (isNumeric(token)) {
            doubleStack.push(std::atof(token.c_str()));
        }
        // if expression is a math operator, pop numbers from stack
        // & send the popped numbers to the 'calculate' function
        else if (isMathOperator(token[0]) && (!doubleStack.empty())) {
            double value1 = 0;
            double value2 = 0;
            char mathOperator = static_cast<unsigned char>(std::tolower(token[0]));

			// if expression is sin, cos, tan, cot
			// log, or ln operation only pop stack once
			if (mathOperator == 'o' || mathOperator == 's' || mathOperator == 'c' ||
				mathOperator == 't' || mathOperator == 'l' || mathOperator == 'n') {
				value2 = 0;
				value1 = doubleStack.top();
				doubleStack.pop();
                answer = calculate(mathOperator, value1, value2);
				doubleStack.push(answer);

            } else if (doubleStack.size() > 1) {
                value2 = doubleStack.top();
                doubleStack.pop();
                value1 = doubleStack.top();
                doubleStack.pop();
                answer = calculate(mathOperator, value1, value2);
                doubleStack.push(answer);
            }
        } else {
            // this should never execute, & if it does, something went really wrong
			throw invalid_argument{ "INVALID POSTFIX STRING" };
        }
    }
    // pop the final answer from the stack, and return to main
    if (!doubleStack.empty()) {
        answer = doubleStack.top();
    }
    return answer;
}// end of evaluatePostfix



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
			infix = '~';
		}
		else {
			EditDisplay->Text = EditDisplay->Text + '-';
			infix = infix + '~';
		}
		nMode = false;
	}

	if(d2Mode == true) {
		dMode = true;
    }

	if(EditDisplay->Text == "0") {
		EditDisplay->Text = b->Caption;
		infix = char(EditDisplay->Text[1]);
	}
	else {
		EditDisplay->Text = EditDisplay->Text + b->Caption;
		infix = infix + char(EditDisplay->Text[EditDisplay->Text.Length()]);
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
			infix = '(';
		}
		else {
			EditDisplay->Text = EditDisplay->Text + '(';
			infix = infix + '(';
		}
		lastChar = '(';
		pCount++;
		dMode = false;
		d2Mode = true;
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ParenClick2(TObject *Sender)
{
	if(lastChar != '(' && pCount > 0 && (fMode == true || lastChar == ')' )) {

		TButton* b = ((TButton*)Sender);

		EditDisplay->Text = EditDisplay->Text + ')';
		infix = infix + ')';

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
		infix = infix + '+';
		lastChar = '+';
		fMode = false;
		dMode = false;
		d2Mode = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SubClick(TObject *Sender)
{
	if(fMode == true) {
		TButton* b = ((TButton*)Sender);
		EditDisplay->Text = EditDisplay->Text + '-';
		infix = infix + '-';
		lastChar = '-';
		fMode = false;
		dMode = false;
		d2Mode = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MulClick(TObject *Sender)
{
	if(fMode == true) {
		TButton* b = ((TButton*)Sender);
		EditDisplay->Text = EditDisplay->Text + '*';
		infix = infix + '*';
		lastChar = '*';
		fMode = false;
		dMode = false;
		d2Mode = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DivClick(TObject *Sender)
{
	if(fMode == true) {
		TButton* b = ((TButton*)Sender);
		EditDisplay->Text = EditDisplay->Text + '/';
		infix = infix + '/';
		lastChar = '/';
		fMode = false;
		dMode = false;
		d2Mode = true;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DotClick(TObject *Sender)
{
	if(dMode == true) {
		TButton* b = ((TButton*)Sender);
		EditDisplay->Text = EditDisplay->Text + '.';
		infix = infix + '.';
		lastChar = '.';
		dMode = false;
		d2Mode = false;
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
		infix = infix + "^(";
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
	infix = "0";
	lastChar = '0';
	fMode = false;
	dMode = false;
	d2Mode = true;
    pCount = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SinClick(TObject *Sender)
{
	if(fMode == false) {
		if(EditDisplay->Text == "0") {
			EditDisplay->Text = "sin(";
			infix = "s(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "sin(";
			infix = infix + "s(";
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
			infix = "c(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "cos(";
			infix = infix + "c(";
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
			infix = "t(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "tan(";
			infix = infix + "t(";
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
			infix = "o(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "cot(";
			infix = infix + "o(";
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
			infix = "n(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "ln(";
			infix = infix + "n(";
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
			infix = "l(";
		}
		else {
			EditDisplay->Text = EditDisplay->Text + "log(";
			infix = infix + "l(";
		}
		pCount++;
		lastChar = '(';
		dMode = false;
		fMode = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BackClick(TObject *Sender)
{
	if(EditDisplay->Text.Length() == 1) {
		EditDisplay->Text = "0";
		infix = "0";
		lastChar = '0';
		fMode = false;
		dMode = false;
		d2Mode = true;
	}
	else {
		if(lastChar == '.') {
			dMode = true;
		}
		if(lastChar == '(') {
			pCount--;
		}
		if(lastChar == ')') {
            pCount++;
        }
		EditDisplay->Text = EditDisplay->Text.Delete(EditDisplay->Text.Length(),1);
		lastChar = EditDisplay->Text[EditDisplay->Text.Length()];
		if(lastChar == '+' || lastChar == '*' || lastChar == '/' || lastChar == '(') {
			fMode = false;
			dMode = false;
			d2Mode = true;
		}
		else if(lastChar == '-') {
			if(EditDisplay->Text.Length() == 1) {
				EditDisplay->Text = "0";
				infix = "0";
				lastChar = '0';
				fMode = false;
				dMode = false;
				d2Mode = true;
			}
			else {
				char nlChar = EditDisplay->Text[EditDisplay->Text.Length()-1];
				if(nlChar == '+' || nlChar == '*' || nlChar == '/' || nlChar == '(' ||
				   nlChar == '-') {
					EditDisplay->Text = EditDisplay->Text.Delete(EditDisplay->Text.Length(),1);
					infix.pop_back();
					lastChar = EditDisplay->Text[EditDisplay->Text.Length()];
					fMode = false;
					dMode = false;
					d2Mode = true;
				}
			}
		}
		else if(lastChar == '.') {
			fMode = false;
			dMode = false;
            d2Mode = false;
		}
		else if(lastChar == '^') {
			EditDisplay->Text = EditDisplay->Text.Delete(EditDisplay->Text.Length(),1);
			infix.pop_back();
			lastChar = EditDisplay->Text[EditDisplay->Text.Length()];
		}
		else if(lastChar == 's' || lastChar == 't' || lastChar == 'g') {
			if(EditDisplay->Text.Length() == 3) {
				EditDisplay->Text = "0";
				infix = "0";
				lastChar = '0';
				fMode = false;
				dMode = false;
				d2Mode = true;
			}
			else {
				EditDisplay->Text = EditDisplay->Text.Delete(EditDisplay->Text.Length(),1);
				EditDisplay->Text = EditDisplay->Text.Delete(EditDisplay->Text.Length(),1);
				EditDisplay->Text = EditDisplay->Text.Delete(EditDisplay->Text.Length(),1);
				infix.pop_back();
				infix.pop_back();
				infix.pop_back();
				lastChar = EditDisplay->Text[EditDisplay->Text.Length()];
				fMode = false;
				dMode = false;
				d2Mode = true;
			}
		}
		else if(lastChar == 'n') {
			char nlChar = EditDisplay->Text[EditDisplay->Text.Length()-1];
			if(nlChar == 'l') {
				if(EditDisplay->Text.Length() == 2) {
					EditDisplay->Text = "0";
					infix = "0";
					lastChar = '0';
					fMode = false;
					dMode = false;
					d2Mode = true;
				}
				else {
					EditDisplay->Text = EditDisplay->Text.Delete(EditDisplay->Text.Length(),1);
					EditDisplay->Text = EditDisplay->Text.Delete(EditDisplay->Text.Length(),1);
					infix.pop_back();
					infix.pop_back();
					lastChar = EditDisplay->Text[EditDisplay->Text.Length()];
					fMode = false;
					dMode = false;
					d2Mode = true;
				}
			}
			else {
					if(EditDisplay->Text.Length() == 3) {
					EditDisplay->Text = "0";
					infix = "0";
					lastChar = '0';
					fMode = false;
					dMode = false;
					d2Mode = true;
				}
				else {
					EditDisplay->Text = EditDisplay->Text.Delete(EditDisplay->Text.Length(),1);
					EditDisplay->Text = EditDisplay->Text.Delete(EditDisplay->Text.Length(),1);
					EditDisplay->Text = EditDisplay->Text.Delete(EditDisplay->Text.Length(),1);
					infix.pop_back();
					infix.pop_back();
                    infix.pop_back();
					lastChar = EditDisplay->Text[EditDisplay->Text.Length()];
					fMode = false;
					dMode = false;
					d2Mode = true;
				}
            }
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AnsClick(TObject *Sender)
{
	if(pCount > 0) {
		AnswerDisplay->Text = "Please Close Parenthesis";
		return;
	}
	if(lastChar == '+' || lastChar == '*' || lastChar == '/' || lastChar == '-') {
		AnswerDisplay->Text = "Please Finish Equation";
        return;
	}
	//wchar_t* infix0 = EditDisplay->Text.c_str();
	//wstring ws(infix0);
	//string str(ws.begin(), ws.end());
	//string postfix = convert(str);
	string postfix = convertInfixToPostfix(infix);
	double answer = evaluatePostfix(postfix);
	AnswerDisplay->Text = answer;
}
//---------------------------------------------------------------------------

