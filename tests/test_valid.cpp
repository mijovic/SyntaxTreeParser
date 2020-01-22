#include <doctest.h>
#include <SyntaxTreeParser.h>

TEST_CASE("ValidInput")
{
    SUBCASE("SpacesAndBrackets")
    {
        SyntaxTreeParser tree("(4 + 5 * (7 - 3)) - 2");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(!status.Valid);
        CHECK_EQ(status.Value, 22);
    }

    SUBCASE("NoSpacesNoBrackets")
    {
        SyntaxTreeParser tree("4+5+7/2");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(!status.Valid);
        CHECK_EQ(status.Value, 12);
    }

    SUBCASE("SingleLiteral")
    {
        SyntaxTreeParser tree("7");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(!status.Valid);
        CHECK_EQ(status.Value, 7);
    }

    SUBCASE("SingleLiteralInBrackets")
    {
        SyntaxTreeParser tree("(9)");
        SyntaxTreeStatus status = tree.Evaluate();
        CHECK_FALSE(!status.Valid);
        CHECK_EQ(status.Value, 9);
    }
}