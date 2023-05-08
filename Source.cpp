#include <iostream>
#include "windows.h"
#include "ALHES.h"
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ALHES ed;
	vector<string> files;
	string help = " Команди:\n - 'е' або 'експорт' - зашифрувати\\дешифрувати вибраний файл\n - 'д' або 'довідка' - список команд\n - 'з' або 'закрити' - закрити файл який зараз вибраний\n ...";
	std::string path, cmd, name, form, s;
	int part = 0, i;
	cout << "Acc-Encrypt - версія: альфа 0.03UA" << endl;
	while (true) {
		switch (part) {
			case 0:
				i = 1;
				for (const auto & entry : fs::directory_iterator("")) {
					s = string(entry.path().string());
					files.push_back(s);
					cout << i << " - " << s << endl;
					i++;
				}
				i = files.size();
				if (i > 0) {
					cout << "* " << i << " файлів було знайдено у директорії програми. Щоб відкрити за номером використовуйте префікс '!номер', або введіть свій шлях до файлу\n";
				}
				cout << "шлях\\номер\\-> ";
				cin >> path;
				if (path.rfind("!", 0) == 0) {
					path = files[stoi(path.erase(0, 1))-1];
				}
				files.clear();
				if(ed.read(path)) {
					name = path.substr(0, path.find('.'));
					form = path.substr(path.find_last_of('.') + 1);
					cout << " Назва: '" << name << "'\n" << " Формат: " + form;
					ed.isEncoded() ? cout << " (зашифрований)" : cout << " (дешифрований)";
					cout << "\n Розмір файлу: " << ed.size() << " БІТ\n Файл було успішно прочитано!\n";
					part = 1;
				}else {
					cout << " Помилка при читанні файлу, будь ласка перевірте шлях"
						<< "\nПриклад: 'document.docx'" << endl;
				}
				break;
			case 1:
				cout << "команда\\-> ";
				cin >> cmd;
				if (cmd == "е" | cmd == "експорт") {
					ed.isEncoded() ? name = path.substr(0,path.find_last_of('.')) : name = path + "." + ALHES::FRMT;
					if (ed.xport(name)) {
						cout << " Файл успішно експортовано як '" << name << "'!\n";
					}else {
						cout << " Внутрішня помилка при експортуванні файла\n";
					}
				}else if (cmd == "д" | cmd == "довідка") {
					cout << help << endl;
				}else if(cmd == "з" | cmd == "закрити"){
					ed.reset();
					cout << " Файл закритий." << endl;
					part = 0;
				}else {
					cout << "Введена команда не знайдена. Команда довідки: 'д'.\n";
				}
				break;
		}
		
	}
	return 0;
}