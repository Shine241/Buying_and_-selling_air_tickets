
#include <iostream>
#include <string>
#include <regex>
#include <windows.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// хеш таблица, открытое хеширование
class Passengers {

private:

    std::string passport;
    std::string Place_and_date_of_issue_passport;
    std::string fullName;
    std::string date_of_birth;

public:
    Passengers() {

        passport = "NNNN-NNNNNNNN";
        Place_and_date_of_issue_passport = "-";
        fullName = "Иванов Иван Иванович";
        date_of_birth = "01.01.2024";
    }

    void insert_date_of_Passenger(std::string passport, std::string Place_and_date_of_issue_passport, std::string fullName, std::string date_of_birth) {

        this->passport = passport;
        this->Place_and_date_of_issue_passport = Place_and_date_of_issue_passport;
        this->fullName = fullName;
        this->date_of_birth = date_of_birth;
    }

    std::string getPassport() {
        return passport;
    }
    std::string getPlace_and_date_of_issue_passport() {
        return Place_and_date_of_issue_passport;
    }
    std::string getfullName() {
        return fullName;
    }
    std::string getdate_of_birth() {
        return date_of_birth;
    }



};

class LinckedLst {
public:
    Passengers data;
    LinckedLst* next;

    LinckedLst(const Passengers& passenger) : data(passenger), next(nullptr) {}

};

class HashTable {
public:
    LinckedLst** table;
    int size;

