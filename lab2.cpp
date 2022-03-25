// dequeue.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <optional>

template <class T>
class twoLinkedListItem {
public:
    twoLinkedListItem(T data, twoLinkedListItem<T>* next = nullptr, twoLinkedListItem<T>* previous = nullptr) {
        this->data = { data };
        this->next = next;
        this->previous = previous;
    }
    twoLinkedListItem* next = nullptr;
    twoLinkedListItem* previous = nullptr;
    std::optional<T> data = std::nullopt;
private:
};


template <class T>
class dequeue {
public:
    dequeue() {};
    std::optional<T> shift() {
        if (head) {
            std::optional<T> data = head->data;
            twoLinkedListItem<T>* li = head;
            if (tail == li) { tail = nullptr; }
            head = li->next;
            if (head) { head->previous = nullptr; }
            delete li;
            return data;
        }
        else { return std::nullopt; }
    }
    void unshift(T data) {
        if (head) {
            head->previous = new twoLinkedListItem<T>(data, head);
            head = head->previous;
        }
        else { head = new twoLinkedListItem<T>(data); }
        if (!tail) { tail = head; }
    }
    void push(T data) {
        if (tail) {
            tail->next = new twoLinkedListItem<T>(data,nullptr,tail);
            tail = tail->next;
        } else { tail = new twoLinkedListItem<T>(data); }
        if (!head) { head = tail; }
    }
    std::optional<T> pop() {
        if (tail) {
            std::optional<T> data = tail->data;
            twoLinkedListItem<T>* li = tail;
            if (head == li) {head = nullptr;}
            tail = li->previous;
            if (tail) { tail->next = nullptr; }
            delete li;
            return data;
        } else { return std::nullopt; }
    }
private:
    twoLinkedListItem<T>* head = nullptr;
    twoLinkedListItem<T>* tail = nullptr;
};


int main()
{

    dequeue<std::string> dq;
    dq.push("a");
    dq.push("s");
    dq.push("d");
    dq.unshift("q");
    dq.unshift("w");
    std::cout << *(dq.pop()) << "|";
    std::cout << *(dq.pop()) << "|";
    std::cout << *(dq.pop()) << "|";
    std::cout << *(dq.shift()) << "|";
    std::cout << *(dq.pop()) << "|";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
