#include <iostream>
#include "Identify.h"
#include "Id_number.h"
#include "Id_student_number.h"
int main() {
    Identify identify;
    Id_number id_number;
    Id_student_number id_student_number;
    identify.print();
    id_number.print();
    id_student_number.print();
    return 0;
}