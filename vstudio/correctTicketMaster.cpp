#define  _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#include "json.h"
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <codecvt>
#include <locale>
#include <vector>
#include <list>
#include <map>
//#include <any>
#include <stdio.h>
#include <cstdio>
#include <cstdlib> 
#include <cstddef>
#include <ctime> 
#include <random>
#include <algorithm>
#include <windows.h>
#include <fileapi.h>
#include <stringapiset.h>

//namespace fs = std::filesystem;


using namespace std;
using namespace Json;

//std::wstring toWideString(const std::string& s)
//{
//	int len;
//	int slength = (int)s.length() + 1;
//	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
//	wchar_t* buf = new wchar_t[len];
//	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
//	std::wstring r(buf);
//	delete[] buf;
//	return r;
//}
//std::string toUtf8(const std::wstring& str)
//{
//	std::string ret;
//	int len = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0, NULL, NULL);
//	if (len > 0)
//	{
//		ret.resize(len);
//		WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), &ret[0], len, NULL, NULL);
//	}
//	return ret;
//}

void writeJsonToFile(Json::Value source, const std::string& path) {
	Json::StreamWriterBuilder builder;
	const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	ofstream file(path);
	writer->write(source, &file);
	file.close();
}
Json::Value readJsonFromFile(const std::string& path) {
	Json::Value source;
	ifstream ifs(path); 
	Json::CharReaderBuilder builder2;
	JSONCPP_STRING errs;
	if (!Json::parseFromStream(builder2, ifs, &source, &errs)) {
		std::cout << errs << std::endl;
		return EXIT_FAILURE;
	}
	ifs.close();
	return source;
}
Json::Value createEmpty() {
	Json::Value booleanJson;
	for (size_t i = 0; i < 32; i++) {
		booleanJson[to_string(i)] = false;
	}
	return booleanJson;
}
vector<bool> getVector(Json::Value booleanJson) {
	vector<bool> values;
	auto itVector = values.begin();
	for (auto it = booleanJson.begin(); it != booleanJson.end(); ++it)
	{
		string temp = it.key().asString();
		bool value = booleanJson[temp].asBool();
		itVector = values.insert(itVector, value);
	}
	return values;
}
int randomQuestion(Json::Value& vectorOfGroup, int amountOfQuestions) {
	int res;
	int iteration = 0;
	bool x = false;

	if (std::find(vectorOfGroup.begin(), vectorOfGroup.end(), x) != vectorOfGroup.end()) {
		do {
			res = rand() % amountOfQuestions;
			iteration++;
		} while (vectorOfGroup[to_string(res)].asBool());
		vectorOfGroup[to_string(res)] = true;
		return res;
	}
	else {
		vectorOfGroup = createEmpty();
		return randomQuestion(vectorOfGroup, amountOfQuestions);
	}
}
void writeToFile(const std::string& path, const std::wstring& infoToWrite) {
	std::wofstream outfile;
	outfile.imbue(std::locale(outfile.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	outfile.open(path, std::ios_base::app); // append instead of overwrite
	outfile << infoToWrite;
	outfile.close();
}

//Запись в json файл
//root["1"] = u8"Определение операционной системы и ее функции. Понятие виртуальной машины.Управление ресурсами.";
//root["2"] = u8"История разработки операционных систем, поколения ЭВМ и операционных систем.Влияние аппаратуры на развитие операционных систем.";
//root["3"] = u8"Классификация и примеры операционных систем.Многозадачность.Вид многозадачности.Многопоточная обработка.Критерии эффективности многозадачных операционных систем.";
//root["4"] = u8"Функциональные требования, предъявляемые к операционным системам, и способы их реализации.Расширяемость.Переносимость.Надежность.Совместимость. Безопасность.Производительность.";
//root["5"] = u8"Основные архитектуры операционных систем : монолитные, многоуровневые, микроядро, объектно - ориентированные, виртуальные машины.";
//root["6"] = u8"Абстракция процесса, управление процессами в многозадачной операционной системе.Определение процесса.Диаграмма состояния, контекст, дескриптор процесса.Квантование и приоритетное планирование. Нити(потоки исполнения)";
//root["7"] = u8"Функциональные возможности многозадачности в ОС Windows. Способы использования многозадачности в приложениях.";
//root["8"] = u8"Планировщик ОС Windows.Класс и уровень приоритета.Переключение контекста. Потоки, не являющиеся готовыми.Динамический приоритет.";
//root["9"] = u8"Эффект инверсии приоритетов. Пример возникновения инверсии. Способы преодоления.";
//root["10"] = u8"Мультипроцессорная обработка в ОС Windows. Термины, вызовы API, их назначение.";
//root["11"] = u8"Состояние состязания.Пример возникновения и способ преодоления.";
//root["12"] = u8"Средства синхронизации в режиме пользователя в ОС Windows. Функции,реализующие атомарные операции, объект «критическая секция»";
//root["13"] = u8"Задача о критической секции.Алгоритм Питерсона для двух процессов. задачи.Объяснение принципа работы алгоритма";
//root["14"] = u8"Предотвращение агрессивной оптимизации кода с использованием модификатора volatile.Эффект голодания, пример возникновения.";
//root["15"] = u8"Эффект ложного разделения переменных. Пример влияния кэш - линий на скорости исполнения многопоточных программ.";
//root["16"] = u8"Управление объектами ядра в ОС Windows. Описатель объекта.Таблица описателей объектов процесса.Создание, наследование, именование, дублирование описателей.";
//root["17"] = u8"Средства синхронизации в режиме ядра в ОС Windows.События, семафоры, мьютексы.";
//root["18"] = u8"Эффект взаимоблокировки или возникновения тупика.Определение, условия возникновения, моделирование графами Холта.";
//root["19"] = u8"Стратегия «обнаружение - устранение» для борьбы с взаимоблокировками. Применение графов Холта и матриц распределения ресурсов.";
//root["20"] = u8"Стратегия избегания блокировок. Диаграмма траектории ресурсов. Алгоритм банкира для одного вида ресурсов.";
//root["21"] = u8"Предотвращение блокировок путем исключения условий их возникновения.";
//root["22"] = u8"Методы управления памятью без использования внешней памяти. Фиксированные, динамические и перемещаемые разделы.";
//root["23"] = u8"Методы управления памятью с использованием внешней памяти. Сегментный, страничный, сегментно - страничный способ.";
//root["24"] = u8"Назначение, принцип работы механизма свопинга.";
//root["25"] = u8"Назначение, принцип работы механизма кэширования.";
//root["26"] = u8"Реализация сегментного механизма управления памятью в процессорах семейства x86_32.";
//root["27"] = u8"Реализация страничного механизма управления памятью в процессорах семейства x86_32. Размер и основные поля структур данных, особенности реализации.";
//root["28"] = u8"Принцип работы алгоритмов замещения страниц, оптимальный алгоритм. Простые аппроксимации оптимального алгоритма : алгоритм NRU, алгоритм FIFO, алгоритм «вторая попытка», алгоритм «часы».";
//root["29"] = u8"Алгоритмы выгрузки дольше всех не использовавшейся страницы LRU : аппаратные реализации LRU, алгоритм NFU, алгоритм старения.";
//root["30"] = u8"Понятие «рабочий набор», алгоритм WSClock.";
//root["31"] = u8"Средства ОС Windows для управления виртуальной памятью процесса. Функция VirtualAlloc.Структурированная обработка исключений.Файлы, отображаемые в память.";
//root["32"] = u8"Архитектура программного обеспечения ввода - вывода.Средства программного взаимодействия с внешними устройствами.Архитектура программного стека, функции слоев.";
//root["33"] = u8"Общие принципы организации файловых систем и файлов. Идентификация файлов в файловых системах, логическая и физическая организация файлов.";	
//writeJsonToFile(root, pathToQuestions);
//Запись в Json файл



wstring readFromFile(string path) {
	wifstream myFile;
	myFile.imbue(std::locale(myFile.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	myFile.open(path);
	wstring allInfo = L""; 
	wstring line;
	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{
			allInfo += line;
		}
		myFile.close();
	}
	return line;
}
vector<wstring> readVectorFromFile(string path) {
	wifstream myFile;
	vector<wstring> readStrings;
	//vector<wstring>::iterator it;
	//it = readStrings.begin();
	myFile.imbue(std::locale(myFile.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	myFile.open(path);
	wstring line;
	if (myFile.is_open())
	{
		while (getline(myFile, line))
		{
			//it = readStrings.insert(it,line);
			readStrings.push_back(line);
		}
		myFile.close();
	}
	return readStrings;
}
using convert_type = std::codecvt_utf8<wchar_t>;
string convertToString(wstring str) {
	std::wstring_convert<convert_type, wchar_t> converter;
	return converter.to_bytes(str);
}

Json::Value makeAQuestionsJsonFile(vector<wstring> myVector) {
	Json::Value questionsJson;
	int index = 1;
	for (std::vector<wstring>::iterator it = myVector.begin(); it != myVector.end(); ++it) {
		wstring wstringTemp = *it;
		string stringTemp = convertToString(wstringTemp);
		string key = to_string(index);
		questionsJson[key] = stringTemp;
		index++;
	}
	return questionsJson;
}
wstring convertToWstring(string str)
{
	std::wstring wsTmp(str.begin(), str.end());
	return wsTmp;
}
const int NUM_TICKETS = 4;
const int NUM_QUESTS_IN_TICKET = 16;

void printRandomQuestion() {
	unsigned rand_choice = rand();
	cout << u8"Номер билета: " << (rand_choice / NUM_QUESTS_IN_TICKET % NUM_TICKETS + 1) << std::endl;
	cout << u8"Номер вопроса: " << (rand_choice % NUM_QUESTS_IN_TICKET + 1) << std::endl;
}

int main(int argc, char* argv[]) {	
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	wstring name = readFromFile("nameArg");
	wstring surname = readFromFile("surnameArg");
	string group = convertToString(readFromFile("GroupArg"));
	//string pathToQuestions = "C:\\Everest\\questions.txt";
	//string pathToGroupTickets = "C:\\Everest\\groupTicketList.json";
	//string pathToInfoFile = "C:\\Everest\\Text.txt";
	string pathToQuestions = argv[1];
	string pathToGroupTickets = argv[2];
	string pathToInfoFile = argv[3];
	Json::Value questions = makeAQuestionsJsonFile(readVectorFromFile(pathToQuestions));
	Json::Value groupListJson = readJsonFromFile(pathToGroupTickets);
	Json::Value::Members keyList = groupListJson.getMemberNames();
	srand((unsigned)time(NULL));
	string questionNumber1 = to_string(1+randomQuestion(groupListJson[group], 32));
	string questionNumber2 = to_string(1+randomQuestion(groupListJson[group], 32));
	string questionString1 = questions[questionNumber1].asString();
	string questionString2 = questions[questionNumber2].asString();	//a poch argc=4?
	cout << u8"Билет:" << endl;
	cout << u8"Вопрос " << questionNumber1 << ". " << questionString1 << endl;
	cout << u8"Вопрос " << questionNumber2 << ". " << questionString2;

	cout << endl <<"--------------------------------------" << endl;
	cout << u8"Дополнительные вопросы: " << endl;
	printRandomQuestion();
	cout << endl;
	printRandomQuestion();
	writeJsonToFile(groupListJson, pathToGroupTickets);
	wstring infoString = convertToWstring(group) + L" " + name + L" " + surname + L" Вопросы номер: " + convertToWstring(questionNumber1) + L" , " + convertToWstring(questionNumber2) + L"\n";
	writeToFile(pathToInfoFile, infoString);

}