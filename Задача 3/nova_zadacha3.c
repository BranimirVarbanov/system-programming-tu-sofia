#include <stdio.h>
#include <stdint.h>

//chistene na buffer
void clear_input_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

const uint8_t bcd_add_table[10][10] = {
    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09},
    {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10},
    {0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11},
    {0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12},
    {0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13},
    {0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14},
    {0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15},
    {0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16},
    {0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17},
    {0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18}
};

const uint8_t bcd_nine_complement[10] = {9,8,7,6,5,4,3,2,1,0};


//dali chisla sa ravni
int is_equal(int64_t number1, int64_t number2){
    return !(number1^number2);
}

//dali BCD-to e otricatelno
int is_BCD_negative (int64_t BCD_number){
    int last_digits = (BCD_number & 0xF000000000000000) >> 60;
    return last_digits == 0xF;
}

void print_BCD();
int64_t bitwise_BCD_add();
int64_t bitwise_BCD_subtract();

// + -> -
int64_t positive_to_negative_BCD(int64_t BCD_number){
    int64_t negative_result = bitwise_BCD_subtract(0x999999999, BCD_number);
    negative_result = bitwise_BCD_add(negative_result, 1);
    //print_BCD(BCD_number);
    //print_BCD(negative_result |= 0xF999999000000000);
    //printf("\n\n");
    return negative_result |= 0xF999999000000000;
}

// - -> +
int64_t negative_to_positive_BCD(int64_t BCD_number){
    BCD_number ^= 0xF999999000000000;
    //print_BCD(BCD_number);
    BCD_number = bitwise_BCD_subtract(BCD_number,1);
    //print_BCD(BCD_number);
    int64_t result = BCD_number;
    for(int shift = 0; shift < 9; shift++){
        int64_t digit = (BCD_number >> (shift * 4)) & 0xF;
        int64_t complement_digit = bcd_nine_complement[digit];

        result &= ~(0xFLL << (shift * 4));
        result |= (complement_digit & 0xF) << (shift * 4);
    }
    //print_BCD(result);
    return result;
}

//sravnqvane na BCD-ta
int compare_BCD_numbers(int64_t number1, int64_t number2){
    if(is_equal(number1, number2)) return 0; //ako sa ravni

    if(is_BCD_negative(number1) && !is_BCD_negative(number2))
        return -1;  //-x < y

    else if(!is_BCD_negative(number1) && is_BCD_negative(number2))
        return 1;   //x > -y

    else{ //ako imat ednakuv znak
        if(!is_BCD_negative(number1)){  //ako sa polojitelni
            for(int i = 36; i >= 0; i--){
                int bit1 = (number1 >> i) & 1;
                int bit2 = (number2 >> i) & 1;

                if(bit1 == 1 && bit2 == 0) return 1;
                if(bit1 == 0 && bit2 == 1) return -1;
            }
        }
        else{  //ako sa otricatelni
            number1 = negative_to_positive_BCD(number1);
            number2 = negative_to_positive_BCD(number2);

            for(int i = 36; i >= 0; i--){
                int bit1 = (number1 >> i) & 1;
                int bit2 = (number2 >> i) & 1;

                if(bit1 == 1 && bit2 == 0) return -1; //oburnati poneje sa otricatelni
                if(bit1 == 0 && bit2 == 1) return 1;
            }
        }
    }
}

//ot decimal do decimal-a na BCD-to
int64_t decimal_to_BCD(int64_t number1){
    int64_t BCD_number = 0;
    int is_negative = 0;
    int shift = 0;

    if(number1 < 0) {
        if(-number1 > 0x7FFFFFFFFFFFFFFF){
            printf("Overflow is detected! Your number will be assigned to the highest one!\n");
            number1 = 0x7FFFFFFFFFFFFFFF;
        }
        else{
            number1 = -number1;
        }
        is_negative = 1;
    }

    while(number1 > 0 && shift < 16) {
        int digit = number1 % 10;
        BCD_number |= ((int64_t)digit << (shift * 4));
        number1 /= 10;
        shift++;
    }

    if(is_negative)
        BCD_number = positive_to_negative_BCD(BCD_number);

    return BCD_number;
}

