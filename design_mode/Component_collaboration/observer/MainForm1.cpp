#include <string>
#include "FileSplitter1.h"
using namespace std;


class Form {
	/* 界面基类无关紧要 */
};

class MainForm : public Form
{
	TextBox* txtFilePath;
	TextBox* txtFileNumber;
	ProgressBar* progressBar;

public:
	void Button1_Click(){

		string filePath = txtFilePath->getText();
		int number = atoi(txtFileNumber->getText().c_str());

		FileSplitter splitter(filePath, number, progressBar);

		splitter.split();

	}
};

