#include "MyForm.h"
#include "JsonHandler.h"

#include <string>
#include <msclr/marshal_cppstd.h>
#include <Windows.h>
using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
void Main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    cryptgui::MyForm form;
    Application::Run(% form);
}

System::Void cryptgui::MyForm::lollipopButton2_Click(System::Object^ sender, System::EventArgs^ e) {
    if (checkedListBox1->SelectedItems->Count == 0) {
        MessageBox::Show("Выберите метод шифрования!", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }
    else {
        if (checkedListBox1->SelectedIndex == 0) {
            if (!change.is_keys_generated()) {
                MessageBox::Show("Не существует ключа для данного типа шифровки!", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            change.code();   
        }
        else if (checkedListBox1->SelectedIndex == 1) {
            if (!trans.is_keys_generated()) {
                MessageBox::Show("Не существует ключа для данного типа шифровки!", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            trans.code();
        }
        else {
            if (!gam.is_keys_generated()) {
                MessageBox::Show("Не существует ключа для данного типа шифровки!", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            gam.code();
        }
    }
    MessageBox::Show("Зашифровано!", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Information);
    return;
}

 //key generation

System::Void cryptgui::MyForm::lollipopButton1_Click(System::Object^ sender, System::EventArgs^ e) { 
    if (checkedListBox1->SelectedItems->Count == 0) {
        MessageBox::Show("Выберите метод шифрования!", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }
    if (!file_path) {
        MessageBox::Show("Выберите исходный текст!", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }
    else {
        if (checkedListBox1->SelectedIndex == 0) {
            change = JsonChangeKey();
            String^ pt = file_path;
            change.get_dec_text_from_file(msclr::interop::marshal_as<std::string>(pt));
            change.generate_key();
        }
        else if (checkedListBox1->SelectedIndex == 1) {
            trans = JsonTransposKey();
            String^ pt = file_path;
            trans.get_dec_text_from_file(msclr::interop::marshal_as<std::string>(pt));
            trans.generate_key();

        }
        else {
            gam = Gamma();
            String^ pt = file_path;
            gam.get_dec_text_from_file(msclr::interop::marshal_as<std::string>(pt));
            gam.generate_key();
        }
    }
    MessageBox::Show("Ключ готов!", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Information);
    return;
}

System::Void cryptgui::MyForm::lollipopButton3_Click(System::Object^ sender, System::EventArgs^ e) {
    if (checkedListBox1->SelectedItems->Count == 0) {
        MessageBox::Show("Выберите метод шифрования!", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
        return;
    }
    else {
        if (checkedListBox1->SelectedIndex == 0) {
            if (!change.is_keys_generated()) {
                MessageBox::Show("Не существует ключа для данного типа шифровки!", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            change.decode();
        }
        else if (checkedListBox1->SelectedIndex == 1) {
            if (!trans.is_keys_generated()) {
                MessageBox::Show("Не существует ключа для данного типа шифровки!", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            trans.decode();
        }
        else {
            if (!gam.is_keys_generated()) {
                MessageBox::Show("Не существует ключа для данного типа шифровки!", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            gam.decode();
        }
    }
    MessageBox::Show("Раскодировано!", "Сообщение", MessageBoxButtons::OK, MessageBoxIcon::Information);
    return;
}