int64_t bitwise_BCD_add(int64_t BCD_number1, int64_t BCD_number2){
    int shift = 0;
    int64_t final_result = 0;
    int carry = 0;

    //printf("\n[DEBUG] Starting BCD Addition\n");

    while(shift < 9){
        int digit1 = (BCD_number1 >> (shift * 4)) & 0xF;
        int digit2 = (BCD_number2 >> (shift * 4)) & 0xF;

        int addition_result = bcd_add_table[digit1][digit2];
        int local_result = addition_result & 0xF;
        int local_carry = (addition_result >> 4) & 0xF;

        if(carry == 1){
            addition_result = bcd_add_table[local_result][1];
            local_result = addition_result & 0xF;
            local_carry += (addition_result >> 4) & 0xF;
        }

        if(local_result > 9){
            addition_result = bcd_add_table[local_result][6];
            local_result = addition_result & 0xF;
            local_carry = 1;  //ima carry
        }

        carry = local_carry ? 1 : 0;

        final_result |= ((int64_t)(local_result & 0xF)) << (shift * 4);

        //printf("[DEBUG] Shift: %d | Digit1: %d Digit2: %d | Result: %d | Carry: %d\n", shift, digit1, digit2, local_result, carry);

        shift++;
    }

    if(carry == 1){
        int addition_result = bcd_add_table[0][1];
        int extra_digit = addition_result & 0xF;
        final_result |= ((int64_t)extra_digit) << (shift * 4);
       //printf("[DEBUG] Extra carry added at position %d\n", shift);
    }

    //printf("[DEBUG] Final BCD Sum: ");
    //print_BCD(final_result);

    return final_result;
}



int64_t bitwise_BCD_subtract(int64_t BCD_number1, int64_t BCD_number2) {
    int64_t nine_complement = 0;
    int shift = 0;

    while(shift < 9){
        int64_t digit = (BCD_number2 >> (shift * 4)) & 0xF;
        int64_t complement_digit = bcd_nine_complement[digit];
        nine_complement |= (complement_digit << (shift * 4));
        shift++;
    }

    int64_t temp_sum = bitwise_BCD_add(BCD_number1, nine_complement);
    int64_t final_result = bitwise_BCD_add(temp_sum, 0x1);

    return final_result;
}

