#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stack>

/* 汉诺塔：ABC三个塔，A塔中的盘移动到C塔所需要的最小步数，唯一的要求是大盘不能叠在小盘的上面，也就是盘的顺序是大的在下小的在上，
 * ABC可以随意移动，符合规则就行
 * 汉诺塔问题改进的题目，现在要求盘的移动只能想临移动，比如A->B,B->C 不能直接A->C
 *
 * */

const char* LEFT  = "left ";
const char* MID   = "mid  ";
const char* RIGHT = "right";
//const char* FORMATSHOW = "Move %d FROM %s TO %s\n";
const char* FORMATSHOW = "Move %d %s -> %s\n";

int equal(const char* a, const char* b) {
    return strcmp(a, b) == 0 ? 1 : 0;
}

int hanoix(int stage, const char* left, const char* mid, const char* right, const char* from, const char* to) {
    if (1 == stage) {
        if (equal(from, MID) || equal(to, MID)) {
            printf(FORMATSHOW, 1, from, to);
            return 1;
        } else {
            printf(FORMATSHOW, 1, from, mid);
            printf(FORMATSHOW, 1, mid, to);
            return 2;
        }
    }

    if (equal(from, MID) || equal(to, MID)) {
        const char* another = (equal(from, LEFT) || equal(to, LEFT)) ? RIGHT : LEFT;
        int part1 = hanoix(stage - 1, left, mid, right, from, another);
        
        int part2 = 1;
        printf(FORMATSHOW, stage, from, to);

        int part3 = hanoix(stage - 1, left, mid, right, another, to);
        return part1 + part2 + part3;
    } else {
        int part1 = hanoix(stage - 1, left, mid, right, from, to);
        
        int part2 = 1;
        printf(FORMATSHOW, stage, from, mid);

        int part3 = hanoix(stage - 1, left, mid, right, to, from);

        int part4 = 1;
        printf(FORMATSHOW, stage, mid, to);

        int part5 = hanoix(stage - 1, left, mid, right, from, to);
        return part1 + part2 + part3 + part4 + part5;
    }
}


int hanoi(int stage, const char* left, const char* mid, const char* right, const char* from, const char* to) {
    if (1 == stage) {
        printf(FORMATSHOW, 1, from, to);
        return 1;
    }

    const char* another;
    if (!equal(from, LEFT) && !equal(to, LEFT)) {
        another = LEFT;
    } else if (!equal(from, MID) && !equal(to, MID)) {
        another = MID;
    } else {
        another = RIGHT;
    }

    int part1 = hanoix(stage - 1, left, mid, right, from, another);

    int part2 = 1;
    printf(FORMATSHOW, stage, from, to);

    int part3 = hanoix(stage - 1, left, mid, right, another, to);
    return part1 + part2 + part3;
}


enum action {
    NONE = 0,
    LTOM = 1,
    MTOL = 2,
    MTOR = 3,
    RTOM = 4
};
int fstack_to_ttack(action& record, action preact, action nowact,
    std::stack<int>& fstack, std::stack<int>& tstack, const char* from, const char* to) {
    if (record != preact && fstack.top() < tstack.top()) {
        tstack.push(fstack.top());
        fstack.pop();
        printf(FORMATSHOW, tstack.top(), from, to);
        record = nowact;
        return 1;
    }
}

int hanoixloop(int num, const char* left, const char* mid, const char* right) {
    std::stack<int> ls;
    std::stack<int> ms;
    std::stack<int> rs;
    ls.push(INT_MAX);
    ms.push(INT_MAX);
    rs.push(INT_MAX);
    for (int i = num; i > 0; --i) {
        ls.push(i);
    }

    action record= NONE;
    int step = 0;
    while (rs.size() != num+1) {
        step += fstack_to_ttack(record, MTOL, LTOM, ls, ms, left, mid);
        step += fstack_to_ttack(record, LTOM, MTOL, ms, ls, mid, left);
        step += fstack_to_ttack(record, RTOM, MTOR, ms, rs, mid, right);
        step += fstack_to_ttack(record, MTOR, RTOM, rs, ms, right, mid);
    }
    return step;
}


int main() {

    //printf("hanoix=%d\n", hanoix(3, LEFT, MID, RIGHT, LEFT, RIGHT));
    printf("hanoix=%d\n", hanoix(1, LEFT, MID, RIGHT, LEFT, RIGHT));

    printf("hanoi=%d\n", hanoi(1, LEFT, MID, RIGHT, LEFT, RIGHT));

    printf("hanoix=%d\n", hanoix(2, LEFT, MID, RIGHT, LEFT, RIGHT));
    printf("hanoixloop=%d\n", hanoixloop(2, LEFT, MID, RIGHT));
    printf("hanoi=%d\n", hanoi(2, LEFT, MID, RIGHT, LEFT, RIGHT));



    return 0;
}



