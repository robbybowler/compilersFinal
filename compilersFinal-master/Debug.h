#include <iostream>

#ifndef ShowMessages
#define ShowMessages 1
#if ShowMessages == 1
#define MSG(X) std::cout << X << std::endl;
#endif

#endif