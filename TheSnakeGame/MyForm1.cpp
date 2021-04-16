#include "MyForm1.h"
#include "MyForm.h"

TheSnakeGame::MyForm1::MyForm1()
{
		InitializeComponent();
		imgHead = "D:\\VisualProjects\\games\\TheSnakeGame\\head2.png";
		imgTail = "D:\\VisualProjects\\games\\TheSnakeGame\\tail.png";
		EditSerpens();
}		

void TheSnakeGame::MyForm1::EditSerpens()
{
	SerpensCur = gcnew array<PictureBox^>(10);
	SerpensCur[0] = gcnew PictureBox();
	int positionHeadX = this->ClientSize.Width / 2;
	int positionHeadY = this->ClientSize.Height / 2;
	SerpensCur[0]->Location = Point(positionHeadX, positionHeadY);
	SerpensCur[0]->Image = gcnew Bitmap(imgHead);
	SerpensCur[0]->Width = size;
	SerpensCur[0]->Height = size;
	this->Controls->Add(SerpensCur[0]);
	for (int i = 1; i < 10; i++) {
		SerpensCur[i] = gcnew PictureBox();
		SerpensCur[i]->Location = Point(positionHeadX, positionHeadY + i * size);
		SerpensCur[i]->Width = size;
		SerpensCur[i]->Height = size;
		SerpensCur[i]->Image = gcnew Bitmap(imgTail);
		this->Controls->Add(SerpensCur[i]);
	}
}

System::Void TheSnakeGame::MyForm1::buttonEditTail_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();
	ofd->Filter = "Image Files (*BMP;*.JPG;*.GIF;*.PNG)|*BMP;*.JPG;*.GIF;*.PNG|All Files (*.*)|*.*";
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
	imgTail = ofd->FileName;
	for (int i = 1; i < 10; i++)
		SerpensCur[i]->Image = gcnew Bitmap(imgTail);
	}
	return System::Void();
}

