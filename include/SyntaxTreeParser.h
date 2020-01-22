#pragma once

#include <string>
#include <unordered_map>
#include <stack>
#include <memory>

/// Status of parsing and evaluating
struct SyntaxTreeStatus {
    /// if expression is valid based on rules defined
    bool valid = false;

    /// numeric value of expression
    int Value = 0;
};

/// Abstract Syntax Tree Node
struct SyntaxTreeNode
{
    /// left and right child in case of operand, literals are leafs and have both set to null
    std::shared_ptr<SyntaxTreeNode> left, right;

    /// value of node - can be literal or operand
    char value;

    /// Constructor for node
    /// \param v value of node - can be operand or literal
    explicit SyntaxTreeNode(char v) : value(v) {}
};

/// Syntax parser class to be used as proxy to parsing and evaluating
class SyntaxTreeParser {
public:
    /// Constructor, marked as explicit to avoid unintentional use of it
    /// \param expr aritmetic expression to be used
    explicit SyntaxTreeParser(std::string expr) : expression(std::move(expr)) {};

    /// Evaluetes given expression
    /// \return status of evaluation
    SyntaxTreeStatus evaluate();

private:
    /// Creates syntax tree based on expression
    /// \return is expression valid
    bool createSyntaxTree();

    /// Attaches top operator from operators to top 2 nodes from tree node
    /// \param treeNodes syntax tree nodes
    /// \param operators operator nodes
    /// \return if operation can be executed, if false expression is invalid
    bool attachOperator(std::stack<std::shared_ptr<SyntaxTreeNode>>& treeNodes,
                        std::stack<std::shared_ptr<SyntaxTreeNode>>& operators);

    /// Calculate priority of operator
    /// \param op operator as char
    /// \return priority (greater first)
    static inline int precedence(char op);

    /// Calculates result of binary operation
    /// \param a first literal
    /// \param b second literal
    /// \param op operator to be applied
    /// \return a op b
    static int binaryOpRes(int a, int b, char op);

    /// Checks if char is valid operator
    /// \param c operator as char
    /// \return true if operator is valid binary operator
    static inline bool isBinaryOp(char c);

    /// Recursive function to evaluate valid expression value
    /// \param node root node of syntax tree
    /// \return value of expression
    static int evaluateTree(std::shared_ptr<SyntaxTreeNode> node);

    /// given expression
    std::string expression;

    /// syntax tree root node
    std::shared_ptr<SyntaxTreeNode> root;
};
