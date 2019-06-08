#ifndef TEST_H
#define TEST_H
#include <string>//strings
#include <vector>
#include <memory>//smart vector

using namespace std;

class Test
{
    public:
        Test();
        virtual ~Test();
        vector<unique_ptr<Item>> equipment;

    protected:

    private:
};

#endif // TEST_H
