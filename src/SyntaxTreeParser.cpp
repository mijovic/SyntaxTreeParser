#include <SyntaxTreeParser.h>
#include <iostream>

// calculates priority for given operator
// if operator is invalid 0 will be returned
int SyntaxTreeParser::precedence(char op)
{
    if (op == '*' || op == '/') return 2;
    else if (op == '+' || op == '-') return 1;
    else return 0;
};

// does parsing and evaluating of given expression
SyntaxTreeStatus SyntaxTreeParser::evaluate()
{
    if (createSyntaxTree()) return { true, evaluateTree(root) };
    return { false, 0 };
}

// parses given expression and creates syntax tree
bool SyntaxTreeParser::createSyntaxTree()
{
    std::stack<char> input;
    for (const auto& c: expression)
    {
        if (!isspace(c)) input.push(c);
    }

    char temp;
    std::stack<std::shared_ptr<SyntaxTreeNode>> treeNodes;
    std::stack<std::shared_ptr<SyntaxTreeNode>> operators;

    while (!input.empty())
    {
        temp = input.top();
        input.pop();

        if (isdigit(temp)) treeNodes.push(std::make_shared<SyntaxTreeNode>(temp));
        else if (temp == ')') operators.push(std::make_shared<SyntaxTreeNode>(temp));
        else if (isBinaryOp(temp))
        {
            if (input.empty() || isBinaryOp(input.top())) return false;
            bool pushed = false;
            while(!pushed)
            {
                if (operators.empty())
                {
                    operators.push(std::make_shared<SyntaxTreeNode>(temp));
                    pushed = true;
                }
                else if (operators.top()->value ==')')
                {
                    operators.push(std::make_shared<SyntaxTreeNode>(temp));
                    pushed = true;
                }
                else if (precedence(temp) >= precedence(operators.top()->value))
                {
                    operators.push(std::make_shared<SyntaxTreeNode>(temp));
                    pushed = true;
                }
                else if (!attachOperator(treeNodes,operators)) return false;
            }
        }
        else if (temp == '(')
        {
            while (!operators.empty() && operators.top()->value != ')')
            {
                if(!attachOperator(treeNodes, operators)) return false;
            }
            if (operators.empty()) return false;
            operators.pop();
        }
        else return false;
    }

    while(!operators.empty())
    {
        if (!attachOperator(treeNodes, operators)) return false;
    }

    root = treeNodes.top();
    return (treeNodes.size() == 1);
}


// if node is literal just return it
// if node is operator return eval(left) op eval(right)
int SyntaxTreeParser::evaluateTree(std::shared_ptr<SyntaxTreeNode> node)
{
    int first, second, result;
    if (isBinaryOp(node->value))
    {
        first = evaluateTree(node->left);
        second = evaluateTree(node->right);
        result = binaryOpRes(first, second, node->value);
        return result;
    }
    else return node->value - '0';
}

// pops operator from a stack
// builds tree node with the top two nodes in the
// treeNode stack as its left and right children.
bool SyntaxTreeParser::attachOperator(std::stack<std::shared_ptr<SyntaxTreeNode>>& treeNodes,
    std::stack<std::shared_ptr<SyntaxTreeNode>>& operators)
{
    if (operators.empty() || treeNodes.size() < 2) return false;

    auto operatorNode = operators.top();
    operators.pop();
    operatorNode->left = treeNodes.top();
    treeNodes.pop();
    operatorNode->right = treeNodes.top();
    treeNodes.pop();
    treeNodes.push(operatorNode);

    return true;
}

// Calculates a op b
int SyntaxTreeParser::binaryOpRes(int a, int b, char op)
{
    int res = 0;
    switch (op) {
        case '+': res = a + b; break;
        case '-': res = a - b; break;
        case '*': res = a * b; break;
        case '/': res = a / b; break;
        default: break;
    }
    return res;
}

// checks if op is valid binary operator
// as all legal operators are defined in precedence we can check if value of precedence is valid
bool SyntaxTreeParser::isBinaryOp(char op)
{
    return precedence(op) > 0;
}