#include <doctest.h>
#include "game_object.hpp"

namespace go_test {
    class TestCmp : public Component {
    public:
        int val{ 0 };
        TestCmp(GameObject* go) : Component{ go } { }
        void update() override {
            val += 1;
        }
    };
}

TEST_CASE("Update test first level") {
    GameObject* go{ new GameObject{nullptr} };
    go_test::TestCmp* test_cmp{ new go_test::TestCmp{go} };
    go->update();
    CHECK_EQ(test_cmp->val, 1);
    go->update();
    CHECK_EQ(test_cmp->val, 2);
}

TEST_CASE("Update test second level") {
    GameObject* go1{ new GameObject{nullptr} };
    go_test::TestCmp* test_cmp1{ new go_test::TestCmp{go1} };
    GameObject* go2{ new GameObject{go1} };
    go_test::TestCmp* test_cmp2{ new go_test::TestCmp{go2} };

    go1->update();
    CHECK_EQ(test_cmp1->val, 1);
    CHECK_EQ(test_cmp2->val, 1);
    go1->update();
    CHECK_EQ(test_cmp1->val, 2);
    CHECK_EQ(test_cmp2->val, 2);
}