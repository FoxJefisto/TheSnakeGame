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

//Структура для 2D пространства
struct Vector2 {
	int X, Y;
};

Vector2 direction; //направление змейки
Vector2 positionFruit; //позиция фрукта
Vector2 gameArea; //игровая зона

//Конструктор формы

TheSnakeGame::MyForm::MyForm(void)
{
	InitializeComponent();

	//Задаем размеры игровой зоны
	gameArea.X = 640;
	gameArea.Y = 570;

	firstLaunch = true;
	NewGame();
}

//Действия игры

//генерация позиции фрукта
void TheSnakeGame::MyForm::GeneratePositionFruit()
{
	//Генерируем позицию фрукту
	Random^ rand = gcnew Random();
	positionFruit.X = rand->Next(30, gameArea.X);
	positionFruit.Y = rand->Next(170, gameArea.Y);

	//Проверка, чтобы фрукт не создался на змейке
	for (int i = 0; i < score; i++) {
		if (positionFruit.X == Serpens[i]->Location.X &&
			positionFruit.Y == Serpens[i]->Location.Y)
			GeneratePositionFruit();
	}

	//Преобразуем значение, чтобы было кратно шагу
	int tempX = positionFruit.X % step;
	positionFruit.X -= tempX;
	int tempY = positionFruit.Y % step;
	positionFruit.Y -= tempY;

	//Присваиваем позицию фрукту
	fruit->Location = Point(positionFruit.X, positionFruit.Y);

	//Добавляем объект на форму
	this->Controls->Add(fruit);
}
//поедание фрукта
void TheSnakeGame::MyForm::Eating()
{
	//Добавляем очки
	if (Serpens[0]->Location.X == positionFruit.X && Serpens[0]->Location.Y == positionFruit.Y) {
		labelScore->Text = "Cчёт: " + ++score;
		//Увеличиваем размер змейки
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
//движение змейки
void TheSnakeGame::MyForm::Movement()
{
	//Двигаем каждый компонент змейки
	for (int i = score; i >= 1; i--) {
		Serpens[i]->Location = Serpens[i - 1]->Location;
	}
	Serpens[0]->Location = Point(Serpens[0]->Location.X + direction.X * step,
		Serpens[0]->Location.Y + direction.Y * step);
}
//столкновение с самим собой
void TheSnakeGame::MyForm::EatYourself()
{
	for (int i = 1; i < score; i++) {
		if (Serpens[0]->Location == Serpens[i]->Location)
			GameOver();
	}
}
//проигрыш
void TheSnakeGame::MyForm::GameOver()
{
	play = true;
	die = true;

	labelGameOver->Visible = true;
}
//начало игры
void TheSnakeGame::MyForm::NewGame()
{
	//Если инициализация была, то удаляем объекты с формы
	if (!firstLaunch) {
		this->Controls->Remove(fruit);

		for (int i = 0; i <= score; i++)
		{
			this->Controls->Remove(Serpens[i]);
		}
	}
	else
		firstLaunch = false;

	//Инициализируем змейку
	Serpens = gcnew array <PictureBox^>(400);
	Serpens[0] = gcnew PictureBox();
	Serpens[0]->Location = Point(210, 370);
	Serpens[0]->Image = gcnew Bitmap(imgHead1); //голова будет зеленой
	Serpens[0]->Width = step;
	Serpens[0]->Height = step;
	score = 0;
	this->Controls->Add(Serpens[0]);

	//Инициализируем фрукт
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

	//Задаем интервал обновления и запускаем таймер для обновления
	timer->Interval = updateInterval;
	timer->Start();

	//Задаем направление на запуске
	direction.X = 1;
	direction.Y = 0;

	//Начало игры
	play = true;
	die = false;

	labelScore->Text = "Счет: 0";

	//Скрываем ненужные компоненты на форме
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

//Обработчики нажатия на кнопки

System::Void TheSnakeGame::MyForm::новаяИграToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	NewGame();
	return System::Void();
}

System::Void TheSnakeGame::MyForm::паузапродолжитьToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
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

System::Void TheSnakeGame::MyForm::настройкиToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
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

System::Void TheSnakeGame::MyForm::информацияОИгреToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("Правила игры: \n1. Для управления использовать стрелки \n2. Ешьте фрукты для увеличение змейки\n3. Нельзя есть себя и врезаться в стены", "Правила игры:");

	return System::Void();
}

System::Void TheSnakeGame::MyForm::выходToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
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

//Отслеживание нажатия клавиш

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

//Событие по обновлению игры - указывается в timer

void TheSnakeGame::MyForm::MyForm_Update(Object^ object, EventArgs^ e)
{
	if (!die && play) {
		//движение змейки
		Movement();
		//проверка, на съедание фрукта
		Eating();
		//проверка, съел ли сам себя
		EatYourself();
		//проверка на столкновение со стеной
		CheckBorders();
	}
	else if (die && play) {
		timer->Stop();
		MessageBox::Show("Игра окончена", "Внимание!");
	}
	else if (!play && !die) {
		timer->Stop();
		MessageBox::Show("Игра приостановлена!", "Внимание!");
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
