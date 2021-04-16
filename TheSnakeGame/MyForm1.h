#pragma once

namespace TheSnakeGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm1
	/// </summary>
	public ref class MyForm1 : public System::Windows::Forms::Form
	{
	public:
		MyForm1();
		MyForm1(String^ img);
	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MyForm1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ buttonEditTail;
	protected:
	private: System::Windows::Forms::Button^ buttonEditHead;


	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm1::typeid));
			this->buttonEditTail = (gcnew System::Windows::Forms::Button());
			this->buttonEditHead = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// buttonEditTail
			// 
			this->buttonEditTail->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonEditTail.BackgroundImage")));
			this->buttonEditTail->Location = System::Drawing::Point(515, 419);
			this->buttonEditTail->Name = L"buttonEditTail";
			this->buttonEditTail->Size = System::Drawing::Size(142, 34);
			this->buttonEditTail->TabIndex = 0;
			this->buttonEditTail->Text = L"»зменить чешую";
			this->buttonEditTail->UseVisualStyleBackColor = true;
			this->buttonEditTail->Click += gcnew System::EventHandler(this, &MyForm1::buttonEditTail_Click);
			// 
			// buttonEditHead
			// 
			this->buttonEditHead->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonEditHead.BackgroundImage")));
			this->buttonEditHead->Location = System::Drawing::Point(178, 419);
			this->buttonEditHead->Name = L"buttonEditHead";
			this->buttonEditHead->Size = System::Drawing::Size(142, 34);
			this->buttonEditHead->TabIndex = 1;
			this->buttonEditHead->Text = L"»зменить голову";
			this->buttonEditHead->UseVisualStyleBackColor = true;
			// 
			// MyForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(819, 503);
			this->Controls->Add(this->buttonEditHead);
			this->Controls->Add(this->buttonEditTail);
			this->ForeColor = System::Drawing::Color::Red;
			this->Name = L"MyForm1";
			this->Text = L"»зменить змею";
			this->ResumeLayout(false);

		}
#pragma endregion
	public:
		String^ imgHead;
		String^ imgTail;
		bool isEdit = false;
	private:
		array<PictureBox^>^ SerpensCur;
		int size = 10;
		void EditSerpens(); //јнимаци€ змеи
	private: System::Void buttonEditTail_Click(System::Object^ sender, System::EventArgs^ e);
	public:
		String^ GetImage() {
			return imgTail;
		}
	};
}
