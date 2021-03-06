#include <vcl.h>
#pragma hdrstop

#include "MainOCR.h"
#include <XMLDoc.hpp>
#include <Letters.h>
#include <string.h>
#include <sstream>
#include <cstdlib>

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int image16[16][16];
float maxAccuracy = 0.3f;
// ---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
	Image1->Canvas->Pen->Width = 10;
	// Image1->Canvas->Brush->Color = clBlack;
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::Image1MouseMove(TObject *Sender, TShiftState Shift,
	int X, int Y)
    {

    if (Shift.Contains(ssLeft))
    {
        Image1->Canvas->LineTo(X, Y);
        Image1->Canvas->MoveTo(X, Y);
    }
    else Image1->Canvas->MoveTo(X, Y);
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::ClearButtonClick(TObject *Sender)
{
	Image1->Canvas->Pen->Width = 0;
	Image1->Canvas->Brush->Color = clWhite;
	Image1->Canvas->Rectangle(-1, -1, Image1->Width + 1, Image1->Height + 1);
	Image1->Canvas->Brush->Color = clBlack;
	Image1->Canvas->Pen->Width = 10;

	Image2->Canvas->Brush->Color = clWhite;
	Image2->Canvas->Rectangle(-1, -1, Image2->Width + 1, Image2->Height + 1);
	Image2->Canvas->Brush->Color = clBlack;

}

// ---------------------------------------------------------------------------
void __fastcall TForm1::TransformButtonClick(TObject *Sender)
{
 float q = 0;
	int blackCounter = 0;
	for (int iL = 0; iL <= 15; iL++)
    {
		for (int jL = 0; jL <= 15; jL++)
        {

			for (int i = iL * 10; i <= iL * 10 + 10; i++)
            {
				for (int j = jL * 10; j <= jL * 10 + 10; j++)
                {
					if (Image1->Canvas->Pixels[j][i] == clBlack)
						blackCounter++;
				}
			}
			q = blackCounter / 256.0f;
			if (q >= 0.15f)
				image16[jL][iL] = 1;
			else
				image16[jL][iL] = 0;
			blackCounter = 0;
		}
	}

	Image2->Canvas->Pen->Width = 0;
	Image2->Canvas->Brush->Color = clBlack;

	for (int i = 0; i < 16; i++)
    {
		for (int j = 0; j < 16; j++)
        {
			StringGrid1->Cells[i][j] = image16[i][j];
			if (image16[i][j] == 1)
				Image2->Canvas->Rectangle(i*10, j*10, (i*10) + 10, (j*10) + 10);
		}
	}
}

// ---------------------------------------------------------------------------
void __fastcall TForm1::SaveXMLButtonClick(TObject *Sender)
{
    if(Edit1->Text != "")
    {
        //Forcing transform one more time, to exclude your mistakes
        TForm1::TransformButtonClick(this);

        _di_IXMLlettersType Letters = Getletters(XMLDocument1);
        _di_IXMLsignatureType Signature = Letters->Add();

        std::ostringstream os;
        for (int i = 0; i < 16; i++)
        {
            for (int j = 0; j < 16; j++)
            {
                os<<image16[i][j];
            }
        }
        std::string sarray(os.str());

        Signature->array = sarray.c_str();

        AnsiString ansiE1(Edit1->Text);
        char* str = new char[1];
        std::strcpy(str, ansiE1.c_str());
        Signature->letter = str[0];
        delete[] str;

        XMLDocument1->SaveToFile(XMLDocument1->FileName);
        Edit1->Text = "";
    }
}
// ---------------------------------------------------------------------------
void __fastcall TForm1::CheckButtonClick(TObject *Sender)
{
        Label1->Caption = "None";

        _di_IXMLlettersType Letters = Getletters(XMLDocument1);
        float
        	accuracy = 0.0f,
        	tmpAccuracy = 0.0f;
        int bothMatches = 0,
        	whiteMatches = 0,
            blackMatches = 0;
        String labelLetter = "None";

        //* Tranfsorm from matrix to 1-dimensional array
        int *image16_1d = &image16[0][0];


        for(int x = 0; x < Letters->Count; x++)
        {
        	wchar_t* array = Letters->signature[x]->array.c_str();
            for (int i = 0; i < 256; i++)
            {
                   if(image16_1d[i] == 0 && array[i] == '0') whiteMatches++;
                   if(image16_1d[i] == 1 && array[i] == '1') blackMatches++;
                   if((image16_1d[i] == 0 && array[i] == '0') || (image16_1d[i] == 1 && array[i] == '1')) bothMatches++;
            }
            tmpAccuracy = blackMatches / (256.0f - whiteMatches);
            if(tmpAccuracy >= accuracy && tmpAccuracy >= maxAccuracy)
            {
                accuracy = tmpAccuracy;
                labelLetter = Letters->signature[x]->letter;
            }
            bothMatches = 0;
            whiteMatches = 0;
            blackMatches = 0;
        }
        Label1->Caption = labelLetter;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
    if(Edit1->Text == "") SaveXMLButton->Enabled = false;
    else  SaveXMLButton->Enabled = true;
}
//---------------------------------------------------------------------------
