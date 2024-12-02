#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define BIG_INTEGER_MAX 1000

typedef struct {
    int storage_[BIG_INTEGER_MAX];  // Only storage pure number!
    unsigned int size_;             // The length of pure number string.
    bool is_postive_;

} BigIntegerPrivate;

typedef struct {
    bool (*isEqual)(void* this, void* another);
    bool (*isGreaterThan)(void* this, void* another);
    bool (*isLessThan)(void* this, void* another);
    bool (*isEqualOrGreaterThan)(void* this, void* another);
    bool (*isEqualOrLessThan)(void* this, void* another);
    bool (*isNotEqual)(void* this, void* another);

    void (*print)(void* this);

    BigIntegerPrivate* private_;
} BigInteger;


/**
 * @program:     BigInteger_Private_Print_Implication function.
 * @description: Print the BigInteger.
 * @this:        Pointer to the object itself.
 */
void BigIntegerPrivatePrintImpl(void* this) {
    BigInteger* obj = (BigInteger*)this;
    int size = obj->private_->size_ + 1;

    // Don't worry aboubt '+', '-', or '\0', this size is the length of real
    // length of pure number string!

    int* storage_ptr = obj->private_->storage_;
    char* print_string = (char*)malloc(sizeof(char) * (size + 1));
    
    // Use the standard C, not GCC!

    for (int i = size - 1; i >= 1; --i) {
        print_string[i - 1] = storage_ptr[size - i - 1] + '0';
    }
    print_string[size] = '\0';
    printf("%s", print_string);
}

/**
 * @program:     BigInteger_Public_isEqual_Implication function.
 * @description: Similar to C++ operator == function. O(n)
 * @this:        Pointer to object itself.
 * @another:     Pointer to another object.
 */
bool BigIntegerPublicIsEqualImpl(void* this, void* another) {
    BigInteger* obj_this = (BigInteger*)this;
    BigInteger* obj_another = (BigInteger*)another;

    if (obj_this->private_->size_ != obj_another->private_->size_) {
        return false; // If size is not equal, then they are not equal.
    } else if (obj_this->private_->is_postive_ != obj_another->private_->is_postive_) {
        return false; // If sign is not equal, then they are not equal.
    } else {
        for (int i = 0; i <= obj_this->private_->size_ - 1; ++i) {
            if (obj_this->private_->storage_[i] != obj_another->private_->storage_[i]) {
                return false;
            }
        }
        return true;
    }
}

/**
 * @program:     BigInteger_Public_isGreaterThan_Implication function.
 * @description: Similar to C++ operator > function. O(n))
 * @this:        Pointer to object itself.
 * @another:     Pointer to another object.
 */
bool BigIntegerPublicIsGreaterThanImpl(void* this, void* another) {
    BigInteger* obj_this = (BigInteger*)this;
    BigInteger* obj_another = (BigInteger*)another;

    bool ispos_1 = obj_this->private_->is_postive_;
    bool ispos_2 = obj_another->private_->is_postive_;
    unsigned int size_1 = obj_this->private_->size_;
    unsigned int size_2 = obj_another->private_->size_;
    int* storage_1 = obj_this->private_->storage_;
    int* storage_2 = obj_another->private_->storage_;

    unsigned int count = 0;

    if (ispos_1 && ispos_2 && size_1 < size_2) {
        return false;   // a,b > 0, len(a) < len(b) => a < b
    } else if (ispos_1 && ispos_2 && size_1 > size_2) {
        return true;    // a,b > 0, len(a) > len(b) => a > b
    } else if (!ispos_1 && !ispos_2 && size_1 > size_2) {
        return true;    // a,b < 0, len(a) < len(b) => a > b
    } else if (!ispos_1 && !ispos_2 && size_1 < size_2) {
        return false;   // a,b < 0, len(a) > len(b) => a < b
    } else if (!ispos_1 && ispos_2) {
        return false;   // a < 0, b > 0
    } else if (ispos_1 && !ispos_2) {
        return true;    // a > 0, b < 0
    } else if (size_1 == size_2) {
        for (int i = size_1 - 1; i >= 0; i--) {
            if (storage_1[i] < storage_2[i]) {
                return false;
            } else if (storage_1[i] == storage_2[i]) {
                count++;
            } else {
                return true;
            }
        }
        return !(count == size_1);
    }
    return false;   // It will never be executed.
}

/**
 * @program:     BigInteger_Public_isLessThan_Implication function.
 * @description: Similar to C++ operator < function. O(n))
 * @this:        Pointer to object itself.
 * @another:     Pointer to another object.
 */
bool BigIntegerPublicIsLessThanImpl(void* this, void* another) {
    return !(BigIntegerPublicIsEqualImpl(this, another) 
          || BigIntegerPublicIsGreaterThanImpl(this, another));
}

/**
 * @program:     BigInteger_Public_isEqualOrGreaterThan_Implication function.
 * @description: Similar to C++ operator >= function. O(n))
 * @this:        Pointer to object itself.
 * @another:     Pointer to another object.
 */