    HashTable() {
        size = 300;

        table = new LinckedLst * [size];
        for (int i = 0; i < size; ++i)
        {
            table[i] = nullptr;
        }

    }
    ~HashTable() {
        for (size_t i = 0; i < size; ++i) {
            LinckedLst* current = table[i];
            while (current) {
                LinckedLst* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] table;
    }

    int hashFun(const std::string& passport) {

        int hash = 0;
        for (char c : passport) {
            if (c != '-') {
                hash += c;
            }
        }
        return hash % size;
    }

    void insertToTable(Passengers& person) {

        int id = hashFun(person.getPassport());
        LinckedLst* newNode = new LinckedLst(person);
        // Устанавливаем указатель next нового узла на текущую голову списка
        newNode->next = table[id];
        // Обновляем указатель на голову списка, чтобы он указывал на новый узел
        table[id] = newNode;

    }

    void delInTable(const std::string& passport) {
        int id = hashFun(passport);
        LinckedLst* target = table[id];
        LinckedLst* previous = nullptr;

        while (target != nullptr)
        {
            if (target->data.getPassport() == passport) {
                // Найден пассажир с заданным номером паспорта, удаляем его из списка
                if (previous != nullptr) {
                    previous->next = target->next;
                }
                else {
                    table[id] = target->next;
                }
                delete target;
                std::cout << "!---------Пассажир удален-------!" << std::endl;
                return;
            }
            previous = target;
            target = target->next;
        }

    }

    void findInTable(const std::string& passport) {

        int id = hashFun(passport);
        LinckedLst* target = table[id];


        while (target != nullptr)
        {
            if (target->data.getPassport() == passport) {
                std::cout << "\nПаспорт: " << target->data.getPassport() << std::endl;
                std::cout << "Место и дата выдачи паспорта: " << target->data.getPlace_and_date_of_issue_passport() << std::endl;
                std::cout << "ФИО: " << target->data.getfullName() << std::endl;
                std::cout << "Дата рождения: " << target->data.getdate_of_birth() << std::endl;
                return;
            }
            target = target->next;
        }
    }

    void displayTable() {

        for (int i = 0; i < size; ++i) {
            LinckedLst* target = table[i];
            while (target != nullptr) {
                std::cout << "\n\nПаспорт: " << target->data.getPassport() << std::endl;
                std::cout << "Место и дата выдачи паспорта: " << target->data.getPlace_and_date_of_issue_passport() << std::endl;
                std::cout << "ФИО: " << target->data.getfullName() << std::endl;
                std::cout << "Дата рождения: " << target->data.getdate_of_birth() << std::endl;
                std::cout << "--------------------------------------------------------------------------" << std::endl;
                target = target->next;
            }
        }
    }

    void findInTableByFIO(const std::string& FIO) {

        for (int i = 0; i < size; ++i)
        {
            LinckedLst* target = table[i];
            while (target != nullptr)
            {
                if (target->data.getfullName() == FIO)
                {
                    std::cout << "\n\nПаспорт: " << target->data.getPassport() << std::endl;
                    std::cout << "Место и дата выдачи паспорта: " << target->data.getPlace_and_date_of_issue_passport() << std::endl;
                    std::cout << "ФИО: " << target->data.getfullName() << std::endl;
                    std::cout << "Дата рождения: " << target->data.getdate_of_birth() << std::endl;
                }
                target = target->next;
            }
        }
    }

    /*void clearDataAboutPassengers() {

        for (int i = 0; i < size; ++i) {
            LinckedLst* target = table[i];
            while (target != nullptr) {
                LinckedLst* temp = target;
                target = target->next;
                delete temp;
            }
            table[i] = nullptr;
        }

    }*/


    bool passengers_existence(const std::string& pass) {
        int index = hashFun(pass);
        LinckedLst* current = table[index];
        while (current != nullptr) {
            if (current->data.getPassport() == pass) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void findAndDisplayFIO(const std::string& passport) {

        int id = hashFun(passport);
        LinckedLst* target = table[id];


        while (target != nullptr)
        {
            if (target->data.getPassport() == passport) {
                std::cout << "ФИО: " << target->data.getfullName() << std::endl;
                return;
            }
            target = target->next;
        }
    }

};


std::string passportCheck() {

    std::string pass;
    std::regex pattern("\\d{4}-\\d{6}");

    while (true) {
        std::cout << "Введите номер паспорта в формате NNNN-NNNNNN: ";
        std::cin >> pass;

        if (std::regex_match(pass, pattern)) {
            break;
        }
        else {
            std::cout << "Некорректный формат номера паспорта. Пожалуйста, попробуйте снова.\n";
        }
    }
    return pass;
}

void create_Passengers(Passengers& person, HashTable& hashTable) {

    std::string passport;
    std::string Place_and_date_of_issue_passport;
    std::string fullName;
    std::string date_of_birth;

    passport = passportCheck();

    std::regex pattern2("\\d{2}\\.\\d{2}\\.\\d{4}");

    std::cout << "Введите Место и дату выдачи паспорта: ";
    std::getline(std::cin >> ::std::ws, Place_and_date_of_issue_passport);
    std::cout << "Введите ФИО: ";
    std::getline(std::cin >> ::std::ws, fullName);
    while (true) {
        std::cout << "Введите дату рождения в формате NN.NN.NNNN: ";
        std::cin >> date_of_birth;

        if (std::regex_match(date_of_birth, pattern2)) {
            break;
        }
        else {
            std::cout << "Некорректный формат даты рождения. Пожалуйста, попробуйте снова.\n";
        }
    }

    person.insert_date_of_Passenger(passport, Place_and_date_of_issue_passport, fullName, date_of_birth);

    hashTable.insertToTable(person);
}

void findPassengers_ByPass(HashTable& hashTable) {


    std::string pass;
    pass = passportCheck();
    hashTable.findInTable(pass);
}

void findPassengers_ByFIO(HashTable& hashTable) {

    std::string fullName;
    std::cout << "Введите ФИО: ";
    std::getline(std::cin >> std::ws, fullName);

    hashTable.findInTableByFIO(fullName);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////АВЛ дерево, метод обхода обратный, алгоритм Боуера и Мура (БМ)

class Flights {

private:

    std::string Flight_number; // номер авиарейса
    std::string Airline_name; // название авиакомпании
    std::string Departure_airport; // аэтопорт прибытия
    std::string Arrival_airport; // аэропорт отправления
    std::string Departure_date; // дата отправления
    std::string Departure_time; // время отправления
    int Total_number_of_seats; // всего мест на самолете 

public:
    int Number_of_free_seats; // Количество свободных мест
    Flights() {

        Flight_number = "AAA-NNN";
        Airline_name = "-";
        Departure_airport = "-";
        Arrival_airport = "-";
        Departure_date = "00.00.0000";
        Departure_time = "00.00.00";
        Total_number_of_seats = 0;
        Number_of_free_seats = 0;
    }

    void insert_date_of_Flights(std::string Flight_number, std::string Airline_name, std::string Departure_airport, std::string Arrival_airport,
        std::string Departure_date, std::string Departure_time, int Total_number_of_seats, int Number_of_free_seats) {

        this->Flight_number = Flight_number;
        this->Airline_name = Airline_name;
        this->Departure_airport = Departure_airport;
        this->Arrival_airport = Arrival_airport;
        this->Departure_date = Departure_date;
        this->Departure_time = Departure_time;
        this->Total_number_of_seats = Total_number_of_seats;
        this->Number_of_free_seats = Number_of_free_seats;
    }

    std::string getFlight_number() {
        return Flight_number;
    }
    std::string getAirline_name() {
        return Airline_name;
    }
    std::string getDeparture_airport() {
        return Departure_airport;
    }
    std::string getArrival_airport() {
        return Arrival_airport;
    }
    std::string getDeparture_date() {
        return Departure_date;
    }
    std::string getDeparture_time() {
        return Departure_time;
    }
    int getTotal_number_of_seats() {
        return Total_number_of_seats;
    }
    int getNumber_of_free_seats() {
        return Number_of_free_seats;
    }



};

struct TreeNode
{
    Flights data;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(Flights value) : data(value), left(nullptr), right(nullptr), height(1) {}
};


int height(TreeNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

int getBalance(TreeNode* node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return height(node->left) - height(node->right);
}

TreeNode* rightRotate(TreeNode* y)
{
    TreeNode* x = y->left;
    TreeNode* Z = x->right;

    x->right = y;
    y->left = Z;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

TreeNode* leftRotate(TreeNode* x)
{
    TreeNode* y = x->right;
    TreeNode* Z = y->left;
    y->left = x;
    x->right = Z;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

bool searchFlight_number(TreeNode* root, std::string& Flight_number) {
    if (root == nullptr) {
        return false;
    }
    if (root->data.getFlight_number() == Flight_number) {
        return true;
    }
    if (Flight_number < root->data.getFlight_number()) {
        searchFlight_number(root->left, Flight_number);
    }
    searchFlight_number(root->right, Flight_number);

}

TreeNode* insertAndBalance(TreeNode* root, Flights value)
{
    if (root == nullptr)
    {
        return new TreeNode(value);
    }

    std::string str = value.getFlight_number();

    if (searchFlight_number(root, str)) {
        std::cout << "Такой авиарейс уже существует";
        return nullptr;
    }

    if (value.getFlight_number() < root->data.getFlight_number())
    {
        root->left = insertAndBalance(root->left, value);
    }
    else
    {
        root->right = insertAndBalance(root->right, value);
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && value.getFlight_number() < root->left->data.getFlight_number())
    {
        return rightRotate(root);
    }

    if (balance < -1 && value.getFlight_number() > root->right->data.getFlight_number())
    {
        return leftRotate(root);
    }

    if (balance > 1 && value.getFlight_number() > root->left->data.getFlight_number())
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && value.getFlight_number() < root->right->data.getFlight_number())
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

TreeNode* minValueNode(TreeNode* node)
{
    TreeNode* current = node;
    while (current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

TreeNode* deleteNode(TreeNode* root, std::string& value)
{
    if (root == nullptr)
    {
        return root;
    }

    if (value < root->data.getFlight_number())
    {
        root->left = deleteNode(root->left, value);
    }
    else if (value > root->data.getFlight_number())
    {
        root->right = deleteNode(root->right, value);
    }
    else
    {
        if ((root->left == nullptr) || (root->right == nullptr))
        {
            TreeNode* temp = root->left ? root->left : root->right;
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else
            {
                *root = *temp;
            }
            delete temp;
        }
        else
        {
            TreeNode* temp = minValueNode(root->right);
            root->data = temp->data;
            std::string str = temp->data.getFlight_number();
            root->right = deleteNode(root->right, str);
        }
    }

    if (root == nullptr)
    {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
    {
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
    {
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void printTreeStructure(TreeNode* root, int level = 0)
{
    if (root == nullptr)
        return;

    printTreeStructure(root->right, level + 1);

    for (int i = 0; i < level; ++i)
        std::cout << "    ";

    std::cout << root->data.getFlight_number() << std::endl;

    printTreeStructure(root->left, level + 1);
}

void displayTree(TreeNode* root) {

    if (root != nullptr) {

        displayTree(root->left);
        displayTree(root->right);

        std::cout << "\n\nНомер авиарейса: " << root->data.getFlight_number() << std::endl;
        std::cout << "Название авиакомпании: " << root->data.getAirline_name() << std::endl;
        std::cout << "Аэтопорт прибытия: " << root->data.getDeparture_airport() << std::endl;
        std::cout << "Аэропорт отправления: " << root->data.getArrival_airport() << std::endl;
        std::cout << "Дата отправления: " << root->data.getDeparture_date() << std::endl;
        std::cout << "Время отправления: " << root->data.getDeparture_time() << std::endl;
        std::cout << "Всего мест на самолете: " << root->data.getTotal_number_of_seats() << std::endl;
        std::cout << "Количество свободных мест: " << root->data.getNumber_of_free_seats() << std::endl;
        std::cout << "--------------------------------------------------------------------------" << std::endl;

    }


}

TreeNode* search_Flight_number(TreeNode* root, const std::string& Flight_number) {
    if (root == nullptr || root->data.getFlight_number() == Flight_number) {
        return root;
    }
    if (Flight_number < root->data.getFlight_number()) {
        return search_Flight_number(root->left, Flight_number);
    }
    return search_Flight_number(root->right, Flight_number);
}
/////////////////////////////
bool BMsearch(const std::string& text, const std::string& pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) return true;

    // Таблица смещений
    const int ALPHABET_SIZE = 256;
    int shiftTable[ALPHABET_SIZE];

    // Создание таблицы смещений
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        shiftTable[i] = m; // Инициализация значением длины шаблона
    }
    for (int i = 0; i < m - 1; ++i) {
        shiftTable[(unsigned char)pattern[i]] = m - 1 - i;
    }

    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j]) {
            --j;
        }
        if (j < 0) {
            // Проверяем, что перед найденным совпадением нет букв
            if (s == 0 || !isalpha(text[s - 1])) {
                // Проверяем, что после найденного совпадения также нет букв
                int endIndex = s + m;
                if (endIndex == n || !isalpha(text[endIndex])) {
                    return true;
                }
            }
            s += m;
        }
        else {
            // Используем таблицу смещений
            int max_value = (1 > shiftTable[(unsigned char)text[s + j]]) ? 1 : shiftTable[(unsigned char)text[s + j]];
            s += max_value;
        }
    }

    return false;
}


void search_By_Fragments(TreeNode* root, std::string& Departure_airport) {

    if (root != nullptr) {
        // Сначала обходим левое поддерево
        search_By_Fragments(root->left, Departure_airport);

        // Затем обходим правое поддерево
        search_By_Fragments(root->right, Departure_airport);

        // После обхода поддеревьев проверяем узел
        if (BMsearch(root->data.getDeparture_airport(), Departure_airport)) {
            std::cout << "\n\nНомер авиарейса: " << root->data.getFlight_number() << std::endl;
            std::cout << "Аэтопорт прибытия: " << root->data.getDeparture_airport() << std::endl;
            std::cout << "Дата отправления: " << root->data.getDeparture_date() << std::endl;
            std::cout << "Время отправления: " << root->data.getDeparture_time() << std::endl;
            std::cout << "--------------------------------------------------------------------------" << std::endl;
        }
    }
}
/////////////////////////////

std::string flightNumberCheck() {

    std::string flightNumber;
    std::regex pattern("[A-Z]{3}-\\d{3}");

    while (true) {
        std::cout << "Введите номер рейса в формате AAA-NNN: ";
        std::cin >> flightNumber;

        if (std::regex_match(flightNumber, pattern)) {
            break;
        }
        else {
            std::cout << "Некорректный формат номера рейса. Пожалуйста, попробуйте снова.\n";
        }
    }
    return flightNumber;
}

void create_Flights(TreeNode*& root, Flights& flight) {

    std::string Flight_number; // номер авиарейса
    std::string Airline_name; // название авиакомпании
    std::string Departure_airport; // аэтопорт прибытия
    std::string Arrival_airport; // аэропорт отправления
    std::string Departure_date; // дата отправления
    std::string Departure_time; // время отправления
    int Total_number_of_seats{ 0 }; // всего мест на самолете 
    int Number_of_free_seats; // Количество свободных мест

    Flight_number = flightNumberCheck();

    std::regex pattern2("\\d{2}\\.\\d{2}\\.\\d{4}");

    std::cout << "Введите название авиакомпании: ";
    std::getline(std::cin >> ::std::ws, Airline_name);
    std::cout << "Введите аэтопорт прибытия: ";
    std::getline(std::cin >> ::std::ws, Departure_airport);
    std::cout << "Введите аэропорт отправления: ";
    std::getline(std::cin >> ::std::ws, Arrival_airport);
    std::cout << "Введите дата отправления: ";
    std::getline(std::cin >> ::std::ws, Departure_date);
    std::cout << "Введите время отправления: ";
    std::getline(std::cin >> ::std::ws, Departure_time);
    std::cout << "Введите количество мест на самолете: ";
    std::cin >> Total_number_of_seats;

    Number_of_free_seats = Total_number_of_seats;

    flight.insert_date_of_Flights(Flight_number, Airline_name, Departure_airport, Arrival_airport, Departure_date, Departure_time, Total_number_of_seats, Number_of_free_seats);
    root = insertAndBalance(root, flight);
}

void search_By_Departure_airport(TreeNode* root) {

    std::string fragment;
    std::cout << "Введите фрагмент названия аэропорта прибытия: ";
    std::getline(std::cin >> std::ws, fragment);

    search_By_Fragments(root, fragment);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Двунаправленный список, быстрая сортировка

class Air_tickets {

private:

    std::string passport;
    std::string Flight_number;
    std::string Ticket_number;//строка из 9 цифр

public:
    Air_tickets() {

        passport = "NNNN-NNNNNNNN";
        Flight_number = "AAA-NNN";
        Ticket_number = "000000000";
    }

    void insert_date_of_Air_tickets(std::string passport, std::string Flight_number, std::string Ticket_number) {

        this->passport = passport;
        this->Flight_number = Flight_number;
        this->Ticket_number = Ticket_number;
    }

    std::string getPass() {
        return passport;
    }
    std::string getF_number() {
        return Flight_number;
    }
    std::string getTicket_number() {
        return Ticket_number;
    }
};

class Node {
public:
    Air_tickets data;
    Node* next;
    Node* prev;

    Node(const Air_tickets& d) : data(d), next(nullptr), prev(nullptr) {}
};

class LinkedList {
private:

    Node* tail;

    Node* getMiddle(Node* low, Node* high) {
        Node* current = low;

        // Создаем итератор для подсчета количества элементов в списке
        int count = 0;
        while (current != nullptr) {
            if (current == high) {
                break;
            }
            current = current->next;
            count++;
        }

        // Делим счетчик пополам
        int middle = count / 2;

        // Находим центральный элемент
        current = low;
        for (int i = 0; i < middle; ++i) {
            current = current->next;
        }

        return current;
    }


    Node* partition(Node* low, Node* high) {
        Node* pivotNode = getMiddle(low, high); // Получаем центральный элемент
        Air_tickets pivot = pivotNode->data; // Значение центрального элемента

        Node* i = low;
        Node* j = high;

        while (true) {
            while (i->data.getF_number() < pivot.getF_number()) {
                i = i->next;
            }
            while (j->data.getF_number() > pivot.getF_number()) {
                j = j->prev;
            }
            if (i == nullptr || j == nullptr || i == j || i->prev == j) {
                break;
            }
            Air_tickets temp = i->data;
            i->data = j->data;
            j->data = temp;

            i = i->next;
            j = j->prev;
        }

        return j;
    }

    void quickSort(Node* low, Node* high) {
        if (high != nullptr && low != nullptr && low != high && low != high->next) {
            Node* pi = partition(low, high);
            if (pi != nullptr) {
                quickSort(low, pi);
                quickSort(pi->next, high);
            }
        }
    }

public:
    Node* head;
    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void insert(Air_tickets& data, TreeNode* root, HashTable& table) {

        if (!table.passengers_existence(data.getPass())) {
            std::cout << "Пассажир не найден!\n";
            return;
        }

        TreeNode* value = search_Flight_number(root, data.getF_number());

        if (value == nullptr) {
            std::cout << "\nДанного рейса нет!\n";
            return;
        }

        if (value->data.getNumber_of_free_seats() == 0) {

            std::cout << "\nНет свободных мест в самолете!\n";
            return;
        }
        value->data.Number_of_free_seats--;

        Node* newNode = new Node(data);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        // Вызываем быструю сортировку после добавления элемента
        quickSort(head, tail);
    }

    void displayAllTickets() const {
        Node* current = head;
        while (current) {
            std::cout << "Passport: " << current->data.getPass() << std::endl;
            std::cout << "Flight number: " << current->data.getF_number() << std::endl;
            std::cout << "Ticket number: " << current->data.getTicket_number() << std::endl;
            std::cout << std::endl;
            current = current->next;
        }
    }

    Node* searchByTicketNumber(const std::string& Ticket_number) {
        Node* current = head;
        while (current) {
            if (current->data.getTicket_number() == Ticket_number) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Если билет с указанным номером не найден
    }

    void remove(const std::string& Ticket_number, TreeNode* root) {

        Node* current = head;
        while (current) {
            if (current->data.getTicket_number() == Ticket_number) {

                // Находим объект с информацией о номере авиарейса
                TreeNode* value = search_Flight_number(root, current->data.getF_number());
                if (value) {
                    // Увеличиваем количество свободных мест на авиарейсе
                    value->data.Number_of_free_seats++;
                }

                if (current == head) {
                    head = current->next;
                    if (head) head->prev = nullptr;
                }
                else if (current == tail) {
                    tail = current->prev;
                    tail->next = nullptr;
                }
                else {
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                }
                delete current;


                return;
            }
            current = current->next;
        }
    }
};


std::string getValidTicket() {
    std::string input;
    std::regex pattern("\\d{9}");

    // Запрашиваем ввод от пользователя, пока не будет введена корректная строка
    while (true) {
        std::cout << "Введите строку в формате NNNNNNNNN (9 цифр): ";
        std::cin >> input;

        // Проверяем введенную строку на соответствие паттерну
        if (std::regex_match(input, pattern)) {
            break; // Введенная строка соответствует формату, выходим из цикла
        }
        else {
            std::cout << "Некорректный ввод. Пожалуйста, повторите попытку." << std::endl;
        }
    }

    return input;
}

void sale_ticket(LinkedList& myList, TreeNode*& root, HashTable& hashTable, Air_tickets& Air_tickets) {

    std::string passport;
    std::string Flight_number;
    std::string Ticket_number;

    passport = passportCheck();
    Flight_number = flightNumberCheck();
    Ticket_number = getValidTicket();

    Air_tickets.insert_date_of_Air_tickets(passport, Flight_number, Ticket_number);

    myList.insert(Air_tickets, root, hashTable);
}

void refund_ticket(LinkedList& myList, TreeNode*& root) {

    std::string Ticket_number;

    Ticket_number = getValidTicket();


    myList.remove(Ticket_number, root);
}

void find_all_info_about_Flight(TreeNode*& root, HashTable& hashTable, LinkedList& myList, std::string& Flight_number) {

    TreeNode* value = search_Flight_number(root, Flight_number);

    if (value != nullptr)
    {
        std::cout << "\n\nНомер авиарейса: " << value->data.getFlight_number() << std::endl;
        std::cout << "Название авиакомпании: " << root->data.getAirline_name() << std::endl;
        std::cout << "Аэтопорт прибытия: " << value->data.getDeparture_airport() << std::endl;
        std::cout << "Аэтопорт отправления: " << value->data.getArrival_airport() << std::endl;
        std::cout << "Дата отправления: " << value->data.getDeparture_date() << std::endl;
        std::cout << "Время отправления: " << value->data.getDeparture_time() << std::endl;
        std::cout << "Всего мест на самолоете: " << value->data.getTotal_number_of_seats() << std::endl;
        std::cout << "Всего свободных мест на самолоете: " << value->data.getNumber_of_free_seats() << std::endl;
        std::cout << "--------------------------------------------------------------------------" << std::endl;
    }
    std::cout << "Пассажиры: \n";

    Node* current = myList.head;
    while (current) {

        if (current->data.getF_number() == value->data.getFlight_number() && hashTable.passengers_existence(current->data.getPass())) {

            // Выводим информацию о пассажире
            std::cout << "Паспорт: " << current->data.getPass() << std::endl;
            hashTable.findAndDisplayFIO(current->data.getPass());
            std::cout << "--------------------------------------------------------------------------"<< std::endl;
        }
        current = current->next;

    }


}

void search_By_Flight_number(TreeNode*& root, HashTable& hashTable, LinkedList& myList) {

    std::string Flight_number;
    std::cout << "Введите номер авиарейса: ";
    std::getline(std::cin >> std::ws, Flight_number);

    find_all_info_about_Flight(root, hashTable, myList, Flight_number);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void del_Flights(TreeNode* root, Flights& flight, LinkedList& myList) {

    std::string std = flightNumberCheck();

    Node* current = myList.head;
    while (current) {

        if (current->data.getF_number() == std) {
            std::cout << "На этот авиарейс есть пассажиры! \n";
            return;
        }
        current = current->next;

    }
    root = deleteNode(root, std);
}

void deletePassengers(HashTable& hashTable, LinkedList& myList) {

    std::string pass;
    pass = passportCheck();

    Node* current = myList.head;
    while (current) {

        if (current->data.getPass() == pass) {
            std::cout << "У этого пассажира есть билет! \n";
            return;
        }
        current = current->next;

    }

    hashTable.delInTable(pass);
}

void clearTree(TreeNode*& root, LinkedList& myList) {
    if (root == nullptr) {
        return;
    }
    clearTree(root->left, myList);
    clearTree(root->right, myList);
    Node* current = myList.head;
    while (current) {

        if (current->data.getF_number() == root->data.getFlight_number()) {
            std::cout << "На этот авиарейс есть пассажиры! \n";
            return;
        }
        current = current->next;

    }
    delete root;
    root = nullptr;
}

void clearDataAboutPassengers(HashTable& hashTable, LinkedList& myList) {
    for (int i = 0; i < 300; ++i) {
        LinckedLst* target = hashTable.table[i];
        while (target != nullptr) {
            LinckedLst* temp = target;
            target = target->next;

            // Проверяем наличие пассажира в связном списке
            Node* current = myList.head;
            while (current) {
                if (current->data.getPass() == temp->data.getPassport()) {
                    std::cout << "У пассажира " << temp->data.getPassport() << " есть билет! \n";
                    break; // Прерываем цикл, так как пассажир найден
                }
                current = current->next;
            }

            delete temp;
        }
        hashTable.table[i] = nullptr;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Load_test_data(TreeNode*& root, HashTable& hashTable, LinkedList& myList, Passengers passengers, Flights flights, Air_tickets Air_tickets) {

    passengers.insert_date_of_Passenger("1233-123203", "МВД РОССИИ, г. СПБ", "Семенов Игорь Витальевич", "19.04.2002");

    hashTable.insertToTable(passengers);

    passengers.insert_date_of_Passenger("5233-153503", "МВД РОССИИ, г. СПБ", "Вилкин Станислав Сергеевич", "10.04.2002");

    hashTable.insertToTable(passengers);

    passengers.insert_date_of_Passenger("9898-636363", "МВД РОССИИ, г. МОСКВА", "Иванов Иван Иванович", "22.09.2003");

    hashTable.insertToTable(passengers);
    //////
    flights.insert_date_of_Flights("AER-123", "Аэрофлот", "Пулково", "Шереметьево", "19.06.2024", "13:00", 45, 45);
    root = insertAndBalance(root, flights);

    flights.insert_date_of_Flights("AMA-555", "American Airlines", "Домодедово", "Bandirma", "19.05.2024", "12:00", 50, 50);
    root = insertAndBalance(root, flights);

    flights.insert_date_of_Flights("BKA-324", "Байкал Аэро", "Пулково", "Шереметьево", "21.07.2024", "14:00", 200, 200);
    root = insertAndBalance(root, flights);
    //////
    Air_tickets.insert_date_of_Air_tickets("1233-123203", "AER-123", "127465728");

    myList.insert(Air_tickets, root, hashTable);

    Air_tickets.insert_date_of_Air_tickets("5233-153503", "AMA-555", "827465328");

    myList.insert(Air_tickets, root, hashTable);

    Air_tickets.insert_date_of_Air_tickets("9898-636363", "AER-123", "907405328");

    myList.insert(Air_tickets, root, hashTable);
}

void Menu_passengers(HashTable& hashTable, LinkedList& myList);
void Menu_flights(TreeNode*& root, HashTable& hashTable, LinkedList& myList);
void Menu_Sale_and_refund_tickets(LinkedList& myList, TreeNode*& root, HashTable& hashTable);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int a, b, c, d, e, f;

    a = fmod(256, 6);
    b = fmod(256, 4);
    c = fmod(256, 7);
    d = fmod(256, 5);
    e = fmod(256, 3);
    f = fmod(256, 2);


    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;

    std::setlocale(LC_ALL, "Russian");
    HashTable hashTable;
    TreeNode* root = nullptr;
    LinkedList myList;

    Air_tickets Air_tickets;
    Passengers passengers;
    Flights flights;
    while (true)
    {
        std::cout << "---------------------Продажа авиабилетов-----------------------\n";
        std::cout << "1. Пассажиры\n";
        std::cout << "2. Авиарейсы\n";
        std::cout << "3. Продажа и возврат авиабилетов\n";
        std::cout << "4. Добавить тестовые данные\n";
        std::cout << "0. Выход\n\n";
        std::cout << "Ввод: ";

        int chose{};
        std::cin >> chose;

        switch (chose)
        {
        case 1:
            Menu_passengers(hashTable, myList);
            break;

        case 2:
            Menu_flights(root, hashTable, myList);
            break;

        case 3:
            Menu_Sale_and_refund_tickets(myList, root, hashTable);
            break;

        case 4:
            Load_test_data(root, hashTable, myList, passengers, flights, Air_tickets);
            break;

        case 0:
            exit(1);
            break;

        default:
            std::cout << "Ой, что-то пошло не так!";
            break;
        }


    }

}

void Menu_passengers(HashTable& hashTable, LinkedList& myList) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Passengers person;
    while (true)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        std::cout << "\n\n";
        std::cout << "---------------------Меню_пассажиров-----------------------\n";
        std::cout << "1. Регистрация нового пассажира\n";
        std::cout << "2. Удаление данных о пассажире\n";
        std::cout << "3. Просмотр всех зарегистрированных пассажиров\n";
        std::cout << "4. Очистка данных о пассажирах\n";
        std::cout << "5. Поиск пассажира по «номеру паспорта»\n";
        std::cout << "6. Поиск пассажира по ФИО\n";
        std::cout << "0. <-Назад\n\n";
        std::cout << "Ввод: ";

        int chose{};
        std::cin >> chose;

        switch (chose)
        {
        case 1:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            create_Passengers(person, hashTable);
            break;

        case 2:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            deletePassengers(hashTable, myList);
            break;

        case 3:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            hashTable.displayTable();
            break;

        case 4:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            /*hashTable.clearDataAboutPassengers();*/
            clearDataAboutPassengers(hashTable, myList);
            break;

        case 5:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            findPassengers_ByPass(hashTable);
            break;

        case 6:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            findPassengers_ByFIO(hashTable);
            break;

        case 0:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return;
            break;

        default:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << "Ой, что-то пошло не так!";
            break;
        }


    }



}

void Menu_flights(TreeNode*& root, HashTable& hashTable, LinkedList& myList) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    Flights flights;
    while (true)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        std::cout << "\n\n";
        std::cout << "---------------------Меню_авиарейсов-----------------------\n";
        std::cout << "1. Добавление нового авиарейса\n";
        std::cout << "2. Удаление сведений об авиарейсе\n";
        std::cout << "3. Просмотр всех авиарейсов\n";
        std::cout << "4. Очистка данных об авиарейсах\n";
        //std::cout << "5. Поиск авиарейса по «номеру авиарейса»\n";
        std::cout << "5. Поиск авиарейса по фрагментам названия аэропорта прибытия\n";
        std::cout << "0. <-Назад\n\n";
        std::cout << "Ввод: ";

        int chose{};
        std::cin >> chose;

        switch (chose)
        {
        case 1:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            create_Flights(root, flights);
            break;

        case 2:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            del_Flights(root, flights, myList);
            break;

        case 3:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            displayTree(root);
            break;

        case 4:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            clearTree(root, myList);
            break;

            /*case 5:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;*/

        case 5:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            search_By_Departure_airport(root);
            break;

        case 0:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return;
            break;

        default:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << "Ой, что-то пошло не так!";
            break;
        }


    }
}

void Menu_Sale_and_refund_tickets(LinkedList& myList, TreeNode*& root, HashTable& hashTable) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    Air_tickets Air_tickets;
    while (true)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
        std::cout << "\n\n";
        std::cout << "---------------------Меню продажи и возврата-----------------------\n";
        std::cout << "1. Регистрация продажи пассажиру авиабилета\n";
        std::cout << "2. Регистрация возврата пассажиром авиабилета\n";
        std::cout << "3. Просмотр всех активных билетов\n";
        std::cout << "4. Поиск авиарейса по «номеру авиарейса»\n";
        std::cout << "0. <-Назад\n\n";
        std::cout << "Ввод: ";

        int chose{};
        std::cin >> chose;

        switch (chose)
        {
        case 1:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            sale_ticket(myList, root, hashTable, Air_tickets);
            break;

        case 2:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            refund_ticket(myList, root);
            break;

        case 3:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            myList.displayAllTickets();
            break;

        case 4:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            search_By_Flight_number(root, hashTable, myList);
            break;


        case 0:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            return;
            break;

        default:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << "Ой, что-то пошло не так!";
            break;
        }


    }
}
