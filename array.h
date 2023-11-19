#ifndef ARRAY_H_
#define ARRAY_H_
#define MAX_STRING_LEN 50
// Array-Deklaration in der Headerdatei
struct KostalStruct {
    int Adresse;
    char Description [MAX_STRING_LEN + 1]; 
    char Unit [9]; // Array für eine Zeichenkette mit maximal 8 Zeichen (+1 für das Nullzeichen)
    int Format;
    int N1;
};
extern KostalStruct globalArray[107];

#endif /* ARRAY_H_ */