bool BigIntegerPublicIsEqualOrGreaterThanImpl(void* this, void* another) {
    return BigIntegerPublicIsEqualImpl(this, another)
        || BigIntegerPublicIsGreaterThanImpl(this, another);
}

/**
 * @program:     BigInteger_Public_isEqualOrLess_Implication function.
 * @description: Similar to C++ operator <= function. O(n))
 * @this:        Pointer to object itself.
 * @another:     Pointer to another object.
 */
bool BigIntegerPublicIsEqualOrLessThanImpl(void* this, void* another) {
    return BigIntegerPublicIsEqualImpl(this, another)
        || BigIntegerPublicIsLessThanImpl(this, another);
}

/**
 * @program:     BigInteger_Public_isNotEqual_Implication function.
 * @description: Similar to C++ operator != function. O(n))
 * @this:        Pointer to object itself.
 * @another:     Pointer to another object.
 */
bool BigIntegerPublicIsNotEqualImpl(void* this, void* another) {
    return !BigIntegerPublicIsEqualImpl(this, another);
}

/**
 * @program:     BigInteger_Constructor.
 * @description: Constructor of class BigInteger.
 * @str:         The origin string of a BigInteger object.
 * @size:        Please use sizeof(str) / sizeof(char) to calculate the size of string,
 *               notice that it will return the length of **C-Style** string, such as
 *                  ['+', '1', '0', '9', '\0'] => len = 5.
 */
BigInteger* BigIntegerConstructor(const char* str, int size) {
    BigInteger* obj = (BigInteger*)malloc(sizeof(BigInteger));
    BigIntegerPrivate* private = (BigIntegerPrivate*)malloc(sizeof(BigIntegerPrivate));

    // allocate the memory

    if (obj == NULL || private == NULL) {
        fprintf(stderr, "BigInteger memory allocation failed!\n");
        exit(1);
    }

    int has_signed;
    if (str[0] == '+') {
        has_signed = 1;
        private->is_postive_ = true;
        private->size_ = size - 2;
        
        // The size involves '+' or '-' and '\0'

    } else if (str[0] == '-') {
        has_signed = 1;
        private->is_postive_ = false;
        private->size_ = size - 2;
    } else {
        has_signed = 0;
        private->is_postive_ = true;
        private->size_ = size - 1;
        
        // The size only involves '\0'
        // When there is no sign, we consider the BigInteger is positive by default.
    }

    for (int i = 0; i <= size - has_signed - 2; ++i) {
        private->storage_[i] = str[size - i - 2] - '0';

        // has_signed = 1, size = 4, i <= 1
        // ['+',       '1',          '2',         '\0']
        //              ^             ^
        // size(4) - i(1) - 2        size(4) - i(0) - 2
    }

    obj->isEqual              = BigIntegerPublicIsEqualImpl;
    obj->isGreaterThan        = BigIntegerPublicIsGreaterThanImpl;
    obj->isLessThan           = BigIntegerPublicIsLessThanImpl;
    obj->isEqualOrGreaterThan = BigIntegerPublicIsEqualOrGreaterThanImpl; 
    obj->isEqualOrLessThan    = BigIntegerPublicIsEqualOrLessThanImpl;
    obj->isNotEqual           = BigIntegerPublicIsNotEqualImpl;
    obj->print                = BigIntegerPrivatePrintImpl;

    // Public methods.

    obj->private_ = private;

    // Private methods.
    return obj;
}

// --------------------- TEST  --------------------- 

typedef struct {
    char* str;
    unsigned int len;
} String;

int main(int argc, const char* argv[]) {
    printf("------------------- VALID -------------------\n");

    String str_valid[] = {
        {"++++123"}
    };

    printf("------------------- COMPARISION -------------------\n");

    String str_comparision[] = {   // A pair for comparision
        {"1234", strlen("1234") + 1}, {"+1234", strlen("+1234") + 1},
    };

    size_t len_comparision = sizeof(str_comparision) / sizeof(String);

    for (int i = 0; i <= len_comparision - 2; ++i) {
        BigInteger* big_a = BigIntegerConstructor(str_comparision[i].str, str_comparision[i].len);
        BigInteger* big_b = BigIntegerConstructor(str_comparision[i + 1].str, str_comparision[i + 1].len);
        printf("---- %s %s ----\n", str_comparision[i].str, str_comparision[i + 1].str);
        printf("a >  b : %d\n", (int)big_a->isGreaterThan(big_a, big_b));
        printf("a <  b : %d\n", (int)big_a->isLessThan(big_a, big_b));
        printf("a == b : %d\n", (int)big_a->isEqual(big_a, big_b));
        printf("a != b : %d\n", (int)big_a->isNotEqual(big_a, big_b));
        printf("a <= b : %d\n", (int)big_a->isEqualOrLessThan(big_a, big_b));
        printf("a >= b : %d\n", (int)big_a->isEqualOrGreaterThan(big_a, big_b));
    }

}