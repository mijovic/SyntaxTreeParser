#include <doctest.h>
#include <SyntaxTreeParser.h>

TEST_CASE("ValidInput")
{
    SUBCASE("SpacesAndBrackets")
    {
        SyntaxTreeParser tree("(4 + 5 * (7 - 3)) - 2");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(!status.valid);
        CHECK_EQ(status.value, 22);
    }

    SUBCASE("NoSpacesNoBrackets")
    {
        SyntaxTreeParser tree("4+5+7/2");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(!status.valid);
        CHECK_EQ(status.value, 12);
    }

    SUBCASE("SingleLiteral")
    {
        SyntaxTreeParser tree("7");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(!status.valid);
        CHECK_EQ(status.value, 7);
    }

    SUBCASE("SingleLiteralInBrackets")
    {
        SyntaxTreeParser tree("(9)");
        SyntaxTreeStatus status = tree.evaluate();
        CHECK_FALSE(!status.valid);
        CHECK_EQ(status.value, 9);
    }
}