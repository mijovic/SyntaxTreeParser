#include <doctest.h>
#include <SyntaxTreeParser.h>

TEST_CASE("InvlidInput")
{
    SUBCASE("InvalidLiteral")
    {
        SyntaxTreeParser tree("1+10-2");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(status.valid);
    }

    SUBCASE("UnaryMinus")
    {
        SyntaxTreeParser tree("-1+1+2");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(status.valid);
    }

    SUBCASE("InvalidExpression")
    {
        SyntaxTreeParser tree("1+10+-2");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(status.valid);
    }

    SUBCASE("UnpairedBrackets1")
    {
        SyntaxTreeParser tree("((1+1) * 2 - 2");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(status.valid);
    }

    SUBCASE("UnpairedBrackets2")
    {
        SyntaxTreeParser tree("(1+1) * 2) - 2");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(status.valid);
    }

    SUBCASE("InvalidOperand")
    {
        SyntaxTreeParser tree("(1+1) * 2 % 2");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(status.valid);
    }

    SUBCASE("EndingInOperand")
    {
        SyntaxTreeParser tree("(1+1)*2+");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(status.valid);
    }

    SUBCASE("SingleIllegalLiteral")
    {
        SyntaxTreeParser tree("11");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(status.valid);
    }
}