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
	string help = " �������:\n - '�' ��� '�������' - �����������\\����������� �������� ����\n - '�' ��� '������' - ������ ������\n - '�' ��� '�������' - ������� ���� ���� ����� ��������\n ...";
	std::string path, cmd, name, form, s;
	int part = 0, i;
	cout << "Acc-Encrypt - �����: ����� 0.03UA" << endl;
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
					cout << "* " << i << " ����� ���� �������� � �������� ��������. ��� ������� �� ������� �������������� ������� '!�����', ��� ������ ��� ���� �� �����\n";
				}
				cout << "����\\�����\\-> ";
				cin >> path;
				if (path.rfind("!", 0) == 0) {
					path = files[stoi(path.erase(0, 1))-1];
				}
				files.clear();
				if(ed.read(path)) {
					name = path.substr(0, path.find('.'));
					form = path.substr(path.find_last_of('.') + 1);
					cout << " �����: '" << name << "'\n" << " ������: " + form;
					ed.isEncoded() ? cout << " (������������)" : cout << " (������������)";
					cout << "\n ����� �����: " << ed.size() << " ���\n ���� ���� ������ ���������!\n";
					part = 1;
				}else {
					cout << " ������� ��� ������ �����, ���� ����� �������� ����"
						<< "\n�������: 'document.docx'" << endl;
				}
				break;
			case 1:
				cout << "�������\\-> ";
				cin >> cmd;
				if (cmd == "�" | cmd == "�������") {
					ed.isEncoded() ? name = path.substr(0,path.find_last_of('.')) : name = path + "." + ALHES::FRMT;
					if (ed.xport(name)) {
						cout << " ���� ������ ������������ �� '" << name << "'!\n";
					}else {
						cout << " �������� ������� ��� ������������ �����\n";
					}
				}else if (cmd == "�" | cmd == "������") {
					cout << help << endl;
				}else if(cmd == "�" | cmd == "�������"){
					ed.reset();
					cout << " ���� ��������." << endl;
					part = 0;
				}else {
					cout << "������� ������� �� ��������. ������� ������: '�'.\n";
				}
				break;
		}
		
	}
	return 0;
}