#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>

namespace unit_tests {

template<typename T>
void compare(const T& actual, const T& expected, const char* actual_s, const char* expected_s, const char* file, int line)
{
    std::cout << (actual == expected ? "OK" : "FAILED") << "\t" << file << ":" << line << "\t(" << actual_s << " == " << expected_s << ")\tActual (" << actual << ") Expected (" << expected << ")\n";
}

} // namespace unit_tests

#define COMPARE(actual, expected) unit_tests::compare(actual, expected, #actual, #expected, __FILE__, __LINE__)

bool operators_compare(char a, char b)
{
    static std::vector<char> order = { '-', '+', '*', '/' };
    auto ait = std::find(std::begin(order), std::end(order), a);
    auto bit = std::find(std::begin(order), std::end(order), b);
    return ait < bit;
}

int evaluate(auto begin, auto end)
{
    if (*begin == '(' && *std::prev(end) == ')') {
        ++begin;
        --end;
    }

    auto it = begin;
    auto op = begin;

    std::stack<char> stack;

    for (; it != end; ++it) {
        if (*it == '(')
            stack.push(*it);
        else if (*it == ')')
            stack.pop();
        else if (stack.empty() && it != end && !std::isdigit(*it) && operators_compare(*it, *op))
            op = it;
    }

    int left = 0, right = 0;

    if (std::distance(begin, op) > 1)
        left = evaluate(begin, op);
    else
        left = *std::prev(op) - '0';

    if (std::distance(std::next(op), end) > 1)
        right = evaluate(std::next(op), end);
    else
        right = *std::next(op) - '0';

    switch(*op) {
        case '+': return left + right;
        case '-': return left - right;
        case '/': return left / right;
        case '*': return left * right;
        default: return 0;
    }

    return 0;
}


void simple_test()
{
    std::string expression = "4+3*(5-1)-8/2";
    COMPARE(evaluate(std::begin(expression), std::end(expression)), 12);

    expression = "((2-3)*3/3+5)/4";
    COMPARE(evaluate(std::begin(expression), std::end(expression)), 1);
}

int main(int argc, char *argv[])
{
    simple_test();
    return 0;
}
