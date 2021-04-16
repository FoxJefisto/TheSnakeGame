#include "MyForm.h"
#include "MyForm1.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	TheSnakeGame::MyForm form;
	Application::Run(% form);
}

//��������� ��� 2D ������������
struct Vector2 {
	int X, Y;
};

Vector2 direction; //����������� ������
Vector2 positionFruit; //������� ������
Vector2 gameArea; //������� ����

//����������� �����

TheSnakeGame::MyForm::MyForm(void)
{
	InitializeComponent();

	//������ ������� ������� ����
	gameArea.X = 640;
	gameArea.Y = 570;

	firstLaunch = true;
	NewGame();
}

//�������� ����

//��������� ������� ������
void TheSnakeGame::MyForm::GeneratePositionFruit()
{
	//���������� ������� ������
	Random^ rand = gcnew Random();
	positionFruit.X = rand->Next(30, gameArea.X);
	positionFruit.Y = rand->Next(170, gameArea.Y);

	//��������, ����� ����� �� �������� �� ������
	for (int i = 0; i < score; i++) {
		if (positionFruit.X == Serpens[i]->Location.X &&
			positionFruit.Y == Serpens[i]->Location.Y)
			GeneratePositionFruit();
	}

	//����������� ��������, ����� ���� ������ ����
	int tempX = positionFruit.X % step;
	positionFruit.X -= tempX;
	int tempY = positionFruit.Y % step;
	positionFruit.Y -= tempY;

	//����������� ������� ������
	fruit->Location = Point(positionFruit.X, positionFruit.Y);

	//��������� ������ �� �����
	this->Controls->Add(fruit);
}
//�������� ������
void TheSnakeGame::MyForm::Eating()
{
	//��������� ����
	if (Serpens[0]->Location.X == positionFruit.X && Serpens[0]->Location.Y == positionFruit.Y) {
		labelScore->Text = "C���: " + ++score;
		//����������� ������ ������
		Serpens[score] = gcnew PictureBox();
		Serpens[score]->Location = Point(Serpens[score - 1]->Location.X + step * direction.X, Serpens[score - 1]->Location.Y + step * direction.Y);
		if (imgSerpens == nullptr)
			Serpens[score]->BackColor = Color::LightGreen;
		else
			Serpens[score]->Image = gcnew Bitmap(imgSerpens);
		Serpens[score]->Width = step;
		Serpens[score]->Height = step;
		this->Controls->Add(Serpens[score]);
		fruit->Image = gcnew Bitmap(imgApples[score % 7]);

		GeneratePositionFruit();
	}
}
//�������� ������
void TheSnakeGame::MyForm::Movement()
{
	//������� ������ ��������� ������
	for (int i = score; i >= 1; i--) {
		Serpens[i]->Location = Serpens[i - 1]->Location;
	}
	Serpens[0]->Location = Point(Serpens[0]->Location.X + direction.X * step,
		Serpens[0]->Location.Y + direction.Y * step);
}
//������������ � ����� �����
void TheSnakeGame::MyForm::EatYourself()
{
	for (int i = 1; i < score; i++) {
		if (Serpens[0]->Location == Serpens[i]->Location)
			GameOver();
	}
}
//��������
void TheSnakeGame::MyForm::GameOver()
{
	play = true;
	die = true;

	labelGameOver->Visible = true;
}
//������ ����
void TheSnakeGame::MyForm::NewGame()
{
	//���� ������������� ����, �� ������� ������� � �����
	if (!firstLaunch) {
		this->Controls->Remove(fruit);

		for (int i = 0; i <= score; i++)
		{
			this->Controls->Remove(Serpens[i]);
		}
	}
	else
		firstLaunch = false;

	//�������������� ������
	Serpens = gcnew array <PictureBox^>(400);
	Serpens[0] = gcnew PictureBox();
	Serpens[0]->Location = Point(210, 370);
	Serpens[0]->Image = gcnew Bitmap(imgHead1); //������ ����� �������
	Serpens[0]->Width = step;
	Serpens[0]->Height = step;
	score = 0;
	this->Controls->Add(Serpens[0]);

	//�������������� �����
	imgApples = gcnew array <String^>(7);
	imgApples[0] = "D:\\VisualProjects\\games\\TheSnakeGame\\apple1.png";
	imgApples[1] = "D:\\VisualProjects\\games\\TheSnakeGame\\apple2.png";
	imgApples[2] = "D:\\VisualProjects\\games\\TheSnakeGame\\apple3.png";
	imgApples[3] = "D:\\VisualProjects\\games\\TheSnakeGame\\apple4.png";
	imgApples[4] = "D:\\VisualProjects\\games\\TheSnakeGame\\apple5.png";
	imgApples[5] = "D:\\VisualProjects\\games\\TheSnakeGame\\apple6.png";
	imgApples[6] = "D:\\VisualProjects\\games\\TheSnakeGame\\apple7.png";
	fruit = gcnew PictureBox();
	fruit->Image = gcnew Bitmap(imgApples[0]);
	fruit->Width = step;
	fruit->Height = step;
	GeneratePositionFruit();

	//������ �������� ���������� � ��������� ������ ��� ����������
	timer->Interval = updateInterval;
	timer->Start();

	//������ ����������� �� �������
	direction.X = 1;
	direction.Y = 0;

	//������ ����
	play = true;
	die = false;

	labelScore->Text = "����: 0";

	//�������� �������� ���������� �� �����
	labelGameOver->Visible = false;
	groupBoxSettings->Visible = false;
}

