/*
 * 在符号表 symbol table 中没有 找到var这个符号 ??? 局部变量不会被别的模块链接所以不需要记录？？
 */
int global_var = 100;

int main() {
    static int static_var = 200;
    int var = 300;
    
    return 0;
}
