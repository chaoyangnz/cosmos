/*
 * an ANSI compliant atexit function
 */

typedef void (*void_function_ptr)();
void_function_ptr _atexit_functions[32];
int _atexit_index = 0;

int _atexit(function)
     void (*function)();
{
     /*
      * We must support at least 32 atexit functions
      * but we don't have to support any more.
      */
     if (_atexit_index >= 32)
         return -1;

     _atexit_functions[_atexit_index++] = function;
     return 0;
}
     
int atexit(function)
     void (*function)();
{
     return _atexit(function);
}

/*
 * Call atexit functions in reverse order.
 */
void _run_atexits()
{
     int i;

     for (i = _atexit_index - 1; i >= 0; i--)
         (*_atexit_functions[i])();
}

