#include <doctest.h>
#include <SyntaxTreeParser.h>

TEST_CASE("InvlidInput")
{
    SUBCASE("InvalidLiteral")
    {
        SyntaxTreeParser tree("1+10-2");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(status.Valid);
    }

    SUBCASE("UnaryMinus")
    {
        SyntaxTreeParser tree("-1+1+2");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(status.Valid);
    }

    SUBCASE("InvalidExpression")
    {
        SyntaxTreeParser tree("1+10+-2");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(status.Valid);
    }

    SUBCASE("UnpairedBrackets1")
    {
        SyntaxTreeParser tree("((1+1) * 2 - 2");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(status.Valid);
    }

    SUBCASE("UnpairedBrackets2")
    {
        SyntaxTreeParser tree("(1+1) * 2) - 2");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(status.Valid);
    }

    SUBCASE("InvalidOperand")
    {
        SyntaxTreeParser tree("(1+1) * 2 % 2");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(status.Valid);
    }

    SUBCASE("EndingInOperand")
    {
        SyntaxTreeParser tree("(1+1)*2+");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(status.Valid);
    }

    SUBCASE("SingleIllegalLiteral")
    {
        SyntaxTreeParser tree("11");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(status.Valid);
    }
}