#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define BIG_INTEGER_MAX 1000

typedef struct {
    int storage_[BIG_INTEGER_MAX];  // Only storage pure number!
    unsigned int size_;             // The length of pure number string.
    bool is_postive_;

} BigIntegerPrivate;

typedef struct {
    bool (*isGreaterThan)(void* this, void* another);
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
    char print_string[size + 1];
    for (int i = size - 1; i >= 1; --i) {
        print_string[i] = storage_ptr[size - i - 1] + '0';
    }
    print_string[size] = '\0';
    printf("%s", print_string);
}

bool BigIntegerPublicIsGreaterThanImpl(void* this, void* another) {
    return true;
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

    obj->isGreaterThan = BigIntegerPublicIsGreaterThanImpl;
    obj->print = BigIntegerPrivatePrintImpl;

    // Public methods.

    obj->private_ = private;

    // Private methods.
    return obj;
}

int main(int argc, const char* argv[]) {
    char test_str[] = "1234";
    printf("%lu", sizeof(test_str) / sizeof(char));
    BigInteger* test = BigIntegerConstructor(test_str, sizeof(test_str) / sizeof(char));
    printf("Test!");
    test->print(test);
}