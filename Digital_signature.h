//
// Created by bayk on 18.11.2021.
//

#ifndef COURSE_PROJECT_DIGITAL_SIGNATURE_H
#define COURSE_PROJECT_DIGITAL_SIGNATURE_H

#include <string>

/*
 * В RSA e и n являютня открытым ключом, но в ЭЦП наоборот. e, n - секретный ключ, d, n - открытый ключ
 */

class Digital_signature {
    std::string e, d, n;
    std::string system_e = "b0ed6dd2537173267eb1686f0cc166e1", // можно поменять эти значения, так как они расчитаны на size = 256, но так работает быстро
                system_d = "4c5bb0be7a3e6face887d988da63a321",
                system_n = "b0ed6dd2537173282a186570203ede31"; // это системные переменные, которые нужны для создания и проверки сертификатов
public:
    Digital_signature();
};

#endif //COURSE_PROJECT_DIGITAL_SIGNATURE_H
