#include <exception>
#include <iostream>
#include <linked_list/linked_list.hpp>
#include <ostream>

int main()
{
    LinkedList<int> ll = LinkedList<int>();
    ll.enqueue(11);
    ll.enqueue(12);

    ll.enqueue({1, 2, 3, 4, 5});
    int s = ll.length();

    for (int i = 0; i < s + 1; ++i)
    {
        int s;
        try
        {
            s = ll.dequeue();
        }
        catch (std::exception)
        {
            std::cout << "yikes :()";
        }

        std::cout << s << '\n';
    }

    return 0;
}
