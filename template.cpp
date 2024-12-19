#include <iostream>
#include <vector>
using namespace std;

// Linked list загвар класс
template <typename T>
class LinkedList {
protected:
  // Зангилаа бүтэц
  struct Node {
    T data;
    Node *next;

    // Зангилаа бүтцийн байгуулагч функц
    Node(T d) {  
      data = d;
      next = nullptr;  
    }
  };

  Node *head;
  int size;

public:
  // Linked list классын байгуулагч функц
  LinkedList() {
    size = 0;
    head = nullptr;  // Эхэндээ жагсаалт хоосон
  }

  // Linked list классын устгагч функц
  ~LinkedList() {
    while (head) {
      Node *tmp = head;   // элементийг устгахдаа хэрэглэх заагч
      head = head->next;
      delete tmp;
    }
  }

  // Жагсаалтын сүүлд элементийг нэмэх функц
  void add(T t) {
    Node *newNode = new Node(t);

    if (head == nullptr) {   // Хэрэв элементгүй бол жагсаалтын эхэнд оруулна
      head = newNode;
    } else {
      Node *tmp = head;
      while (tmp->next) { // Жагсаалтын төгсгөл хүртэл явна
        tmp = tmp->next;
      }
      tmp->next = newNode; // Жагсаалтын төгсгөлд очоод элементийг холбоно
    }
    size++;
  }

  // Index - дүгээрт элемент оруулна
  void insert(T t, int index) {
    if (index < 0 || index > size) {
      cout << "Индекс буруу байна!" << endl;
      return;
    }

    Node *newNode = new Node(t);  // shine element uusgeh

    if (index == 0) {  // ehend oruulah
      newNode->next = head;
      head = newNode;
    } else {
      Node *tmp = head;
      for (int i = 0; i < index - 1; ++i) {  // zuw index hurtel
        tmp = tmp->next;
      }
      newNode->next = tmp->next;
      tmp->next = newNode;  // indexn bairlald element oruulah
    }
    size++;
  }

  // i-р элементийн утгыг буцаана
  T get(int index) {
    if (index < 0 || index >= size) {
      throw out_of_range("Индекс буруу байна!");
    }

    Node *tmp = head;
    for (int i = 0; i < index; ++i) {  // index hurtel guij element olood butsaah
      tmp = tmp->next;
    }
    return tmp->data;
  }

  // i-р элементийг устгана
  void remove(int index) {
    if (index < 0 || index >= size) {
      cout << "Индекс буруу байна!" << endl;
      return;
    }

    Node *toDelete;
    if (index == 0) {  // ehnii element ustgah
      toDelete = head;
      head = head->next;
    } else {
      Node *tmp = head;
      for (int i = 0; i < index - 1; ++i) {  // indexn umnuh elementg olno
        tmp = tmp->next;
      }
      toDelete = tmp->next;
      tmp->next = toDelete->next;  // elementiig ustgana
    }
    delete toDelete;  
    size--;
  }

  // Жагсаалтын уртыг буцаана
  int length() {
    return size;
  }
};

int main() {
  // jishee
  LinkedList<int> list;

  list.add(1);
  list.add(2);
  list.add(3);

  list.insert(4, 1); // 1-r bairlald 4-iig oruulna
  cout << "Жагсаалтын урт: " << list.length() << endl;

  for (int i = 0; i < list.length(); ++i) {
    cout << "Элемент [" << i << "]: " << list.get(i) << endl;
  }

  list.remove(2); // 2-r elementiig ustgana
  cout << "2-р элементийг устгасны дараа:" << endl;
  for (int i = 0; i < list.length(); ++i) {
    cout << "Элемент [" << i << "]: " << list.get(i) << endl;
  }

  return 0;
}