//vizualizirane na BCD-to
void print_BCD(int64_t BCD_number){
    printf("BCD: ");
    for(int i=63; i>=0; i--){
        printf("%d", (BCD_number >> i) & 1);
        if (i % 4 == 0 && i != 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int64_t BCD_to_decimal(int64_t BCD_number) {
    int is_negative = ((BCD_number >> 60) & 0xF) == 0xF;
    int64_t result = 0;
    int64_t multiplier = 1;

    if(is_negative) {
        BCD_number = negative_to_positive_BCD(BCD_number);
    }

    for(int i = 0; i < 9; i++) {
        int64_t digit = (BCD_number >> (i * 4)) & 0xF;
        result += digit * multiplier;
        multiplier *= 10;
    }

    if(is_negative)
        return -result;
    else
        return result;
}

//izvurshvane na BCD operacii; subirane + izvdajdane 4rez subirane + umnojenie 4rez subirane (stepeni na 10 i bitovo mestene)
int64_t BCD_operation(int64_t number1, int64_t number2, int option){
    int shift = 0;
    int64_t final_result = 0;
    int apply_negative = 0;
    int64_t operation_number1, operation_number2;

    //operation handler
    if(!is_BCD_negative(number1) && is_BCD_negative(number2)){ //(x,-y)
        number2 = negative_to_positive_BCD(number2); //(x,-y) -> (x,y)
        if(option == 3){ //pri subirane
            if(compare_BCD_numbers(number1, number2) == -1){ //[y] > [x] -> x-y = -(y-x)
                apply_negative = 1; //za dobavqne na minus
                operation_number1 = number2;
                operation_number2 = number1;
                option = 4; //operaciqta ot subirane stana izvajdane
            } else if(compare_BCD_numbers(number1, number2) == 1){ //[x] > [y] -> x-y
                operation_number1 = number1;
                operation_number2 = number2;
                option = 4;
            } else return 0LL; //[x] = [y]
        } else if(option == 4){ //pri izvajdane
            operation_number1 = number1; //x-(-y) = x+y
            operation_number2 = number2;
            option = 3;
        } else { //pri umnojenie
            apply_negative = 1; //x*(-y) = -(x*y)
            operation_number1 = number1;
            operation_number2 = number2;
        }
    }
    else if(is_BCD_negative(number1) && !is_BCD_negative(number2)){ //(-x,y)
        number1 = negative_to_positive_BCD(number1);
        if(option == 3){
            if(compare_BCD_numbers(number1, number2) == 1){ //-x+y -> [x]>[y] -> -(x-y) //(-3,2) -> -3+2 = -1 || -(3-2) = -1
                apply_negative = 1;
                operation_number1 = number1;
                operation_number2 = number2;
                option = 4;
            } else if(compare_BCD_numbers(number1, number2) == -1){ //[x] < [y] -> y //(-2,3) -> -2+3 = 1 || 3-2 = 1
                operation_number1 = number2;
                operation_number2 = number1;
                option = 4;
            } else return 0LL;
        } else if(option == 4){ //-x-y -> -(x+y)
            apply_negative = 1;
            operation_number1 = number1;
            operation_number2 = number2;
            option = 3;
        } else {
            apply_negative = 1;
            operation_number1 = number1;
            operation_number2 = number2;
        }
    }
    else if(is_BCD_negative(number1) && is_BCD_negative(number2)){ //(-x,-y)
        number1 = negative_to_positive_BCD(number1);
        number2 = negative_to_positive_BCD(number2);
        if(option == 3){ //-x-y = -(x+y)
            apply_negative = 1;
            operation_number1 = number1;
            operation_number2 = number2;
        } else if(option == 4){
            if(compare_BCD_numbers(number1, number2) == 1){ //-x+y -> [x] > [y] //(-5,-2) -> -5-(-2) = -5+2 = -3 -> -(5-2)
                apply_negative = 1;
                operation_number1 = number1;
                operation_number2 = number2;
            } else if(compare_BCD_numbers(number1, number2) == -1){ // [x] < [y] -> (-2,-5) -> -2-(-5) = 5-2
                operation_number1 = number2;
                operation_number2 = number1;
            } else return 0LL;
        } else {
            operation_number1 = number1;
            operation_number2 = number2;
        }
    }
    else { //(x,y)
        if(compare_BCD_numbers(number1, number2) == -1 && option == 4){ //[x] < [y] -> razmenqne
            apply_negative = 1;
            operation_number1 = number2;
            operation_number2 = number1;
        } else {
            operation_number1 = number1;
            operation_number2 = number2;
        }
    }


    if(option == 3){ //subirane
        int64_t final_result = bitwise_BCD_add(operation_number1, operation_number2);

        if(apply_negative)
            return positive_to_negative_BCD(final_result);
        else
            return final_result;
    }


    //operation handler -> izvdajdaneto e 4rez polojitelni chisla, kato pri num1 - num2 -> num1 > num2 -> samo 9's complement + 1
    else if(option == 4){ //izvajdane
        int64_t final_result = bitwise_BCD_subtract(operation_number1, operation_number2);

        if(apply_negative)
            return positive_to_negative_BCD(final_result);
        else
            return final_result;
    }


    else{ //umnojenie
        for (int i = 4; i < 16; i++) { //dali chisloto 4-cifreno
            if (((operation_number1 >> (i * 4)) & 0xF) != 0 ||
                ((operation_number2 >> (i * 4)) & 0xF) != 0) {
                printf("\nError: Multiplication supports only up to 4-digit numbers!\n");
                return 0;
            }
        }

        int64_t result = 0;

        for(int i = 0; i < 4; i++){
            int digit = (operation_number2 >> (i * 4)) & 0xF;
            if(digit == 0) continue;

            int64_t partial = 0;
            for(int j = 0; j < digit; j++) {
                partial = bitwise_BCD_add(partial, operation_number1);
            }

            int64_t shifted_partial = partial << (i * 4);
            result = bitwise_BCD_add(result, shifted_partial);
        }

        if(apply_negative)
            return positive_to_negative_BCD(result);
        else
            return result;
    }
}

void print_HEX(int64_t BCD_number) {
    uint64_t mask = 0xF000000000000000;
    int shift = 60;
    int lead_zero = 1;

    printf("HEX: 0x");

    for (int i = 0; i < 16; i++) {
        uint8_t digit = (BCD_number & mask) >> shift;

        if (digit != 0 || !lead_zero || i == 15) {
            lead_zero = 0;
            if (digit < 10)
                printf("%d", digit);
            else
                printf("%c", 'A' + digit - 10);
        }

        mask >>= 4;
        shift -= 4;
    }

    printf("\n");
}

void print_binary(int64_t BCD_number) {
    printf("\nBinary: ");
    for (int i = 63; i >= 0; i--) {
        printf("%d", (BCD_number >> i) & 1);
        if (i % 4 == 0 && i != 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void print_result(int64_t result_bcd){
    printf("Decimal: %lld\n", BCD_to_decimal(result_bcd));
    print_BCD(result_bcd);
    //print_HEX(result_bcd); //ako ima nujda ot HEX
    printf("\n");
}

int main(){

    int64_t number1 = 0, number2 = 0;
    int64_t bcd1 = 0;
    int64_t bcd2 = 0;

    while(1){
        printf("\nMenu:\n");
        printf("1) Enter Number#1\n");
        printf("2) Enter Number#2\n");
        printf("3) Number#1 + Number#2\n");
        printf("4) Number#1 - Number#2\n");
        printf("5) Number#1 * Number#2\n");
        printf("6) Compare Number#1 and Number#2\n");
        printf("7) Exit\n\n");
        printf("Select an option: ");

        int option;
        while(scanf("%d",&option) != 1)
        {
            clear_input_buffer();
            printf("Please enter a number!\n\n");
            printf("Select an option: ");
            if(scanf("%d",&option) == 1) break;
        }

        int is_number_valid = 0;
        switch(option){
        case 1:
            //vuvejdane na purvo chislo
            printf("\nEnter Number#1: ");
            is_number_valid = scanf("%lld",&number1);
            if(is_number_valid && (number1 > 99999999 || number1 < -99999999)){
                printf("\nPlease enter number which is not higher than 8-digit!\n");
                break;
            }
            else if(is_number_valid != 1){
                clear_input_buffer();
                printf("\nInvalid number!\n");
                break;
            }
            else{
                bcd1 = decimal_to_BCD(number1);
                print_binary(number1);
                print_HEX(bcd1);
                print_BCD(bcd1);
                break;
            }

        case 2:
            //vuvejdane na vtoro chislo
            printf("\nEnter Number#2: ");
            is_number_valid = scanf("%lld",&number2);
            if(is_number_valid && (number2 > 99999999 || number2 < -99999999)){
                printf("\nPlease enter number which is not higher than 8-digit!\n");
                break;
            }
            else if(is_number_valid != 1){
                clear_input_buffer();
                printf("\nInvalid number!\n");
                break;
            }
            else{
                bcd2 = decimal_to_BCD(number2);
                print_binary(number2);
                print_HEX(bcd2);
                print_BCD(bcd2);
                break;
            }

        case 3:
            //subirane
            printf("\nFinal result: \n\n");
            print_result(BCD_operation(bcd1, bcd2, option));
            break;

        case 4:
            //izvajdane
            printf("\nFinal result: \n\n");
            print_result(BCD_operation(bcd1, bcd2, option));
            break;

        case 5:
            //umnojenie
            printf("\nFinal result: \n\n");
            print_result(BCD_operation(bcd1, bcd2, option));
            break;

        case 6:
            //sravnenie
            printf("\nComparison result: \n");
            int cmp = compare_BCD_numbers(bcd1, bcd2);
            if(cmp == 1)
                printf("Number#1 > Number#2\n");
            else if(cmp == -1)
                printf("Number#1 < Number#2\n");
            else
                printf("Number#1 = Number#2\n");
            break;

        case 7:
            //izhod
            printf("\nGoodbye!\n");
            return 0;

        default:
            //nevaliden izbor
            printf("Invalid option! Enter number from 1 to 7.\n\n");
        }
    }
    /*int n1 = 99999999, n2 = -99999999;
    int64_t BCD1 = decimal_to_BCD(n1);
    int64_t BCD2 = decimal_to_BCD(n2);
    print_BCD(BCD1);
    printf("Decimal: %lld\n\n", BCD_to_decimal(BCD1));
    print_BCD(BCD2);
    printf("Decimal: %lld\n\n", BCD_to_decimal(BCD2));
    //printf("\n");
    int64_t result = BCD_operation(BCD1, BCD2, 4);
    print_BCD(result);
    printf("Decimal result: %lld\n\n", BCD_to_decimal(result));*/
    //printf("MAX INT64_T: %lld\n", 0x7FFFFFFFFFFFFFFF);
    //printf("MIN INT64_T: %lld\n", 0x8000000000000000);
    return 0;
}
