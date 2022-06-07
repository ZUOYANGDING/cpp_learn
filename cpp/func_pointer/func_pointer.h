#pragma once

#define FUNC_PTR f_ptr
#define FUNC_PTR_RET ff_ptr  
// define a type which is a function pointer
typedef void (*f_ptr)();

// defina a function pointer which point to a function with return type is a function pointer
typedef void (*(*ff_ptr)())();