int romanToInt(char* s) {
    int total = 0;
    int i;
    int value = 0;
    for(i = 0; s[i]; ++i) {
        switch (s[i]) {
            case 'I':
                switch (s[i + 1]) {
                    case 'V':
                        value = 4;
                        ++i;
                        break;
                    case 'X':
                        value = 9;
                        ++i;
                        break;
                    default:
                        value = 1;
                }
                break;
            case 'V':
                value = 5;
                break;
            case 'X':
                  switch (s[i + 1]) {
                    case 'L':
                        value = 40;
                        ++i;
                        break;
                    case 'C':
                        value = 90;
                        ++i;
                        break;
                    default:
                        value = 10;
                }
                break;
            case 'L':
                value = 50;
                break;
            case 'C':
               switch (s[i + 1]) {
                    case 'D':
                        value = 400;
                        ++i;
                        break;
                    case 'M':
                        value = 900;
                        ++i;
                        break;
                    default:
                        value = 100;
                }
                break;
            case 'D':
                value = 500;
                break;
            case 'M':
                value = 1000;
                break;
        }
        total += value;
    }
    return total;
}
