#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <limits.h>

struct Queue {
    int element_[12];
    unsigned int head_;
    unsigned int tail_;
} queue = {.head_ = 1, .tail_ = 1};

void print(struct Queue* q) {
    unsigned int ref = q->head_;
    unsigned int length = sizeof(q->element_) / sizeof(int) - 2;
    while (ref != q->tail_) {
        if (ref == length + 1) {
            ref = 1;
        }
        if (ref == q->tail_) break;
        printf("%d", q->element_[ref]);
        ref++;
    }
    printf("\n");
}

void print_realstate(struct Queue* q) {
    unsigned int length = sizeof(q->element_) / sizeof(int) - 2;
    for (int i = 1; i <= length; ++i) {
        if (q->tail_ >= q->head_ && (i < q->head_ || i >= q->tail_)) {
            printf("* ");
        } else if (q->tail_ >= q->head_ && (i >= q->head_ && i < q->tail_)) {
            printf("%d", q->element_[i]);
        } else if (q->tail_ < q->head_ && (i >= q->tail_ && i < q->head_)) {
            printf("* ");
        } else {
            printf("%d", q->element_[i]);
        }
    }
    printf("\n");
}

bool check_queue_empty(struct Queue* q) {
    return (q->head_ == q->tail_);
}

bool check_queue_full(struct Queue* q) {
    unsigned int length = sizeof(q->element_) / sizeof(int) - 2;
    return (q->head_ == q->tail_ % (length + 1) + 1);
}

void enqueue(struct Queue* q, int x) {
    unsigned int length = sizeof(q->element_) / sizeof(int) - 2;
    if (check_queue_full(q)) {
        assert(-1);
        printf("FULL");
    } else {
        q->element_[q->tail_] = x;
        if (q->tail_ == length + 1) {
            q->tail_ = 1;
        } else {
            q->tail_++;
        }
    }
    print(q);
    print_realstate(q);
}

int dequeue(struct Queue* q) {
    unsigned int length = sizeof(q->element_) / sizeof(int) - 2;
    int x = 0;
    if (check_queue_empty(q)) {
        assert(-1);
        printf("EMPTY");
        return INT_MIN;
    } else {
        x = q->element_[q->head_];
        if (q->head_ == length + 1) {
            q->head_ = 1;
        } else {
            q->head_++;
        }
    }
    print(q);
    print_realstate(q);
    return x;
}

int main() {
    for (int i = 1; i <= 20)
    return 0;
}