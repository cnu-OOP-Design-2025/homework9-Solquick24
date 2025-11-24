#include <iostream>
#include <string>
#include <list>
using namespace std;

template<typename T>
class MyVector {
/* TODO */
private:
    T* data; // 동적 배열을 가리키는 포인터
    size_t capacity; // 현재 할당된 배열 크기
    size_t length; // 실제 저장된 요소 개수

    void resize() {
        cout << "Resize: " << capacity << " -> " << capacity * 2 << endl;
        
        size_t newCap = capacity * 2;
        T* newData = new T[newCap]; // capacity 2배로 늘리고 새로운 배열 할당 (new)
        for (size_t i = 0; i < length; ++i) { // 기존 데이터 복사
            newData[i] = data[i];
        }

        delete[] data; // 기존 배열 해제
        data = newData; // data가 새로운 배열을 가리키도록 설정
        capacity = newCap; // 업데이트된 capacity 저장
    }

public:
    MyVector() : capacity(2), length(0) {
        data = new T[capacity]; // 동적할당
    }

    ~MyVector() {
        delete[] data; // 동적할당 해제
    }

    void push_back(const T& value) {
        if ( length == capacity ) {       // length가 capacity에 도달하면 resize()를 호출.
            resize();
        }

        data[length++] = value; // 새로운 요소를 배열 끝에 추가하고 length를 1만큼 증가
    }

    T pop_back() {
        if (length == 0)
            throw out_of_range("Vector is empty");
        return data[--length]; // 마지막 요소 제거
    }

    T& operator[] (const int index) {  // 연산자 오버로딩 operator[] ( 클래스가 배열처럼 동작하는 것임 )
        // MyClass obj;
        // obj[5]; 이런 식으로 호출 가능
        return data[index];
    }

    size_t size() const {
        return length;
    }


};

template<typename T>
void testVector(const string& name, std::list<T> values) {

    cout << "------------------" << endl;
    MyVector<T> vec;
    for (auto& v : values)
        vec.push_back(v);

    cout << name << ": ";
    for (size_t i = 0; i < vec.size(); ++i)
        cout << vec[i] << " ";

    cout << endl;
    while(vec.size())
        cout << "Pop: " << vec.pop_back() << "\n";
}

int main() {
    testVector<int>("IntVec", {1, 2, 3, 4, 5, 6});
    testVector<double>("DoubleVec", {1.1, 2.2, 3.3, 4.4, 5.5});
    testVector<char>("CharVec", {'A', 'B', 'C', 'D', 'E', 'F'});
    testVector<string>("StringVec", {"Hello", "World", "C++", "Template", "Vector"});
    return 0;
}
