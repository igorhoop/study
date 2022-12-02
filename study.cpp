/* ===========================

ПРОГРАММА ДЛЯ ОБУЧЕНИЯ

============================= */

#include <iostream>
#include <string.h>

class String
{
    public:
        String();                   // конструктор по умолчанию
        String(const char *const);  // еще зачем то конструктор
        String(const String &);     // еще зачем то конструктор
        ~String();                  // деструктор

        char & operator[] (unsigned short offset);      // перегрузка оператора индекса
        char operator[] (unsigned short offset) const;  // перегрузка оператора индекса еще раз зачем то
        String operator+(const String&);
        void operator+=(const String&);
        String & operator= (const String &);


        unsigned short GetLen() const { return itsLen; }
        const char * GetString() const { return itsString; }

    private:
        String (unsigned short);    // закрытый конструктор
        char * itsString;
        unsigned short itsLen;
};


//===КОНСТРУКТОР ПО УМОЛЧАНИЮ ДЛЯ СОЗДАНИЯ СТРОКИ НУЛЕВОЙ ДЛИНЫ
String::String()
{
    std::cout << "Вызван обычный конструктор для создания строки нулевой длины\n";
    itsString = new char[1];
    itsString[0] = '\0';
    itsLen=0;
}


//===ЗАКРЫТЫЙ (тот что в Private) КОНСТРУКТОР, ИСПОЛЬЗУЕМЫЙ ТОЛЬКО МЕТОДАМИ КЛАССА, ДЛЯ СОЗДАНИЯ СТРОК НАПОЛНЕННЫХ NULL
String::String(unsigned short len)
{
    itsString = new char[len+1];
    for(unsigned short i=0; i<=len; i++)
        itsString[i] = '\0';
    itsLen=len;
}


//===КОНСТРУКТОР КОТОРОМУ ПОДАЕТСЯ СИМВОЛЬНЫЙ МАССИВ (указатель типа const char *)
String::String(const char * const cString) // неизменяемый указатель на неизменяемую строку
{
    std::cout << "Вызван конструктор на вход которому подается символьный массив\n";
    itsLen = strlen(cString);
    itsString = new char[itsLen+1];
    for (unsigned short i=0; i < itsLen; i++)
        itsString[i] = cString[i];
    itsString[itsLen]='\0';
}



//===КОНСТРУКТОР КОПИЙ ЧТО БЛЯТЬ
String::String (const String & rhs)
{
    itsLen=rhs.GetLen();
    itsString= new char[itsLen+1];
    for (unsigned short i=0; i < itsLen; i++)
        itsString[i] = rhs[i];
    itsString[itsLen] = '\0';

}

String::~String()
{
    delete [] itsString;
    itsLen = 0;
}



String& String::operator=(const String & rhs)
{
    if (this == &rhs)
        return *this;
    delete [] itsString;
    itsLen=rhs.GetLen();
    itsString = new char[itsLen+1];
    for (unsigned short i=0; i<itsLen; i++)
    {
        itsString[i] = rhs[i];
    }
    itsString[itsLen] = '\0';
    return *this;

}



// Непостоянный адрес индексирования, возвращает ссылку на символ так что ее можно изменить
char & String::operator[](unsigned short offset)
{
    if (offset > itsLen)
        return itsString[itsLen-1];
    else
        return itsString[offset];
}

// Постоянный оператор индексирования для исопльзования с постоянными объектами (см. конструктор копий)
char String::operator[](unsigned short offset) const
{
    if (offset > itsLen)
        return itsString[itsLen-1];
    else
        return itsString[offset];
}


// создание новой строки добавляя текущую к rhs. конкатенация?
String String::operator+(const String& rhs)
{
    unsigned short totalLen = itsLen + rhs.GetLen();
    String temp(totalLen);
    unsigned short i;
    for (i=0; i<itsLen; i++)
    {
        temp[i] = itsString[i];
    }
    for (unsigned short j=0; j<rhs.GetLen(); j++, i++)
    {
        temp[i]=rhs[j];
    }
    temp[totalLen]='\0';
    return temp;
}


// добавить к строке ?
void String::operator+=(const String& rhs)
{
    unsigned short rhsLen = rhs.GetLen();
    unsigned short totalLen = itsLen + rhsLen;
    String temp(totalLen);
    unsigned short i;
    for (i=0; i<itsLen; i++)
        temp[i] = itsString[i];
    for (unsigned short j=0; j<rhs.GetLen(); j++, i++)
        temp[i] = rhs[i-itsLen];
    temp[totalLen]='\0';
    *this = temp;
}






int main()
{

    const char * mystring = "test test test";
    String s1(mystring);
    std::cout << "S1:\t" << s1.GetString() <<  std::endl;
    String s2;


    //char * temp = "Hello World";
    //s1 = "asdfasdf";
    //std::cout << "S1:\t" << s1.GetString() << "  длина строки: " << s1.GetLen() << std::endl;

    int array[3][3];
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
            array[i][j] = 0;
    }

    
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            printf("array[%d][%d] = %d \n", i, j, array[i][j]);


    const char * names[] = {"Igor", "Sasha", "Ilya", "Vadim"};
    const char * secondnames[] = {"Parandiuk","Sergievskijj", "Kainov", "Toma"};
    const char * fio[] = {"I.P.", "S.S.", "I.K.", "V.T."};


    char * fullnames[4];

    // инициализация массива с помощью брания памяти в куче
    for (int i=0; i < 4; i++)
    {
        fullnames[i] = new char[100]; // строка наврядли будет больше 100 символов
        strncpy(fullnames[i], names[i], strlen(names[i]));
    }


    // добавляем к финальной строке фамилию

    for (int i=0; i < 4; i++)
    {
        int lenNames = strlen(names[i]);
        int lenSecondnames = strlen(secondnames[i]);


        // добавляем пробел в конец массива перед конкатенацией
        strncpy(fullnames[i] + lenNames, " ", 1);

        strncpy(fullnames[i] + (lenNames+1), secondnames[i], lenSecondnames);
    }

    // добавляем к финальной строке ФИО

    for (int i=0; i < 4; i++)
    {
        int lenLast = strlen(fullnames[i]);
        int lenFio = strlen(fio[i]);

        // добавляем пробел в конец массива перед конкатенацией
        strncpy(fullnames[i] + lenLast, " ", 1);

        strncpy(fullnames[i] + (lenLast+1), fio[i], lenFio);
    }


    
    

    printf("Адрес начала: %p \n", fullnames);
    printf("Адрес 1: %s \n", fullnames[0]);
    printf("Адрес 2: %s \n", fullnames[1]);
    printf("Адрес 3: %s \n", fullnames[2]);
    printf("Адрес 4: %s \n", fullnames[3]);


    printf("\n\n\n\n");

    
    int * Array[500];
    printf("Указатель на указатель: %p \n", &Array);
    printf("Адрес начала Array: %p \n", Array);
    printf("Адрес ячейки 0: %p \n", &Array[0]);
    printf("Адрес ячейки 1: %p \n", &Array[1]);
    printf("Адрес ячейки 2: %p \n", &Array[2]);
    printf("Адрес ячейки 3: %p \n", &Array[3]);
    printf("Адрес ячейки 4: %p \n", &Array[4]);
    printf("Адрес ячейки 5: %p \n", &Array[5]);
    printf("Адрес ячейки 6: %p \n", &Array[6]);

    std::cout << Array;




    return 0;
} 