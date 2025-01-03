
/*------------------- Mehrfach Defines verhindern ----------------------------*/
#ifndef ARRAY_H_
#define ARRAY_H_
#define MAX_STRING_LEN 50
// Array-Deklaration in der Headerdatei
struct KostalStruct {
    int Adresse;
    char Description [MAX_STRING_LEN + 1]; 
    char Unit [9]; // Array für eine Zeichenkette mit maximal 8 Zeichen (+1 für das Nullzeichen)
    int Format; //64=float, 16=int,16 & N1=2 =long
    int N1;
    int enabel;
    float fval;
    long ival;
    char State [MAX_STRING_LEN + 1]; 
    char sVal [MAX_STRING_LEN + 1]; 
    ; 
 

};
extern KostalStruct globalArray[107];
extern KostalStruct globalArrayKEBA[21];

#endif /* ARRAY_H_ */
