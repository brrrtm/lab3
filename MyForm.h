#pragma once
#include "JsonHandler.h"


namespace cryptgui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}
		String^ file_path;
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
    private: LollipopButton^ lollipopButton1;
    private: System::Windows::Forms::CheckedListBox^ checkedListBox1;
	private: LollipopButton^ lollipopButton2;
	private: LollipopButton^ lollipopButton3;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: LollipopButton^ lollipopButton4;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lollipopButton1 = (gcnew LollipopButton());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->lollipopButton2 = (gcnew LollipopButton());
			this->lollipopButton3 = (gcnew LollipopButton());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->lollipopButton4 = (gcnew LollipopButton());
			this->SuspendLayout();
			// 
			// lollipopButton1
			// 
			this->lollipopButton1->BackColor = System::Drawing::Color::Transparent;
			this->lollipopButton1->BGColor = L"#508ef5";
			this->lollipopButton1->FontColor = L"#ffffff";
			this->lollipopButton1->Location = System::Drawing::Point(116, 130);
			this->lollipopButton1->Name = L"lollipopButton1";
			this->lollipopButton1->Size = System::Drawing::Size(128, 41);
			this->lollipopButton1->TabIndex = 0;
			this->lollipopButton1->Text = L"Сгенерировать ключ";
			this->lollipopButton1->Click += gcnew System::EventHandler(this, &MyForm::lollipopButton1_Click);
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->BackColor = System::Drawing::SystemColors::Control;
			this->checkedListBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->checkedListBox1->CheckOnClick = true;
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Метод замены", L"Метод перестановки", L"Гаммирование " });
			this->checkedListBox1->Location = System::Drawing::Point(116, 43);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(128, 45);
			this->checkedListBox1->TabIndex = 1;
			this->checkedListBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::checkedListBox1_SelectedIndexChanged);
			// 
			// lollipopButton2
			// 
			this->lollipopButton2->BackColor = System::Drawing::Color::Transparent;
			this->lollipopButton2->BGColor = L"#508ef5";
			this->lollipopButton2->FontColor = L"#ffffff";
			this->lollipopButton2->Location = System::Drawing::Point(116, 191);
			this->lollipopButton2->Name = L"lollipopButton2";
			this->lollipopButton2->Size = System::Drawing::Size(128, 41);
			this->lollipopButton2->TabIndex = 2;
			this->lollipopButton2->Text = L"Зашифровать";
			this->lollipopButton2->Click += gcnew System::EventHandler(this, &MyForm::lollipopButton2_Click);
			// 
			// lollipopButton3
			// 
			this->lollipopButton3->BackColor = System::Drawing::Color::Transparent;
			this->lollipopButton3->BGColor = L"#508ef5";
			this->lollipopButton3->FontColor = L"#ffffff";
			this->lollipopButton3->Location = System::Drawing::Point(116, 252);
			this->lollipopButton3->Name = L"lollipopButton3";
			this->lollipopButton3->Size = System::Drawing::Size(128, 41);
			this->lollipopButton3->TabIndex = 3;
			this->lollipopButton3->Text = L"Расшифровать";
			this->lollipopButton3->Click += gcnew System::EventHandler(this, &MyForm::lollipopButton3_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// lollipopButton4
			// 
			this->lollipopButton4->BackColor = System::Drawing::Color::Transparent;
			this->lollipopButton4->BGColor = L"#508ef5";
			this->lollipopButton4->FontColor = L"#ffffff";
			this->lollipopButton4->Location = System::Drawing::Point(116, 310);
			this->lollipopButton4->Name = L"lollipopButton4";
			this->lollipopButton4->Size = System::Drawing::Size(128, 41);
			this->lollipopButton4->TabIndex = 4;
			this->lollipopButton4->Text = L"Выбрать файл";
			this->lollipopButton4->Click += gcnew System::EventHandler(this, &MyForm::lollipopButton4_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(370, 379);
			this->Controls->Add(this->lollipopButton4);
			this->Controls->Add(this->lollipopButton3);
			this->Controls->Add(this->lollipopButton2);
			this->Controls->Add(this->checkedListBox1);
			this->Controls->Add(this->lollipopButton1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

		}
#pragma endregion
    private: System::Void checkedListBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
        if (checkedListBox1->CheckedItems->Count > 1)
        {
            for (int i = 0; i < checkedListBox1->Items->Count; i++)
                checkedListBox1->SetItemChecked(i, false);
            checkedListBox1->SetItemChecked(checkedListBox1->SelectedIndex, true);
        }
    }
	private: System::Void lollipopButton2_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void lollipopButton1_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void lollipopButton4_Click(System::Object^ sender, System::EventArgs^ e) {
		openFileDialog1->ShowDialog();
		file_path = openFileDialog1->FileName;
	}
	private: System::Void lollipopButton3_Click(System::Object^ sender, System::EventArgs^ e);
};
}
JsonChangeKey change;
JsonTransposKey trans;
Gamma gam;