void TheSnakeGame::MyForm::CheckBorders()
{
	if (Serpens[0]->Location.X >= RightBorder->Location.X ||
		Serpens[0]->Location.X <= LeftBorder->Location.X) {
		GameOver();
	}
	if (Serpens[0]->Location.Y >= LowerBorder->Location.Y ||
		Serpens[0]->Location.Y <= UpperBorder->Location.Y) {
		GameOver();
	}

	labelCoordinates->Text = "(X,Y) = (" + Convert::ToString(Serpens[0]->Location.X) + "," + Convert::ToString(Serpens[0]->Location.Y) + ")";
}

//����������� ������� �� ������

System::Void TheSnakeGame::MyForm::���������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	NewGame();
	return System::Void();
}

System::Void TheSnakeGame::MyForm::���������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (play)
		play = false;
	else
	{
		play = true;
		timer->Start();
	}
	return System::Void();
}

System::Void TheSnakeGame::MyForm::���������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (groupBoxSettings->Visible == false) {
		play = false;
		buttonEdit->Enabled = true;
		buttonApplySpeed->Enabled = true;
		numericUpDownSpeedSnake->Enabled = true;
		groupBoxSettings->Visible = true;
	}
	else {
		play = true;
		timer->Start();
		buttonEdit->Enabled = false;
		buttonApplySpeed->Enabled = false;
		numericUpDownSpeedSnake->Enabled = false;
		groupBoxSettings->Visible = false;
	}
	return System::Void();
}

System::Void TheSnakeGame::MyForm::���������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("������� ����: \n1. ��� ���������� ������������ ������� \n2. ����� ������ ��� ���������� ������\n3. ������ ���� ���� � ��������� � �����", "������� ����:");

	return System::Void();
}

System::Void TheSnakeGame::MyForm::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();

	return System::Void();
}

System::Void TheSnakeGame::MyForm::buttonApplySpeed_Click(System::Object^ sender, System::EventArgs^ e)
{
	updateInterval = 201 - Convert::ToSingle(numericUpDownSpeedSnake->Value);
	timer->Interval = updateInterval;

	buttonEdit->Enabled = false;
	buttonApplySpeed->Enabled = false;
	numericUpDownSpeedSnake->Enabled = false;
	groupBoxSettings->Visible = false;

	play = true;
	timer->Start();
	return System::Void();
}

//������������ ������� ������

System::Void TheSnakeGame::MyForm::MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode.ToString() == "Right") {
		direction.X = 1;
		direction.Y = 0;
		Serpens[0]->Image = gcnew Bitmap(imgHead1);
	}
	else if (e->KeyCode.ToString() == "Left") {
		direction.X = -1;
		direction.Y = 0;
		Serpens[0]->Image = gcnew Bitmap(imgHead3);
	}
	else if (e->KeyCode.ToString() == "Up") {
		direction.X = 0;
		direction.Y = -1;
		Serpens[0]->Image = gcnew Bitmap(imgHead2);
	}
	else if (e->KeyCode.ToString() == "Down") {
		direction.X = 0;
		direction.Y = 1;
		Serpens[0]->Image = gcnew Bitmap(imgHead4);
	}
	return System::Void();
}

//������� �� ���������� ���� - ����������� � timer

void TheSnakeGame::MyForm::MyForm_Update(Object^ object, EventArgs^ e)
{
	if (!die && play) {
		//�������� ������
		Movement();
		//��������, �� �������� ������
		Eating();
		//��������, ���� �� ��� ����
		EatYourself();
		//�������� �� ������������ �� ������
		CheckBorders();
	}
	else if (die && play) {
		timer->Stop();
		MessageBox::Show("���� ��������", "��������!");
	}
	else if (!play && !die) {
		timer->Stop();
		MessageBox::Show("���� ��������������!", "��������!");
	}
}

System::Void TheSnakeGame::MyForm::buttonEdit_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyForm1^ form1 = gcnew MyForm1(imgSerpens);
	form1->ShowDialog();
		imgSerpens = form1->GetImage();
		if (form1->isEdit)
			for (int i = 1; i <= score; i++)
				Serpens[i]->Image = gcnew Bitmap(imgSerpens);
	return System::Void();
}
