#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

struct Stack {
    int element_[100];
    int top_;
} stack = {.top_ = 0};

void print(struct Stack* s) {
    for (int i = 1; i <= s->top_; ++i) {
        printf("%d ", s->element_[i]);
    }
    printf("\n");
}

bool check_stack_empty(struct Stack* s) {
    return (s->top_ == 0);
}

bool check_stack_full(struct Stack* s) {
    return (s->top_ == sizeof(s->element_) / sizeof(int));
}

void push(struct Stack* s, int x) {
    if (check_stack_full(s)) {
        assert(-1);
        printf("FULL\n");
    } else {
        s->top_++;
        s->element_[s->top_] = x;
        print(s);
    }
}

int pop(struct Stack* s) {
    if (check_stack_empty(s)) {
        assert(-1);
        printf("EMPTY\n");
        return INT_MIN;
    } else {
        s->top_--;
        print(s);
        return s->element_[s->top_ + 1];
    }
}

void clear(struct Stack* s) {
    s->top_ = 0;
}



int main() {
    srand(time(NULL));
    for (int i = 1; i <= 12; ++i) {
        push(&stack, rand() % 10);
    }
    for (int i = 1; i <= 15; ++i) {
        pop(&stack);
    }
    return 0;
}

