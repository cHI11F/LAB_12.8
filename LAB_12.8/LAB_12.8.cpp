#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Структура елемента списку
struct Node {
    string data;
    Node* next;
};

// Функція для додавання елемента в кінець списку
void appendToList(Node*& head, string data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Функція для виведення списку на екран
void printList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

// Функція для звільнення пам'яті, що використовується списком
void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Функція для зчитування даних з текстового файлу у список
void readFromFileToList(Node*& head, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file " << filename << endl;
        return;
    }

    string item;
    while (getline(file, item)) {
        appendToList(head, item);
    }

    file.close();
}

// Функція для перевірки чи містить список заданий елемент
bool contains(Node* head, int value) {
    Node* current = head;
    while (current != nullptr) {
        if (stoi(current->data) == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Функція для видалення елементів зі списку за заданими позиціями
void deletePositions(Node*& head, Node* positions) {
    while (positions != nullptr) {
        int position = stoi(positions->data);
        if (position == 1) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        else {
            Node* prev = nullptr;
            Node* curr = head;
            for (int i = 1; i < position && curr != nullptr; ++i) {
                prev = curr;
                curr = curr->next;
            }
            if (curr != nullptr) {
                prev->next = curr->next;
                delete curr;
            }
        }
        positions = positions->next;
    }
}

int main() {
    Node* firstList = nullptr; // Перший список
    Node* secondList = nullptr; // Другий список

    // Зчитування даних з файлу для першого списку
    string filename;
    cout << "Enter the filename to read from: ";
    cin >> filename;
    readFromFileToList(firstList, filename);

    // Виведення першого списку
    cout << "Input list: ";
    printList(firstList);

    // Просимо ввести позиції для видалення з першого списку
    cout << "Enter positions to delete from the first list (separated by spaces), type '0' to finish input:\n";
    int position;
    while (cin >> position && position != 0) {
        string positionStr = to_string(position);
        appendToList(secondList, positionStr);
    }

    // Видаляємо позиції з першого списку
    deletePositions(firstList, secondList);

    // Виводимо відредагований перший список
    cout << "Edited first list: ";
    printList(firstList);

    // Просимо ввести елементи для другого списку
    cout << "Enter numbers for the second list (separated by spaces):\n";
    cin.ignore(); // Очистка буфера вводу перед використанням getline()
    string input;
    getline(cin, input);

    // Додаємо числа в другий список
    stringstream ss(input);
    while (ss >> input) {
        appendToList(secondList, input);
    }

    // Виводимо другий список
    cout << "Second list: ";
    printList(secondList);

    // Просимо ввести позиції для видалення з другого списку
    cout << "Enter positions to delete from the second list (separated by spaces), type '0' to finish input:\n";
    Node* thirdList = nullptr; // Третій список для збереження позицій
    while (cin >> position && position != 0) {
        string positionStr = to_string(position);
        appendToList(thirdList, positionStr);
    }

    // Видаляємо позиції з другого списку
    deletePositions(secondList, thirdList);

    // Виводимо відредагований другий список
    cout << "Edited second list: ";
    printList(secondList);

    // Звільнення пам'яті, що використовується списками
    freeList(firstList);
    freeList(secondList);
    freeList(thirdList);

    return 0;
}
